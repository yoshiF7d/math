#include <parser.h>
#include <Symbol.h>
#include <SymbolTable.h>
#define KNRM  "\x1B[0m"
#define KBLK  "\x1B[30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT "\x1B[37m"

Parser::Tokenizer::Tokenizer(){
	Expr *last,*e;
	Symbol *symbol;
	std::list<Context> context = SymbolTable::context;
	this->optree = last = new Expr(internal_Node);
	
	/*making operator tree*/
	
	/*example*/
	/*root -> + -> + -> Increment */
	/*          -> Plus           */
	/*     -> - -> - -> Decrement */
	/*          -> Minus          */
	/*     -> [ -> LeftBracket -> Function */
	/*     -> ] -> RightBracket -> Function */
	
	for(auto&& c : context){
		for(auto&& t: c.second){
			symbol = t.second;
			for(int i=0;i<2;i++){
				if(!(symbol->mark[i].empty())){
					int j=0;
					for(last=this->optree;j<symbol->mark[i].length();last = e,j++){
						for(e=last->child;e;e=e->next){
							if(e->symbol->id == internal_Character){
								if(getData(CharacterData,e->data,character) == symbol->mark[i][j]){
									goto loopend;
								}
							}
						}
						last->appendChild(e = new Expr(internal_Character));
						getData(CharacterData,e->data,character) = symbol->mark[i][j];
						  loopend:;
					}
					if(symbol->associativity==Associativity::bracket){
						if(i==0){
							last->appendChild(e = new Expr(internal_LeftBracket));
							getData(LeftBracketData,e->data,expr) = new Expr(symbol);
						}else{
							last->appendChild(e = new Expr(internal_RightBracket));
							getData(RightBracketData,e->data,expr) = new Expr(symbol);
						}
					}else{
						last->appendChild(new Expr(symbol));
						std::cout << KCYN << symbol->toString() << KNRM << "\n";
						break;
					}
				}
			}
		}
	}
	TreeForm::mod(this->optree);
	std::cout << std::endl;
}
Parser::Tokenizer::~Tokenizer(){
	this->optree->deleteRoot();
}

void Parser::Tokenizer::set(std::string string){
	this->string = string;
	this->current = this->string.begin();
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

Parser::Tokenizer::ExpType Parser::Tokenizer::readexp(){
	std::string::iterator it=current;
	ExpType rtn;
	
	if(*it=='e' || *it=='E'){
		it++;
		if(*it=='+'){
			it++;
			if(isdigit(*it)){
				rtn = ExpType::Plus;
				goto end;
			}
		}else if(*it=='-'){
			it++;
			if(isdigit(*it)){
				rtn = ExpType::Minus;
				goto end;
			}
		}else if(isdigit(*it)){
			rtn = ExpType::Plus;
			goto end;
		}
	}
	return ExpType::False;
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
			std::cout << std::string(save,current) << "\n";
			switch(e){
			  case ExpType::Plus:
				return Integer::createExp(std::string(save,current));
			  case ExpType::Minus:
				return Real::create(std::string(save,current));
			  default:
				return Integer::create(std::string(save,current));
			}
		}
	}else if(*current=='.'){
		if(!isdigit(*++current)){current = save; return nullptr;}
	}else{
		current = save; return nullptr;
	}
	while(isdigit(*current)){current++;}
	return Real::create(std::string(save,current));
}

Expr* Parser::Tokenizer::readsymbol(){
	std::string::iterator save = current;
	if(!isalpha(*current)){
		if(!(*current & 0x80)){current = save; return nullptr;} /*UTF*/
	}
	while(isalnum(*current) || (*current & 0x80)){current++;}
	return new Expr(std::string(save,current));
}

Expr* Parser::Tokenizer::readstring(){
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
	return new Expr(std::string(save,current));
}

Expr* Parser::Tokenizer::read(){
	Expr *expr;
	std::string::iterator save;
	while(isblank(*current)){current++;}
	if(current==string.end()){return nullptr;}
	save = current;
	if((expr=readsymbol())){
		std::cout << KMAG << "SYMBOL" << KNRM << "\n";
		return expr;
	}else if((expr=readnum())){
		std::cout << KMAG << "NUMBER" << KNRM << "\n";
		return expr;
	}else if((expr=readstring())){
		std::cout << KMAG << "STRING" << KNRM << "\n";
		return expr;
	}else if(optree){
		std::cout << KMAG << "ELSE" << KNRM << "\n";
		Expr *last=optree,*e;
	  head:
		for(e=last->child;e;e=e->next){
			if(e->symbol->id==internal_Character){
				if(getData(CharacterData,e->data,character)==*current){
					last = e;
					current++;
					goto head;
				}
			}else{
				expr = e;
			}
		}
		return expr;
	}
	std::cout << __func__ << " unregistered token " << *current << " is found" << std::endl;
	current = save;
	return nullptr;
}

Parser::Parser(){
	tokenizer = new Tokenizer();
	root = previous = current = nullptr;
	end = nullptr;
}

Parser::~Parser(){}

Parser::Parser(Tokenizer *tokenizer, Symbol *end){
	this->tokenizer = tokenizer;
	this->end = end;
	root = previous = current = nullptr;
}

void Parser::finish(){
	delete tokenizer;
	tokenizer = nullptr;
}

void Parser::set(std::string string){
	this->tokenizer->set(string);
	this->root = previous = current = nullptr;
}

