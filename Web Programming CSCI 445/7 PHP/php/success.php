<h3>Order submitted!</h3>
<!-- $first = $last = $email = $product = $quantity = $donation = $timestamp = ""; -->
<?php include 'productArray.php';?>

<h4><?php echo $first." ".$last." (".$email.") ordered ".$quantity."x".$products[(int)$product-1]." at ".$timestamp;?></h4>
<?php if ($donation == "yes") echo "<h5>Thank you for your donation!</h5>";?>
