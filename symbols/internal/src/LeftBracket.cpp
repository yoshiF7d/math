#include <SymbolList.h>
#include <SymbolTable.h>
LeftBracket::LeftBracket() : Symbol("LeftBracket","",internal_LeftBracket,1000,Protected,0,"",""){}
Data* LeftBracket::createData(){return new LeftBracketData ();}
LeftBracketData::LeftBracketData() : expr(nullptr){};
LeftBracketData::~LeftBracketData(){};
bool LeftBracketData::operator ==(const Data& data){
	return this->expr == static_cast<const LeftBracketData&>(data).expr;
};
std::string LeftBracketData::toString(){
	std::string str;
	if(this->expr){
		str = "Left ";
	    str += this->expr->toString();
	}else{
		str="LeftBracket";
	}
	return str;
}

