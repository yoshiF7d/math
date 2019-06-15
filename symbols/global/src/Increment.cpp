#include <SymbolList.h>
#include <SymbolTable.h>
Increment::Increment() : Symbol("Increment","++",global_Increment,660,HoldFirst|Protected|ReadProtected,post,"",""){}
