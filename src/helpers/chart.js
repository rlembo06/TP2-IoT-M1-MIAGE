import moment from "moment";

export default {
  sortByDate(documents) {
    return documents.sort(
      (a, b) => new Date(a.createTime) - new Date(b.createTime)
    );
  },
  lastUpdateTemperatures(documents) {
    return moment(documents[documents.length - 1].createTime).format(
      "MMMM Do YYYY, h:mm"
    );
  },
  temperaturesToChartLineData(documents, maxElements) {
    const result = [];
    documents.length >= maxElements &&
      documents.slice(documents.length - maxElements);

    this.sortByDate(documents);
    documents.forEach(doc => {
      result.push({
        date: moment(doc.createTime).format("h:mm:ss a"),
        celsius: doc.fields.temperatureInCelsius.doubleValue
      });
    });
    return result;
  }
};
