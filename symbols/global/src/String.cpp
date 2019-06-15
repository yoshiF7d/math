#include <SymbolList.h>
#include <SymbolTable.h>
String::String() : Symbol("String","",global_String,1000,Protected,0,"",""){}
Expr *String::create(std::string string){
	Expr *expr = new Expr(global_String);
	expr->data = new StringData(string);
	expr->next = nullptr;
	expr->previous = nullptr;
	expr->child = nullptr;
	expr->parent = nullptr;
	return expr;
}
Data* String::createData(){return new StringData ();}
StringData::StringData(){
	this->string = "";
}
StringData::StringData(std::string){
	this->string = string;
}
StringData::~StringData(){}

