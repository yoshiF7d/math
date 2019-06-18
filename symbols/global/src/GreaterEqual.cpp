#include <SymbolList.h>
#include <SymbolTable.h>
GreaterEqual::GreaterEqual() : Symbol("GreaterEqual",">=",global_GreaterEqual,290,Protected,none,"",""){}
void GreaterEqual::printdoc(){printf(
	"                          x >= y yields True if x is determined to be greater than or equal to y.\n"
	"                          x_1 > x_2 > x_3 yields True if the x_i form a non-increasing sequence.\n"
);}
