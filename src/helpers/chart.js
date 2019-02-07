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
    const columns = ["date"];

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
          dataset => newDevice && dataset.date == newDate
        );

        if (!datasetExist) {
          await datasets.push({
            date: newDate,
            [newDevice]: newValue
          });
        } else {
          await datasets.forEach(async dataset => {
            if (dataset.date == newDate) {
              dataset[newDevice] = newValue;
            }
          });
        }

        const columnExist = await columns.find(column => column == newDevice);
        !columnExist && (await columns.push(newDevice));
      }
    });

    return { datasets, columns, lastUpdate };
  }

  /* chartLineData(dataName, documents, maxElements) {
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
  } */

  /* chartLineData(documents) {
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
  } */
};
