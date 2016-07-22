Recipe Database
==========

A PHP / Postgres / Bootstrap recipe book.

You will need Wamp (Postgres, PHP and Apache with .htaccess / mod_rewrite enabled). 

1. Download the code to your web host.
2. Use the included db.sql file to set up your database. 
3. Copy lib/config.php.example to lib/config.php and edit the database connection values

The website should be set up at this point. You should have some categories and a working site
but no recipes or ingredients. 

You can use [LibreOffice Base](http://www.libreoffice.org/) and the included file, RecipeBook.odb, 
to add recipes to your site. LibreOffice Base is a little slow to start up, but once it has loaded
the forms it works pretty well. 

Note: Once a LibreOffice form is opened, dropdowns and linked field options are not re-populated. 
This means that if you forget to add an ingredient before adding a recipe, you'll need to close the 
recipe form, add the ingredient then re-open the recipe form to be able to select it in the list. 

License
-------

Licensed under the [MIT License](LICENSE.txt). Free for commercial or non-commercial use. 
