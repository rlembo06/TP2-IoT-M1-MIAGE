<template>
    <div>
        <div class="md-layout">
            <div class="md-layout-item">
                <md-button class="md-raised md-success" @click="getTemperaturesChart()">
                    <md-icon>cached</md-icon>
                    <md-tooltip md-direction="top">Raffraîchir</md-tooltip>
                </md-button>
            </div>
            <div class="md-layout-item">
                <md-field>
                    <label>Seuil C°</label>
                    <md-input v-model="temperatureLimen" type="number" min="-20" max="40"></md-input>
                    <md-button class="md-raised md-success" @click="setLimens()">Modifier</md-button>
                </md-field>
            </div>
        </div>
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
import db from "../plugins/firestore.js"
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
        temperatureLimen: 0,
        brightnessLimen: 0,
    }),
    components: {
        StatsCard
    },
    mounted() {
        this.getTemperaturesChart();
        this.getLimens();
    },
    methods: {
        async getTemperaturesChart() {
            const { documents } = await firestore.getTemperatures();
            this.chartData.rows = chartHelpers.chartLineData("celsius", documents, this.maxElements);
            this.lastUpdate = chartHelpers.lastUpdateData(documents);
        },

        async getLimens() {
            const { temperatureLimen, brightnessLimen } = await firestore.getLimens();
            this.temperatureLimen = +temperatureLimen;
            this.brightnessLimen = +brightnessLimen;
        },

        async setLimens() {
            try {
                const response = await db.collection("configurations")
                    .doc("cB1CljpmA9o0lRsUvuQh")
                    .set({
                        temperatureSwitch: +this.temperatureLimen,
                        brightnessSwitch: +this.brightnessLimen,
                    });            
                this.getLimens();
            } catch (error) {
                console.error("[Temperatures/setTemperatureLimen]: ", error)
            }
        }
    }
}
</script>
