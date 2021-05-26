const express = require('express');

const app = express();

app.use("/examples", express.static(__dirname + "/examples"));
app.use("/build", express.static(__dirname + "/build"));
app.use("/cube_map", express.static(__dirname + "/cube_map"));

app.get("/*", (req, res) => {
	res.sendFile(__dirname + "/examples/index.html");
});

app.listen(6969, () => {
	console.log("server go vroom");
});