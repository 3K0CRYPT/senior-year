<link rel="stylesheet" type="text/css" href="navbar.css" />
<ul id="navbar">
        <li><a href="javascript:void(0).html" class="active">Home</a></li>
        <?php if ($thisPage=="Home") echo " class=\"active\""; ?>
        <?php if ($thisPage=="Home") echo " href=\"javascript:void(0).html\""; else echo " href=\"index.php\""?>
        <li><a href="<?php echo __DIR__?>aboutme/aboutme.php">About Me</a></li>
        <li class="dropdown">
            <span>CSS Tutorials</span>
            <div class="dropdown-content">
                <a href="./csstutorials/turtlecoders.html">Turtle Coders</a>
                <a href="./csstutorials/posEx.html">posEx</a>
                <a href="./csstutorials/floatExBoxes.html">floatExBoxes</a>
                <a href="./csstutorials/clearEx.html">clearEx</a>
            </div>
        </li>
        <li class="dropdown">
            <span>Javascript</span>
            <div class="dropdown-content">
                <a href="javascript/jsmouse.php">JS Mouse</a>
                <a href="javascript/jskeyboard.php">JS Keyboard</a>
            </div>
        </li>
        <li class="dropdown">
            <span>jQuery</span>
            <div class="dropdown-content">
                <a href="./jquery/quiz.php">Quiz</a>
            </div>
        </li>
    </ul>
    <header>
        <h1 id="aboutme">Michael Bartlett's CSCI445 Website</h1>
    </header>
