#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#define ATT_TABLE(ATT_FUNC) \
ATT_FUNC(Orderless,0x0001) \
ATT_FUNC(Flat,0x0002) \
ATT_FUNC(OneIdentity,0x0004) \
ATT_FUNC(Listable,0x0008) \
ATT_FUNC(Constant,0x0010) \
ATT_FUNC(NumericFunction,0x0020) \
ATT_FUNC(Protected,0x0040) \
ATT_FUNC(Locked,0x0080) \
ATT_FUNC(ReadProtected,0x0100) \
ATT_FUNC(HoldFirst,0x0200) \
ATT_FUNC(HoldRest,0x0400) \
ATT_FUNC(HoldAll,0x0800) \
ATT_FUNC(HoldAllComplete,0x1000) \
ATT_FUNC(SequenceHold,0x2000) \
ATT_FUNC(Temporary,0x4000) \
ATT_FUNC(NHoldAll,0x08000) \

#define ATT_ENUM(ATT,VAL) ATT=VAL,
enum Attributes{ATT_TABLE(ATT_ENUM)};
#undef ATT_TABLE
#undef ATT_ENUM
#endif