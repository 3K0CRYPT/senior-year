<?php
$page = basename($_SERVER['PHP_SELF'])
?>

<!DOCTYPE html >
<html lang="en">

<head>
    <title>Michael Bartlett JS Keyboard</title>
    <meta charset="utf-8">
    <meta id="author" name="Michael Bartlett" content="Michael Bartlett" lang="en">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="../navbar.css" />
    <link rel="stylesheet" type="text/css" href="style.css" />
    <script src='jskeyboard.js'></script>
</head>

<body>
<?php include '../templateHeader.php';?>
    <section>
        <h2>Canvas Keyboard Demonstration</h2>
        <h3>Drive around this little guy!</h3><img src="../images/car.png" alt="car sprite">
        <canvas id="canvas" height="300" style="border: 1px dashed red"></canvas>
    </section>
    <hr />
    <?php include '../templateFooter.php';?>
    
</html>