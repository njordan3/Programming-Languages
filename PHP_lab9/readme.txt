
GETTING STARTING WITH PHP 

The version of PHP on sleipnir is:
$ php --version
PHP 5.2.0-8+etch16 (cli) (built: Nov 24 2009 06:58:21) 
Copyright (c) 1997-2006 The PHP Group
Zend Engine v2.2.0, Copyright (c) 1998-2006 Zend Technologies

The default extension for PHP is '.php' and the apache web server on sleipnir 
is configured so that files with .php extension will be automatically handled 
by the PHP interpreter on sleipnir.

PHP files are server-side scripts. To test syntax use -l flag:

    $ php -l test.php           # will test for syntax only

To run a php script from the command line, make it executable and add this 
as the top line in the script:

     #!/usr/local/bin/php

Or use the -f extension:

     $ php -f test.php           # execute the script

A PHP file can include any valid HTML tags, but the actual PHP code must be 
enclosed in this tag:

   <?php
   ...
   ?>


To run a PHP script from a browser, your files must be in 'public_html'.
However, you can give your php files 700 permission. This means that no
one on sleipnir can see your code, yet it will be executed. This URL will run 
my test_web.php script:

   www.cs.csubak.edu/~donna/cs350/Code/PHP/test_web.php


