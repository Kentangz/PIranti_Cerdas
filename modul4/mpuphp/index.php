<?php
$host = 'localhost';
$dbname = 'sensor_data';
$username = 'root';
$password = '';
$pdo = new PDO("mysql:host=$host;dbname=$dbname", $username, $password);
$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

$stmt = $pdo->query("SELECT * FROM mpu6050_data ORDER BY timestamp DESC");
$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
?>

<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MPU6050 Sensor Data</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>MPU6050 Sensor Data</h1>
    <table border="1">
        <tr>
            <th>ID</th>
            <th>Gyro X</th>
            <th>Gyro Y</th>
            <th>Gyro Z</th>
            <th>Timestamp</th>
        </tr>
        <?php foreach ($data as $row): ?>
            <tr>
                <td><?= $row['id'] ?></td>
                <td><?= $row['gyro_x'] ?></td>
                <td><?= $row['gyro_y'] ?></td>
                <td><?= $row['gyro_z'] ?></td>
                <td><?= $row['timestamp'] ?></td>
            </tr>
        <?php endforeach; ?>
    </table>
</body>
</html>
