COMPILER = clang++
CFLAGS = -g -O0 -std=c++11
LIBS = 
INCLUDE = -I./inc -I./autoinc
TARGET = ../bin/math
SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./inc
AUTOINCDIR = ./autoinc
SDIR = ../symbols

LDFLAGS = -lm -lgmp -lmpfr -lreadline -lncurses
SRCNAMES = math.cpp parser.cpp Expr.cpp Symbol.cpp SymbolTable.cpp

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

$(OBJDIR)/parser.o : $(AUTOINCDIR)/SymbolList.h

.PHONY : clean print
clean :
	-rm -f $(OBJDIR)/*.o
	-rm -f $(AUTOINCDIR)/SymbolList.h 
	
print : 
	echo $(SOBJS)
	echo $(SSRCS)
