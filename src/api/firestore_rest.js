//import temperaturesMock from "../mocks/temperatures.mock";
import temperaturesMock from "../mocks";

const URI =
  "https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents";

export default {
  async getTemperaturesMock() {
    try {
      return await Promise.resolve(temperaturesMock);
    } catch (error) {
      console.error("[API/firestore_rest/getTemperaturesMock]: ", error);
    }
  },

  async getTemperatures() {
    try {
      const response = await fetch(`${URI}/temperatures`);
      return response.json();
    } catch (error) {
      console.error("[API/firestore_rest/getTemperatures]: ", error);
    }
  },

  async getLimens() {
    try {
      const response = await fetch(`${URI}/configurations`);
      const { documents } = await response.json();
      const {
        fields: {
          brightnessSwitch: { integerValue: brightnessLimen },
          temperatureSwitch: { integerValue: temperatureLimen }
        }
      } = documents[0];
      return { brightnessLimen, temperatureLimen };
    } catch (error) {
      console.error("[API/firestore_rest/getLimens]: ", error);
    }
  }
};
