#include <Expr.h>
#include <Symbol.h>
class TreeForm : public Symbol{
public :
	TreeForm();
	#define TREEFORM_H_MAXDEPTH 256

static Expr* mod2(Expr* expr, std::string branch);
	static void mod(Expr *expr);
	Expr* evaluate(Expr* expr) override;	void printdoc() override;

};
