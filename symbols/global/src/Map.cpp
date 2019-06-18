#include <SymbolList.h>
#include <SymbolTable.h>
Map::Map() : Symbol("Map","/@",global_Map,620,Protected,right,"",""){}
void Map::printdoc(){printf(
	"                          Map[f,expr] or f/@expr applies f to each element on the first level in expr.\n"
	"                          Map[f,expr,levelspec] applies f to parts of expr specified by levelspec.\n"
);}
