<!DOCTYPE HTML>
<head>
    <title>Hobbit</title>
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
					<h2>Hobbiter</h2>
					<img src='Bilder/Hobsyssel.jpg' alt='Hobsyssel' class='Bilde' id='Hobbiten'>
					<div class='tekst'>
					<p> Hobbiter er eventyrlige figurer som er relativt like mennesker. De forekommer i bøkene Hobbiten og Ringenes herre av J.R.R. Tolkien. Hobbitene er nok små og tilsynelatende ubetydelige, men tross sine ufullkommenheter, er det nettopp hobbiter som Bilbo, Frodo og Sam som viser seg å være de virkelige heltene i Tolkiens bøker.

Hobbiter er på størrelse med barn i småskolen (omtrent 1-1,2 meter høye) og har store hårete føtter. Derfor bruker de sjelden sko. De er et fredsommelig folk som ikke bryr seg så mye om verden utenfor sitt eget land, Hobsyssel, hvis det da ikke skjer noe som får dem til å bryte ut av sin koselige hverdagstilværelse. Hobbiter har ikke skjegg, liker å kle seg i gult og grønt, er glade i god mat og har lett for å bli runde over magen. De spiser middag to ganger om dagen dersom det lar seg gjøre.

Fra gammelt av var hobbitene delt i tre stammer: hørfotene, stoorer og blakkenskinner. Hørfotene var brune i huden, og selv om de ikke trengte det, gikk de i støvler. Stoorene bodde helst langs elver og på flat mark. Blakkenskinner var lysere i huden, og var ofte høyere og slankere enn de andre.

Hobbitene har aldri vært krigerske, og de har aldri slåss innbyrdes. De fleste våpnene i Hobsyssel er bare til pynt eller kan beskues på museum.
                        </p></div></div>
        <?php
		  // Henter tilkoblingsinformasjon tilkobling.php
			include "tilkobling.php";
			
        // Henter ut alle karakterene med hobbit som rase
			$sql = "SELECT * FROM Karakter WHERE Rase = 'Hobbit'";
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
                    <td><a class='link 'id='oppdaterlink' href='update.php?update_id=".$Karakter_Id."&Rase=Hobbit&Gender=$Gender'><p>Oppdater</p></a></td>
                    <td><a class='link' id='slettlink' href='delete.php?delete_id=".$Karakter_Id."'><p>Slett</p></a></td>
                </tr>";
						
		};
			echo "</table>";
		echo "</div>";
                
    ?>
        <!--Legger til et passende bilde for å linke til siden der man kan legge til karakterer-->
    <div class="Ring">
        <b>Legg til karakter:</b>
        <a href="Leggtilkarakter.php?Rase=Hobbit"><img src='Bilder/Ring.png' alt='Legg til hobbit' class='Pluss'></a>
    </div>
    </div>
       <footer>
        <p>Laget av Thomas Bruflot</p>
        <a href="">Kontakt meg</a>
    </footer>
</body>
