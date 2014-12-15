$( document ).ready(function() {
    
    // Refresh temperature & light level
    $.get('/api/temperature', function(json_data) {
      $('#temperature').html('Temperature: ' + json_data.temperature + ' C');
       $.get('/api/light', function(json_data) {
         $('#light').html('Light level: ' + json_data.light + ' %');
       });    
    });
    
    // Refresh forecast
    $.get('/api/forecast', function(json_data) {
      $('#summary').html('Summary: ' + json_data.currently.summary);
    });
    
});