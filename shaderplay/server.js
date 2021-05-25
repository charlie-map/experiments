const express = require('express');

const app = express();

app.use(express.static(__dirname + "/public"));

app.get("/*", (req, res) => {
	res.sendFile(__dirname + "/views/index.html");
});

app.listen(6969, () => {
	console.log("server go vroom");
});