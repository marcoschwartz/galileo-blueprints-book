// Includes
//var mraa = require("mraa");
//var util = require('util');

// Required modules
var express = require('express');
var app = express();

// Main route
app.get('/', function (req, res) {
  res.send('Hello World!');
});

// Start server
var server = app.listen(3000, function () {

  var host = server.address().address;
  var port = server.address().port;

  console.log('Example app listening at http://%s:%s', host, port);

});