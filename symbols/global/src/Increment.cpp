#include <SymbolList.h>
#include <SymbolTable.h>
Increment::Increment() : Symbol("Increment","++",global_Increment,660,HoldFirst|Protected|ReadProtected,post,"",""){}
void Increment::printdoc(){printf(
	"                          x++ increses the value of x by 1, returning the old value of x.\n"
);}
