<?php
$page = basename($_SERVER['PHP_SELF']);

if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $CID = $_GET["ID"];
}

function table( $result ) {
    $result->fetch_array( MYSQLI_ASSOC );
    echo '<table>';
    tableHead( $result );
    tableBody( $result );
    echo '</table>';
}

function tableHead( $result ) {
    echo '<thead>';
    foreach ( $result as $x ) {
    echo '<tr>';
    foreach ( $x as $k => $y ) {
        echo '<th>' . ucfirst( $k ) . '</th>';
    }
    echo '</tr>';
    break;
    }
    echo '</thead>';
}

function tableBody( $result ) {
    echo '<tbody>';
    foreach ( $result as $x ) {
    echo '<tr>';
    foreach ( $x as $y ) {
        echo '<td>' . $y . '</td>';
    }
    echo '</tr>';
    }
    echo '</tbody>';
}
?>

<!DOCTYPE html >
<html lang="en">

<head>
    <title>All Orders</title>
    <meta charset="utf-8">
    <meta id="author" name="Michael Bartlett" content="Michael Bartlett" lang="en">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="../csci445.css" />
    <style>
    .error {color: #FF0000;}
    table * {
        border: 1px dashed black;
        padding: 3px;
    }
    </style>
</head>
<body>
    <?php include '../templateHeader.php';?>
    <hr />
    <h2>Past Orders</h2>
    <?php
    if (!$CID) echo "<h2 class=\"error\">ERROR, INVALID REDIRECT</h2>"; 
    else {
        $dbhost = 'localhost';
        $dbuser = 'mbartlet';
        $dbpass = 'GEUUEAEC';
        $db = 'f17_mbartlet';
        $link = mysqli_connect($dbhost, $dbuser, $dbpass, $db);
        if (mysqli_connect_errno()) { echo "Failed to connect to MySQL: " . mysqli_connect_error(); }
        $query = "select concat(FirstName,' ',LastName,' (',Email,')') as customer from CUSTOMERS WHERE ID = ".$CID.";";
        $results = mysqli_query($link, $query);
        if (!$results) echo "<h3 class=\"error\">Error: No orders have been placed yet!</h3>";
        else {
            while ($crow = mysqli_fetch_row($results)) {
                echo "<li>".$crow[0]."</li>";
                echo "<ul>";
                $query1 = "Select *, CEIL(Price*Tax*Quantity) as Total from (Select (select Product from PRODUCTS as p WHERE p.ID = o.PID) as Product, Timestamp, Quantity, Tax, Donation, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price from ORDERS as o WHERE Donation = 1 AND CID = ".$CID.") as t UNION ALL Select *, TRUNCATE(Price*Tax*Quantity, 2) as Total from (Select (select Product from PRODUCTS as p WHERE p.ID = o.PID) as Product, Timestamp, Quantity, Tax, Donation, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price from ORDERS as o WHERE Donation = 0 AND CID = ".$CID.") as t;";
                $results1 = mysqli_query($link, $query1);
                
                table($results1);
                
                echo "</ul>";
            }
            $query = "Select (IFNULL((Select SUM(CEIL(Price*Tax*Quantity)) as Total from (Select Quantity, Tax, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price from ORDERS as o WHERE Donation = 1 AND CID = ".$CID.") as t),0) + IFNULL((Select SUM(TRUNCATE(Price*Tax*Quantity, 2)) as Total from (Select Quantity, Tax, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price from ORDERS as o WHERE Donation = 0 AND CID = ".$CID.") as t), 0)) as Total, (IFNULL((Select SUM(CEIL(Price*Tax*Quantity)) as Total from (Select Quantity, Tax, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price from ORDERS as o WHERE Donation = 1 AND CID = ".$CID.") as t),0) + IFNULL((Select SUM(TRUNCATE(Price*Tax*Quantity, 2)) as Total from (Select Quantity, Tax, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price from ORDERS as o WHERE Donation = 0 AND CID = ".$CID.") as t),0))/(Select COUNT(*) FROM ORDERS WHERE CID = ".$CID.") as \"Average $\";";
            $results = mysqli_query($link, $query);
            echo "<li>Stats</li><ul>";
            table($results);
            echo "</ul>";
        }
    }
    ?>
    <hr />
    <?php include '../templateFooter.php';?>
</body>

</html>
