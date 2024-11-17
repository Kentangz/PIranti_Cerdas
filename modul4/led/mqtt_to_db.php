<?php

require __DIR__ . '/vendor/autoload.php';

use PhpMqtt\Client\MqttClient;
use PhpMqtt\Client\ConnectionSettings;
use PhpMqtt\Client\Exceptions\ConnectingToBrokerFailedException;

// Koneksi database
$host = "localhost";
$dbname = "iot_database";
$username = "root";
$password = "";

$conn = new mysqli($host, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Koneksi gagal: " . $conn->connect_error);
}

// Koneksi ke MQTT broker
$server = 'c2f562274065493ba19a32413408826b.s1.eu.hivemq.cloud';
$port = 8883;
$clientId = 'PHPClient';

// Buat pengaturan koneksi
$connectionSettings = (new ConnectionSettings())
    ->setUsername('AdminRill') // Username MQTT
    ->setPassword('Admin#1234') // Password MQTT
    ->setUseTls(true) // Gunakan TLS untuk koneksi aman
    ->setKeepAliveInterval(60); // Interval keep-alive (dalam detik)

// Inisialisasi klien MQTT
$mqtt = new MqttClient($server, $port, $clientId);

try {
    // Sambungkan ke broker dengan pengaturan koneksi
    $mqtt->connect($connectionSettings, true);

    echo "Terhubung ke broker MQTT\n";

    // Subscribe ke topik
    $mqtt->subscribe('esp32/led/status', function (string $topic, string $message) use ($conn) {
        echo "Pesan diterima dari topik [$topic]: $message\n";

        // Simpan data ke database
        $sql = "INSERT INTO led_status (status) VALUES (?)";
        $stmt = $conn->prepare($sql);
        $stmt->bind_param("s", $message);

        if ($stmt->execute()) {
            echo "Data berhasil disimpan ke database\n";
        } else {
            echo "Error: " . $stmt->error . "\n";
        }
        $stmt->close();
    });

    // Jalankan loop untuk mendengarkan pesan
    $mqtt->loop(true);

} catch (ConnectingToBrokerFailedException $e) {
    echo "Gagal terhubung ke broker MQTT: " . $e->getMessage() . "\n";
} finally {
    $mqtt->disconnect();
    $conn->close();
}
