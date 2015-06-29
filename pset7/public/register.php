<?php
    
    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must provide password confirmation.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Please re-enter password correctly.");
        }
        
        $insert = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 100000.00)", $_POST["username"], crypt($_POST["password"]));
        
        // query database for users - initial cash balance is $100,000.00
        if ( $insert === false)
        {
            apologize("Username taken.");
        }
        
        // query database for user
        $rows = query("SELECT LAST_insert_ID() AS id");
        $id = $rows[0]["id"];
       
        // remember that user's now logged in by storing user's ID in session
        $_SESSION["id"] = $id;
        $_SESSION["username"] = $rows[0]["username"];

        // redirect to portfolio
        redirect("/");

        
        
    }
    else
    {
        //else render form
        render("register_form.php",["title" => "Register"]);
    }
    
?>
