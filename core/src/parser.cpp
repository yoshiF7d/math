#include <Symbol.h>
#include <SymbolTable.h>
#include <parser.h>

Parser::Tokenizer::Tokenizer(){
	Expr *last,*e;
	Symbol *symbol;
	std::list<Context> context = SymbolTable::context;
	this->optree = last = new Expr(global_Symbol);
	
	/*making operator tree*/
	
	/*example*/
	/*root -> + -> + -> Increment */
	/*          -> Plus           */
	/*     -> - -> - -> Decrement */
	/*          -> Minus          */
	/*     -> [ -> Left -> Bracket */
	/*     -> ] -> Right -> Bracket */
	/*     -> ( -> Left -> Parenthesis */
	/*     -> ) -> Right -> Parenthesis */
	
	for(auto&& c : context){
		for(auto&& t: c.second){
			symbol = t.second;
			for(int i=0;i<2;i++){
				if(!(symbol->mark[i].empty())){
					int j=0;
					for(last=this->optree;j<symbol->mark[i].length();last = e,j++){
						for(e=last->child;e;e=e->next){
							if(e->symbol->id == internal_Character){
								if(castData(CharacterData,e->data)->character == symbol->mark[i][j]){
									goto loopend;
								}
							}
						}
						last->appendChild(e = new Expr(internal_Character));
						castData(CharacterData,e->data)->character = symbol->mark[i][j];
						  loopend:;
					}
					if(symbol->associativity==Associativity::bracket){
						if(i==0){
							last->appendChild(e = new Expr(internal_LeftBracket));
							castData(LeftBracketData,e->data)->expr = new Expr(symbol);
						}else{
							last->appendChild(e = new Expr(internal_RightBracket));
							castData(RightBracketData,e->data)->expr = new Expr(symbol);
						}
					}else{
						last->appendChild(new Expr(symbol));
						//std::cout << KCYN << symbol->toString() << KNRM << "\n";
						break;
					}
				}
			}
		}
	}
	//TreeForm::mod(this->optree);
	//std::cout << std::endl;
}
Parser::Tokenizer::~Tokenizer(){
	this->optree->deleteRoot();
}

void Parser::Tokenizer::set(std::string string){
	this->string = string;
	this->current = this->string.begin();
}

/*
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
			//std::cout << std::string(save,current) << "\n";
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
		if(!(*current & 0x80)){current = save; return nullptr;}
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
*/

Expr* Parser::Tokenizer::read(Symbol *endtoken){
	Expr *expr=nullptr;
	std::string::iterator save;
	while(isspace(*(this->current))){this->current++;}
	if(this->current==this->string.end()){return nullptr;}
	save = this->current;
	if((expr=Symbol::parse(&(this->current)))){return SymbolContainer::wrap(expr);} /*prevent symbol to bond when full form is inputed*/
	if((expr=Number::parse(&(this->current)))){return expr;}
	if((expr=String::parse(&(this->current),string.end()))){return expr;}
	if(optree){
		Expr *last=optree;
		bool hit;
		do{
			hit = false;
			for(Expr* e=last->child;e;e=e->next){
				if(e->symbol->id==internal_Character){
					if(castData(CharacterData,e->data)->character==*current){
						last = e;
						hit = true;
					}
				}else{
					expr = e;
					if(endtoken && expr->symbol->id == internal_RightBracket){
						if(castData(RightBracketData,expr->data)->expr->symbol == endtoken){
							hit=false; 
							break;
						}
					}
				}
			}
			if(hit){current++;}
		}while(hit);
		return expr;
	}
	std::cout << __func__ << " unregistered token " << *current << " is found" << std::endl;
	current = save;
	return nullptr;
}

Parser::Parser(){
	tokenizer = new Tokenizer();
	this->end = nullptr;
	root = current = nullptr;
}

Parser::~Parser(){}

Parser::Parser(Tokenizer *tokenizer, Symbol *end){
	this->tokenizer = tokenizer;
	this->end = end;
	root = current = nullptr;
}

