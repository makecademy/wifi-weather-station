// Required packages
var express = require('express');
var path = require('path');
var arest = require("arest");

// Create app
var app = express();
var port = 3700;

// Set views
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.static(path.join(__dirname, 'views')));

// Serve files
app.get('/interface', function(req, res){
  res.sendfile('views/interface.html')
});

// API access
app.get("/send", function(req, res){
  arest.send(req,res);
});

// Start server
app.listen(port);
console.log("Listening on port " + port);