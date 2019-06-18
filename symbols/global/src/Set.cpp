#include <SymbolList.h>
#include <SymbolTable.h>
Set::Set() : Symbol("Set","=",global_Set,40,HoldFirst|Protected|SequenceHold,right,"",""){}
void Set::printdoc(){printf(
	"                          lhs = rhs evaluates rhs and assigns the result to be the value of lhs.\n"
	"                          From then on, lhs is replaced by rhs whenever it appears.\n"
	"                          {l1,l2,...} = {r1,r2,...} evaluates the ri, and assigns the results to be the values of the corresponding li.\n"
);}
