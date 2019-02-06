const URI =
  "https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents";

export default {
  async getTemperatures() {
    try {
      const response = await fetch(`${URI}/temperatures`);
      return response.json();
    } catch (error) {
      console.error("[API/firestore_rest/getTemperatures]: ", error);
    }
  }
};
