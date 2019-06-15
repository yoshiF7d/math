COMPILER = clang
CFLAG = -g
LIBS =
INCLUDE =  
TARGET = ./bin/prec
SRCDIR = ./src

LDFLAGS = -lm

SRCNAMES = prec.c

$(TARGET) : src/prec.c 
	$(COMPILER) $(CFLAGS) -o $@ $< $(LDFLAGS)


.POHNY : clean
clean :
	rm $(TARGET)	
