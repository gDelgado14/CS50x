<!DOCTYPE html>

<html>

    <head>
        <title>dump</title>
    </head>

    <body>
    <?
        $variable = $_SESSION["id"];
    ?>
        <pre><?php print_r($variable); ?></pre>
    </body>

</html>
