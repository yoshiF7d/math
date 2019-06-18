#include <SymbolList.h>
#include <SymbolTable.h>
Number::Number() : Symbol("Number","",global_Number,670,Protected,0,"",""){}
Expr* Number::parse(std::string::iterator *current){
	std::string::iterator it,save,iend;
	it = save = iend = *current;
	Expr *expr;
	if(isdigit(*it)){
		if(*it=='0'){
			if(isdigit(*++it)){
				goto nonum;
			}else{
				goto num;
			}
		}
	}else{goto nonum;}
	while(isdigit(*it)){it++;}
  num:
	iend = it;
	if(*it=='.'){it++;}
	else{
		if(*it=='e' || *it=='E'){
			it++;
			if(*it=='+'){
				it++;
				if(isdigit(*it)){
					*current = it; while(*it){it++;}
					expr = Integer::create(
						std::stoi(std::string(save,iend)),
						std::stoi(std::string(*current,it))
					);
					goto end;
				}
			}else if(*it=='-'){
				it++;
				if(isdigit(*it)){
					*current = it; while(*it){it++;}
					expr = Real::create(std::string(save,it));
					goto end;
				}
			}else if(isdigit(*it)){
				*current = it; while(*it){it++;}
				expr = Integer::create(
					std::stoi(std::string(save,iend)),
					std::stoi(std::string(*current,it))
				);
				goto end;
			}
		}
		expr = Integer::create(std::string(save,iend));
		it = iend;
		goto end;
	}
	while(isdigit(*it)){it++;}
	expr = Real::create(std::string(save,it));
	goto end;
  nonum:
	if(*it=='.'){
		if(isdigit(*++it)){
			while(isdigit(*it)){it++;}
			expr = Real::create(std::string(save,it));
			goto end;
		}
	}
	it = save;
	expr = nullptr;
  end:
	*current = it;
	return expr;
}
void Number::printdoc(){printf(
	"                          Number represents an exact integer or an approximate real number in Read.\n"
);}
