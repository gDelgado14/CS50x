
    <ul class="nav nav-pills">
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
    
    
<table class="table">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Shares To Sell</th>
        </tr>
    </thead>
    
    <tbody align="left">

        <tr>
            <form action="sell.php" method="post">
                <fieldset>
                    <td>
                    <div class="form-group">
                        <select class="form-control" name="symbol">
                            <option value=""> </option>
                            <?php foreach ($positions as $position): ?>
                            
                                <option value = "<?= $position['symbol'] ?>"> <?= $position["symbol"] ?> </option>
                         
                            <?php endforeach ?>
                         </select>   
                    </div>
                    </td>
                    
                    <td>
                        <input autofocus class="form-control" name="shares" placeholder="# shares" type="text"/>    
                    </td>  
             
                 </tr>
             </tbody>
        </table>
     
    <div class="form-group">
        <button type="submit" class="btn btn-default">Sell</button>
    </div>

    </fieldset>
</form>

