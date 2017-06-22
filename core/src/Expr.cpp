#include <Expr.h>

Expr::Expr(int id) : data(id) {
	symbol = SymbolTable::get(id);
}

Expr::Expr(string string){
	symbol = SymbolTable::get(string);
	symbol->data_init(this->data);
}

Expr::Expr(Symbol *symbol){
	this->symbol = symbol;
}

Expr::Expr(const Expr& expr){
	symbol = expr.symbol;
	data(expr.data,symbol);
	flag=expr.flag;
	next=expr.next;
	child=expr.child;
}

void Expr::deleteRoot(){
	Expr *c, *n;
	for(c=child;c;c=n){
		n = c->next;
		c->deleteRoot();
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

string Expr::toString(){
	return this->symbol->toString(this->data);
}

static Expr* Expr::appendTo(Expr *expr,Expr *next){
	if(expr){
		return expr->append(next);
	}else{
		return next;
	}
}

Expr* Expr::append(Expr *expr){
	Expr *e;
	for(e=this;e->next;e=e->next){}
	e->next = expr;
	return this;
}

Expr* Expr::appendChild(Expr *child){
	this->child->append(child);
	return this;
}

Expr* Expr::prependChild(Expr *child){
	if(child){
		this->child = child->append(this->child);
	}
	return this;
}

Expr* Expr::insert(Expr *p, Expr *c){
	if(!p){
		return this->appendChild(c);
	}else if(!c){
		return p->appendChild(this);
	}else if(p==c){
		return p->appendChild(this);
	}else if(p->child != c){
		cout << __func__ + "Expr_insert : p and c are not parent-child\n";
	}
	p->child = this;
	this->appendChild(c);
	return p;
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


friend void Expr::swap(Expr& e1,Expr& e2){
	using std::swap;
	swap(e1.symbol,e2.symbol);
	swap(e1.data,e2.data);
	swap(e1.flag.e2.flag);
	swap(e1.next,e2.next);
	swap(e1.child,e2.child);
}

Expr& Expr::operator = (Expr other){
	swap(*this,other);
	return *this;
}

bool Expr::operator == (const Expr& e1, const Expr& e2){
	if(e1.symbol==e2.symbol){
		return e1.data==e2.data;
	}else{
		return false;
	}
}