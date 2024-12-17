<template>
  <div>
    <h3>Data Status Sensor</h3>
    <table class="table">
      <thead>
        <tr>
          <th>ID</th>
          <th>Status</th>
          <th>Waktu</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="sensor in sensors" :key="sensor.id">
          <td>{{ sensor.id }}</td>
          <td>{{ sensor.status }}</td>
          <td>{{ new Date(sensor.created_at).toLocaleString() }}</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script>
import apiClient from "../api/axios";

export default {
  data() {
    return {
      sensors: [],
    };
  },
  methods: {
    fetchSensors() {
      apiClient
        .get("/sensors")
        .then((response) => {
          this.sensors = response.data;
        })
        .catch((error) => {
          console.error("Error fetching data:", error);
        });
    },
  },
  mounted() {
    this.fetchSensors();
  },
};
</script>

<style scoped>
.table {
  width: 100%;
  border-collapse: collapse;
  margin-top: 20px;
}
.table th,
.table td {
  border: 1px solid #ddd;
  padding: 8px;
}
</style>
