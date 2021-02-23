<!DOCTYPE HTML>
<head>
    <title>Oppdater informasjon</title>
    <meta charset="UTF-8">
    <meta name="description" content="Innovasjonsprosjekt">
    <meta name="keyword" keyword="Curling, sport">
    <meta http-equiv="content-type" content="text/html;charset=utf-8" />
    <link rel="shortcut icon" href="Bilder/Curling.png"/>
    <link rel="stylesheet" href="Stilark/Update.css">
</head>
<?php
    include "Meny.php";
?>
<style>
    <?php include "Stilark/Meny.css";
    ?>

</style>
         <?php
            include "tilkobling.php";

            $update_id = $_GET["update_id"];

            $sql = "SELECT * From Kast WHERE idKast = '$update_id'";

            $resultat = $kobling->query($sql);

            $rad = $resultat->fetch_assoc(); 

                $Trening = $rad['Trening_idTrening'];
                $Kommentar = $rad['Kommentar'];
                $Lag_id = $rad['Trening_Person_Lag_idLag'];


            $sql2 = "SELECT * FROM Person WHERE idPerson = (SELECT Trening_Person_idPerson FROM Kast WHERE idKast = '$update_id')";
                
                $resultat2 = $kobling->query($sql2);
                $rad2 = $resultat2->fetch_assoc(); 

                $Fornavn = $rad2['Fornavn'];
                $Etternavn = $rad2['Etternavn'];



            $sql3 = "SELECT Lagnavn FROM Lag WHERE idLag = '$Lag_id'";
                $resultat3 = $kobling->query($sql3);
                $rad3 = $resultat3->fetch_assoc(); 
                $Lag = $rad3['Lagnavn'];
        
        

?>

            <div class='Oppdater'>
                        <h1 id='topp'>Endre informasjonen</h1>
                <div class='boks'>
                         <form method='POST' class='container'>

                                <label><b>Fornavn</b></label><br>

                            <input type='text' name='FornavnInput' value='<?php echo"$Fornavn";?>' placeholder='Skriv her'><br>

                                <label><b>Etternavn</b></label><br>
                            
                            <input type='text' name='EtternavnInput' value='<?php echo"$Etternavn";?>' placeholder='Eksempel: 90800'><br>



                                <label><b>Lag</b></label><br>

              <input type='text' value='<?php echo"$Lag";?>' name='LagInput'><br><br>


                                <label><b>Kommentar</b></label><br>

                           <input type='text' value='<?php echo"$Kommentar";?>' name='KommentarInput'><br><br>
                             
                             
                            <input type='submit' name='Leggtil' value='Oppdater'>

                            </form>
                    </div>
                </div>

<?php
        if(isset($_POST["Leggtil"])) {
            
            include "tilkobling.php";
            $kobling->set_charset("utf8");

            $update_id = $_GET["update_id"];

                $FornavnInput = $_POST['FornavnInput'];
                $EtternavnInput = $_POST['EtternavnInput'];
                $LagInput = $_POST['LagInput'];
                $KommentarInput = $_POST['KommentarInput'];
        
            $sql = "UPDATE Lag SET Lagnavn = '$LagInput' WHERE idLag = (SELECT Trening_Person_Lag_idLag FROM Kast WHERE idKast = '$update_id')";
            $resultat = $kobling->query($sql);
            
            $sql2 = "UPDATE Person SET Fornavn = '$FornavnInput', Etternavn = '$EtternavnInput' WHERE idPerson = (SELECT Trening_Person_idPerson FROM Kast WHERE idKast = '$update_id')";
                
            $resultat2 = $kobling->query($sql2);
            
            $sql3 = "UPDATE Kast SET Kommentar = '$KommentarInput' WHERE idKast = '$update_id'";
            
            $resultat3 = $kobling->query($sql3);

        }

?>

   <footer>
        <p>Laget av Thomas Bruflot</p>
        <a href="">Kontakt meg</a>
    </footer>
    

