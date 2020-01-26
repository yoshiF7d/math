#include <SymbolList.h>
#include <SymbolTable.h>
Greater::Greater() : Symbol("Greater",">",global_Greater,290,Protected,none,"",""){}
void Greater::printdoc(){printf(
	"                          x > y yields True if x is determined to be greater than y.\n"
	"                          x_1 > x_2 > x_3 yields True if the x_i form a strictly decreasing sequence.\n"
);}
