<!Doctype HTML>

<head>
    <title>Oversikt</title>
    <meta charset="UTF-8">
    <meta name="description" content="Innovasjonsprosjekt">
    <meta name="keyword" keyword="Curling, sport">
    <!--http-equiv med content type spesifiserer tegnsett for dokumentet-->
    <meta http-equiv="content-type" content="text/html;charset=utf-8" />
    <link rel="shortcut icon" href="Bilder/Ring.png" />
    <link rel="Stylesheet" href="Stilark/Oversikt.css">
</head>

<body>

    <style>
        <?php //Henter inn stilark samt menyens php-script med include
        include "Meny.css" ?>

    </style>

    <?php
			include "Meny.php"
	?>
        <br><div class="Wrapper">
            <h1>Oversikt over alle kastene</h1>
            <div class='info'>
                <p>Dette er en oversikt over kastene i databasen. Ønsker du å sortere etter alfabetisk/stigende rekkefølge er det bare å trykke på kategorinavnene så får du stigende eller synkende størrelser :D
                </p>
            </div>
            <?php
		// Henter tilkoblingsinformasjon tilkobling.php
			include "tilkobling.php";
			//Hvis det allerede er definert hva det skal sorteres etter, sorter etter dette
			if(isset ($_GET['order'])) {
				$order = $_GET['order'];
			} else {
                //Hvis det ikke er definert er standarden fornavn
				$order = 'Fornavn';
			} 
			
			//Hvis det er bestemt sorteringstype, bruk denne
			if(isset ($_GET['sort'])) {
				$sort = $_GET['sort'];
			} else {
                //Hvis det ikke er bestemt: Sorter etter ascending rekkefølge - økende. Dette vil gi økende tall og A som første output.
				$sort = 'ASC'; 
			}
			//Henter alt fra karaktertabellen og sorterer order f.eks Fødselsdato med enten ASC eller DESC avhengig av hva sort er
			$sql = "SELECT * FROM Kast JOIN Trening ON Kast.Trening_idTrening = Trening.idTrening JOIN Person ON Kast.Trening_Person_idPerson = Person.idPerson JOIN Lag ON Kast.Trening_Person_Lag_idLag = Lag.idLag ORDER BY $order $sort";
			$resultat = $kobling->query($sql);
			
            //Hvis det hentes ut mer enn 0 resultater:
			if($resultat->num_rows > 0) {

                //Hvis sort er DESC sort ASC, ellers DESC, SORT=DESC ? betyr TRUE ELLER FALSE, hvis TRUE -> SORT=ASC ellers SORT='DESC'
				$sort == 'DESC' ? $sort = 'ASC' : $sort = 'DESC';
                
				//Legger inn lenker som tablehead slik at sort- og ordervariablene sendes opp i inntastingsfeltet og det kan hentes ned med get for å sortere i spørringen rett over.
			echo "<div class='Oversikt'>";
					echo "<table>
					<tr id = 'ovre'>
						<th><a href='?order=Fornavn&&sort=$sort'>Fornavn  <img src='Bilder/Oppned.png' alt='sorter' id='Piler'></a></th>
						<th><a href='?order=Etternavn&&sort=$sort'>Etternavn  <img src='Bilder/Oppned.png' alt='sorter' id='Piler'></a></th>
						<th><a href='?order=idTrening&&sort=$sort'>Trening  <img src='Bilder/Oppned.png' alt='sorter' id='Piler'></a></th>
						<th><a href='?order=Lagnavn&&sort=$sort'>Lagnavn  <img src='Bilder/Oppned.png' alt='sorter' id='Piler'></a></th>
                        <th><a href='?order=Bilde&&sort=$sort'>Bilde  <img src='Bilder/Oppned.png' alt='sorter' id='Piler'></a></th>
                        <th><a href='?order=Kommentar&&sort=$sort'>Kommentar  <img src='Bilder/Oppned.png' alt='sorter' id='Piler'></a></th>
					</tr>";
                //Mens det hentes ut rader med informasjon
					while ($rad=$resultat->fetch_assoc()){
						$Fornavn = $rad['Fornavn'];
						$Etternavn = $rad['Etternavn'];
						$Trening = $rad['idTrening'];
						$Lag = $rad['Lagnavn'];
                        $Bilde = $rad['Bilde'];
                        $Kommentar = $rad['Kommentar'];
                        $idKast = $rad['idKast'];
						
                        echo "<tr> 
                                <td>$Fornavn</td>
                                <td>$Etternavn</td>
                                <td>$Trening</td>
                                <td>$Lag</td>
                                <td><a href='$Bilde'> $Bilde</a></td>
                                <td>$Kommentar</td>
                                <td><a class='link' id='slettlink' href='delete.php?delete_id=".$idKast."'><img src='Bilder/Minus.png' id='mini'></a></td>
                                <td><a class='link' id='updatelink' href='update.php?update_id=".$idKast."'><img src='Bilder/Oppd.png' id='mini'></a></td>
                            </tr>";
						
		};
			echo "</table>";
		echo "</div>";
	} else {
                //Hvis det ikke hentes ut noe
		echo "Ingen resultater hentet";
	}
    ?>
        </div>
    <div class="Ring">
        <b>Legg til karakter:</b>
        <a href="LeggtilInfo.php"><img src='Bilder/Curling.png' alt='Legg til kast' class='Pluss'></a>
    </div>
       <footer>
        <p>Laget av Thomas Bruflot</p>
        <a href="">Kontakt meg</a>
    </footer>
</body>
