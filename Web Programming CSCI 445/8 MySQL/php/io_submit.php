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
    <?php
// define variables and set to empty values
$firstErr = $lastErr = $emailErr = $productErr = $quantityErr = $donationErr = $timestampErr = "";
$first = $last = $email = $product = $quantity = $donation = $timestamp = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
  if (empty($_POST["first"])) {
    $firstErr = "Name is required";
  } else {
    $first = test_input($_POST["first"]);
    // check if name only contains letters and whitespace
    if (!preg_match("/^[a-zA-Z ]*$/",$first)) {
      $firstErr = "Only letters and white space allowed"; 
    }
  }
  
  if (empty($_POST["last"])) {
    $lastErr = "Name is required";
  } else {
    $last = test_input($_POST["last"]);
    // check if name only contains letters and whitespace
    if (!preg_match("/^[a-zA-Z ]*$/",$last)) {
      $lastErr = "Only letters and white space allowed"; 
    }
  }
  
  if (empty($_POST["email"])) {
    $emailErr = "Email is required";
  } else {
    $email = test_input($_POST["email"]);
    // check if e-mail address is well-formed
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
      $emailErr = "Invalid email format"; 
    }
  }
    
  if (empty($_POST["product"])) {
    $productErr = "Product is required";
  } else {
    $product = test_input($_POST["product"]);  
  }

  if (empty($_POST["quantity"])) {
        $quantityErr = "Must order more than 0";
  } else {
    $quantity = test_input($_POST["quantity"]);
  }

  if (empty($_POST["donation"])) {
    $donationErr = "Donation must be specified";
  } else {
    $donation = test_input($_POST["donation"]);
  }
  if (empty($_POST["timestamp"])) {
  } else {
    $timestamp = test_input($_POST["timestamp"]);
  }
}

function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

$values = array($firstErr , $lastErr , $emailErr , $productErr , $quantityErr , $donationErr , $timestampErr);

$products=array();
$prices=array();
if (($handle = fopen("itemlist.csv", "r")) !== FALSE) {
    while (($data = fgetcsv($handle)) !== FALSE) {
        array_push($products,$data[0] . " ($".$data[1].")");
        array_push($prices,$data[1]);
    }
    fclose($handle);
}

if(count(array_unique($values)) === 1) {
  echo "<h3>Order submitted!</h3>";
  echo "<h4>";
  $total = $prices[(int)$product-1] * $quantity * 1.07;
  if ($donation == "yes") $total = ceil($total);
  
  echo $first." ".$last." (".$email.") ordered ".$quantity."x".$products[(int)$product-1]." (7% tax) at ".$timestamp.". Total price: $".$total;
  echo "</h4>";
  if ($donation == "yes") echo "<h5>Thank you for your donation!</h5>";
  $order = array($first,$last,$email,$products[(int)$product-1],$quantity,$total,$timestamp);
//   $file = fopen("orders.csv","a+");
  $file = fopen('./orders.csv','a+');
  fputcsv($file,$order);
  fclose($file);
}
?>
    <p><span class="error">* required field.</span></p>
    <form method="post" action="io_submit.php">  
        <fieldset>
        First Name: <input type="text" name="first" value="<?php echo $first;?>">
        <span class="error">* <?php echo $firstErr;?></span>    
        <br>
        
        Last Name: <input type="text" name="last" value="<?php echo $last;?>">
        <span class="error">* <?php echo $lastErr;?></span>    
        <br>
        
        E-mail: <input type="text" name="email" value="<?php echo $email;?>">
        <span class="error">* <?php echo $emailErr;?></span>
        <br>
        
        
           <?php  if ($product > 0) echo '<img src="/mbartlet/images/'.$product.'.jpg"><br>'; ?>
           
           Product: <select name="product"  onchange="this.form.submit()">
           <option selected disabled hidden>Select a product</option>
                   <?php
                  foreach($products as $key => $value):
                    $key = $key + 1;
                  echo '<option value="'.$key.'"';
                  if ($product==$key) echo 'selected';
                  echo '>'.$value.'</option>';
                  endforeach;
                  ?>
           </select>
           <span class="error">* </span>
           <br>
        
        Quantity: <input type="number" name="quantity" value=0>
        <span class="error">* <?php echo $quantityErr;?></span>
        <br>
        
        Donation:
        <input type="radio" name="donation" <?php if (isset($donation) && $donation=="yes") echo "checked";?> value="yes">Yes
        <input type="radio" name="donation" <?php if (isset($donation) && $donation=="no") echo "checked";?> value="no">No
        <span class="error">* <?php echo $donationErr;?></span>
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
