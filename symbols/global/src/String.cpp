#include <SymbolList.h>
#include <SymbolTable.h>
String::String() : Symbol("String","",global_String,1000,Protected,0,"",""){}
Expr *String::parse(std::string::iterator *current,std::string::iterator end){
	std::string::iterator it,save;
	std::string str;
	it = save = *current;
	bool escape = false;
	if(*it!='"'){return nullptr;}
	for(it++;it!=end;it++){
		if(escape){
			switch(*it){
			  case '"':
				str += '"'; break;
			  case 'n':
				str += '\n'; break;
			  case '\t':
				str += '\t'; break;
			  case '\\':
				str += '\\'; break;
			}
			escape = false;
		}else if(*it=='\\'){
			escape = true;
			continue;
		}else if(*it=='"'){
			break;
		}else{
			str += *it;
		}
	}
	*current = it;
	return String::create(str);
}
Expr *String::create(std::string string){
	Expr *expr = new Expr();
	expr->symbol = SymbolTable::get(global_String);
	expr->data = new StringData(string);
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
std::string StringData::toString(){
	return this->string;
}

void String::printdoc(){printf(
	"                          String is the head of a character string \"text\" \n"
);}
