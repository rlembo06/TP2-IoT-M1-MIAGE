<template>
    <div>
        <div class="small">
            <ve-line :data="chartData"></ve-line>
        </div>
        <div class="md-layout">
            <div class="md-layout-item">
                <stats-card data-background-color="green">
                    <template slot="header">
                        <md-icon >access_time</md-icon>
                    </template>

                    <template slot="content">
                        <p class="category">Dernière mise à jour</p>
                        <h3 class="title">{{lastUpdate}}</h3>
                    </template>
                </stats-card>
            </div>
            <div class="md-layout-item">
                <stats-card data-background-color="green">
                    <template slot="header">
                        <md-icon >assessment</md-icon>
                    </template>

                    <template slot="content">
                        <p class="category">Nombre d'éléments</p>
                        <h3 class="title">{{chartData.rows.length}}</h3>
                    </template>
                </stats-card>
            </div>
        </div>
    </div>
</template>

<script>
import firestore from "../api/firestore_rest.js";
import moment from "moment"
import chartHelpers from "../helpers/chart.js";
import {StatsCard} from "@/components";

export default {
    data: () => ({
        chartData: {
            columns: ['date', 'celsius'],
            rows: []
        },
        lastUpdate: null,
        maxElements: 10,
    }),
    components: {
        StatsCard
    },
    mounted() {
        this.getTemperaturesChart();
    },
    methods: {
        async getTemperaturesChart() {
            const { documents } = await firestore.getTemperatures();
            this.chartData.rows = chartHelpers.chartLineData("celsius", documents, this.maxElements);
            this.lastUpdate = chartHelpers.lastUpdateData(documents);
        }
    }
}
</script>
