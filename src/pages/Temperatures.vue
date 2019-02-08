<template>
    <ChartLine 
        :chartData="chartData" 
        :limenType="limenType"
        :lastUpdate="lastUpdate"
        :getChartData="getChartData"
        :minMax="minMax"/>
</template>

<script>
import firestore from "../api/firestore_rest.js";
import ChartLine from "@/components/ChartLine";
import chartHelpers from "../helpers/chart.js";

export default {
    data: () => ({
        documents: [],
        limenType: '°C',
        chartData: {
            columns: [],
            rows: []
        },
        lastUpdate: null,
        minMax: {
            min: -40,
            max: 40
        }
    }),
    components: {
        ChartLine, 
    },
    mounted() {
        this.getChartData();
    },
    methods: {
        async getChartData() {
            //const { documents } = await firestore.getTemperaturesMock();
            const { documents } = await firestore.getTemperatures();
            const { datasets, columns, lastUpdate } = await chartHelpers.chartLineData(await documents, "temperatureInCelsius");
            this.chartData.rows = datasets;
            this.chartData.columns = columns;
            this.lastUpdate = lastUpdate;
        },
    }
}
</script>