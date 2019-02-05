<template>
	<code>{{temperatures}}</code>
</template>

<script>
import db from "../plugins/firestore.js";

export default {
	data: () => ({
		//temperatures: []
		test: null,
	}),
	firestore: {
        temperatures: db.collection('temperatures'),
	},
}
</script>
