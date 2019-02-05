<template>
    <div> 
        <div>
            <code>{{temperatures}}</code>
        </div>
        <div>
            <chart-card
                :chart-data="temperatures.data"
                :chart-type="'Line'"
                data-background-color="blue">
                <template slot="content">
                    <h4 class="title">Températures</h4>
                </template>

                <template slot="footer">
                    <div class="stats">
                    <md-icon>access_time</md-icon>
                    Dernière mise à jour : {{lastUpdate}}
                    </div>
                </template>
            </chart-card>
        </div>
    </div>
</template>

<script>
import firestore from "../api/firestore_rest.js";
import { ChartCard } from "@/components";
import moment from "moment"

export default {
    data: () => ({
        temperatures: {
            data: {
                labels: [],
                series: [[]]
            },
        },
        lastUpdate: null,
    }),
    components: {
        ChartCard,
    },
    mounted() {
        this.getTemperaturesChart();
        console.log("temperatures: ", this.temperatures)
    },
    methods: {
        async getTemperaturesChart() {
            const jsonObserver = await firestore.getTemperatures() || [];
            const data = JSON.parse(JSON.stringify(jsonObserver)).documents
            data.forEach(item => {
                this.temperatures.data.labels.push(moment(item.createTime).format('h:mm:ss a'))
                this.temperatures.data.series[0].push(item.fields.temperatureInCelsius.doubleValue)
            });
            this.lastUpdate = data[data.length - 1].createTime
            this.lastUpdate = moment(this.lastUpdate).format('MMMM Do YYYY, h:mm:ss a')
        }
    }
}
</script>
