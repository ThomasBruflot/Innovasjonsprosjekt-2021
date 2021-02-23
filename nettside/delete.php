<?php
    include "tilkobling.php";
        
     $delete_id = $_GET['delete_id'];
     $sql = "DELETE FROM Kast WHERE idKast = '$delete_id'"; 

if (mysqli_query($kobling, $sql)) {
    mysqli_close($kobling);
    header('Location: ' . $_SERVER['HTTP_REFERER']);
    //Standard måte å sende tilbake på i php men ikke spesielt trygg metode fordi informasjonen helst ikke bare bør sendes over på denne måten, da kan den fanges opp
    exit;
} else {
    echo "Error deleting record";
    
}
?>
