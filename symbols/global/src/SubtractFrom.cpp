#include <SymbolList.h>
#include <SymbolTable.h>
SubtractFrom::SubtractFrom() : Symbol("SubtractFrom","-=",global_SubtractFrom,100,HoldFirst|Protected,left,"",""){}
void SubtractFrom::printdoc(){printf(
	"                          x-=dx subtract dx from x and returns the new value of x.\n"
);}
