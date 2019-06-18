#include <utility>
#include <Expr.h>
#include <Symbol.h>
#include <SymbolTable.h>

Expr::Expr(){
	symbol=nullptr;
	data=nullptr;
	next=nullptr;
	previous=nullptr;
	child=nullptr;
	parent=nullptr;
}

Expr::Expr(int id){
	symbol = SymbolTable::get(id);
	data = symbol->createData();
	next=nullptr;
	previous=nullptr;
	child=nullptr;
	parent=nullptr;
	//printf("Expr_id\t");
	//printf("%x\t",this);
	//std::cout << symbol->name << "\n";
}

Expr::Expr(std::string string){
	//printf("Expr_string\n");
	symbol = SymbolTable::get(string);
	data = symbol->createData();
	next=nullptr;
	previous=nullptr;
	child=nullptr;
	parent=nullptr;
}

Expr::Expr(Symbol *symbol){
	this->symbol = symbol;
	data = symbol->createData();
	next=nullptr;
	previous=nullptr;
	child=nullptr;
	parent=nullptr;
	//printf("Expr_symbol\t");
	//printf("%x\t",this);
	//std::cout << symbol->name << "\n";
}

Expr::Expr(const Expr& expr){
	symbol = expr.symbol;
	data = symbol->createData();
	next=nullptr;
	previous=nullptr;
	child=nullptr;
	parent=nullptr;
	//printf("Expr_copy\t");
	//printf("%x\t",this);
	//std::cout << symbol->name << "\n";
}

Expr::~Expr(){
	//printf("~Expr\t",this);
	//printf("%x\t",this);
	//std::cout << symbol->name << "\n";
	symbol->deleteData(data);
}

void Expr::deleteRoot(){
	for(Expr* c=child;c;){
		Expr* n = c->next;
		c->deleteRoot();
		c = n;
	}
	delete this;
}

void Expr::deleteLast(){
	Expr *e,*last;
	for(e=this;e->next;e=e->next){}
	last = e->next;
	if(last){
		e->next = nullptr;
		last->deleteRoot();
	}else{
		this->deleteRoot();
	}
}

void Expr::deleteChild(Expr *child){
	Expr *e,*last;
	for(e=this->child;e;e=e->next){
		if(e==child){
			if(e==this->child){this->child=e->next;}
			e->deleteRoot();
			break;
		}
	}
}

void Expr::deleteChildren(){
	Expr *e;
	for(e=this->child;e;e=e->next){
		e->deleteRoot();
	}
	this->child = nullptr;
}

int Expr::getLength(){
	Expr *e;
	int i=0;
	for(e=this;e;e=e->next,i++){}
	return i;
}

std::string Expr::toString(){
	if(this->data){
		return this->data->toString();
	}else{
		return this->symbol->toString();
	}
}

Expr* Expr::appendTo(Expr *expr,Expr *next){
	if(expr){
		return expr->append(next);
	}else{
		return next;
	}
}

Expr* Expr::copy(){
	return new Expr(*this);
}

Expr* Expr::append(Expr *expr){
	Expr *e;
	for(e=this;e->next;e=e->next){}
	e->next = expr;
	expr->previous = e;
	return this;
}

Expr* Expr::appendChild(Expr *child){
	if(this->child){this->child->append(child);}
	else{this->child = child;}
	for(Expr* e=this->child;e;e=e->next){e->parent = this;}
	return this;
}

Expr* Expr::prependChild(Expr *child){
	if(child){this->child = child->append(this->child);}
	else{this->child = child;}
	for(Expr* e=this->child;e;e=e->next){e->parent = this;}
	return this;
}

Expr* Expr::insert(Expr *p, Expr *c){
	if(!p){
		return this->appendChild(c);
	}else if(!c || p==c){
		return p->appendChild(this);
	}else if(c->parent != p){
		std::cout << __func__ << ": "; 
		if(p){std::cout << p->toString();
		}else{std::cout << "null";}
		std::cout << " is not a parent of ";
		if(c){std::cout << c->toString();
		}else{std::cout << "null";}
		std::cout << "\n";
		exit(1);
	}
	c->replace(this);
	c->isolate();
	this->appendChild(c);
	return p;
}

Expr* Expr::preinsert(Expr *p, Expr *c){
	if(!p){
		return this->prependChild(c);
	}else if(!c || p==c){
		return p->prependChild(this);
	}else if(c->parent != p){
		std::cout << __func__ << ": "; 
		if(p){std::cout << p->toString();
		}else{std::cout << "null";}
		std::cout << " is not a parent of ";
		if(c){std::cout << c->toString();
		}else{std::cout << "null";}
		std::cout << "\n";
		exit(1);
	}
	c->replace(this);
	c->isolate();
	this->prependChild(c);
	return p;
}

Expr* Expr::replace(Expr *expr){
	Expr* previous = nullptr;
	Expr* next = nullptr;
	Expr* parent = nullptr;
	
	parent = this->parent;
	previous = this->previous;
	next = this->next;

	if(expr!=next){expr->next=next;}
	if(expr!=previous){expr->previous=previous;}
	if(expr!=parent){expr->parent=parent;}
	if(previous){
		if(expr!=previous){previous->next=expr;}
	}else{
		if(parent && expr!=parent){parent->child = expr;}
	}
	if(next){
		if(expr!=next){next->previous=expr;}
	}
	return expr;
}

Expr* Expr::isolate(){
	this->parent = this->previous = this->next = nullptr;
	return this;
}

Expr* Expr::getChild(int index){
	Expr *e,*rtn=nullptr;
	int k;
	for(e=this->child,k=0;e;e=e->next,k++){
		if(k==index){
			rtn=e;
			break;
		}
	}
	return rtn;
}


void Expr::swap(Expr& e1,Expr& e2){
	std::swap(e1.symbol,e2.symbol);
	std::swap(e1.data,e2.data);
	std::swap(e1.next,e2.next);
	std::swap(e1.previous,e2.previous);
	std::swap(e1.child,e2.child);
	std::swap(e1.parent,e2.parent);
}

Expr& Expr::operator = (const Expr &other){
	Expr temp(other);
	swap(*this,temp);
	return *this;
}

bool Expr::operator == (const Expr& e){
	if(symbol==e.symbol){
		return *data == *(e.data);
	}else{
		return false;
	}
}
