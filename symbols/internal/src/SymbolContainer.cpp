#include <SymbolList.h>
#include <SymbolTable.h>
SymbolContainer::SymbolContainer() : Symbol("SymbolContainer","",internal_SymbolContainer,670,Protected,0,"",""){}
Expr* SymbolContainer::preEvaluate(Expr* expr){
	return unwrap(expr);
}
Expr* SymbolContainer::wrap(Expr* expr){
	delete expr->data;
	expr->data = new SymbolContainerData(expr->symbol);
	expr->symbol = SymbolTable::get(internal_SymbolContainer);
	return expr;
}
Expr* SymbolContainer::unwrap(Expr* expr){
	expr->symbol = castData(SymbolContainerData,expr->data)->symbol;
	delete expr->data;
	expr->data = expr->symbol->createData();
	return expr;
}
Data* SymbolContainer::createData(){return new SymbolContainerData ();}
SymbolContainerData::SymbolContainerData(Symbol* symbol){
	this->symbol = symbol;
}
std::string SymbolContainerData::toString(){
	std::string string;
	if(this->symbol){string=this->symbol->toString();}
	return string;
}
SymbolContainerData::~SymbolContainerData(){}

