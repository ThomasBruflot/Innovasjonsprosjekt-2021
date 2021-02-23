<?php

//INNLOGGING // localhost:8889 for mac
			$sv = "localhost:8889"; // localhost:8889 for mac
			$un = "root";
			$pw = "root";
			$db = "curling_db";
// Variabelen kobling er definert som selve koblingen til databasen
			$kobling = new mysqli($sv,$un,$pw,$db);

			// HOUSEKEEPING - får jeg tilgang avsluttes loopen
			if($kobling->connect_error){
				die($kobling->connect_error);
			} //Velger UTF-8 som tegnsett
			$kobling->set_charset("utf8mb4");
?>