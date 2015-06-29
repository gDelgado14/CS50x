<?php
    
    // controller for selling stocks
    
    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        $stock = lookup($_POST["symbol"]);
        
        if (!$stock)
        {
            apologize("Please enter a correct symbol.");
        }
        
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must provide a number of shares.");
        }
        else if (! preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Please enter a positive integer.");
        }
        
        
        $price = $stock["price"];
        
        $cost = $_POST["shares"] * $price;
        
        $user = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        
        
        if ($cost > $user[0]["cash"])
        {
            apologize("You need more money, honey.");
        }
        else
        {
            // update the holdings from 'portfolios'
            query("INSERT INTO portfolios (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);     
            
            // add proceeds to 'users'
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
            
            query("INSERT INTO history (transaction, symbol, shares, price, date, id) VALUES('buy', ?, ?, ?, now(), ?)", strtoupper($_POST["symbol"]), $_POST["shares"], $price, $_SESSION["id"]); 
        }
        
        redirect('/');
    
        
    }
    else
    {
    
        //each position is an array of rows (rows containing each owned stock's info)
        $positions = [];
        
        //info for each equity in portfolio
        $rows = query("SELECT * FROM portfolios WHERE id = ?", $_SESSION["id"]);
        
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            
            if ($stock !== false)
            {
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"]
                ];
            }
        }

        // render portfolio
        render("buy_form.php", ["title" => "Buy stock"]);

    }
?>


