<template>
    <div>
        <div class="md-layout">
            <div class="md-layout-item">
                <md-button class="md-raised md-success" @click="getChartData()">
                    <md-icon>cached</md-icon>
                    <md-tooltip md-direction="top">Raffraîchir</md-tooltip>
                </md-button>
            </div>
            <div class="md-layout-item">
                <md-field>
                    <label>Seuil {{limenType}}</label>
                    <md-input v-model="limen" type="number" :min="minMax.min" :max="minMax.max"></md-input>
                    <md-button class="md-raised md-success" @click="setLimens()">Modifier</md-button>
                </md-field>
            </div>
        </div>
        <div class="small">
            <p v-if="chartData.rows.length === 0">Chargement...</p>
            <ve-line 
                v-if="chartData.rows.length > 0"
                :data="chartData">
            </ve-line>
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
        temperatureLimen: 0,
        brightnessLimen: 0,
        limen: null,
    }),
    props: {
        limenType: {
            type: String,
            default: ""
        },
        chartData: {
            type: Object,
            default: {
                columns: [],
                rows: []
            }
        },
        lastUpdate: {
            type: String,
            default: ""
        },
        minMax: {
            type: Object,
            default: {
                min: 0,
                max: 0
            }
        },
        getChartData: Function,
    },
    components: {
        StatsCard, 
    },
    mounted() {
        this.getLimens();
    },
    methods: {
        async getLimens() {
            const { temperatureLimen, brightnessLimen } = await firestore.getLimens();
            this.temperatureLimen = +temperatureLimen;
            this.brightnessLimen = +brightnessLimen;
            this.limen = this.limenType === '°C' ? temperatureLimen : brightnessLimen;
        },

        async setLimens() {
            try {
                const response = await db.collection("configurations")
                    .doc("cB1CljpmA9o0lRsUvuQh")
                    .set({
                        temperatureSwitch: this.limenType === '°C' ? +this.limen : +this.temperatureLimen,
                        brightnessSwitch: this.limenType === 'LDR' ? +this.limen : +this.brightnessLimen,
                    });            
                this.getLimens();
            } catch (error) {
                console.error("[ChartLine/setTemperatureLimen]: ", error)
            }
        }
    }
}
</script>