<!Doctype HTML!>
<head>
	<title>Meny</title>
	<link rel="Stylesheet" href="Stilark/Meny.css">
	<meta charset="UTF-8">
    <!--Bruker Jquery for å skrive en funksjon som endrer om menyen, under lenker jeg til et bibliotek for slik kode-->
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
</head>
<body>
		<header>
			<img src='Bilder/CurTech.png' alt='Filtypen støttes ikke av nettleseren din...' class='Bildet'>
		</header>
		<div class="nav">
			<ul>
				<div class="svg-wrapper">
					<svg height="40" width="150" xmlns="http://www.w3.org/2000/svg">
						<rect id="shape" height="40" width="150" />
						<div id="text">
							<a href="Index.php"><span class="spot"></span>Hjem</a>
						</div>
					</svg>
				</div>
				<div class="svg-wrapper">
					<svg height="40" width="150" xmlns="http://www.w3.org/2000/svg">
						<rect id="shape" height="40" width="150" />
						<div id="text">
							<a href="Oversikt.php"><span class="spot"></span>Oversikt</a>
					 </div>
					</svg>
				</div>
                				<div class="svg-wrapper">
					<svg height="40" width="150" xmlns="http://www.w3.org/2000/svg">
						<rect id="shape" height="40" width="150" />
						<div id="text">
							<a href="LeggtilInfo.php"><span class="spot"></span>Legg til info</a>
						</div>
					</svg>
				</div>
				<div class="svg-wrapper">
					<svg height="40" width="150" xmlns="http://www.w3.org/2000/svg">
						<rect id="shape" height="40" width="150" />
						<div id="text">
							<a href="About.php"><span class="spot"></span>Om oss</a>
					 </div>
					</svg>
				</div>		
			</ul>	
			<div class="handle">Meny</div>
			</div>
    <!--Javascript som skrur på og av menylisten på små skjermer (når man har redusert vindu som f.eks på en telefon)
        Det som skjer: Trykker man på .handle som er vist med output "Meny" så kjøres en funksjon der tabellen som er unlisted viser og skjuler classen showing avhengig av hva man trykker på (annenhver gang)-->
			<script>
		$('.handle').on('click', function(){
			$('ul').toggleClass('showing');
		});
		</script>
</body>		
		
