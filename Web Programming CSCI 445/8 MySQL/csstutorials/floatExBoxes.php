<?php
$page = basename($_SERVER['PHP_SELF']);
?>


    <!DOCTYPE html>
    <html lang="en">

    <head>
        <meta charset="utf-8" />
        <link rel="stylesheet" type="text/css" href="floatExBoxes.css" />
        <title>Float Property</title>
        <link rel="stylesheet" type="text/css" href="../navbar.css" />
    </head>

    <body>
    <?php include '../templateHeader.php';?>
    

        <p><span class="big-letter">I</span>n this exercise, you will use nested boxes to explore float, margin, and padding. Using group selectors, make all outer boxes a total size of 200x200 pixels, and inner boxes a total size of 100x100 pixels. Give
            all boxes a dashed, 3px border. Float and spacing options will vary with each pair of boxes.</p>
        <p>Inner box is floated right, with a margin of 10px and padding of 20px</p>
        <div class="outer">
            This is the outer box.
            <div class="inner1">
                This is the inner box.
            </div>
        </div>

        <p>Inner box is floated left, with a margin of 10px and padding of 10px</p>
        <div class="outer">
            This is the outer box.
            <div class="inner2">
                This is the inner box.
            </div>
        </div>

        <p>Inner box is floated right, with a top margin of 40px, right margin of 0px and no padding</p>
        <div class="outer">
            This is the outer box.
            <div class="inner3">
                This is the inner box.
            </div>
        </div>
        <?php include '../templateFooter.php';?>


    </body>

    </html>