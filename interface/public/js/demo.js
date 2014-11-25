// Function to motor direction
$(document).ready(function() {

  // Timeout
  $.ajaxSetup({
    timeout: 1500 //Time in milliseconds
  });

  // Refresh interface
  function refreshTemperature() {
	  $.getq('queue', '/weather_station/temperature', function(json_data) {

	  	// Temperature
	  	if (json_data.temperature){
	      $("#temperature").text('Temperature: ' + json_data.temperature + " C");
	  	}

	  	// Status
	  	if (json_data.connected){
	  	  $("#status").text('Online');
	  	  $("#status").css('color', 'green');
	  	}
	  	else {
	       $("#status").text('Offline');
	       $("#status").css('color', 'red');
	  	}

	  }).fail(function(){
	  	$("#status").text('Offline');
	    $("#status").css('color', 'red');
	  });
  }

  function refreshHumidity() {
    $.getq('queue', '/weather_station/humidity', function(json_data) {

      // Humidity
      if (json_data.humidity){
        $("#humidity").text('Humidity: ' + json_data.humidity + " %");
      }
     
    });
  }
 
  // Refresh interface
  refreshTemperature();
  refreshHumidity();
  setInterval(refreshTemperature, 2000);
  setInterval(refreshHumidity, 2000);
 
});