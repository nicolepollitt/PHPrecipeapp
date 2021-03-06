<?php

$config = parse_ini_file('config.php');

$db = pg_connect("host={$config['host']} port={$config['port']} user={$config['user']} password={$config['password']} dbname={$config['dbname']}");

function getAll(){
    $res = pg_query_params('SELECT r.*,c.name AS category FROM recipes r,categories c WHERE ("hide"=false OR "hide" IS NULL) AND r.category=c.id ORDER BY c.name,r.name',Array());
    return $res;
}

function getUnits(){
    $res = pg_query("SELECT id,name FROM units ORDER BY name");
    $rows = Array();
    while($row = pg_fetch_assoc($res)){
        $rows[] = $row;
    }
    return $rows;
}

function getAllFromCategory($cat){
    $res = pg_query_params('SELECT r.*,c.name AS category FROM recipes r,categories c WHERE ("hide"=false OR "hide" IS NULL) AND r.category=c.id AND c.name=$1 ORDER BY c.name,r.name',Array($cat));
    return $res;
}

function getQuick(){
    $res = pg_query_params('SELECT r.*,c.name AS category,c.label as catlabel FROM recipes r,categories c WHERE ("hide"=false OR "hide" IS NULL) AND r.category=c.id AND r.quick=\'t\' ORDER BY c.name,r.name',Array());
    return $res;
}

function getFavorites(){
    $res = pg_query_params('SELECT r.*,c.name AS category,c.label as catlabel FROM recipes r,categories c WHERE ("hide"=false OR "hide" IS NULL) AND r.category=c.id AND r.favorite=\'t\' ORDER BY c.name,r.name',Array());
    return $res;
}


function getCategories(){
    $res = pg_query_params('SELECT DISTINCT 
        categories.*,
        COALESCE(categories.label,categories.name) AS label
        FROM
        categories, recipes
        WHERE categories.id=recipes.category
        AND (hide=false OR hide IS NULL)
        ORDER BY COALESCE(categories.label,categories.name)',Array());
    $rows = Array();
    while($row = pg_fetch_assoc($res)){
        $rows[] = $row; 
    }

    return $rows;
}

function getCategory($cat) {
    if(is_numeric($cat)){
        $res = pg_query_params('SELECT *,COALESCE(label,name) AS label FROM categories WHERE id=$1',Array($cat));
    }else{
        $res = pg_query_params('SELECT *,COALESCE(label,name) AS label FROM categories WHERE name=$1',Array($cat));
    }
    return pg_fetch_assoc($res);
}

function getMealIds(){
    $res = pg_query_params('SELECT DISTINCT ON (category) id
        FROM recipes
        WHERE hide=false
        ORDER BY category,RANDOM()',Array());

    $rows = Array();
    while($row = pg_fetch_assoc($res)){
        $rows[] = $row['id'];
    }

    return $rows;
}

function getUnit($id){
    $res = pg_query_params("SELECT * FROM units WHERE id=$1",Array($id));
    return pg_fetch_assoc($res);
}

function getIngredient($id){
    $res = pg_query_params("SELECT * FROM ingredients WHERE id=$1",Array($id));
    return pg_fetch_assoc($res);
}

function getIngredientIdByIdOrName($ingId){
    if(is_numeric($ingId)){
        return $ingId;
    }
    
    $res = pg_query_params("SELECT id FROM ingredients WHERE name=$1",Array($ingId));
    $assoc = pg_fetch_assoc($res);
    if(isset($assoc['id'])){
        return $assoc['id'];
    }

    return FALSE;
}

function getAllIngredients(){
    $res = pg_query_params("SELECT i.name AS ingredient,COUNT(r.recipe_id) AS count
        FROM 
        ingredients i 
        LEFT JOIN recipe_ingredient r ON (r.ingredient_id=i.id)
        GROUP BY i.name
        ORDER BY name",Array());
    return $res;
}

function getRecipesByIngredient($ingredientName){
    $res = pg_query_params('
        SELECT 
        r.*,
        c.name AS catecory,
        c.label as catlabel 
        FROM 
        recipes r, 
        categories c, 
        pretty_ingredients pi,
        ingredients i
        WHERE 
        i.name=$1 AND
        pi.recipe_id=r.id AND
        c.id=r.category AND 
        pi.ingredient_id=i.id
        ',Array($ingredientName));
    return $res;
}

function search($term){
    $res = pg_query_params('SELECT * FROM search WHERE search ILIKE $1',Array('%' . $term . '%'));
    return $res;
}

function typeAhead($table,$q){
    $res = pg_query_params('SELECT id,name FROM ' . $table . ' WHERE name ILIKE $1',Array('%' . $q . '%'));

    $rows = Array();
    while($row = pg_fetch_assoc($res)){
        $rows[] = $row;
    }

    return $rows;
}
