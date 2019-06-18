#include <Expr.h>
#include <Symbol.h>
class Real : public Symbol{
public :
	Real();
	
static Expr* create(std::string string);	void printdoc() override;

	Data* createData() override;

};
struct RealData : Data{
	#ifdef mpz
		mpf_class real;
	#else
		double real;
	#endif
	RealData();
	RealData(std::string string);
	RealData(double real);
	~RealData();
	void set(std::string string);
	void set(double real);
	std::string toString() override;
};

