<?php
    
    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        
        // validate submission
        if (empty($_POST["opswrd"]))
        {
            apologize("You must provide your old password.");
        }
        else if (empty($_POST["npswrd"]))
        {
            apologize("You must provide your new password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must provide password confirmation.");
        }
        else if ($_POST["npswrd"] != $_POST["confirmation"])
        {
            apologize("Please re-enter password correctly.");
        }
        
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $row = $rows[0];
        print_r($row);
        
        if (crypt($_POST["opswrd"], $row["hash"]) == $row["hash"])
        {
            $update = query("UPDATE users SET hash = ?", crypt($_POST["npswrd"]));
            
            // query database for users - initial cash balance is $100,000.00
            if ( $update === false)
            {
                apologize("password reset error.");
            }
        }
        else
        {
            apologize("incorrect old password.");
        }

        // redirect to portfolio
        redirect("/");
        
        
    }
    else
    {
        //else render form
        render("reset_form.php",["title" => "Reset Password"]);
    }
    
?>
