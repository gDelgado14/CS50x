
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
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>Total</th>
            </tr>
        </thead>
        <tbody align="left">
        
        <?php $total = 0 ?>
        
        <?php foreach ($positions as $position): ?>
                
                <tr>
                    <td><?= $position["symbol"] ?></td>
                    <td><?= $position["name"] ?></td>
                    <td><?= $position["shares"] ?></td>
                    <td>$<?= number_format($position["price"],4) ?></td>
                    <td>$<?= number_format($position["shares"] * $position["price"],2) ?></td>
                </tr>
                
             <?php $total += $position["shares"] * $position["price"] ?>
             
            <?php endforeach ?>
        <tr>    
            <td colspan="4">TOTAL EQUITY</td>
            <td> $<?= number_format($total,2) ?></td>
        </tr>
        <tr>
            <td colspan="4">CASH</td>
            <td> $<?=number_format(100000 - $total,2) ?></td>
        </tr>
        
        </tbody>
        
    </table>
    
