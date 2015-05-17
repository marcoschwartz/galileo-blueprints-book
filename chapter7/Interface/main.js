// Includes
var mraa = require("mraa");
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
light_sensor_pin.setBit(12);
var temp_sensor_pin = new mraa.Aio(1);
temp_sensor_pin.setBit(12);

// Relay pin
var relay_pin = new mraa.Gpio(7); //setup digital read on pin 5
relay_pin.dir(mraa.DIR_OUT); //set the gpio direction to output
    
// Main route
app.get('/', function(req,res){
  res.render('interface');
});

// Relay
app.get('/api/relay', function(req,res){
    
  // Get desired state    
  var state = req.query.state;
  console.log(state);
    
  // Apply state
  relay_pin.write(parseInt(state));       
    
  // Send answer
  json_answer = {};
  json_answer.message = "OK";
  res.json(json_answer);
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

// Start server
var port = 3000;
app.listen(port);
console.log('Listening on port ' + port);