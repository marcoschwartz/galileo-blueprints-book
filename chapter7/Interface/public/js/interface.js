$( document ).ready(function() {
    
    // Refresh temperature & light level
    $.get('/api/temperature', function(json_data) {
      $('#temperature').html('Temperature: ' + (json_data.temperature).toFixed(2) + ' C');
       $.get('/api/light', function(json_data) {
         $('#light').html('Light level: ' + (json_data.light).toFixed(2) + ' %');
       });    
    });
    
    // Relay control
    $('#on').click(function() {
      $.get('/api/relay?state=1');
    });
    
    $('#off').click(function() {
      $.get('/api/relay?state=0');
    });
    
});