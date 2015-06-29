<?php
    
    // file that's loaded by default when you visit a URL
    
    // configuration
    require("../includes/config.php"); 
    
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
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio"]);

?>
