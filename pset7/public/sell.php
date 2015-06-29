<?php
    
    // controller for selling stocks
    
    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        //info for each equity in portfolio
        $row = query("SELECT * FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        
        //print_r ($row);
        
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must provide a number of shares.");
        }
        else if (! ctype_digit ($_POST["shares"]))
        {
            apologize("Please enter an integer.");
        }
        else if ($_POST["shares"] < 0 || $_POST["shares"] > $row[0]["shares"])
        {
            apologize("Provide a correct number of shares.");
        }
        
        $share_info = lookup($row[0]["symbol"]);
        $price = $share_info["price"];
        $sale = $_POST["shares"] * $price;
        
        if ($_POST["shares"] == $row[0]["shares"])
        {
            // delete the holdings from 'portfolios'
            query("DELETE FROM portfolios WHERE id = ? AND symbol = ?",$_SESSION["id"], $row[0]["symbol"]);
            
            // add proceeds to 'users'
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $sale, $_SESSION["id"]);

        }
        else if ($_POST["shares"] > $row[0]["shares"])
        {
            apologize("You ain't got that many shares, son.");
        }
        else // if less than
        {
            // update the holdings from 'portfolios'
            query("UPDATE portfolios SET shares = shares - ? WHERE id = ? AND symbol = ?", $_POST["shares"], $_SESSION["id"], $row[0]["symbol"]);
            
            // add proceeds to 'users'
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $sale, $_SESSION["id"]);
            
            
        }
        
        query("INSERT INTO history (transaction, symbol, shares, price, date, id) VALUES('sell', ?, ?, ?, now(), ?)", strtoupper($_POST["symbol"]), $_POST["shares"], $price, $_SESSION["id"]);
        
        
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
        render("sell_form.php", ["positions" => $positions, "title" => "Sell"]);
    
    }
?>
