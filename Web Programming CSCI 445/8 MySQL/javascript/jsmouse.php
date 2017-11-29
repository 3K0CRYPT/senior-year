<?php
$page = basename($_SERVER['PHP_SELF']);
?>


<!DOCTYPE html >
<html lang="en">

<head>
    <title>Michael Bartlett JS Mouse</title>
    <meta charset="utf-8">
    <meta id="author" name="Michael Bartlett" content="Michael Bartlett" lang="en">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="../navbar.css" />
    <link rel="stylesheet" type="text/css" href="style.css" />
    <script src='jsmouse.js'></script>
</head>

<body>
<?php include '../templateHeader.php';?>
    <section>
        <h2>Canvas Mouse Demonstration</h2>
        <button style="margin:auto;" type="button">Draw yellow smiley!</button>
        <canvas id="canvas" height="500" style="border: 1px dashed red"></canvas>
    </section>
    <hr />
    <?php include '../templateFooter.php';?>
    

</html>