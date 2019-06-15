#include <Expr.h>
#include <Symbol.h>
class FullForm : public Symbol{
public :
	FullForm();
	static Expr* mod(Expr* expr);
	Expr* function(Expr* expr) override;
};
