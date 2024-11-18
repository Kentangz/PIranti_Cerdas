<?php
$host = 'localhost';
$dbname = 'sensor_data'; // Nama database Anda
$username = 'root';      // Username database Anda
$password = '';          // Password database Anda

// Koneksi ke database menggunakan MySQLi
$mysqli = new mysqli($host, $username, $password, $dbname);

// Periksa koneksi
if ($mysqli->connect_error) {
    die("Connection failed: " . $mysqli->connect_error);
}

// Query untuk mengambil data dari tabel mpu6050_data
$query = "SELECT * FROM mpu6050_data ORDER BY id DESC";
$result = $mysqli->query($query);

// Cek jika query berhasil
if (!$result) {
    die("Query failed: " . $mysqli->error);
}
//hai-
// Menyimpan hasil query dalam array
$data = [];
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

$mysqli->close(); // Tutup koneksi MySQLi
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Data Sensor MPU6050</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Data Sensor MPU6050</h1>
    <table border="1">
        <tr>
            <th>ID</th>
            <th>Angka Sumbu</th>
            <th>Gyro X</th>
            <th>Gyro Y</th>
            <th>Timestamp</th>
        </tr>
        <?php foreach ($data as $row): ?>
            <tr>
                <td><?= htmlspecialchars($row['id']) ?></td>
                <td><?= htmlspecialchars($row['angka_sumbu']) ?></td>
                <td><?= htmlspecialchars($row['gyro_x']) ?></td>
                <td><?= htmlspecialchars($row['gyro_y']) ?></td>
                <td><?= htmlspecialchars($row['timestamp'] ?? 'N/A') ?></td>
            </tr>
        <?php endforeach; ?>
    </table>
</body>
</html>
