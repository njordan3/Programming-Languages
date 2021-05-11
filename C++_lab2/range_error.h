/*
  Filename: range_error.h
  Purpose: a RangeError exception class 
*/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const unsigned FileNameSize = 40;

//out of range subscript exception class
class RangeError {
  // added funcName to output
  friend ostream & operator <<( ostream & os, const RangeError & err )
  { 
    os << "RangeError exception thrown, file: "
       << err.fileName
       << ", function: " << err.funcName
       << ", lineno: " << err.lineNumber
       << ", index: " << err.value
       << endl;
       return os;
  }

  public:
    // added funcName to constructor
    RangeError( const char* file, const char* func, int line, int subscr )
    {
      strcpy(fileName, file);
      strcpy(funcName, func);
      lineNumber = line;
      value = subscr;
    }
   
    // a standard method for all range error classes  -- returns error type
    const char * what () const
    {  
       return "RangeError Exception";
    }
    
  private:
    // added funcName to definition
    char funcName [50];                 // __FUNC__
    char fileName [FileNameSize + 1];   // __FILE__
    int lineNumber;                     // __LINE__
    int value;                          // the out-of-range index 
};

#endif
