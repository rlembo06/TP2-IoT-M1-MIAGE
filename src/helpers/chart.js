import moment from "moment";

export default {
  getRandomColor() {
    const letters = "0123456789ABCDEF";
    let color = "#";
    for (var i = 0; i < 6; i++) {
      color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
  },

  sortByDate(documents) {
    return documents.sort(
      (a, b) => new Date(a.createTime) - new Date(b.createTime)
    );
  },

  /* lastUpdateData(documents) {
    return moment(documents[documents.length - 1].createTime).format(
      "MMMM Do YYYY, h:mm"
    );
  }, */

  lastUpdateData(documents) {
    return moment(documents[documents.length - 1].createTime).format(
      "MMMM Do YYYY, h:mm a"
    );
  },

  chartLineData(documents) {
    const datasets = [];
    const labels = [];

    this.sortByDate(documents);
    const lastUpdate = this.lastUpdateData(documents);

    documents.forEach(async doc => {
      const newDevice =
        (await doc.fields.macAddress) &&
        (await doc.fields.macAddress.stringValue)
          ? await doc.fields.macAddress.stringValue
          : null;

      if (newDevice) {
        const newDate = await moment(doc.createTime).format("h:mm:ss a");
        const newValue = await doc.fields.temperatureInCelsius.doubleValue;

        const datasetExist = datasets.find(
          dataset => newDevice && dataset.label == newDevice
        );

        if (!datasetExist) {
          await datasets.push({
            label: newDevice,
            borderColor: this.getRandomColor(),
            fill: false,
            data: [newValue]
          });
        } else {
          await datasets.forEach(async dataset => {
            if (dataset.label == newDevice) {
              await dataset.data.push(newValue);
            }
          });
        }
        labels.push(newDate);
      }
    });

    return { datasets, labels, lastUpdate };
  }
};
