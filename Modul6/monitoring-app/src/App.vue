<template>
  <div class="container">
    <h1 class="text-center my-4">Monitoring Sensor</h1>
    <SensorTable />
    <SensorChart /> <!-- Ganti SensorForm dengan SensorChart -->
  </div>
</template>

<script>
import SensorTable from "./components/SensorTable.vue";
import SensorChart from "./components/SensorChart.vue"; // Ganti SensorForm dengan SensorChart

export default {
  components: {
    SensorTable,
    SensorChart, // Pastikan SensorChart terdaftar di sini
  },
};
</script>

<style>
.container {
  max-width: 800px;
  margin: auto;
}
</style>
