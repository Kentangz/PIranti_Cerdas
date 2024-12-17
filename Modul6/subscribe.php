<?php

require 'vendor/autoload.php';
use PhpMqtt\Client\MqttClient;
use PhpMqtt\Client\ConnectionSettings;

// Konfigurasi database
$host = 'localhost';
$dbname = 'mqtt_data';
$username = 'root';
$password = '';
$pdo = new PDO("mysql:host=$host;dbname=$dbname", $username, $password);
$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

// Konfigurasi MQTT
$server = '71a93091f15b4f328bf8a2e440e0481b.s1.eu.hivemq.cloud';
$port = 8883;
$mqtt_username = 'admin';
$mqtt_password = 'Admin123';
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
        $status = $data['status']; // Mendapatkan nilai status (flat/tilted)
        $angleX = $data['angleX']; // Mendapatkan nilai angleX
        $angleY = $data['angleY']; // Mendapatkan nilai angleY

        // Insert data ke database
        $stmt = $pdo->prepare("INSERT INTO mpu6050_data (status, angle_x, angle_y) VALUES (:status, :angleX, :angleY)");
        $stmt->execute([
            'status' => $status,
            'angleX' => $angleX,
            'angleY' => $angleY
        ]);
        echo "Data inserted to database\n";
    } else {
        echo "Invalid data format\n";
    }
}, 0);

$mqtt->loop(true);
$mqtt->disconnect();
