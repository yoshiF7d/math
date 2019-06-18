#include <SymbolList.h>
#include <SymbolTable.h>
LessEqual::LessEqual() : Symbol("LessEqual","<",global_LessEqual,290,Protected,0,"",""){}
void LessEqual::printdoc(){printf(
	"                          x < y yields True if x is determined to be less than y.\n"
	"                          x_1 < x_2 < x_3 yields True if the x_i form a strictly increasing sequence.\n"
);}
