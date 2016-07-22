<?php
//comment
require_once('lib/template.php');
printHeader('Favorite Recipes!','favorite');
?>
<div class="jumbotron">
<h1>Favorite Recipes!<?=$favoriteicon?></h1>
</div>
<div class="container">
<?php

$prevCat = '';
$res = getFavorites();
while($row = pg_fetch_assoc($res)){
    if($row['catlabel'] !== $prevCat){
        if($prevCat !== ''){
            print "</ul>";
        }

        $prevCat = $row['catlabel'];
        print "<h2>" . htmlentities($prevCat) . "</h2>";
        print "<ul class='recipelist'>";
    }

    print "<li><a href='../recipe/" . urlencode($row['name']) . "' alt='{$row['name']}'>{$row['name']}</a>".($row['quick'] == 't' ? $quickicon : '') . ($row['favorite'] == 't' ? $favoriteicon : '')."</li>";
}

print "</ul></div>";

printFooter();
