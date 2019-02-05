<template>
    <div>
        <div class="small">
            <ve-line :data="chartData"></ve-line>
        </div>
    </div>
</template>

<script>
import firestore from "../api/firestore_rest.js";
import moment from "moment"
import chartHelpers from "../helpers/chart.js";

export default {
    data: () => ({
        chartData: {
            columns: ['date', 'celsius'],
            rows: []
        },
        temperatures: null,
        lastUpdate: null,
        maxElements: 10,
        sizeData: 0,
    }),
    mounted() {
        console.log("getTemperaturesChart / this.chartData BEFORE: ", this.chartData)
        this.getTemperaturesChart();
    },
    methods: {
        async getTemperaturesChart() {
            const { documents } = await firestore.getTemperatures();
            this.chartData.rows = chartHelpers.temperaturesToChartLineData(documents, this.maxElements);
        }
    }
}
</script>
