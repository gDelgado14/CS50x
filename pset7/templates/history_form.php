
    <ul class="nav nav-pills">
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
    
    <!-- $positions is an array of associative array - each of which contains portfolio info !-->
    
    <table class="table">
        <thead>
            <tr>
                <th>Purchase</th>
                <th>Symbol</th>
                <th>Shares</th>
                <th>Price / Share</th>
                <th>Transaction Date</th>
            </tr>
        </thead>
        <tbody align="left">
        
        
        <?php foreach ($rows as $row): ?>
                
                    <td><?= $row["transaction"] ?></td>
                    <td><?= $row["symbol"] ?></td>
                    <td><?= $row["shares"] ?></td>
                    <td>$<?= number_format($row["price"],4) ?></td>
                    <td><?= $row["date"] ?></td>
                </tr>
                   
        <?php endforeach ?>

        
        </tbody>
        
    </table>
    
