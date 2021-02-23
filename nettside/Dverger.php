<!DOCTYPE HTML>
<head>
    <title>Dverger</title>
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
	<style>
		<?php
			include "Index.css"
		?>
	</style>
	<?php
			include "Meny.php"
	?>
    <div class="Wrapper">
    <div class='Info'>
					<h2>Dverger</h2>
					<img src='Bilder/Dverg.png' alt='Hobsyssel' class='Bilde' id='Dvergen'>
					<div class='tekst'>
					<p>Dverger er i fiksjonen til J.R.R. Tolkien en rase som befolket verden Arda, en fiktiv forhistorisk jord som innbefatter det kontinentale Midgard. Tolkiens dverger opptrer i bøkene Hobbiten (1937), Ringenes herre (1954–55) og den posthum utgitte verkene Silmarillion (1977), Ufullendte fortellinger (1980) og Historien om Midgard (1983–96), de siste tre redigert av hans sønn og litterære testamentfullbyrder Christopher Tolkien.

Tolkien lot seg inspirere av blant annet dverger i norrøn mytologi. I hans fortellinger er dverger et folk som bor i huler og grotter, inni og under fjellet. De er kortvokste, og har tykke skjegg. Dvergene ble skapt av Aulë, en av Valaene, når han ble utålmodig når han ventet på skapelsen av Ilúvatars barn, alvene. Ilúvatar ga dem liv etter å ha snakket med Aulë om hva han hadde gjort og sett at han var både ydmyk og angrende. Dvergene i Tolkiens verden levde lenge. Nesten fire ganger så lenge som en vanlig mann (rundt 250 år), men var ikke fruktbare. Å få barn skjedde en sjelden gang, og det var få kvinnelige dverger. Barn av dvergene ble tatt veldig godt vare på av foreldrene, og de ble beskyttet med alle middler mot forskjellige fiender, som for eksempel orker. Et langvarig fiendskap mellom dverger og alver er også en grunn til kryssavl.

Hva som skjer med dem etter at de dør er uklart: en teori (som alvene foretrekker) er at de går tilbake til jorden og steinen de i sin tid ble laget av, en annen (foretrukket av dvergene selv) er at Aulë Skaperen, som de kaller Mahal, samler dem i særskilte saler i Mandos, og at Aulë i gammel tid erklærte for deres fedre at Ilúvatar vil hellige dem og gi dem en plass blant alver og mennesker til slutt.
                        </p></div></div>
    <?php
		// Henter tilkoblingsinformasjon tilkobling.php
			include "tilkobling.php";
			// Henter ut alle karakterene med hobbit som rase
			$sql = "SELECT * FROM Karakter WHERE Rase = 'Dverg'";
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
                    <td><a class='link 'id='oppdaterlink' href='update.php?update_id=".$Karakter_Id."&Rase=Dverg&Gender=$Gender'><p>Oppdater</p></a></td>
                    <td><a class='link' id='slettlink' href='delete.php?delete_id=".$Karakter_Id."'><p>Slett</p></a></td>
                </tr>";
						
		};
			echo "</table>";
		echo "</div>";
                
    ?>
        <!--Legger til et passende bilde for å linke til siden der man kan legge til karakterer-->
    <div class="Ring">
        <b>Legg til karakter:</b>
        <a href="Leggtilkarakter.php?Rase=Dverg"><img src='Bilder/Ring.png' alt='Legg til hobbit' class='Pluss'></a>
    </div>
    </div>
       <footer>
        <p>Laget av Thomas Bruflot</p>
        <a href="">Kontakt meg</a>
    </footer>
</body>
