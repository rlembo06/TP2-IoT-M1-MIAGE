<template>
	<code>{{brightness}}</code>
</template>

<script>
import db from "../plugins/firestore.js";

export default {
	firestore: {
		brightness: db.collection('brightness'),
	},
}
</script>
