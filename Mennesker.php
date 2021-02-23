<!DOCTYPE HTML>
<head>
    <title>Mennesker</title>
    <meta charset="UTF-8">
    <meta name="description" content="Frederiks fanpage om ringenes herre...">
    <meta name="keyword" keyword="Frederik, Ringenes Herre, LOTR">
    <meta http-equiv="content-type" content="text/html;charset=utf-8" />
    <link rel="shortcut icon" href="Bilder/Ring.png"/>
    <link rel="stylesheet" href="Stilark/Rase.css">
</head>
<body>
        <style>
		<?php
            //Henter inn stilark samt menyens php-script med include
			include "Stilark/Meny.css"
		?>
	</style>
	<?php
			include "Meny.php"
	?>
    <div class="Wrapper">
    <div class='Info'>
					<h2>Mennesker</h2>
					<img src='Bilder/Aragorn.jpg' alt='Hobsyssel' class='Bilde' id='Mennesket'>
					<div class='tekst'>
					<p>Menneske (Homo sapiens) er en art med tobeinte primater (Primates) i familien av store aper (Hominidae) og tilhører menneskeslekten (Homo). Det vitenskapelige navnet kommer fra latin og betyr «det kloke mennesket». Det moderne mennesket er synonym med underarten H. s. sapiens, men det kan ha eksistert flere underarter. Disse spørsmålene er imidlertid fortsatt uavklarte. Menneske kan være både primærkonsument, sekundærkonsument, tertiærkonsument og toppkonsument i en næringskjede. 
                        </p></div></div>
    <?php
		 // Henter tilkoblingsinformasjon tilkobling.php
			include "tilkobling.php";
			// Henter ut alle karakterene med hobbit som rase
			$sql = "SELECT * FROM Karakter WHERE Rase = 'Menneske'";
			// Output: Tabell med tableheaders som viser hva informasjonen under er
            echo "<div class='Rase' id='Hobbit'>";
            echo  "<table>
					<tr>
						<th>Fornavn</th>
						<th>Etternavn</th>
						<th>Fødselsdato</th>
						<th>Kjønn</th>
                        <th>Rase</th>
                        <th>Hjemstednavn</th>
                        <th>Oppdater</th>
                        <th>Slett</th>
					</tr>";
            //Variablen er selve spørringen som blir kjørt på databasen som er definert i tilkobling.php Her er kobling selve tilkoblingen.
			$resultat = $kobling->query($sql);
            // Mens det hentes ut rader fra databasen defineres variablene og blir output i echo
            while ($rad = $resultat->fetch_assoc()) {
                $Karakter_Id = $rad["Karakter_Id"];
                $Fornavn = $rad["Fornavn"];
                $Etternavn = $rad["Etternavn"];
                $BirthDate = $rad["Fødselsdato"];
                $Gender = $rad["Kjønn"];
                $Rase = $rad["Rase"];
                $Hjemstednavn = $rad["Hjemstednavn"];
    
            echo "<tr> 
                    <td>$Fornavn</td>
				    <td>$Etternavn</td>
                    <td>$BirthDate</td>
                    <td>$Gender</td>
                    <td>$Rase</td>
                    <td>$Hjemstednavn</td>
                    <td><a class='link 'id='oppdaterlink' href='update.php?update_id=".$Karakter_Id."&Rase=Menneske&Gender=$Gender'><p>Oppdater</p></a></td>
                    <td><a class='link' id='slettlink' href='delete.php?delete_id=".$Karakter_Id."'><p>Slett</p></a></td>
                </tr>";
						
		};
			echo "</table>";
		echo "</div>";
                
    ?>
        <!--Legger til et passende bilde for å linke til siden der man kan legge til karakterer-->
    <div class="Ring">
        <b>Legg til karakter:</b>
        <a href="Leggtilkarakter.php?Rase=Menneske"><img src='Bilder/Ring.png' alt='Legg til hobbit' class='Pluss'></a>
    </div>
    </div>
       <footer>
        <p>Laget av Thomas Bruflot</p>
        <a href="">Kontakt meg</a>
    </footer>
</body>