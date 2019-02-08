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
        limenType: 'LDR',
        chartData: {
            columns: [],
            rows: []
        },
        lastUpdate: null,
        minMax: {
            min: 700,
            max: 2500
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
            const { documents } = await firestore.getBrigthnesses();
            let { datasets, columns, lastUpdate } = await chartHelpers.chartLineData(await documents, "brightnessInLux");
            //datasets = await chartHelpers.sliceDatasets(datasets)
            this.chartData.rows = datasets;
            this.chartData.columns = columns;
            this.lastUpdate = lastUpdate;
        },
    }
}
</script>