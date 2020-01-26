#include <SymbolList.h>
#include <SymbolTable.h>
TreeForm::TreeForm() : Symbol("TreeForm","",global_TreeForm,670,Protected,0,"","木"){}
Expr* TreeForm::mod2(Expr* expr, std::string branch){
	if(!expr){
		printf("null\n");
		return expr;
	}
	std::string estr = expr->toString();
	std::cout << " " << estr  << " ";
	int len = estr.length() + 2;
	int blen;
	if(!branch.empty()){blen = branch.length();}
	else{blen=0;}
		
	std::string nbranch;
	nbranch.resize(blen+len+4);
	for(int i=0;i<blen;i++){
		nbranch[i] = branch[i];
	}	
	for(int i=blen;i<blen+len;i++){
		nbranch[i]=' ';
	}	
	if(expr->child){
		if(expr->child->next){
			nbranch[blen+len]=' ';
			nbranch[blen+len+1]='|';
			nbranch[blen+len+2]=' ';
			nbranch[blen+len+3]='\0';
			std::cout << KWHT << "-+-" << KNRM;
			TreeForm::mod2(expr->child,nbranch);
			Expr* e;
			for(e=expr->child->next;e->next;e=e->next){
				if(!branch.empty()){std::cout << KWHT << branch << KNRM;}
				for(int i=0;i<len;i++){putchar(' ');}
				std::cout << KWHT << " +-" << KNRM;
				TreeForm::mod2(e,nbranch);
			}
			nbranch[blen+len]=' ';
			nbranch[blen+len+1]=' ';
			nbranch[blen+len+2]=' ';
			nbranch[blen+len+3]='\0';
			if(!branch.empty()){std::cout << KWHT << branch << KNRM;}
			for(int i=0;i<len;i++){putchar(' ');}
			std::cout << KWHT << " \\-" << KNRM;
			TreeForm::mod2(e,nbranch);
		}else{
			nbranch[blen+len]=' ';
			nbranch[blen+len+1]=' ';
			nbranch[blen+len+2]=' ';
			nbranch[blen+len+3]='\0';
			std::cout << KWHT << "---" << KNRM;
			TreeForm::mod2(expr->child,nbranch);
		}
	}else{printf("\n");}
	return expr;
}
void TreeForm::mod(Expr *expr){
	mod2(expr,std::string());
}
Expr* TreeForm::evaluate(Expr* expr){
	if(!expr->child){return expr;}
	mod(expr->child);
	return expr;
}
void TreeForm::printdoc(){printf(
	"                          TreeForm[expr] displays expr as a tree with different levels at different depths.\n"
);}
