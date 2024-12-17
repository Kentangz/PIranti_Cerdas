// URL API PHP
const API_URL = 'http://localhost/PIranti_Cerdas/Modul6/getData.php';

// Fungsi untuk mengambil data terbaru dari API
async function fetchLatestData() {
  try {
    const response = await fetch(API_URL);
    const data = await response.json();

    // Perbarui elemen dengan data terbaru
    document.getElementById("sumbuValue").innerText = data.angka_sumbu || "-";
    document.getElementById("arahValue").innerText = data.arah || "-";
    document.getElementById("ledStatus").innerText = data.status_led || "-";
    document.getElementById("buzzerStatus").innerText = data.status_buzzer || "-";
  } catch (error) {
    console.error("Error fetching data:", error);
  }
}

// Jalankan fetchLatestData pertama kali
document.addEventListener("DOMContentLoaded", () => {
  fetchLatestData(); // Ambil data pertama kali
  setInterval(fetchLatestData, 2000); // Perbarui data setiap 2 detik
});