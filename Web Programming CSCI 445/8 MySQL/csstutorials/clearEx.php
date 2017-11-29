<?php
$page = basename($_SERVER['PHP_SELF']);
?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <meta charset="utf-8" />
        <link rel="stylesheet" type="text/css" href="clearEx.css" />
        <title>Clear and Float Properties</title>
        <link rel="stylesheet" type="text/css" href="../navbar.css" />
    </head>

    <body>
    <?php include '../templateHeader.php';?>
    
        <h1>More fun with clear and float!</h1>
        <div class="div3">
            <img id="turtle_left" src="turtle2.gif" alt="turtle logo">
            <!-- notice the effect of overflow auto -->
            <p>Turtles are reptiles. They breathe air and eat plants, insects, snails, worms and sometimes dead marine animals. Ick! A group of turtles is known as a bale. They've been around for a long time (since the late Triassic Period of the Mesozoic
                era, about 220 million years ago). Wow!</p>
        </div>
        <br class="clear-it">
        <div class="div4">
            <img id="cat_right" src="crazycat.gif" alt="cat logo">
            <p>According to Wikipedia: Domestic cats use many vocalizations for communication, including purring, trilling, hissing, growling/snarling, grunting, and several different forms of meowing. By contrast, feral cats are generally silent.
            </p>
            <!-- what happens if this is just a break? -->
            <br class="clear-it">
        </div>
        <p>That is all, folks!</p>
        <?php include '../templateFooter.php';?>


    </body>

    </html>