// Standard function for the aREST API

// Send command via node-aREST
function send(type, target, command) {

  $.ajax({
    type: 'GET',
    url: '/send',
    async: false,
    data: {type: type, target: target, command: command},
    success: function( data ) {
      json_data = jQuery.parseJSON(data);
    }
  });
  
  return json_data;
}