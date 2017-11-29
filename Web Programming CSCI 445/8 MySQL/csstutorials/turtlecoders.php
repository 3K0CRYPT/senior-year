<?php
$page = basename($_SERVER['PHP_SELF']);
?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <meta charset="utf-8" />
        <link rel="stylesheet" type="text/css" href="turtlecoders.css" />
        <link rel="icon" href="favicon.ico" type="image/x-icon">
        <title>Turtle Coders, Inc.</title>
        <link rel="stylesheet" type="text/css" href="../navbar.css" />
    </head>

    <body>
    <?php include '../templateHeader.php';?>
        <div id="wrapper">
            <header>
                <h1>Turtle Coders Inc</h1>
            </header>
            <nav>
                <a href="#">Home</a>
                <a href="#">Services</a>
                <a href="#">Contact</a>
            </nav>
            <div id="content">
                <h2>Web Pages and More!</h2>
                <p id="intro"><span class="company_name">Turtle Coders Inc.</span> will create a righteous website just for you. We offer the following:</p>
                <ul id="services">
                    <li>Website Design</li>
                    <li>Interactive Animation</li>
                    <li>E-Commerce Solutions</li>
                    <li>Usability Studies</li>
                    <li>Search Engine Optimization</li>
                </ul>
                <h2>Recent Customers</h2>
                <p>We have lots of happy customers!</p>
                <ul>
                    <li>Porky Pig</li>
                    <li>Donald Duck</li>
                </ul>
                <p class="motto"><span class="company_name">Turtle Coders Inc.</span> We're slow, but what's the rush?</p>
            </div>
        </div>
        <?php include '../templateFooter.php';?>


    </body>

    </html>