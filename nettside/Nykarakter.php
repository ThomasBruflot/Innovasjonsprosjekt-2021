<?php
		if(isset($_POST["Leggtil"])) {
			
			include "tilkobling.php";

            $kobling->set_charset("utf8");

            $Fornavn      = $_POST["Fornavn"];
            $Etternavn    = $_POST["Etternavn"];
            $BirthDate    = $_POST["Fødselsdato"];
            $Gender       = $_POST["Kjønn"];
            $Rase         = $_POST["Rase"];
            $Hjemstednavn = $_POST["Hjemstednavn"];     

			
            $sql = "INSERT INTO Karakter (Fornavn, Etternavn, Fødselsdato, Kjønn, Rase, Hjemstednavn) VALUES ('$Fornavn', '$Etternavn', '$BirthDate', '$Gender', '$Rase', '$Hjemstednavn')";
       
			
			
			
			if($kobling->query($sql)) {
				echo "Gratulerer $Fornavn $Etternavn er lagt til i læringsplatformen GeoKURT";
				header ("location: Leggtilkarakter.php");
			} else {
				echo "Dårlig nytt.. Karakteren ble ikke lagt til.";
			}
			
	}
	?>
