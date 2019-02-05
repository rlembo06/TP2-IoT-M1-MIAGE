<template>
	<code>{{brightness}}</code>
</template>

<script>
import db from "../plugins/firestore.js";

export default {
	data: () => ({
		//brightness: []
		test: null,
	}),
	firestore: {
        brightness: db.collection('brightness'),
	},
}
</script>
