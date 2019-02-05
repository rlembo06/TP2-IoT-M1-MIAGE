<template>
    <div> 
        <h4>All :</h4>
        <code>{{temperatures}}</code>
    </div>
</template>

<script>
import firestore from "../api/firestore_rest.js";

export default {
    data: () => ({
        temperatures: []
    }),
    mounted() {
        this.getTemperaturesDetails()
    },
    methods: {
        async getTemperaturesDetails() {
            this.temperatures = await firestore.getTemperatures();
        }
    }
}
</script>
