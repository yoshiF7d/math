#include <SymbolList.h>
#include <SymbolTable.h>
Times::Times() : Symbol("Times","*",global_Times,400,Flat | Listable | NumericFunction | OneIdentity | Orderless | Protected,none,"","{乗算}"){}
void Times::printdoc(){printf(
	"                          x*y*z or x y z represents a product of terms.\n"
);}
