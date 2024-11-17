<?php

require 'vendor/autoload.php';
use PhpMqtt\Client\MqttClient;
use PhpMqtt\Client\ConnectionSettings;

// Konfigurasi database
$host = 'localhost';
$dbname = 'sensor_data';
$username = 'root';
$password = '';
$pdo = new PDO("mysql:host=$host;dbname=$dbname", $username, $password);
$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

// Konfigurasi MQTT
$server = 'c2f562274065493ba19a32413408826b.s1.eu.hivemq.cloud';
$port = 8883;
$mqtt_username = 'AdminRill';
$mqtt_password = 'Admin#1234';
$clientId = 'PHPClient';

$connectionSettings = (new ConnectionSettings())
    ->setUsername($mqtt_username)
    ->setPassword($mqtt_password)
    ->setUseTls(true);

$mqtt = new MqttClient($server, $port, $clientId);
$mqtt->connect($connectionSettings, true);

$mqtt->subscribe('esp32/mpu6050/data', function ($topic, $message) use ($pdo) {
    echo "Received message on topic [$topic]: $message\n";

    // Decode JSON data
    $data = json_decode($message, true);
    if ($data) {
        $gyroX = $data['gyroX'];
        $gyroY = $data['gyroY'];
        $gyroZ = $data['gyroZ'];

        // Insert data ke database
        $stmt = $pdo->prepare("INSERT INTO mpu6050_data (gyro_x, gyro_y, gyro_z) VALUES (:gyroX, :gyroY, :gyroZ)");
        $stmt->execute(['gyroX' => $gyroX, 'gyroY' => $gyroY, 'gyroZ' => $gyroZ]);
        echo "Data inserted to database\n";
    }
}, 0);

$mqtt->loop(true);
$mqtt->disconnect();
