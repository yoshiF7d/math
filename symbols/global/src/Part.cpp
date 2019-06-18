#include <SymbolList.h>
#include <SymbolTable.h>
Part::Part() : Symbol("Part","[[]]",global_Part,670,Locked|Protected,bracket,"",""){}
void Part::printdoc(){printf(
	"                          expr[[i]] or Part[expr,i] gives the ith part of expr.\n"
	"                          expr[[-i]] counts from the end.\n"
	"                          expr[[i,j,...]] or Part[expr,i,j,...] is equivalent to expr[[i]][[j]].... \n"
	"                          expr[[{i1,i2,...}]] gives a list of the parts i1, i2, ... of expr. \n"
	"                          expr[[m;;n]] gives parts m through n.\n"
	"                          expr[[m;;n;;s]] gives parts m through n in steps of s.\n"
);}
