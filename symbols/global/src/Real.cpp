#include <SymbolList.h>
#include <SymbolTable.h>
Real::Real() : Symbol("Real","",global_Real,1000,Protected,0,"",""){}
double Real::getDouble(Expr expr){
	return 0;
}
int Real::sign(Expr expr){
	return 0;
}
Expr *Real::create(std::string string){
	Expr *expr = new Expr(global_Real);
	getData(RealData,expr->data,real) = strtold(string.c_str(),NULL);
	return expr;
}
Data* Real::createData(){return new RealData ();}
RealData::~RealData(){};

