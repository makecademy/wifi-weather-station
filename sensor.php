<?php

	// Store data
    if ($_GET["temp"] && $_GET["hum"]) {

      	$myFile = "temp_data.txt";
		$fh = fopen($myFile, 'w');
		fwrite($fh, $_GET["temp"]);
		fclose($fh);

		$myFile = "hum_data.txt";
		$fh = fopen($myFile, 'w');
		fwrite($fh, $_GET["hum"]);
		fclose($fh);
		
    }

?>