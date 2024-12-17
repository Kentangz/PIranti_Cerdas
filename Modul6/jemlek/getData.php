<?php
// Koneksi ke database
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "monitoring";

// Membuat koneksi
$conn = new mysqli($servername, $username, $password, $dbname);

// Cek koneksi
if ($conn->connect_error) {
    die("Koneksi gagal: " . $conn->connect_error);
}

// Query untuk mengambil data terbaru berdasarkan ID (urutan ID terbaru)
$sql = "SELECT angka_sumbu, arah, status_buzzer, status_led
        FROM mpu 
        ORDER BY id DESC LIMIT 1";  // Mengambil data dengan ID terbaru
$result = $conn->query($sql);

$data = [];
if ($result->num_rows > 0) {
    $data = $result->fetch_assoc(); // Ambil satu data terbaru
}

// Mengembalikan data dalam format JSON
header('Content-Type: application/json');
echo json_encode($data);

header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json');

// Tutup koneksi
$conn->close();
?>