void Parser::print(){
	TreeForm::mod(this->tokenizer->optree);
}

void Parser::finish(){
	delete tokenizer;
	tokenizer = nullptr;
}

void Parser::set(std::string string){
	this->tokenizer->set(string);
	this->root = current = nullptr;
}

void Parser::push(Expr *expr){
	Expr *dest;
	/*
	if(root){std::cout << "root symbol : " << root->symbol->name << "\n";}
	if(current){std::cout << "current symbol : " << current->symbol->name << "\n";}
	if(expr){std::cout << "symbol : " << expr->symbol->name << "\n";}
	*/
	
	if(!current){
		setRoot(expr);
		if(expr->symbol->associativity & BINARY){
			expr->appendChild(new Expr(global_Null));
		}
		return;
	}
	
	if(
	   (current->symbol->associativity & BINARY) &&
	   (expr->symbol->associativity & BINARY)
	){
		/*
		if(expr->symbol->id == global_Blank
		|| expr->symbol->id == global_BlankSequence
		|| expr->symbol->id == global_BlankNullSequence
		){
			pushDirect(expr->appendChild(new Expr(global_Null)));
		}else
		*/
		{
			push(new Expr(global_Null));
			push(expr);
		}
		return;
	}
	if(expr->symbol->precedence >= 670){
		dest = current;
	}else{
		for(dest=current;dest;dest=dest->parent){
			if(expr->symbol->precedence >= dest->symbol->precedence){break;}
			current = dest;
		}
	}
	
	if(!dest){
		setRoot(expr->appendChild(current));
		return;
	}
	
	if(dest->symbol->precedence >= 670){
		if( 
		/*checking expr*/
		  (expr->symbol->id == global_Blank
		|| expr->symbol->id == global_BlankSequence
		|| expr->symbol->id == global_BlankNullSequence)
		){
			/*a_ -> a:_*/
			Expr *e = new Expr(internal_PatternBlank);
			if(!dest->parent){setRoot(e->appendChild(dest));}
			else{e->insert(dest->parent,dest);}
			e->appendChild(expr);
			goto end;
		}else if(
		/*checking dest*/
		(  dest->symbol->id == global_Blank
		|| dest->symbol->id == global_BlankSequence
		|| dest->symbol->id == global_BlankNullSequence)
		|| dest->symbol->id == global_Slot
		|| dest->symbol->id == global_SlotSequence
		){
			/*_a -> _[a]*/
			/*#a -> #[a]*/
			pushDirect(expr);
			return;
		}else{
			/*a b -> a*b*/
			push(new Expr(global_Times));
			push(expr);
			return;
		}
	}else{
		switch(dest->symbol->associativity){
		  case Associativity::left: /* a~b~c -> ~[~[a,b],c] */
			//if(root){std::cout <<KCYN << "Left"<< KNRM<<"\n";}
			if(dest->symbol->precedence == expr->symbol->precedence){
				if(!dest->parent){setRoot(expr->appendChild(dest));}
				else{expr->insert(dest->parent,dest);}
				goto end;
			}
			break;
		  case Associativity::none: /* a~b~c -> ~[a,b,c] */
		    //if(root){std::cout <<KCYN << "none"<< KNRM<<"\n";}
			if(dest->symbol == expr->symbol){
				delete expr;
				expr = dest;
				goto end;
			}
			break;
		  case Associativity::post: /*a~b -> ~[a]*b*/
			//if(root){std::cout <<KCYN << "post"<< KNRM<<"\n";}
			if(dest==current && dest->child){
				current = new Expr(global_Times);
				if(!dest->parent){setRoot(current->appendChild(dest));}
				else{current->insert(dest->parent,dest);}
				push(expr);
				return;
			}
			break;
		  case Associativity::right: /* a~b~c -> ~[a,~[b,c]] */
			//if(root){std::cout <<KCYN << "right"<< KNRM<<"\n";}
		  default:
			break;
		}
		expr->insert(dest,current);
	}
  end:
	current = expr;
	return;
}

