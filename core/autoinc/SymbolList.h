#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H
#define TABLE_SIZE 512
#include "../../symbols/internal/inc/Comma.h"
#include "../../symbols/internal/inc/Global.h"
#include "../../symbols/internal/inc/Bracket.h"
#include "../../symbols/internal/inc/LeftBracket.h"
#include "../../symbols/internal/inc/Parenthesis.h"
#include "../../symbols/internal/inc/SymbolContainer.h"
#include "../../symbols/internal/inc/RightBracket.h"
#include "../../symbols/internal/inc/PostApply.h"
#include "../../symbols/internal/inc/Node.h"
#include "../../symbols/internal/inc/PatternBlank.h"
#include "../../symbols/internal/inc/Character.h"
#include "../../symbols/internal/inc/PreApply.h"
#include "../../symbols/global/inc/DivideBy.h"
#include "../../symbols/global/inc/Alternatives.h"
#include "../../symbols/global/inc/True.h"
#include "../../symbols/global/inc/Plus.h"
#include "../../symbols/global/inc/Integer.h"
#include "../../symbols/global/inc/Quit.h"
#include "../../symbols/global/inc/Greater.h"
#include "../../symbols/global/inc/LessEqual.h"
#include "../../symbols/global/inc/Number.h"
#include "../../symbols/global/inc/Rule.h"
#include "../../symbols/global/inc/Span.h"
#include "../../symbols/global/inc/SetDelayed.h"
#include "../../symbols/global/inc/Divide.h"
#include "../../symbols/global/inc/Association.h"
#include "../../symbols/global/inc/Depth.h"
#include "../../symbols/global/inc/Dot.h"
#include "../../symbols/global/inc/All.h"
#include "../../symbols/global/inc/And.h"
#include "../../symbols/global/inc/Blank.h"
#include "../../symbols/global/inc/ReplaceAll.h"
#include "../../symbols/global/inc/Map.h"
#include "../../symbols/global/inc/Power.h"
#include "../../symbols/global/inc/Real.h"
#include "../../symbols/global/inc/Apply.h"
#include "../../symbols/global/inc/Evaluate.h"
#include "../../symbols/global/inc/MatchQ.h"
#include "../../symbols/global/inc/ApplyLevelOne.h"
#include "../../symbols/global/inc/Equal.h"
#include "../../symbols/global/inc/Out.h"
#include "../../symbols/global/inc/Function.h"
#include "../../symbols/global/inc/SubtractFrom.h"
#include "../../symbols/global/inc/Slot.h"
#include "../../symbols/global/inc/TimesBy.h"
#include "../../symbols/global/inc/SameQ.h"
#include "../../symbols/global/inc/Pattern.h"
#include "../../symbols/global/inc/List.h"
#include "../../symbols/global/inc/Set.h"
#include "../../symbols/global/inc/Times.h"
#include "../../symbols/global/inc/ShowOperators.h"
#include "../../symbols/global/inc/Minus.h"
#include "../../symbols/global/inc/Decrement.h"
#include "../../symbols/global/inc/Null.h"
#include "../../symbols/global/inc/Help.h"
#include "../../symbols/global/inc/Replace.h"
#include "../../symbols/global/inc/Unequal.h"
#include "../../symbols/global/inc/SlotSequence.h"
#include "../../symbols/global/inc/Less.h"
#include "../../symbols/global/inc/Derivative.h"
#include "../../symbols/global/inc/PreIncrement.h"
#include "../../symbols/global/inc/FullForm.h"
#include "../../symbols/global/inc/String.h"
#include "../../symbols/global/inc/CompoundExpression.h"
#include "../../symbols/global/inc/AddTo.h"
#include "../../symbols/global/inc/Factorial.h"
#include "../../symbols/global/inc/Thread.h"
#include "../../symbols/global/inc/None.h"
#include "../../symbols/global/inc/Or.h"
#include "../../symbols/global/inc/False.h"
#include "../../symbols/global/inc/TreeForm.h"
#include "../../symbols/global/inc/BlankSequence.h"
#include "../../symbols/global/inc/Increment.h"
#include "../../symbols/global/inc/StringJoin.h"
#include "../../symbols/global/inc/Part.h"
#include "../../symbols/global/inc/PreDecrement.h"
#include "../../symbols/global/inc/BlankNullSequence.h"
#include "../../symbols/global/inc/Not.h"
#include "../../symbols/global/inc/RuleDelayed.h"
#include "../../symbols/global/inc/AtomQ.h"
#include "../../symbols/global/inc/Subtract.h"
#include "../../symbols/global/inc/GreaterEqual.h"
#define CONTEXT_INTERNAL(UNFOLD,TABLE) \
UNFOLD(Comma,TABLE,internal)\
UNFOLD(Global,TABLE,internal)\
UNFOLD(Bracket,TABLE,internal)\
UNFOLD(LeftBracket,TABLE,internal)\
UNFOLD(Parenthesis,TABLE,internal)\
UNFOLD(SymbolContainer,TABLE,internal)\
UNFOLD(RightBracket,TABLE,internal)\
UNFOLD(PostApply,TABLE,internal)\
UNFOLD(Node,TABLE,internal)\
UNFOLD(PatternBlank,TABLE,internal)\
UNFOLD(Character,TABLE,internal)\
UNFOLD(PreApply,TABLE,internal)

