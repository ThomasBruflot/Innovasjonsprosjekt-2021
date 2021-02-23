<!DOCTYPE HTML>
<head>
    <title>Innovasjonsprosjekt gruppe 9</title>
    <meta charset="UTF-8">
    <meta name="description" content="Innovasjonsprosjekt">
    <meta name="keyword" keyword="Curling, sport">
    <meta http-equiv="content-type" content="text/html;charset=utf-8" />
    <link rel="shortcut icon" href="Bilder/Curling.png"/>
    <link rel="stylesheet" href="Stilark/Index.css">
</head>
<body>
    	<style>
		<?php
            //Henter inn ulike stilark samt menyens php-script med include
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
	<div class="Verden">
        <!--Legger inn bilde fra Bilder-mappen og sier at hvis bildet ikke vises skal det si verden isteden.-->
	<img src="Bilder/Steiner.jpg" alt="Verden" id="bilde">
	<div class="Tekstverden"><h3 id="Lesmer">Velkommen til Gruppe 9 sin nettside<br />-Curlingsportens venner</h3></div>
		</div>
    
    <!--Legger til et passende bilde for å linke til siden der man kan legge til karakterer-->
        <div class="Ring">
        <b>Legg til informasjon:</b>
        <a href="LeggtilInfo.php"><img src='Bilder/Curling.png' alt='Legg til informasjon' class='Pluss'></a>
    </div>
    

    <footer>
        <p>Laget av Thomas Bruflot</p>
        <a href="">Kontakt meg</a>
    </footer>
</body>