#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H
#define TABLE_SIZE 512
#include "../../symbols/global/inc/All.h"
#include "../../symbols/global/inc/AtomQ.h"
#include "../../symbols/global/inc/Depth.h"
#include "../../symbols/global/inc/Evaluate.h"
#include "../../symbols/global/inc/False.h"
#include "../../symbols/global/inc/FullForm.h"
#include "../../symbols/global/inc/Increment.h"
#include "../../symbols/global/inc/Integer.h"
#include "../../symbols/global/inc/List.h"
#include "../../symbols/global/inc/None.h"
#include "../../symbols/global/inc/Null.h"
#include "../../symbols/global/inc/Plus.h"
#include "../../symbols/global/inc/PreIncrement.h"
#include "../../symbols/global/inc/Quit.h"
#include "../../symbols/global/inc/Real.h"
#include "../../symbols/global/inc/String.h"
#include "../../symbols/global/inc/Times.h"
#include "../../symbols/global/inc/TreeForm.h"
#include "../../symbols/global/inc/True.h"
#include "../../symbols/internal/inc/Bracket.h"
#include "../../symbols/internal/inc/Character.h"
#include "../../symbols/internal/inc/Comma.h"
#include "../../symbols/internal/inc/LeftBracket.h"
#include "../../symbols/internal/inc/Node.h"
#include "../../symbols/internal/inc/Parenthesis.h"
#include "../../symbols/internal/inc/RightBracket.h"
#define CONTEXT_GLOBAL(UNFOLD,TABLE) \
UNFOLD(All,TABLE,global)\
UNFOLD(AtomQ,TABLE,global)\
UNFOLD(Depth,TABLE,global)\
UNFOLD(Evaluate,TABLE,global)\
UNFOLD(False,TABLE,global)\
UNFOLD(FullForm,TABLE,global)\
UNFOLD(Increment,TABLE,global)\
UNFOLD(Integer,TABLE,global)\
UNFOLD(List,TABLE,global)\
UNFOLD(None,TABLE,global)\
UNFOLD(Null,TABLE,global)\
UNFOLD(Plus,TABLE,global)\
UNFOLD(PreIncrement,TABLE,global)\
UNFOLD(Quit,TABLE,global)\
UNFOLD(Real,TABLE,global)\
UNFOLD(String,TABLE,global)\
UNFOLD(Times,TABLE,global)\
UNFOLD(TreeForm,TABLE,global)\
UNFOLD(True,TABLE,global)

#define CONTEXT_INTERNAL(UNFOLD,TABLE) \
UNFOLD(Bracket,TABLE,internal)\
UNFOLD(Character,TABLE,internal)\
UNFOLD(Comma,TABLE,internal)\
UNFOLD(LeftBracket,TABLE,internal)\
UNFOLD(Node,TABLE,internal)\
UNFOLD(Parenthesis,TABLE,internal)\
UNFOLD(RightBracket,TABLE,internal)

#define UNFOLD(SYMBOL,TABLE,NAME) NAME##_##SYMBOL,
enum ID{
	CONTEXT_GLOBAL(UNFOLD,TABLE)
	CONTEXT_INTERNAL(UNFOLD,TABLE)
end,
};
#undef UNFOLD

#define SET_TABLE(SYMBOL,TABLE,NAME) TABLE[NAME##_##SYMBOL]=new SYMBOL();
#define SET_MAP(SYMBOL,TABLE,NAME) {#SYMBOL,TABLE[NAME##_##SYMBOL]},
#define MAKE_CONTEXT_GLOBAL(LIST,TABLE) \
CONTEXT_GLOBAL(SET_TABLE,TABLE) LIST.push_back(make_pair("global",SymbolMap{CONTEXT_GLOBAL(SET_MAP,TABLE)}));
#define MAKE_CONTEXT_INTERNAL(LIST,TABLE) \
CONTEXT_INTERNAL(SET_TABLE,TABLE) LIST.push_back(make_pair("internal",SymbolMap{CONTEXT_INTERNAL(SET_MAP,TABLE)}));
#define MAKE_CONTEXT(LIST,TABLE) \
MAKE_CONTEXT_GLOBAL(LIST,TABLE)\
MAKE_CONTEXT_INTERNAL(LIST,TABLE)

#endif
