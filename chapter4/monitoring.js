var mraa = require("mraa");

var light_sensor_pin = new mraa.Aio(0);
light_sensor_pin.setBit(12);
var temp_sensor_pin = new mraa.Aio(1);
temp_sensor_pin.setBit(12);
//Create server
var http = require('http');
var app = http.createServer(function (req, res) {
    'use strict';
    
    // Light level
    var a = light_sensor_pin.read();
    console.log("Analog Pin (A0) Output: " + a);
    var light_level = a/4096*100;
    
    // Temperature
    var b = temp_sensor_pin.read();
    console.log("Analog Pin (A1) Output: " + b);
    var temperature = (b/4096*5000 - 500) / 10;
    
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.end('<h1>Measured data</h1><p>Light level: ' + light_level + ' %</p><p>Temperature: ' + temperature + ' C</p>');
}).listen(3000);