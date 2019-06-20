#include <Expr.h>
#include <Symbol.h>
class Comma : public Symbol{
public :
	Comma();
	Expr* preEvaluate(Expr* expr) override;
};
