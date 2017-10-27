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
    <ul id="navbar">
        <li><a href="../index.html">Home</a></li>
        <li><a href="../aboutme/aboutme.html">About Me</a></li>
        <li class="dropdown">
            <span>CSS Tutorials</span>
            <div class="dropdown-content">
                <a href="../csstutorials/turtlecoders.html">Turtle Coders</a>
                <a href="../csstutorials/posEx.html">posEx</a>
                <a href="../csstutorials/floatExBoxes.html">floatExBoxes</a>
                <a href="../csstutorials/clearEx.html">clearEx</a>
            </div>
        </li>
        <li class="dropdown">
            <span>Javascript</span>
            <div class="dropdown-content">
                <a href="javascript:void(0)" class="active">JS Mouse</a>
                <a href="./jskeyboard.html">JS Keyboard</a>
            </div>
        </li>
        <li class="dropdown">
            <span>jQuery</span>
            <div class="dropdown-content">
                <a href="../jquery/quiz.html">Quiz</a>
            </div>
        </li>
    </ul>
    <header>
        <h1 id="aboutme">Michael Bartlett's CSCI445 Website</h1>
    </header>
    <section>
        <h2>Canvas Mouse Demonstration</h2>
        <button style="margin:auto;" type="button">Draw yellow smiley!</button>
        <canvas id="canvas" height="500" style="border: 1px dashed red"></canvas>
    </section>
    <hr />
    <footer>&copy; Am I even allowed to copyright this? Either way, I listed my e-mail above if you have complaints!
        <p>
            <img src="../images/css3-blue.png" alt="css3-blue.png" width="50" height="18">
            <img src="../images/html5-blue.jpg" alt="html5-blue.png" width="50" height="18">
            <img src="../images/wcag2AAA-blue.png" alt="wcag2AAA-blue.png" width="50" height="18">
        </p>
    </footer>

</html>