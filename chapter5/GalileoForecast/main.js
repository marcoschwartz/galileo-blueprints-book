// Includes
var mraa = require("mraa");
var Forecast = require('forecast.io');
var util = require('util');
var express = require('express');

// Express application
var app = express();

// View engine
app.set('view engine', 'jade');
app.set('views', __dirname + '/views');

// Set public folder
app.use(express.static(__dirname + '/public'));

// Sensor pins
var light_sensor_pin = new mraa.Aio(0);
var temp_sensor_pin = new mraa.Aio(1);

// Forecast object
var options = {
  APIKey: 'api_key'
},
forecast = new Forecast(options);
    
// Main route
app.get('/', function(req,res){
  res.render('interface');
});

// Light level
app.get('/api/light', function(req,res){
    
  // Measure
  var a = light_sensor_pin.read();
  console.log("Analog Pin (A0) Output: " + a);
  var light_level = a/4096*100;
    
  // Send answer
  json_answer = {};
  json_answer.light = light_level;
  res.json(json_answer);
});

// Temperature
app.get('/api/temperature', function(req,res){
  
  // Measure
  var b = temp_sensor_pin.read();
  console.log("Analog Pin (A1) Output: " + b);
  var temperature = (b/4096*5000 - 500) / 10;
  
  // Send answer
  json_answer = {};
  json_answer.temperature = temperature;
  res.json(json_answer);
});

// Forecast
app.get('/api/forecast', function(req, res) {
  forecast.get('51.25', '22.56667', function (err, result, data) {
    if (err) throw err;
    console.log('data: ' + util.inspect(data));
    res.json(data);
  });
});

// Start server
var port = 3000;
app.listen(port);
console.log('Listening on port ' + port);