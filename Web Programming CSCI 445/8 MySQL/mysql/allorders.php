<?php
$page = basename($_SERVER['PHP_SELF']);

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
    
    $dbhost = 'localhost';
    $dbuser = 'mbartlet';
    $dbpass = 'GEUUEAEC';
    $db = 'f17_mbartlet';
    $link = mysqli_connect($dbhost, $dbuser, $dbpass, $db);
    if (mysqli_connect_errno()) { echo "Failed to connect to MySQL: " . mysqli_connect_error(); }
    $query = "select concat(FirstName,' ',LastName,' (',Email,')') as customer, ID from CUSTOMERS;";
    $results = mysqli_query($link, $query);
    if (!$results) echo "<h3 class=\"error\">Error: No orders have been placed yet!</h3>";
    else {
        while ($crow = mysqli_fetch_row($results)) {
            echo "<li><a href=\"customer.php?ID=".$crow[1]."\">".$crow[0]."</a></li>";
            echo "<ul>";
            $query1 = "Select *, CEIL(Price*Tax*Quantity) as Total from (Select (select Product from PRODUCTS as p WHERE p.ID = o.PID) as Product, Timestamp, Quantity, Tax, Donation, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price from ORDERS as o WHERE Donation = 1 AND CID = ".$crow[1].") as t UNION ALL Select *, TRUNCATE(Price*Tax*Quantity, 2) as Total from (Select (select Product from PRODUCTS as p WHERE p.ID = o.PID) as Product, Timestamp, Quantity, Tax, Donation, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price from ORDERS as o WHERE Donation = 0 AND CID = ".$crow[1].") as t;";
            $results1 = mysqli_query($link, $query1);
            
            table($results1);
            
            echo "</ul>";
        }
        
        $query = 'select (select "# of Customers") as Stat, (select count(distinct ID) from CUSTOMERS) as "Total", (select count(distinct ID) from CUSTOMERS)/(select count(distinct ID) from ORDERS) as "# per Order", (select count(distinct ID) from CUSTOMERS)/(select count(distinct ID) from CUSTOMERS) as "# per Customer" UNION select (select "# of Orders") as Stat, (select count(distinct ID) from ORDERS) as "Total", (select count(distinct ID) from ORDERS)/(select count(distinct ID) from ORDERS) as "# per Order", (select count(distinct ID) from ORDERS)/(select count(distinct ID) from CUSTOMERS) as "# per Customer" UNION select (select "# of Products") as Stat, (select SUM(Quantity) from ORDERS) as "Total", (select SUM(Quantity) from ORDERS)/(select count(distinct ID) from ORDERS) as "# per Order", (select SUM(Quantity) from ORDERS)/(select count(distinct ID) from CUSTOMERS) as "# per Customer" UNION select (select "Global Subtotal") as Stat, (Select SUM(Price*Quantity) as Total from (Select Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price FROM ORDERS as o) as t) as "Total", (Select SUM(Price*Quantity) as Total from (Select Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price FROM ORDERS as o) as t)/(select count(distinct ID) from ORDERS) as "# per Order", (Select SUM(Price*Quantity) as Total from (Select Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price FROM ORDERS as o) as t)/(select count(distinct ID) from CUSTOMERS) as "# per Customer" UNION select (select "Global Tax") as Stat, (Select SUM(Price*Quantity*0.07) as Total from (Select Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price FROM ORDERS as o) as t) as "Total", (Select SUM(Price*Quantity*0.07) as Total from (Select Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price FROM ORDERS as o) as t)/(select count(distinct ID) from ORDERS) as "# per Order", (Select SUM(Price*Quantity*0.07) as Total from (Select Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID) as Price FROM ORDERS as o) as t)/(select count(distinct ID) from CUSTOMERS) as "# per Customer" UNION select (select "Global Donations") as Stat, (Select SUM(CEIL(Price*Quantity*Tax)-(Price*Quantity*Tax)) as Total from (Select Tax, Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID  AND Donation = 1) as Price FROM ORDERS as o) as t) as "Total", (Select SUM(CEIL(Price*Quantity*Tax)-(Price*Quantity*Tax)) as Total from (Select Tax, Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID AND Donation = 1) as Price FROM ORDERS as o) as t)/(select count(distinct ID) from ORDERS) as "# per Order", (Select SUM(CEIL(Price*Quantity*Tax)-(Price*Quantity*Tax)) as Total from (Select Tax, Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID AND Donation = 1) as Price FROM ORDERS as o) as t)/(select count(distinct ID) from CUSTOMERS) as "# per Customer" UNION select (select "Global Total") as Stat, ((Select SUM(CEIL(Price*Quantity*Tax)) as Total from (Select Tax, Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID  AND Donation = 1) as Price FROM ORDERS as o) as t) + (Select SUM(Price*Quantity*Tax) as Total from (Select Tax, Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID  AND Donation = 0) as Price FROM ORDERS as o) as t2)) as "Total", ((Select SUM(CEIL(Price*Quantity*Tax)) as Total from (Select Tax, Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID  AND Donation = 1) as Price FROM ORDERS as o) as t) + (Select SUM(Price*Quantity*Tax) as Total from (Select Tax, Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID  AND Donation = 0) as Price FROM ORDERS as o) as t2))/(select count(distinct ID) from ORDERS) as "# per Order", ((Select SUM(CEIL(Price*Quantity*Tax)) as Total from (Select Tax, Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID  AND Donation = 1) as Price FROM ORDERS as o) as t) + (Select SUM(Price*Quantity*Tax) as Total from (Select Tax, Quantity, (select Price from PRODUCTS as p WHERE p.ID = o.PID  AND Donation = 0) as Price FROM ORDERS as o) as t2))/(select count(distinct ID) from CUSTOMERS) as "# per Customer";';
        $results = mysqli_query($link, $query);
        echo "<li>Order Statistics</li>";
        echo "<ul>";
        table($results);
        echo "</ul>";
    }
    ?>
    <!-- </ul> -->
    <hr />
    <?php include '../templateFooter.php';?>
</body>

</html>
