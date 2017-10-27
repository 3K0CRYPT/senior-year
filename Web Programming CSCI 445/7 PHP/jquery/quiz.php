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
                <a href="../javascript/jsmouse.html">JS Mouse</a>
                <a href="../javascript/jskeyboard.html">JS Keyboard</a>
            </div>
        </li>
        <li class="dropdown">
            <span>jQuery</span>
            <div class="dropdown-content">
                <a href="javascript:void(0)" class="active">Quiz</a>
            </div>
        </li>
    </ul>
    <header>
        <h1 id="aboutme">Michael Bartlett's CSCI445 Website</h1>
    </header>
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

    <footer>&copy; Am I even allowed to copyright this? Either way, I listed my e-mail above if you have complaints!
        <p>
            <img src="../images/css3-blue.png" alt="css3-blue.png" width="50" height="18">
            <img src="../images/html5-blue.jpg" alt="html5-blue.png" width="50" height="18">
            <img src="../images/wcag2AAA-blue.png" alt="wcag2AAA-blue.png" width="50" height="18">
        </p>
    </footer>



</html>