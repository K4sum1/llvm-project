//===-- llvm/assembly/Parser.h - Parser for VM assembly files ----*- C++ -*--=//
//
//  These classes are implemented by the lib/AssemblyParser library.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_ASSEMBLY_PARSER_H
#define LLVM_ASSEMBLY_PARSER_H

#include <string>

class Module;
class ToolCommandLine;
class ParseException;


// The useful interface defined by this file... Parse an ascii file, and return
// the internal representation in a nice slice'n'dice'able representation.
//
Module *ParseAssemblyFile(const ToolCommandLine &Opts) throw (ParseException);

//===------------------------------------------------------------------------===
//                              Helper Classes
//===------------------------------------------------------------------------===

// ParseException - For when an exceptional event is generated by the parser.
// This class lets you print out the exception message
//
class ParseException {
public:
  ParseException(const ToolCommandLine &Opts, const string &message, 
		 int LineNo = -1, int ColNo = -1);

  ParseException(const ParseException &E);

  // getMessage - Return the message passed in at construction time plus extra 
  // information extracted from the options used to parse with...
  //
  const string getMessage() const;

  inline const string getRawMessage() const {    // Just the raw message...
    return Message;
  }

  inline const ToolCommandLine &getOptions() const {
    return Opts;                           // Get the options obj used to parse.
  }

  // getErrorLocation - Return the line and column number of the error in the
  // input source file.  The source filename can be derived from the 
  // ParserOptions in effect.  If positional information is not applicable, 
  // these will return a value of -1.
  //
  inline const void getErrorLocation(int &Line, int &Column) const {
    Line = LineNo; Column = ColumnNo;
  }

private :
  const ToolCommandLine &Opts;
  string Message;
  int LineNo, ColumnNo;                               // -1 if not relevant

  ParseException &operator=(const ParseException &E); // objects by reference
};

#endif
