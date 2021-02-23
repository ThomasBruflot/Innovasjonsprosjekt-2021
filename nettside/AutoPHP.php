<?php
// Start the session
session_start();
echo "Hei";
    if(isset($_SESSION["idTrening"])) {
        include "tilkobling.php";
        $kobling->set_charset("utf8");

        $sql = "INSERT INTO Kast (Bilde, Kommentar, Trening_idTrening, Trening_Person_idPerson, Trening_Person_Lag_idLag) VALUES ('Midlertidig', 'Kommentar', '$_SESSION[idTrening]', '$_SESSION[idPerson]', '$_SESSION[idLag]')";
        

        $sql2 = "SELECT * From Kast WHERE Trening_idTrening = '$_SESSION[idTrening]'";

        $resultat = $kobling->query($sql2);

        $rad = $resultat->fetch_assoc(); 

        $idKast = $rad['idKast'];

        if($kobling->query($sql)) {
            echo "Gratulerer kastet er lagt til i databasen";

        } else {
            echo "Dårlig nytt.. kastet ble ikke lagt til.";
        }

        $lenke = $_GET["lenke"];

        $sql3 = "UPDATE Kast SET Bilde = '$lenke' WHERE idKast = '$idKast'";

        if($kobling->query($sql3)) {
            echo "Gratulerer kastet er oppdatert";

        } else {
            echo "Dårlig nytt.. kastet ble ikke oppdatert.";
        }
    } else {
        echo "Du må sette inn info først";
    }
        
?>
