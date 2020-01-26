#include <Expr.h>
#include <Symbol.h>
class ApplyLevelOne : public Symbol{
public :
	ApplyLevelOne();
	Expr* preEvaluate(Expr* expr) override;	void printdoc() override;

};
