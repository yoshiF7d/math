#include <SymbolList.h>
#include <SymbolTable.h>
RightBracket::RightBracket() : Symbol("RightBracket","",internal_RightBracket,1000,Protected,0,"",""){}
Data* RightBracket::createData(){return new RightBracketData ();}
RightBracketData::RightBracketData() : expr(nullptr){};
RightBracketData::~RightBracketData(){if(expr){delete expr;expr=nullptr;}};
bool RightBracketData::operator ==(const Data& data){
	return this->expr == static_cast<const RightBracketData&>(data).expr;
};
std::string RightBracketData::toString(){
	std::string str;
	if(this->expr){
		str = "Right ";
		str += this->expr->toString();
	}else{
		str="RightBracket";
	}
	return str;
	}


