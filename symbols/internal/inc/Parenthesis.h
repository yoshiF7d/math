#include <Expr.h>
#include <Symbol.h>
class Parenthesis : public Symbol{
public :
	Parenthesis();
	Expr* preEvaluate(Expr* expr) override;
};
