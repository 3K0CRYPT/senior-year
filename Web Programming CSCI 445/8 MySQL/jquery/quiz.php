<?php
$page = basename($_SERVER['PHP_SELF']);
?>

<!DOCTYPE html >
<html lang="en">

<head>
    <title>Michael Bartlett jQuery</title>
    <meta charset="utf-8">
    <meta id="author" name="Michael Bartlett" content="Michael Bartlett" lang="en">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="../navbar.css" />
    <link rel="stylesheet" type="text/css" href="../csci445.css" />
    <link rel="stylesheet" type="text/css" href="quiz.css" />
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
    <script src="quiz.js"></script>
</head>

<body>
<?php include '../templateHeader.php';?>
    <hr />


    <aside>
        <p style="border-bottom: 1px black solid;">Answered</p>
        <div id="answered">
            <div>test</div>
            <div>test</div>
        </div>
    </aside>
    <section>
        <h2 id="Q">
            Actual question
        </h2>
        <footer id="buttons">
            <input id="T" type="radio"><label for="T">True</label>
            <input id="F" type="radio"><label for="F">False</label>
            <button id="answer"></button>
            <div id="questions"></div>
        </footer>
    </section>

    <?php include '../templateFooter.php';?>

    



</html>