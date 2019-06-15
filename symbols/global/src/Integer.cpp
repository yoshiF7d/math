#include <SymbolList.h>
#include <SymbolTable.h>
Integer::Integer() : Symbol("Integer","",global_Integer,1000,Protected,0,"",""){}
Expr *Integer::create(std::string string){
	Expr *expr = new Expr(global_Integer);
	expr->data = new IntegerData(string);
	return expr;
}
Expr *Integer::create(int integer){
	Expr *expr = new Expr(global_Integer);
	expr->data = new IntegerData(integer);
	return expr;
}
Expr *Integer::createExp(std::string string){
	Expr *expr = new Expr(global_Integer);
	expr->data = IntegerData::IntegerDataExp(string);
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

IntegerData* IntegerData::IntegerDataExp(std::string string){
	int sav,isav;
	int i,e;
	
	IntegerData *data = new IntegerData();
	
	for(i=0;i<string.size();i++){
		if(string[i]=='e' || string[i]=='E'){
			isav=i; sav=string[i]; string[i]='\0';
			i++;
			if(string[i]=='+'){i++;}
			break;
		}
	}
	if(i<string.size()){e=std::stoi(string.substr(i));}
	else{e=1;}
	#ifdef mpz
		mpz_ui_pow_ui(data->integer.get_mpz_t(),10,e);
		data->integer *= mpz_class(string);
	#else
		data->integer = std::stoi(string)*pow(10,e);
	#endif
	string[i] = sav;
	return data;
}

std::string IntegerData::toString(){
	#ifdef mpz
		return this->integer.get_str();
	#else
		return std::to_string(this->integer);
	#endif
}
IntegerData::~IntegerData(){}

