import moment from "moment";

export default {
  sortByDate(documents) {
    return documents.sort(
      (a, b) => new Date(a.createTime) - new Date(b.createTime)
    );
  },

  async lastUpdateData(documents) {
    return documents.length > 0
      ? await moment(documents[documents.length - 1].createTime).format(
          "MMMM Do YYYY, h:mm a"
        )
      : null;
  },

  /* async sliceDatasets(datasets) {
    const limitItems = 10;
    console.log("sliceDatasets / datasets", datasets);
    return datasets.length > 0
      ? datasets.slice(datasets.length - limitItems)
      : datasets;
  }, */

  async sliceDatasets(datasets) {
    const limitItems = 10;
    console.log("sliceDatasets / datasets", datasets);
    return datasets.slice(limitItems);
  },

  async chartLineData(documents, dataType) {
    let datasets = [];
    const columns = ["date"];

    this.sortByDate(documents);
    const lastUpdate = await this.lastUpdateData(documents);

    documents.forEach(async doc => {
      const newDevice =
        (await doc.fields.macAddress) &&
        (await doc.fields.macAddress.stringValue)
          ? await doc.fields.macAddress.stringValue
          : null;

      if (newDevice) {
        const newDate = await moment(doc.createTime).format("h:mm:ss a");
        const newValue = await doc.fields[dataType].doubleValue;

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

        const columnExist = columns.find(column => column === newDevice);
        !columnExist && columns.push(newDevice);
      }
    });
    //datasets = await this.sliceDatasets(datasets);
    return { datasets, columns, lastUpdate };
  }
};
