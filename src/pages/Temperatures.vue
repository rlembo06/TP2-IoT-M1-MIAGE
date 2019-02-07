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
        <!-- <div class="small">
            <ve-line 
                :data="chartData" 
                :settings="chartSettings"
                :mark-point="markPoint">
            </ve-line>
        </div> -->
        <div class="small">
            <p v-if="!loaded">Chargement ....</p>
            <line-chart
                v-if="loaded"
                class="lineChart"
                :chart-data="chartData"
                :options="chartOptions">
            </line-chart>
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
                        <h3 class="title">{{chartData.labels.length}}</h3>
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
import LineChart from '../charts/LineChart'

export default {
    data: () => ({
        chartOptions: {
            responsive: true,
            maintainAspectRatio: false,
            /* animation: {
                duration: 0
            },
            hover: {
                animationDuration: 0
            },
            responsiveAnimationDuration: 0 */
        },
        chartData: {
          labels: [""],
          datasets: [{
            label: "",
            borderColor: "white",
            fill: false,
            data: [0]
          }]
        },
        loaded: false,
        lastUpdate: null,
        maxElements: 10,
        temperatureLimen: 0,
        brightnessLimen: 0,
    }),
    components: {
        StatsCard, 
        LineChart
    },
    mounted() {
        this.getTemperaturesChart();
        this.getLimens();
    },
    methods: {
        async getTemperaturesChart() {
            const { documents } = await firestore.getTemperaturesMock();
            const { datasets, labels, lastUpdate } = await chartHelpers.chartLineData(documents);
            this.chartData.datasets = datasets;
            this.chartData.labels = labels;
            this.lastUpdate = lastUpdate;
            this.loaded = true;
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