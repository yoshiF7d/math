#include <SymbolTable.h>
#include <Expr.h>
#include <cctype>

int isint(char **str){
	char *p=*str;
	int rtn=0;
	
	if(isdigit(*p)){
		if(*p=='0'){
			if(isdigit(*++p)){
				rtn=0; goto end;
			}else{
				rtn=1; goto end;
			}
		}
	}else{goto end;}
	while(isdigit(*p)){p++;}
	rtn=1;
  end:
	if(rtn){
		*str = p; 
	}
	return rtn;
}

int isexp(char **str){
	char *p=*str;
	int rtn=0;
	int minus=0;
	
	if(*p=='e' || *p=='E'){
		p++;
		if(*p=='-' || *p=='+'){
			if(*p=='-'){minus=1;}
			p++;
			if(isdigit(*p)){
				goto mid;
			}
		}else if(isdigit(*p)){
			goto mid;
		}
	}
	rtn=0;
	goto end;
  mid:
	while(isdigit(*p)){p++;}
	if(minus){rtn=2;}
	else{rtn=1;}
	goto end;
  end:
	if(rtn){
		*str = p;
	}
	return rtn;
}

int isnum(char **str){
	char *p=*str;
	int rtn=0,e;
	
	if(isint(&p)){
		if(*p=='.'){rtn=2;p++;}
		else{rtn=1;}
	}else if(*p=='.'){
		if(!isdigit(*++p)){goto end;}
		else{rtn=2;}
	}
	while(isdigit(*p)){p++;}
  end:
	if(rtn){
		*str = p;
		e=isexp(str);
		if(rtn==1){
			if(e==1){rtn=3;}
			else if(e==2){rtn=2;}
		}
	}
	return rtn;
}

int issymbol(char **str){
	char *p = *str, rtn=0;
	
	for(;;){
		if(*p & 0x80){
			rtn=2; while(*p & 0x80){p++;}
		}else if(isalpha(*p)){/*<- isalpha ALPHABET ONLY*/
		  read:
			rtn=1; while(isalnum(*p)){p++;}  /*<- isalnum ALPHABET OR NUMBER*/
		}else if(rtn==2){
			if(isalnum(*p)){goto read;}
			break;
		}else if(rtn==0){
			return 0;
		}else{
			break;
		}
	}
	*str=p; 
	return 1;
}

class Tokenizer{
  public:
	Expr *optree;
	Tokenizer(){
		this->optree = nullptr;
		Expr *last,*e;
		int i;
		list<Context> context = SymbolTable::context;
		
		this->optree = last = new Expr(internal_Node);
		for(auto&& c : context){
			for(auto&& t: c.second){
				if(t.second->sign){
					for(last=this->optree,i=0;;){
						for(e=last->child;e;e=e->next){
							if(e->data.letter == (t.second->sign)[i]){
								last = e;
								goto loopend;
							}
						}
						last->appendChild(e= new Expr(internal_Node));
						e->data.letter = (t.second->sign)[i];
						last = e;
						loopend:
						i++;
						if((t.second->sign)[i]=='\0'){break;}
					}
					last->appendChild(new Expr(t.second));
				}
			}
		}
	}
	
}
