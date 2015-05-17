$( document ).ready(function() {
    
    // Refresh temperature & light level
    $.get('/sensor/temperature', function(json_data) {
      $('#temperature').html('Temperature: ' + (json_data.temperature).toFixed(2) + ' C');
       $.get('/sensor/humidity', function(json_data) {
         $('#humidity').html('Humidity level: ' + (json_data.humidity).toFixed(2) + ' %');
       });    
    });
    
    // Relay control
    $.get('/led/mode/6/o');
    $('#on').click(function() {
      $.get('/led/digital/6/1');
    });
    
    $('#off').click(function() {
      $.get('/led/digital/6/0');
    });
    
});
