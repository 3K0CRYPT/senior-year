<?php
$page = basename($_SERVER['PHP_SELF']);
?>


    <!DOCTYPE html>
    <html lang="en">

    <head>
        <meta charset="utf-8" />
        <link rel="stylesheet" type="text/css" href="posEx.css" />
        <title>Positioning</title>
        <link rel="stylesheet" type="text/css" href="../navbar.css" />
    </head>

    <body>
    <?php include '../templateHeader.php';?>
        <h1>This is a silly example</h1>
        <div id="sidebar">
            <p>Keep me in my place!</p>
        </div>
        <p>This text is shy... I'm hiding behind the sidebar.</p>
        <div class="not-important">
            <p>This is just a random stream of consciousness. Not very important. Don't you hate it when people ramble on and on and on...</p>
        </div>
        <div class="more-important">
            <p>I wanted to provide a bit more context. Stream of consciousness occurs in early Buddhist scriptures. From this they developed an entire theory of mind.</p>
        </div>
        <!-- random text so that you can see the fixed position -->
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <p>Some text</p>
        <div class="important">
            <p>It's important to have some knowledge of CSS positioning. But you will <em>not</em> be an expert after just a few simple examples!</p>
        </div>
        <?php include '../templateFooter.php';?>


    </body>

    </html>