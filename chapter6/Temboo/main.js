// Includes
var mraa = require("mraa");
var util = require('util');

// Sensor pins
var light_sensor_pin = new mraa.Aio(0);
light_sensor_pin.setBit(12);
var temp_sensor_pin = new mraa.Aio(1);
temp_sensor_pin.setBit(12);

// Temboo
var tsession = require("temboo/core/temboosession");
var session = new tsession.TembooSession("your_temboo_name", "your_temboo_app", "your_temboo_key");

// Google Choreo
var Google = require("temboo/Library/Google/Spreadsheets");

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

    var appendRowChoreo = new Google.AppendRow(session);

    // Instantiate and populate the input set for the choreo
    var appendRowInputs = appendRowChoreo.newInputSet();
    
    // Get date
    var d = new Date();

    // Set inputs
    appendRowInputs.set_Password("your_gmail_password");
    appendRowInputs.set_Username("your_gmail_username");
    appendRowInputs.set_RowData(d + "," + temperature + "," + light_level);
    appendRowInputs.set_SpreadsheetTitle("Galileo");

    // Run the choreo, specifying success and error callback handlers
    appendRowChoreo.execute(
        appendRowInputs,
        function(results){console.log(results.get_Response());},
        function(error){console.log(error.type); console.log(error.message);}
    );
}

// Send data every 10 seconds
send_data();
setInterval(send_data, 10000);
