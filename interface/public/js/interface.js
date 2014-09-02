// Hardware parameters
type = 'wifi';
address = '192.168.1.104';

// Update data
setInterval(function() {
  
  // Send command to get temperature
  json_data = send(type, address, '/temperature');

  // Update temperature
  if (json_data.temperature){
    $("#tempDisplay").html("Temperature: " + json_data.temperature + "°C");    
  }

  // Update status
  if (json_data.connected == 1){
    $("#status").html("Station Online");
    $("#status").css("color","green");    
  }
  else {
    $("#status").html("Station Offline");
    $("#status").css("color","red");     
  }
  
  // Send command to get humidity
  json_data = send(type, address, '/humidity');

  // Update humdity
  if (json_data.humidity){
    $("#humDisplay").html("Humidity: " + json_data.humidity + "%");    
  }

}, 5000);