#include <Expr.h>
#include <Symbol.h>
class Integer : public Symbol{
public :
	Integer();
	static Expr *create(std::string string);
	static Expr *create(int integer);
	static Expr *createExp(std::string string);
Data* createData() override;

};
struct IntegerData : Data{
    #ifdef mpz
      mpz_class integer;
    #else
	  long integer;
    #endif
	IntegerData();
	IntegerData(std::string string);
	IntegerData(int integer);
	IntegerData(long integer);
	static IntegerData* IntegerDataExp(std::string string);
	std::string toString() override;
	~IntegerData();
};

