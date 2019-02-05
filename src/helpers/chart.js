import moment from "moment";

export default {
  lastUpdateTemperatures(documents) {
    return moment(documents[documents.length - 1].createTime).format(
      "MMMM Do YYYY, h:mm"
    );
  },
  temperaturesToChartLineData(documents, maxElements) {
    const result = [];
    documents.length >= maxElements &&
      documents.slice(documents.length - maxElements);

    documents.forEach(doc => {
      result.push({
        date: moment(doc.createTime).format("h:mm:ss a"),
        celsius: doc.fields.temperatureInCelsius.doubleValue
      });
    });
    return result;
  }
};
