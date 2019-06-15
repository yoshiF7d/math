#include <Expr.h>
#include <Symbol.h>
class LeftBracket : public Symbol{
public :
	LeftBracket();

Data* createData() override;

};
struct LeftBracketData : Data{
	Expr *expr;
	LeftBracketData();
	~LeftBracketData();
	bool operator ==(const Data& data) override;
	std::string toString() override;
};

