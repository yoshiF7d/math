#include <parser.h>

Parser::Tokenizer::Tokenizer(){
	Expr *last,*e;
	Symbol *symbol;
	std::string *mark;
	list<Context> context = SymbolTable::context;
	this->optree = last = new Expr(internal_Node);
	
	for(auto&& c : context){
		for(auto&& t: c.second){
			symbol = t.second;
			if(symbol->mark){
				for(int i=0;i<2;i++){
					for(last=this->optree,int j=0;j<symbol->mark[i].length();last = e,j++){
						for(e=last->child;e;e=e->next){
							if(e->data.letter == symbol->mark[i][j]){
								goto loopend;
							}
						}
						last->appendChild(e = new Expr(internal_Node));
						e->data.letter = symbol->mark[i][j];
					  loopend:;
					}
					if(symbol->associativity==Associativity::bracket){
						if(i==0){
							last->appendChild(e = new Expr(internal_LeftBracket));
							e->data.expr = new Expr(symbol);
						}else{
							last->appendChild(e = new Expr(internal_RightBracket));
							e->data.expr = new Expr(symbol);
						}
					}else{
						last->appendChild(new Expr(symbol));
						break;
					}
				}
			}
		}
	}
}
Parser::Tokenizer::~Tokenizer(){
	this->optree->deleteRoot();
}

void Parser::Tokenizer::set(std::string string){
	this.string = string;
	this.current = this.string.begin();
}

bool Parser::Tokenizer::readint(){
	std::string::iterator it=current;
	if(isdigit(*it)){
		if(*it=='0'){
			if(isdigit(*++it)){
				return false;
			}else{
				goto end;
			}
		}
	}else{return false;}
	while(isdigit(*it)){it++;}
  end:
	current = it;
	return true;
}

ExpType Parser::Tokenizer::readexp(){
	std::string::iterator it=current;
	ExpType rtn;
	
	if(*it=='e' || *it=='E'){
		it++;
		if(*it=='+'){
			it++;
			if(isdigit(*it)){
				rtn = ExpType:Plus;
				goto end;
			}
		}else if(*it=='-'){
			it++;
			if(isdigit(*it)){
				rtn = ExpType:Minus;
				goto end;
			}
		}else if(isdigit(*it)){
			rtn = ExpType:Plus;
			goto end;
		}
	}
	return ExpType:False;
  end:
	while(isdigit(*it)){it++;}
	current = it;
	return rtn;
}

Expr* Parser::Tokenizer::readnum(){
	std::string::iterator it;
	std::string::iterator save = current;
	ExpType e;
	bool expcheck=false;
	bool isint=false;
	isint = readint();
	if(isint){
		if(*current=='.'){current++;}
		else{
			e = readexp();
			switch(e){
			  case ExpType::Plus:
				return Integer::createExp(std::string::string(save,current-1));
			  case ExpType::Minus:
				return new Real(std::string::string(save,current-1));
			  default:
				return new Integer(std::string::string(save,current-1));
			}
		}
	}else if(*current=='.'){
		if(!isdigit(*++current)){current = save; return nullptr;}
	}
	while(isdigit(*current)){current++;}
	return new Real(std::string::string(save,current-1));
}

Expr* Parser::Tokenizer::readsymbol(){
	std::string::iterator save = current;
	
	if(!isalpha(*current)){
		if(!(*current & 0x80)){current = save; return nullptr;} /*UTF*/
	}
	while(isalnum(*current || (*current & 0x80))){current++;}
	return new Expr(std::string::string(save,current-1));
}

