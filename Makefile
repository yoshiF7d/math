.PHONY : math prec all learn clean print
all:
	make prec && make math
math:
	cd ./core && make
prec:
	./prec/bin/prec ./symbols ./core/inc/SymbolList.h ./core/inc/Data.h
clean: 	
	-rm -f ./symbols/*/src/*.c
	-rm -f ./symbols/*/obj/*.o
	cd ./core && make clean
	cd ./prec && make clean
print:
	cd ./core && make print
