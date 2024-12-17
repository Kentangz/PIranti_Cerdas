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

// Ambil data dari URL
$angka_sumbu = isset($_GET['angka_sumbu']) ? $_GET['angka_sumbu'] : 0;
$arah = isset($_GET['arah']) ? $_GET['arah'] : '';
$status_buzzer = isset($_GET['status_buzzer']) ? $_GET['status_buzzer'] : '';
$status_led = isset($_GET['status_led']) ? $_GET['status_led'] : '';

// Validasi data (opsional)
if (!empty($arah) && !empty($status_buzzer) && !empty($status_led)) {
    // SQL untuk menyimpan data
    $sql = "INSERT INTO mpu (angka_sumbu, arah, status_buzzer, status_led) 
            VALUES ('$angka_sumbu', '$arah', '$status_buzzer', '$status_led')";

    if ($conn->query($sql) === TRUE) {
        echo "Data berhasil disimpan.";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
} else {
    echo "Data tidak lengkap!";
}

// Tutup koneksi
$conn->close();
?>