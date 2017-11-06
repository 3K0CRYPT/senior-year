<?php
$page = basename($_SERVER['PHP_SELF']);
?>

<!DOCTYPE html >
<html lang="en">

<head>
    <title>Shop</title>
    <meta charset="utf-8">
    <meta id="author" name="Michael Bartlett" content="Michael Bartlett" lang="en">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="../csci445.css" />
    <style>
    .error {color: #FF0000;}
    </style>
</head>
<body>
    <?php include '../templateHeader.php';?>
    <hr />
    <h2>Past Orders</h2>
    <ul>
    <?php
    if (file_exists('orders.csv')) {
        $customers=array();
        $totals=array();
        if (($handle = fopen("orders.csv", "r")) !== FALSE) {
            while (($data = fgetcsv($handle)) !== FALSE) {
                // $order = array($first,$last,$email,$products[(int)$product-1],$quantity,$total,$timestamp)
                if (!array_key_exists($data[0]." ".$data[1]." (".$data[2].")", $customers)) $customers[$data[0]." ".$data[1]." (".$data[2].")"] = array();
                if (!array_key_exists($data[0]." ".$data[1]." (".$data[2].")", $totals)) $totals[$data[0]." ".$data[1]." (".$data[2].")"] = 0;
                array_push($customers[$data[0]." ".$data[1]." (".$data[2].")"], $data[4]."×".$data[3]." → $".$data[5]." @ ".$data[6]);
                $totals[$data[0]." ".$data[1]." (".$data[2].")"] += $data[5];
            }
            fclose($handle);
        }
        
        if (empty($customers)) echo "<h3 class=\"error\">Error: No orders have been placed yet!</h3>";
        else {
            foreach($customers as $customer => $orders):
                echo "<li>".$customer."</li>";
                echo "<ul>";
                
                foreach($orders as $key => $order):
                echo '<li>'.($key+1).": ".$order.'</li>';
                endforeach;
                
                echo "</ul>";
            echo "<ul>Grand Total: $".$totals[$customer]."</ul>";
            endforeach;
        }
    }
    else echo "<h3 class=\"error\">Error: No order log file found!</h3>"
    ?>
    </ul>
    <hr />
    <?php include '../templateFooter.php';?>
</body>

</html>
