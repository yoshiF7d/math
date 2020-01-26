#include <SymbolList.h>
#include <SymbolTable.h>
Less::Less() : Symbol("Less","<=",global_Less,290,Protected,none,"",""){}
void Less::printdoc(){printf(
	"                          x <= y yields True if x is determined to be less than or equal to y.\n"
	"                          x_1 <= x_2 <= x_3 yields True if the x_i form a nondecreasing sequence.\n"
);}
