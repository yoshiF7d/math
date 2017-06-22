#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H
#define TABLE_SIZE 512
/*====== symbol table ======*/
#define CONTEXT_GLOBAL(UNFOLD,TABLE) \
UNFOLD(Depth,TABLE,global)

/*====== symbol id ======*/
#define UNFOLD(SYMBOL,TABLE,NAME) NAME##_##SYMBOL,
enum symbol_id{
	CONTEXT_GLOBAL(UNFOLD,TABLE)
id_end,
};
#undef UNFOLD

/*====== make context ======*/
#define SET_TABLE(SYMBOL,TABLE,NAME) TABLE[NAME##_##SYMBOL]=new SYMBOL();
#define SET_MAP(SYMBOL,TABLE,NAME) {#SYMBOL,TABLE[NAME##_##SYMBOL]},
#define MAKE_CONTEXT_GLOBAL(LIST,TABLE) \
CONTEXT_GLOBAL(SET_TABLE,TABLE) LIST.push_back(make_pair("global",SymbolMap{CONTEXT_GLOBAL(SET_MAP,TABLE)}));
#define MAKE_CONTEXT(LIST,TABLE) \
MAKE_CONTEXT_GLOBAL(LIST,TABLE)

#endif
