
<!Doctype HTML>
<head>
	<title>Legg til Informasjon</title>
    <meta charset="UTF-8">
    <meta name="description" content="Innovasjonsprosjekt">
    <meta name="keyword" keyword="Curling, sport">
    <meta http-equiv="content-type" content="text/html;charset=utf-8" />
	<link rel="Stylesheet" href="Stilark/Leggtilkarakter.css">
	<link rel="shortcut icon" href="Bilder/Ring.png"/>
	<meta charset="UTF-8">
</head>
<body>

	<style>
		<?php
			include "Meny.css"
		?>
	</style>
		<?php
			include "Meny.php"
		?>
	<br><div class="Wrapper">
    <h1 id="Overskrift">Legg til Informasjon</h1>
	<div class="boks">
	<form method="POST" class="container">
        
            <label><b>Lagnavn</b></label><br>
		
		
		<input type="text" name="Lagnavn" placeholder="Eksempel: GuttaKrutt"><br>
	
            <label><b>Fornavn</b></label><br>
	
		<input type="text" name="Fornavn" placeholder="Eksempel: Frodo"><br>
		
            <label><b>Etternavn</b></label><br>
		
		<input type="text" name="Etternavn" placeholder="Eksempel: Lommelun"><br>
		
            
        <input type='submit' name='Leggtil' value='Legg til'>
		
        </form>
    </div>
   <?php
                
      // Start the session
        session_start();
		if(isset($_POST["Leggtil"])) {
            //Hvis det er satt inn fødselsdato og etternavn skal denne spørringen kjøres
			
                //Hvis etternavn ikke er satt men fødselsdato er det
                if(!empty($_POST["Fornavn"])) {
                    include "tilkobling.php";

                        $kobling->set_charset("utf8");

                        $Fornavn      = $_POST["Fornavn"];
                        $Etternavn    = $_POST["Etternavn"];
                        $Lagnavn      = $_POST["Lagnavn"];
                    


                        $sql = "INSERT INTO Lag (Lagnavn) VALUES ('$Lagnavn')";
                    
                        if($kobling->query($sql)) {
                            echo "Ok";

                        } else {
                            echo "Dårlig nytt.. Laget $Lagnavn ble ikke lagt til.";
                         }
                        ////////////////////////////
                        $sql2 = "INSERT INTO Person (Fornavn, Etternavn, Lag_idLag) VALUES ('$Fornavn', '$Etternavn', (SELECT idLag FROM Lag WHERE Lagnavn = '$Lagnavn'))";
                    

                        if($kobling->query($sql2)) {
                            echo "Ok";

                        } else {
                            echo "Dårlig nytt.. Karakteren $Fornavn ble ikke lagt til.";
                         }
                        ////////////////////////////
                        $sql3 = "INSERT INTO Trening (Person_idPerson, Person_Lag_idLag) VALUES ((SELECT idPerson FROM Person WHERE Fornavn = '$Fornavn'), (SELECT idLag FROM Lag WHERE Lagnavn = '$Lagnavn'))";

                        if($kobling->query($sql3)) {
                            echo "Ok";

                        } else {
                            echo "Dårlig nytt.. Treningen ble ikke lagt til.";
                         }
                        
                        
                       /* $sql4 = "SELECT idPerson FROM Person WHERE Fornavn = '$Fornavn'";
                        $resultat4 = $kobling->query($sql4);
                        $rad4 =$resultat4->fetch_assoc();
                        $_SESSION["idPerson"] = $rad4["idPerson"];
                    
                        $sql5 = "SELECT idLag FROM Lag WHERE Lagnavn = '$Lagnavn'";
                        $resultat5 = $kobling->query($sql5);
                        $rad5 =$resultat5->fetch_assoc();
                        $_SESSION["idLag"] = $rad5["idLag"];
                    
                        $sql6 = "SELECT idTrening FROM Trening WHERE Person_idPerson = (SELECT idPerson FROM Person WHERE Fornavn = '$Fornavn')";
                        $resultat6 = $kobling->query($sql6);
                        $rad6 =$resultat6->fetch_assoc();
                        $_SESSION["idTrening"] = $rad6["idTrening"];
                    
                        echo "'$_SESSION[idPerson]' '$_SESSION[idLag]' '$_SESSION[idTrening]'";
                        */
                        $command = escapeshellcmd('python3 /Users/thomasbruflot/Documents/nettsider/Curling/Auto2.py');
                        $output = exec($command);
                        echo $output;
                    
                     
                    $sql4 = "INSERT INTO Kast (Bilde, Trening_idTrening, Trening_Person_idPerson, Trening_Person_Lag_idLag) VALUES ('$output', (SELECT idTrening FROM Trening WHERE Person_idPerson = (SELECT idPerson FROM Person WHERE Fornavn = '$Fornavn')), (SELECT idPerson FROM Person WHERE Fornavn = '$Fornavn'), (SELECT idLag FROM Lag WHERE Lagnavn = '$Lagnavn'))";
                   
                    if($kobling->query($sql4)) {
                        echo "Ok";

                    } else {
                        echo "Dårlig nytt.. kastet ble ikke lagt til.";
                     }
                    
                    

                    
                    
                } 
             
        }
	?>
    </div>
    <footer>
        <p>Laget av Thomas Bruflot</p>
        <a href="">Kontakt meg</a>
    </footer>
</body>
