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

$dbhost = 'localhost';
$dbuser = 'mbartlet';
$dbpass = 'GEUUEAEC';
$db = 'f17_mbartlet';
$link = mysqli_connect($dbhost, $dbuser, $dbpass, $db);
if (mysqli_connect_errno()) { echo "Failed to connect to MySQL: " . mysqli_connect_error(); }

if(count(array_unique($values)) === 1) {
  echo "<h3>";
  
      $query = "INSERT INTO CUSTOMERS (FirstName, LastName, Email) VALUES ('".$first."','".$last."','".$email."');";
      $results = mysqli_query($link, $query);
      if (!$results && !empty($first)) {
        $query = "SELECT * FROM CUSTOMERS WHERE LastName = '".$last."' AND FirstName = '".$first."'";
         $results = mysqli_query($link, $query);
         $customer = mysqli_fetch_row($results);
         echo "<p> Welcome back ".$customer[2]."!</p>";
    } else {
            echo "<p> Welcome new customer!</p>";
        }
  
  
  $results = mysqli_query($link,"SELECT Price, Product, Image, Quantity FROM PRODUCTS WHERE ID = ".$product.";");
  $row = mysqli_fetch_row($results);
  $productName = $row[1];
  $price = $row[0];
  $productImage = $row[2];
  $productQuantity = $row[3];
  
  if ($productQuantity < $quantity) echo "<h2 class=\"error\">ORDERED LARGER QUANTITY THAN IN STOCK, PLEASE REQUEST SMALLER QUANTITY.</h3>";
  else {
    $total = $price * $quantity * 1.07;
    if ($donation == "yes") $total = ceil($total);
    
    
    echo $first." ".$last." ordered ".$quantity."x".$productName." ($".$price." with 7% tax) at ".$timestamp.". Total price: $".$total;
    echo "</h3>";
    if ($donation == "yes") {
        echo "<h5>Thank you for your donation!</h5>";
        $donation = 1;
    } else $donation = 0;
    
    $order = "INSERT INTO ORDERS (CID, PID, Quantity, Tax, Donation, Timestamp) VALUES ((SELECT ID FROM CUSTOMERS WHERE LastName = '".$last."' AND FirstName = '".$first."'),".$product.",".$quantity.", 1.07,".$donation.",'".$timestamp."');";
    $results = mysqli_query($link, $order);
    if ($results) {
        echo "<h2>Order submitted!</h3>";
        $results = mysqli_query($link,"UPDATE PRODUCTS SET Quantity = Quantity - ".$quantity." WHERE ID = ".$product.";");
    }
  else echo "<h2 class=\"error\">DUPLICATE ORDER SUBMITTED, IGNORED</h3>";
  }
}
?>
    <p><span class="error">* required field.</span></p>
    <form method="post" action="mysql_submit.php">  
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
        
        
           <?php  
           if ($product > 0) {
                $results = mysqli_query($link,"SELECT Image FROM PRODUCTS WHERE ID = ".$product);
                $image = mysqli_fetch_row($results);
               echo '<img src="/mbartlet/images/'.$image[0].'"><br>'; 
            }
            ?>
           
           Product: <select name="product"  onchange="this.form.submit()">
           <option selected disabled hidden>Select a product</option>
           <?php
       
                $results = mysqli_query($link,"SELECT ID, Product, Quantity FROM PRODUCTS");

                while ($row = mysqli_fetch_row($results)) {
                  echo '<option value="'.$row[0].'"';
                  if ($row[2] <= 0) echo ' disabled';
                  if ($product==$row[0]) echo ' selected';
                  echo '>'.$row[1];
                  if ($row[2] <= 0) echo ' (SOLD OUT)';
                  else echo ' ('.$row[2].')';
                  echo '</option>';                  
                }
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
