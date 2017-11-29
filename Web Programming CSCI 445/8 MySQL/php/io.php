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
    <form method="post" action="io_submit.php">  
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
                  $products=array();
                  if (($handle = fopen("itemlist.csv", "r")) !== FALSE) {
                      while (($data = fgetcsv($handle)) !== FALSE) {
                          array_push($products,$data[0] . " ($".$data[1].")");
                      }
                      fclose($handle);
                  }
                  
                  foreach($products as $key => $value):
                    $key = $key + 1;
                  echo '<option value="'.$key.'">'.$value.'</option>';
                  endforeach;
                  ?>
          </select>
          <span class="error">* </span>
          <br>
        
        Quantity: <input type="number" name="quantity" value=0>
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
