<?php

	$myFile = "temp_data.txt";
	$fh = fopen($myFile, 'r');
	$line = fgets($fh);
	fclose($fh);

	echo $line;

?>