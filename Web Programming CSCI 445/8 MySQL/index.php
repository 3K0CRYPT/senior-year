<?php
$page = basename($_SERVER['PHP_SELF']);
?>

<!DOCTYPE html >
<html lang="en">

<head>
    <title>Michael Bartlett assignment 1</title>
    <meta charset="utf-8">
    <meta id="author" name="Michael Bartlett" content="Michael Bartlett" lang="en">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="csci445.css" />
    <style>
    body {
        text-align: center;
    }
    </style>
</head>
<?php include 'templateHeader.php';?>
<body>
    <section>
        <h2>Hello!</h2>
            <h4>Howdy, welcome to my static website for CSCI445! Everything is meticulously tethered together with duplicate code, but at least that's less expense to render!</h4>
            <h4> This is in an aside tag! </h4>
    </section>
    <hr />
    <?php include 'templateFooter.php';?>
</body>

</html>
