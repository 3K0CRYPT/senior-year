<?php
$thisPage = "Home"
echo "Dir: " . __DIR__ . "<br>"; // Displays: Line number 2
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
    <footer>&copy; Am I even allowed to copyright this? Either way, I listed my e-mail above if you have complaints!
        <p>
        <img src="./images/css3-blue.png" alt="css3-blue.png" width="50" height="18">
        <img src="./images/html5-blue.jpg" alt="html5-blue.png" width="50" height="18">
        <img src="./images/wcag2AAA-blue.png" alt="wcag2AAA-blue.png" width="50" height="18">
        </p>
    </footer>
</body>

</html>