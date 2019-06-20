#include <Expr.h>
#include <Symbol.h>
class TreeForm : public Symbol{
public :
	TreeForm();
	#define TREEFORM_H_MAXDEPTH 256
#define KNRM  "\x1B[0m"
#define KWHT "\x1B[37m"

static Expr* mod2(Expr* expr, std::string branch);
	static void mod(Expr *expr);
	Expr* evaluate(Expr* expr) override;	void printdoc() override;

};
