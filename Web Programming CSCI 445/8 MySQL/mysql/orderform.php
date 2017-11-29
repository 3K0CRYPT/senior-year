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
    body {
        text-align: center;
    }
    .error {color: #FF0000;}
    </style>
</head>
<body>
    <?php include '../templateHeader.php';?>
    <hr />
    <p>Snowboard Shop!</p>
    
    
    <p><span class="error">* required field.</span></p>
    <form method="post" action="mysql_submit.php">  
        <fieldset>
        First Name: <input type="text" name="first" value="">
        <span class="error">* </span>    
        <br>
        
        Last Name: <input type="text" name="last" value="">
        <span class="error">* </span>    
        <br>
        
        E-mail: <input type="text" name="email" value="">
        <span class="error">* </span>
        <br>
        
        
           
           
          Product: <select name="product"  onchange="this.form.submit()">
          <option selected disabled hidden>Select a product</option>
            <?php
                $dbhost = 'localhost';
                $dbuser = 'mbartlet';
                $dbpass = 'GEUUEAEC';
                $db = 'f17_mbartlet';
                $link = mysqli_connect($dbhost, $dbuser, $dbpass, $db);
                if (mysqli_connect_errno()) { echo "Failed to connect to MySQL: " . mysqli_connect_error(); }
                $results = mysqli_query($link,"SELECT ID, Product, Quantity FROM PRODUCTS");

                while ($row = mysqli_fetch_row($results)) {
                  echo '<option value="'.$row[0].'"';
                  if ($row[2] <= 0) echo 'disabled';
                  echo '>'.$row[1];
                  if ($row[2] <= 0) echo ' (SOLD OUT)';
                  echo '</option>';                  
                }
                ?>
          </select>
          <span class="error">* </span>
          <br>
        
        Quantity: <input type="number" name="quantity" value=0 >
        <span class="error">* </span>
        <br>
        
        Donation:
        <input type="radio" name="donation"  value="yes">Yes
        <input type="radio" name="donation"  value="no">No
        <span class="error">* </span>
        <br>
        
        <input type="text" name="timestamp" value=
        <?php echo '"'.date('Y-m-d G:i:s').'"';?>
         hidden>
        <br>
        
        <input type="submit" name="subbtn" value="Submit">
        <input type="reset" name="reset" value="Reset">
        
        </fieldset>
    </form>
    <hr />
    <?php include '../templateFooter.php';?>
</body>

</html>
