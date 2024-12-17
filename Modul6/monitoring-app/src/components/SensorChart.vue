<template>
  <div>
    <h3>Grafik Status Sensor</h3>
    <canvas id="sensorChart"></canvas>
  </div>
</template>

<script>
import { ref, onMounted } from "vue";
import { Chart } from "chart.js";
import apiClient from "../api/axios"; // Jika Anda menggunakan axios untuk API

export default {
  name: "SensorChart",
  setup() {
    const chartData = ref([]);

    // Fetch data dari backend
    const fetchData = () => {
      apiClient
        .get("/sensors") // Ganti endpoint jika perlu
        .then((response) => {
          chartData.value = response.data.map((item) => ({
            x: new Date(item.created_at),
            y: item.status === "Miring" ? 1 : 0, // Misalnya 1 untuk miring, 0 untuk datar
          }));
          renderChart();
        })
        .catch((error) => {
          console.error("Error fetching data:", error);
        });
    };

    // Render chart
    const renderChart = () => {
      const ctx = document.getElementById("sensorChart").getContext("2d");
      new Chart(ctx, {
        type: "line",
        data: {
          datasets: [
            {
              label: "Status Sensor",
              data: chartData.value,
              fill: false,
              borderColor: "#42A5F5",
              tension: 0.1,
            },
          ],
        },
        options: {
          scales: {
            x: {
              type: "time",
              time: {
                unit: "minute",
                tooltipFormat: "ll",
              },
            },
            y: {
              min: 0,
              max: 1,
              ticks: {
                stepSize: 1,
                callback: function (value) {
                  return value === 0 ? "Datar" : "Miring";
                },
              },
            },
          },
        },
      });
    };

    onMounted(() => {
      fetchData();
    });

    return {
      chartData,
    };
  },
};
</script>

<style scoped>
canvas {
  width: 100%;
  height: 400px;
}
</style>
