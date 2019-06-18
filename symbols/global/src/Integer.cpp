#include <SymbolList.h>
#include <SymbolTable.h>
Integer::Integer() : Symbol("Integer","",global_Integer,1000,Protected,0,"",""){}
Expr *Integer::create(std::string string){
	Expr *expr = new Expr();
	expr->symbol = SymbolTable::get(global_Integer);
	expr->data = new IntegerData(string);
	return expr;
}
Expr *Integer::create(int integer){
	Expr *expr = new Expr();
	expr->symbol = SymbolTable::get(global_Integer);
	expr->data = new IntegerData(integer);
	return expr;
}
Expr *Integer::create(int integer,int e){
	Expr *expr = new Expr();
	expr->symbol = SymbolTable::get(global_Integer);
	expr->data = new IntegerData(integer,e);
	return expr;
}
Data* Integer::createData(){return new IntegerData ();}
IntegerData::IntegerData(){
	this->integer = 0;
}
IntegerData::IntegerData(std::string string){
	#ifdef mpz
		this->integer = string;
	#else
		this->integer = std::stoll(string);
	#endif
}
IntegerData::IntegerData(int integer){
	this->integer = integer;
}
IntegerData::IntegerData(long integer){
	this->integer = integer;
}

IntegerData::IntegerData(int integer, int e){
	#ifdef mpz
		mpz_ui_pow_ui(this->integer.get_mpz_t(),10,e);
		this->integer *= mpz_class(integer);
	#else
		this->integer = integer*pow(10,e);
	#endif
}

std::string IntegerData::toString(){
	#ifdef mpz
		return this->integer.get_str();
	#else
		return std::to_string(this->integer);
	#endif
}
IntegerData::~IntegerData(){}

void Integer::printdoc(){printf(
	"                          Integer is the head used for integers.\n"
);}
