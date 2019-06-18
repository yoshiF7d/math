#include <SymbolList.h>
#include <SymbolTable.h>
Power::Power() : Symbol("Power","^",global_Power,590,Listable | NumericFunction | OneIdentity | Protected,right,"",""){}
void Power::printdoc(){printf(
	"                          x^y gives x to the power y.\n"
);}