void Parser::pushToRoot(Expr *expr){
	if(!root){setRoot(expr);}
	else{root->append(expr);}
	current = root;
}

void Parser::pushDirect(Expr *expr){
	if(!root){setRoot(expr);}
	else{
		current->appendChild(expr);
	}
	current = expr;
}

void Parser::pushBracket(Expr *expr){
	if(!root){setRoot(expr);}
	else{
		Expr* dest = current->parent;
		if(!dest){
			setRoot(expr->prependChild(current));
		}else{
			expr->preinsert(dest,current);
		}
	}
	current = expr;
}

void Parser::setRoot(Expr *expr){
	root = current = expr;
}

Expr* Parser::parse(){
	Expr *expr,*expr2;
	//std::cout << "parse start\n";
	while(tokenizer->current != tokenizer->string.end()){
		expr = tokenizer->read(end);
		if(expr){
			/*
			std::cout << "expr : " << expr->toString() << "\n";
			if(root){std::cout << "root : " << root->toString() << "\n";}
			if(current){std::cout << "current : " << current->toString() << "\n";}
			*/
			if(AtomQ::mod(expr)){
				//std::cout << KWHT << "atom" << KNRM << "\n";
				push(expr);
			}else if(expr->symbol->id == internal_LeftBracket){
				//std::cout << KWHT << "LeftBracket" << KNRM << "\n";
				Parser parser(tokenizer,castData(LeftBracketData,expr->data)->expr->symbol);
				expr2 = parser.parse();
				if(expr2){
					expr2 = castData(LeftBracketData,expr->data)->expr->copy()->appendChild(expr2);
				}else{
					expr2 = castData(LeftBracketData,expr->data)->expr->copy()->appendChild(new Expr(global_Null));
				}
				if( expr2->symbol->id == internal_Bracket ||
					expr2->symbol->id == global_Part
				){
					pushBracket(expr2);
				}else{
					push(expr2);
				}
			}else if(expr->symbol->id == internal_RightBracket){
				//std::cout << KWHT << "RightBracket" << KNRM << "\n";
				if(end!=(castData(RightBracketData,expr->data)->expr->symbol)){
				  if(end){
					std::cout << __func__ << " : bracket mismatch 1 : " << end->mark[1] << " and ";
				  }else{
					std::cout << __func__ << " : bracket mismatch 2 : ";
				  }
				  std::cout << castData(RightBracketData,expr->data)->expr->symbol->mark[1] << "\n";
				}
				break;
			}else{
				if(!root || (current->symbol->associativity & BINARY)){
					//std::cout << KWHT << "prefer pre" << KNRM << "\n";
					for(Expr *e=expr;e;e=e->previous){
						if(e->symbol->id != internal_Character && 
							e->symbol->associativity == Associativity::pre){
							expr=e; break;
						}
					}
				}else{
					//std::cout << KWHT << "prefer not pre" << KNRM << "\n";
					//TreeForm::mod(expr->parent);
					for(Expr *e=expr;e;e=e->previous){
						if(e->symbol->id != internal_Character && 
							e->symbol->associativity != Associativity::pre){
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
	if(!current){return nullptr;}
	if(current->symbol->associativity & BINARY){
		pushDirect(new Expr(global_Null));
	}
	if(!end){
		
		std::cout << KYEL << "before pre-eval" << KNRM << "\n";
		TreeForm::mod(root);
		std::cout << std::endl;
		
		root = preEvaluate(root);
	}
	//std::cout << "parse end\n";
	return root;
}

Expr* Parser::preEvaluate(Expr* expr){
	if(expr){
		Expr* e;
		for(e=expr->child;e;e=e->next){e=preEvaluate(e);}
		expr=expr->symbol->preEvaluate(expr);
	}
	return expr;
}