Expr Parser::Tokenizer::readstring(){
	std::string::iterator save = current;
	std::string str;
	bool escape=false;
	
	if(*current!='"'){return nullptr;}
	for(current++;current!=string.end();current++){
		if(escape){
			switch(*current){
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
		}else if(*current=='\\'){
			escape = true;
			continue;
		}else if(*current=='"'){
			break;
		}else{
			str += *current;
		}
	}
	return new Expr(string::string(save,current-1));
}

Expr* Parser::Tokenizer::read(){
	Expr *expr;
	std::string::iterator save;
	while(isblank(*current)){current++;}
	if(current==string.end()){return nullptr;}
	save = current;
	if(expr=readsymbol()){return expr;}
	else if(expr=readnum()){return expr;}
	else if(expr=readstring()){return expr;}
	else if(optree){
		Expr *last=optree,*e;
	  head:
		for(e=last->child;e;e=e->next){
			if(e->symbol->id==internal_Node){
				if(e->data.letter==*current){
					last = e;
					current++;
					goto head;
				}
			}else{
				return e;
			}
		}
	}
	std::cout << __func__ << " unregistered token is found at " << current << std::endl;
	current = save;
	return nullptr;
}

Parser::Parser(){
	tokenizer = new Tokenizer();
	root = previous = current = end = nullptr;
}

Parser::~Parser(){
	delete tokenizer;
}

Parser::Parser(Tokenizer *tokenizer, Expr *end){
	this.tokenizer = tokenizer;
	this.end = end;
	root = previous = current = nullptr;
}

void set(std::string string){
	tokenizer->set(string);
	root = previous = current = nullptr;
}

void Parser::push(Expr *expr){
	Expr *dest;
	
	if(expr->symbol->precedence==1000 && 
	   expr->symbol->precedence==current->symbol->precedence
	   ){
		push(new Expr(global_Times));
		push(expr);
		return;
	}
	
	for(dest=current;dest;dest=dest->parent){
		if(expr->symbol->precedence
		   >= dest->symbol->precedence){
			break;
		}
		current = dest;
	}
	
	if(!dest){
		setRoot(expr->appendChild(current));
		return;
	}
	
	if(!AtomQ::mod(dest)){
		switch(dest->symbol->associativity){
		  case Associativity::left: /* a~b~c -> ~[~[a,b],c] */
			if(dest->symbol->precedence == expr->symbol->precedence){
				if(!dest->parent){setRoot(expr->appendChild(dest));}
				else{expr->insert(dest->parent,dest);current = expr;}
				goto end;
			}
			break;
		  case Associativity::none: /* a~b~c -> ~[a,b,c] */
			if(dest->symbol == expr->symbol){
				delete expr;
				expr = dest;
				return;
			}
			break;
		  case Associativity::post: /*a~b -> ~[a]*b*/
			if(dest==current && dest->child){
				current = new Expr(internal_Node);
				if(!dest->parent){setRoot(current->appendChild(dest));}
				else{current->insert(dest->parent,dest);}
				push(expr);
				return;
			}
			break;
		  case Associativity::binary: /* a~b~c -> ~[~[a,b],c]] */
			if(dest==current && dest->child){
				if(dest->child->next){
					current = new Expr(internal_Node);
					if(!dest->parent){setRoot(current->appendChild(dest));}
					else{current->insert(dest->parent,dest);}
					push(expr);
					return;
				}
			}
			break;
		  case right: /* a~b~c -> ~[a,~[b,c]] */
		  default:
			break;
		}
		expr->insert(dest,current);
	}
  end:
	previous = current;
	current = expr;
	return;
}

void Parser::pushToRoot(Expr *expr){
	if(!root){setRoot(expr);}
	else{root->append(expr);}
	previous=current;
	current = root;
}

void Parser::pushDirect(Expr *expr){
	if(!root){setRoot(expr);}
	else{
		current->appendChild(expr);
	}
	previous=current;
	current = expr;
}

void Parser::setRoot(Expr *expr){
	previous = current;
	root = current = expr;
}

Expr* Parser::parse(){
	Expr *expr;
	while(tokenizer->current != tokenizer->string.end()){
		expr = tokenizer->read();
		if(expr){
			if(AtomQ::mod(expr)){
				push(expr);
			}else if(expr->symbol->id == internal_LeftBracket){
				Parser parser(tokenizer,expr->data.expr);
				push(new Expr(*(expr->data.expr)));
				expr = parser.parse();
				if(expr){push(expr);}
				else{push(new Expr(internal_Null));}
			}else if(expr->symbol->associativity == Associativity::Separator){
				Parser parser(tokenizer,end);
				expr = parser.parse();
				if(expr){pushToRoot(expr);}
				else{pushToRoot(Expr(internal_Null));}
				break;
			}else if(expr->symbol->id == internal_RightBracket){
				if(end==expr->data.expr){
					break;
				}else{
				  std::cout << __func__ << " bracket mismatch : " << end->symbol->mark[0] << end->symbol->mark[1] << std::endl;
					/*ignore*/
				}
			}else if(root &&
					 previous->symbol->associativity == Associativity::post ||
					 previous->symbol->associativity == Associativity::bracket ||
					 previous->symbol->associativity == Associativity::separator 
					 ){
				for(Expr *e=expr;e;e=e->previous){
					if(e->symbol->id != id_Node && e->symbol->associativity!=Associativity::pre){
						expr=e; break;
					}
				}
				push(new Expr(*expr));
			}else{
				for(Expr *e=expr;e;e=e->previous){
					if(e->symbol->associativity == Associativity::pre){
						expr=e; break;
					}
				}
				push(new Expr(*expr));
			}
		}else{
			break;
		}
	}
	return root;
}


