import axios from "axios";

const apiClient = axios.create({
    baseURL: "http://localhost:8000/api", // URL backend Laravel
    headers: {
        "Content-Type": "application/json",
        Accept: "application/json",
    },
});

export default apiClient;
