
    <ul class="nav nav-pills">
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>

    <h1><?= htmlspecialchars($name) ?></h1>
    <h3>Symbol: <?= htmlspecialchars($symbol) ?></h3>
        
    <div id="sinfo">
        Last trade price: <strong>$<?= htmlspecialchars(number_format($price,4)) ?></strong><br>
        52-week low:      <strong>$<?= htmlspecialchars(number_format($yearLow,4)) ?></strong><br>
        52-week high:     <strong>$<?= htmlspecialchars(number_format($yearHigh,4)) ?></strong><br>
        Volume:           <strong><?= htmlspecialchars(number_format($vol,4)) ?></strong><br>
        <!--PE Ratio:         <strong>$<?= htmlspecialchars(number_format($pe,4)) ?></strong><br>!-->
    </div>


