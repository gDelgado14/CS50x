<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        $s = lookup($_POST["symbol"]);
        
        // if proper symbol then display
        if ($s != false)
        {
            render("quote_display.php", $s);
        }
        else
        {
            apologize("Symbol not valid");
        }
        
        
    }
    else
    {
        //else render form
        render("quote_form.php",["title" => "Get Quote"]);
    }



?>
