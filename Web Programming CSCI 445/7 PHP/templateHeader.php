<link rel="stylesheet" type="text/css" href="/mbartlet/navbar.css" />
<ul id="navbar">
        <li><a <?php 
        if ($page=="index.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
        else echo " href=\"/mbartlet/index.php\"";
        ?>>Home</a></li>
        
        <li><a <?php 
        if ($page=="aboutme.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
        else echo " href=\"/mbartlet/aboutme/aboutme.php\"";
        ?>>About Me</a></li>
        
        <li class="dropdown">
            <span>CSS Tutorials</span>
            <div class="dropdown-content">
                <a <?php 
                if ($page=="turtlecoders.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
                else echo " href=\"/mbartlet/csstutorials/turtlecoders.php\"";
                ?>>Turtle Codes</a>

                <a <?php 
                if ($page=="posEx.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
                else echo " href=\"/mbartlet/csstutorials/posEx.php\"";
                ?>>posEx</a>
                
                <a <?php                 
                if ($page=="floatExBoxes.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
                else echo " href=\"/mbartlet/csstutorials/floatExBoxes.php\"";
                ?>>floatExBoxes</a>

                <a <?php 
                if ($page=="clearEx.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
                else echo " href=\"/mbartlet/csstutorials/clearEx.php\"";
                ?>>clearEx</a>
            </div>
        </li>
        <li class="dropdown">
            <span>Javascript</span>
            <div class="dropdown-content">
            <a <?php 
                if ($page=="jsmouse.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
                else echo " href=\"/mbartlet/javascript/jsmouse.php\"";
                ?>>JS Mouse</a>    
                
            <a <?php 
                if ($page=="jskeyboard.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
                else echo " href=\"/mbartlet/javascript/jskeyboard.php\"";
                ?>>JS Keyboard</a>
            
            </div>
        </li>
        <li class="dropdown">
            <span>jQuery</span>
            <div class="dropdown-content">
            <a <?php 
                if ($page=="quiz.php") echo " href=\"javascript:void(0).html\" class=\"active\"";
                else echo " href=\"/mbartlet/jquery/quiz.php\"";
                ?>>Quiz</a>    
            </div>
        </li>
        <li class="dropdown">
            <span>PHP</span>
            <div class="dropdown-content">
            
            <a <?php 
                if ($page=="form.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
                else echo " href=\"/mbartlet/php/form.php\"";
                ?>>Form</a>    
                
            <a <?php 
                if ($page=="io.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
                else echo " href=\"/mbartlet/php/io.php\"";
                ?>>I/O</a>    
                
            <a <?php 
                if ($page=="vieworders.php") echo " href=\"javascript:void(0).html\" class=\"active\"";  
                else echo " href=\"/mbartlet/php/vieworders.php\"";
                ?>>View Orders</a>    
                    
            </div>
        </li>
    </ul>
    <header>
        <h1 id="aboutme">Michael Bartlett's CSCI445 Website</h1>
    </header>
