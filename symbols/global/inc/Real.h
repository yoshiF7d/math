#include <Expr.h>
#include <Symbol.h>
class Real : public Symbol{
public :
	Real();
	double getDouble(Expr expr);
	int sign(Expr expr);
	static Expr *create(std::string string);
Data* createData() override;

};
struct RealData : Data{
	#ifdef mpz
		mpf_class real;
	#else
		double real;
	#endif
	~RealData();
};

