// Includes
var mraa = require("mraa");
var util = require('util');
var request = require('request');

// Sensor pins
var light_sensor_pin = new mraa.Aio(0);
light_sensor_pin.setBit(12);
var temp_sensor_pin = new mraa.Aio(1);
temp_sensor_pin.setBit(12);

function send_data() {
    
    // Measure light
    var a = light_sensor_pin.read();
    var light_level = a/4096*100;
    light_level = light_level.toPrecision(4);
    console.log("Light level: " + light_level + " %");

    // Measure temperature
    var b = temp_sensor_pin.read();
    var temperature = (b/4096*5000 - 500) / 10;
    temperature = temperature.toPrecision(4);
    console.log("Temperature: " + temperature + " C");

    // Send request
    var device_name = 'galileo_5etr6b';
    var dweet_url = 'https://dweet.io/dweet/for/' + device_name + '?temperature=' + temperature + '&light=' + light_level;
    console.log(dweet_url);

    var options = {
      url: dweet_url,
      json: true
    };

    request(options, function (error, response, body) {
      if (error) {console.log(error);}
      console.log(body);    
    });
}

// Send data every 10 seconds
send_data();
setInterval(send_data, 10000);
