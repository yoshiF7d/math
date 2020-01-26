#include <SymbolList.h>
#include <SymbolTable.h>
Real::Real() : Symbol("Real","",global_Real,1000,Protected,0,"",""){}
Expr* Real::create(std::string string){
	Expr *expr = new Expr();
	expr->symbol = SymbolTable::get(global_Real);
	expr->data = new RealData(string);
	return expr;
}
Data* Real::createData(){return new RealData ();}
RealData::RealData(){
	initialized = false;
}
RealData::RealData(std::string string){
	initialized = true;
	#ifdef mpz
		this->real = string;
	#else
		this->real = std::stold(string);
	#endif
}
RealData::~RealData(){};
std::string RealData::toString(){
	if(initialized){
	#ifdef mpz
		return this->real.get_str();
	#else
		size_t needed = snprintf(NULL,0,"%g",this->real);
		char *buf = (char*)malloc(needed+1);
		snprintf(buf,needed+1,"%g",this->real);
		std::string string = buf;
		free(buf);
		return string;
	#endif
	}else{
		return SymbolTable::get(global_Real)->toString();
	}
}

void Real::printdoc(){printf(
	"                          Real is the head used for reals.\n"
);}