void Parser::push(Expr *expr){
	Expr *dest;
	if(root){std::cout << "root symbol : " << root->symbol->name << "\n";}
	if(previous){std::cout << "previous symbol : " << previous->symbol->name << "\n";}
	if(current){std::cout << "current symbol : " << current->symbol->name << "\n";}
	if(expr){std::cout << "symbol : " << expr->symbol->name << "\n";}
	if(!current){setRoot(expr);return;}
	if(expr->symbol->precedence==1000 && 
	   expr->symbol->precedence==current->symbol->precedence
	   ){
	    if(expr->symbol->id==internal_Bracket){
			current->appendChild(expr);
			goto end;
		}else{
			push(new Expr(global_Times));
			push(expr);
			return;
		}
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
			if(root){std::cout <<KCYN << "Left"<< KNRM<<"\n";}
			if(dest->symbol->precedence == expr->symbol->precedence){
				if(!dest->parent){setRoot(expr->appendChild(dest));}
				else{expr->insert(dest->parent,dest);current = expr;}
				goto end;
			}
			break;
		  case Associativity::none: /* a~b~c -> ~[a,b,c] */
		    if(root){std::cout <<KCYN << "none"<< KNRM<<"\n";}
			if(dest->symbol == expr->symbol){
				delete expr;
				current = dest;
				return;
			}
			break;
		  case Associativity::post: /*a~b -> ~[a]*b*/
			if(root){std::cout <<KCYN << "post"<< KNRM<<"\n";}
			if(dest==current && dest->child){
				current = new Expr(global_Times);
				if(!dest->parent){setRoot(current->appendChild(dest));}
				else{current->insert(dest->parent,dest);}
				push(expr);
				return;
			}
			break;
		  case Associativity::binary: /* a~b~c -> ~[~[a,b],c]] */
			if(root){std::cout <<KCYN << "binary"<< KNRM<<"\n";}
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
		  case Associativity::right: /* a~b~c -> ~[a,~[b,c]] */
			if(root){std::cout <<KCYN << "right"<< KNRM<<"\n";}
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
	Expr *expr,*expr2;
	while(tokenizer->current != tokenizer->string.end()){
		expr = tokenizer->read();
		if(expr){
			std::cout << "expr : " << expr->toString() << "\n";
			if(root){std::cout << "root : " << root->toString() << "\n";}
			if(previous){std::cout << "previous : " << previous->toString() << "\n";}
			
			if(AtomQ::mod(expr)){
				std::cout << KWHT << "atom" << KNRM << "\n";
				push(expr);
			}else if(expr->symbol->id == internal_LeftBracket){
				std::cout << KWHT << "LeftBracket" << KNRM << "\n";
				Parser parser(tokenizer,getData(RightBracketData,expr->data,expr->symbol));
				expr2 = parser.parse();
				if(expr2){
					push(getData(LeftBracketData,expr->data,expr)->copy()->appendChild(expr2));
				}
				else{push(new Expr(global_Null));}
			}else if(expr->symbol->associativity == Associativity::separator){
				std::cout << KWHT << "Separator" << KNRM << "\n";
				Parser parser(tokenizer,end);
				expr = parser.parse();
				if(expr){pushToRoot(expr);}
				else{pushToRoot(new Expr(global_Null));}
				break;
			}else if(expr->symbol->id == internal_RightBracket){
				std::cout << KWHT << "RightBracket" << KNRM << "\n";
				if(end==(getData(RightBracketData,expr->data,expr))->symbol){
					break;
				}else{
				  std::cout << __func__ << " : bracket mismatch : " << end->mark[0] << end->mark[1] << std::endl;
					/*ignore*/
					break;
				}
			}else{
				if(!root ||
					(previous && (
						previous->symbol->associativity == Associativity::left ||
						previous->symbol->associativity == Associativity::right ||
						previous->symbol->associativity == Associativity::none || 
						previous->symbol->associativity == Associativity::binary
					))
				){
					std::cout << KWHT << "prefer pre" << KNRM << "\n";
					for(Expr *e=expr;e;e=e->previous){
						if(e->symbol->id != internal_Character 
							&& e->symbol->associativity == Associativity::pre){
							expr=e; break;
						}
					}
				}else{
					std::cout << KWHT << "prefer not pre" << KNRM << "\n";
					for(Expr *e=expr;e;e=e->previous){
						if(e->symbol->id != internal_Character && 
							e->symbol->associativity!=Associativity::pre){
							expr=e; break;
						}
					}
				}
				push(expr->copy());
			}
		}else{
			break;
		}
	}
	if(!end){root = removeBrackets(root);}
	return root;
}

void printexpr(Expr *expr){
	if(expr){
		std::cout << expr->toString() << "\n";
	}else{
		std::cout << "nullptr\n";
	}
}

void Parser::print(){
	std::cout << "root : "; printexpr(root);
	std::cout << "previous : "; printexpr(previous);
	std::cout << "current : "; printexpr(current);
	if(end){std::cout << "end : "; end->toString();}
}

Expr* Parser::removeBrackets(Expr* expr){
	if(expr){
		Expr* e;
		for(e=expr->child;e;e=e->next){e=removeBrackets(e);}
		switch(expr->symbol->id){
		  case internal_Parenthesis:
		  case internal_Bracket:
			e = expr->replace(expr->child);
			delete expr;
			expr = e;
			break;
		  default:
			break;
		}
	}
	return expr;
}