#define CONTEXT_GLOBAL(UNFOLD,TABLE) \
UNFOLD(DivideBy,TABLE,global)\
UNFOLD(Alternatives,TABLE,global)\
UNFOLD(True,TABLE,global)\
UNFOLD(Plus,TABLE,global)\
UNFOLD(Integer,TABLE,global)\
UNFOLD(Quit,TABLE,global)\
UNFOLD(Greater,TABLE,global)\
UNFOLD(LessEqual,TABLE,global)\
UNFOLD(Number,TABLE,global)\
UNFOLD(Rule,TABLE,global)\
UNFOLD(Span,TABLE,global)\
UNFOLD(SetDelayed,TABLE,global)\
UNFOLD(Divide,TABLE,global)\
UNFOLD(Association,TABLE,global)\
UNFOLD(Depth,TABLE,global)\
UNFOLD(Dot,TABLE,global)\
UNFOLD(All,TABLE,global)\
UNFOLD(And,TABLE,global)\
UNFOLD(Blank,TABLE,global)\
UNFOLD(ReplaceAll,TABLE,global)\
UNFOLD(Map,TABLE,global)\
UNFOLD(Power,TABLE,global)\
UNFOLD(Real,TABLE,global)\
UNFOLD(Apply,TABLE,global)\
UNFOLD(Evaluate,TABLE,global)\
UNFOLD(MatchQ,TABLE,global)\
UNFOLD(ApplyLevelOne,TABLE,global)\
UNFOLD(Equal,TABLE,global)\
UNFOLD(Out,TABLE,global)\
UNFOLD(Function,TABLE,global)\
UNFOLD(SubtractFrom,TABLE,global)\
UNFOLD(Slot,TABLE,global)\
UNFOLD(TimesBy,TABLE,global)\
UNFOLD(SameQ,TABLE,global)\
UNFOLD(Pattern,TABLE,global)\
UNFOLD(List,TABLE,global)\
UNFOLD(Set,TABLE,global)\
UNFOLD(Times,TABLE,global)\
UNFOLD(ShowOperators,TABLE,global)\
UNFOLD(Minus,TABLE,global)\
UNFOLD(Decrement,TABLE,global)\
UNFOLD(Null,TABLE,global)\
UNFOLD(Help,TABLE,global)\
UNFOLD(Replace,TABLE,global)\
UNFOLD(Unequal,TABLE,global)\
UNFOLD(SlotSequence,TABLE,global)\
UNFOLD(Less,TABLE,global)\
UNFOLD(Derivative,TABLE,global)\
UNFOLD(PreIncrement,TABLE,global)\
UNFOLD(FullForm,TABLE,global)\
UNFOLD(String,TABLE,global)\
UNFOLD(CompoundExpression,TABLE,global)\
UNFOLD(AddTo,TABLE,global)\
UNFOLD(Factorial,TABLE,global)\
UNFOLD(Thread,TABLE,global)\
UNFOLD(None,TABLE,global)\
UNFOLD(Or,TABLE,global)\
UNFOLD(False,TABLE,global)\
UNFOLD(TreeForm,TABLE,global)\
UNFOLD(BlankSequence,TABLE,global)\
UNFOLD(Increment,TABLE,global)\
UNFOLD(StringJoin,TABLE,global)\
UNFOLD(Part,TABLE,global)\
UNFOLD(PreDecrement,TABLE,global)\
UNFOLD(BlankNullSequence,TABLE,global)\
UNFOLD(Not,TABLE,global)\
UNFOLD(RuleDelayed,TABLE,global)\
UNFOLD(AtomQ,TABLE,global)\
UNFOLD(Subtract,TABLE,global)\
UNFOLD(GreaterEqual,TABLE,global)

#define UNFOLD(SYMBOL,TABLE,NAME) NAME##_##SYMBOL,
enum ID{
	global_Symbol=0,
	CONTEXT_INTERNAL(UNFOLD,TABLE)
	CONTEXT_GLOBAL(UNFOLD,TABLE)
	end
};
#undef UNFOLD

#define SET_TABLE(SYMBOL,TABLE,NAME) TABLE[NAME##_##SYMBOL]=new SYMBOL();
#define SET_MAP(SYMBOL,TABLE,NAME) {#SYMBOL,TABLE[NAME##_##SYMBOL]},
#define MAKE_CONTEXT_INTERNAL(LIST,TABLE) \
CONTEXT_INTERNAL(SET_TABLE,TABLE) LIST.push_back(make_pair("internal",SymbolMap{CONTEXT_INTERNAL(SET_MAP,TABLE)}));
#define MAKE_CONTEXT_GLOBAL(LIST,TABLE) \
CONTEXT_GLOBAL(SET_TABLE,TABLE) LIST.push_back(make_pair("global",SymbolMap{CONTEXT_GLOBAL(SET_MAP,TABLE)}));
#define MAKE_CONTEXT(LIST,TABLE) \
MAKE_CONTEXT_INTERNAL(LIST,TABLE)\
MAKE_CONTEXT_GLOBAL(LIST,TABLE)

#endif
