<?php
// Koneksi ke database
$host = 'localhost';
$dbname = 'mqtt_data';
$username = 'root';
$password = '';

try {
    $pdo = new PDO("mysql:host=$host;dbname=$dbname", $username, $password);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    // Ambil parameter untuk pagination
    $page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
    $limit = isset($_GET['limit']) ? (int)$_GET['limit'] : 10;
    $offset = ($page - 1) * $limit;

    // Query untuk menghitung total record
    $totalStmt = $pdo->query("SELECT COUNT(*) AS total FROM mpu6050_data");
    $totalRecords = $totalStmt->fetch(PDO::FETCH_ASSOC)['total'];

    // Query untuk mengambil data dengan pagination
    $stmt = $pdo->prepare("SELECT * FROM mpu6050_data ORDER BY created_at DESC LIMIT :limit OFFSET :offset");
    $stmt->bindParam(':limit', $limit, PDO::PARAM_INT);
    $stmt->bindParam(':offset', $offset, PDO::PARAM_INT);
    $stmt->execute();

    $data = '';
    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
        $data .= "<tr>
                    <td>{$row['id']}</td>
                    <td>{$row['status']}</td>
                    <td>{$row['angle_x']}</td>
                    <td>{$row['angle_y']}</td>
                    <td>{$row['created_at']}</td>
                  </tr>";
    }

    // Return data dan total record dalam bentuk JSON
    echo json_encode([
        'data' => $data,
        'total' => $totalRecords
    ]);

} catch (PDOException $e) {
    echo json_encode(['error' => $e->getMessage()]);
}
?>
