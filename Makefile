.PHONY : math prec all learn clean print
all:
	make prec && make math
math:
	cd ./core && make
prec:
	cd prec && make
	./prec/bin/prec ./symbols ./core/autoinc/SymbolList.h
clean: 	
	-rm -f ./symbols/*/src/*.cpp
	-rm -f ./symbols/*/obj/*.o
	-rm -f ./symbols/*/inc/*.h
	cd ./core && make clean
	cd ./prec && make clean
print:
	cd ./core && make print

