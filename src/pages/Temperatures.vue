<template>
    <ChartLine :documents="documents" :limenType="limenType"/>
</template>

<script>
import firestore from "../api/firestore_rest.js";
import ChartLine from "@/components/ChartLine";

export default {
    data: () => ({
        documents: [],
        limenType: '° C'
    }),
    components: {
        ChartLine, 
    },
    mounted() {
        this.getTemperatures();
    },
    methods: {
        async getTemperatures() {
            //const { documents } = await firestore.getTemperaturesMock();
            const { documents } = await firestore.getTemperatures();
            this.documents = await documents;
        },

        /* async getTemperatures() {
            //const { documents } = await firestore.getTemperaturesMock();
            //const { documents } = await firestore.getTemperatures();
            const { datasets, columns, lastUpdate } = await chartHelpers.chartLineData(await this.documents);
            this.chartData.rows = datasets;
            this.chartData.columns = columns;
            this.lastUpdate = lastUpdate;
            this.loaded = datasets.length > 0;
        }, */
    }
}
</script>