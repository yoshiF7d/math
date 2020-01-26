#include <Expr.h>
#include <Symbol.h>
class SymbolContainer : public Symbol{
public :
	SymbolContainer();
	Expr* preEvaluate(Expr* expr) override;
	static Expr* wrap(Expr* expr);
	static Expr* unwrap(Expr* expr);
	Data* createData() override;

};
struct SymbolContainerData : Data{
	Symbol* symbol;
	SymbolContainerData(Symbol* symbol=nullptr);
	~SymbolContainerData();
	std::string toString() override;
};

