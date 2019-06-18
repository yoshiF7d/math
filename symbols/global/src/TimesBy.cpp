#include <SymbolList.h>
#include <SymbolTable.h>
TimesBy::TimesBy() : Symbol("TimesBy","*=",global_TimesBy,100,HoldFirst|Protected,left,"",""){}
void TimesBy::printdoc(){printf(
	"                          x*=c multiplies x by c and returns the new value of x.\n"
);}
