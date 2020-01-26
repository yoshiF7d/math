#include <Expr.h>
#include <Symbol.h>
class Bracket : public Symbol{
public :
	Bracket();
	Expr* preEvaluate(Expr* expr) override;
};
