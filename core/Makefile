COMPILER = clang
CFLAGS = -g -O3
LIBS = 
INCLUDE = -I ./inc
TARGET = ../bin/math
SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./inc
SDIR = ../symbols

LDFLAGS = -lm -lreadline -lncurses -lgmp -lmpfr
SRCNAMES = math.cpp parser.cpp Expr.cpp SymbolTable.cpp SymbolList.cpp Data.cpp

SRCS = $(addprefix $(SRCDIR)/, $(SRCNAMES))
OBJS = $(addprefix $(OBJDIR)/, $(SRCNAMES:.cpp=.o))

SSRCS = $(foreach PDIR, $(wildcard $(SDIR)/*), $(wildcard $(PDIR)/src/*.cpp))
SOBJS = $(foreach PDIR, $(wildcard $(SDIR)/*), $(addprefix $(PDIR)/obj/, $(patsubst %.cpp,%.o,$(notdir $(wildcard $(PDIR)/src/*.cpp)))))

OBJS += $(SOBJS)

$(TARGET) : $(OBJS) 
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<	


$(SDIR)/*/obj/%.o : $(SDIR)/*/src/%.cpp
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJDIR)/parser.o : $(INCDIR)/SymbolList.h

.PHONY : clean print
clean :
	-rm -f $(OBJDIR)/*.o
	-rm -f $(INCDIR)/SymbolList.h $(INCDIR)/Data.h
	
print : 
	echo $(SOBJS)
	echo $(SSRCS)
