<?php

// prevents multiple definitions
if( !defined('__XMLREADER__'))
{
  define('__XMLREADER__', 1);
   
   class myXMLReader   // fyi: use keyword 'extends' to specify inheritance 
   {
      // variable types are dynamic 
      var $xml_parser;
      var $parsed_array;
      var $file_pointer;
      var $inventory;  
      var $n_items;
      
      // class constructor v4.x
      function XMLReader()
      {
         // initialize local variables  
         $this->xml_parser = null;       
         $this->parsed_array = array();   // arrays are associative
         $this->file_pointer = null;
      }
      
      // open file and create a parser object and parser event handlers
      function Load($filename)
      {
         $this->xml_parser = xml_parser_create();
        
         // this is messy since in a class 
         xml_set_element_handler($this->xml_parser, 
                                 array(&$this, "XML_startElement"),
                                 array(&$this, "XML_endElement") );
         
         if( !($this->file_pointer = fopen($filename, 'r')) )
         {
            die("could not open XML input");
         }
      }

      // parse the file and call the event handler for each token 
      function ParseLoop() {

         $this->depth = array();
         $this->last_parser = -1;
         $this->n_items = 0;
         $this->current_item = null;

         // read 4096 bytes at a time
         while($data = fread($this->file_pointer, 4096))
         {
            // parse the file
            if(!xml_parse($this->xml_parser, $data, feof($this->file_pointer)) )
            {
               die(sprintf("XML error: %s at line %d",
               xml_error_string(xml_get_error_code($this->xml_parser)),
               xml_get_current_line_number($this->xml_parser)));
            }
         }
         xml_parser_free($this->xml_parser);
      }
      
      function XML_startElement($parser, $name, $attrs = '')
      {
         //echo "attrs = $attrs<br>\n";
         
         switch($name)
         {
            case 'INVENTORY':
               $this->parsed_array['inventory'] = array();
               $this->inventory = &$this->parsed_array['inventory'];
               break;
               
            case 'ITEM':
               $this->n_items++;
               $this->inventory[ $this->n_items ] = array();
               foreach($attrs as $key => $value)
               {
                $this->inventory[ $this->n_items ][ strtolower($key) ] = $value;
               }
               break;
         }
      }

     // print the entire array
      function PrintList() {
         print_r($this->parsed_array);   
         printf('number of items: %d',$this->n_items);
      }
      
     // this function must be present even if empty
     function XML_endElement($parser, $name) { }
      
      
   } // end class
   
} // end if def

?>
