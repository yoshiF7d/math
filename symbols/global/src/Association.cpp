#include <SymbolList.h>
#include <SymbolTable.h>
Association::Association() : Symbol("Association","<||>",global_Association,670,HoldAllComplete|Protected,bracket,"",""){}
void Association::printdoc(){printf(
	"                          Association[key_1->val_1,key_2->val_2,...]<|key_1->val_1,key_2->val_2,...|> \n"
	"                          represents an association between keys and values.\n"
);}
