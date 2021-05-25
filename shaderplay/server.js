const express = require('express');

const app = express();

app.use(express.static(__dirname + "/examples"));
app.use(express.static(__dirname + "/build"));

app.get("/*", (req, res) => {
	res.sendFile(__dirname + "/examples/index.html");
});

app.listen(6969, () => {
	console.log("server go vroom");
});