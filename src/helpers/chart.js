import moment from "moment";

export default {
  sortByDate(documents) {
    return documents.sort(
      (a, b) => new Date(a.createTime) - new Date(b.createTime)
    );
  },

  lastUpdateData(documents) {
    return moment(documents[documents.length - 1].createTime).format(
      "MMMM Do YYYY, h:mm"
    );
  },

  chartLineData(dataName, documents, maxElements) {
    const result = [];

    this.sortByDate(documents);

    if (documents.length >= maxElements) {
      documents = documents.slice(documents.length - maxElements);
    }

    documents.forEach(doc => {
      result.push({
        date: moment(doc.createTime).format("h:mm:ss a"),
        [dataName]: doc.fields.temperatureInCelsius.doubleValue
      });
    });

    return result;
  }
};
