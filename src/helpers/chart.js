import moment from "moment";

export default {
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
