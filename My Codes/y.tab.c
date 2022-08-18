/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "1805051.y" /* yacc.c:339  */

#include<bits/stdc++.h>
#include "SymbolTable.cpp"

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;

SymbolTable* table = new SymbolTable(30);

int numLine = 1;
int numError = 0;
int labels = 0;
int variables = 0;
vector<SymbolInfo> parameterList;
vector<string> completedFunc;
string symbolName;
string symbolType;
string calledFunction;
string currentFunction="global";
string code;
string currentDataType = "void";
vector<string> dataString;
vector<pair<string, string>> arraySet; 


void yyerror(char *s)
{
	//write your code
}

FILE* log_file = fopen("1805051_log.txt", "w");
FILE* error_file = fopen("1805051_error.txt", "w");
FILE* code_file = fopen("code.asm", "w");

void printInLogFile(string grammar, int line) {
	string l = "Line " + to_string(line) + ": " + grammar + "\n\n";
	fprintf(log_file, l.c_str());
}

void printToken(string token){
	string l = token + "\n\n";
	fprintf(log_file, l.c_str());
}

void printError(string error, int line){
	string l = "Error at line " + to_string(line) + ": " + error + "\n\n";
	fprintf(log_file, l.c_str());
	fprintf(error_file, l.c_str());
	++numError;
}

string labelHandler(){
	string label = "LABEL" + to_string(labels);
	labels++;
	return label;
}

string varProduce(){
	string var = "t";
	var += to_string(variables);
	variables++;
	return var;
}

string create_template(vector<string> data, string codeString) {
	string finalCode = ".MODEL SMALL\n\
.STACK 100h\n\
.DATA\n\n\
CR EQU 13\nLF EQU 10\n\n";

	for (int i = 0; i < data.size(); i++) {
		finalCode += data[i] + " DW  ?" + "\n";
	}
	for (int i = 0; i < arraySet.size(); i++) {
		finalCode += arraySet[i].first + " DW DUP "+arraySet[i].second+" \n";
	}
	finalCode += "\n.CODE\n\n" + codeString;

	finalCode += "println PROC\n\
\n\
PUSH AX\n\
PUSH BX\n\
PUSH CX\n\
PUSH DX\n\
OR AX, AX\n\
JGE @END_IF1\n\
\n\
PUSH AX\n\
MOV DL, '-'\n\
MOV AH, 2\n\
INT 21H\n\
POP AX\n\
NEG AX\n\
@END_IF1:\n\
XOR CX, CX\n\
MOV BX, 10D\n\
@REPEAT1:\n\
XOR DX, DX\n\
DIV BX\n\
PUSH DX\n\
INC CX\n\
OR AX, AX\n\
JNE @REPEAT1\n\
\n\
MOV AH, 2\n\
@PRINT_LOOP:\n\
POP DX\n\
OR DL, 30H\n\
INT 21H\n\
LOOP @PRINT_LOOP\n\
MOV AH, 2\n\
MOV DL, CR\n\
INT 21H\n\
MOV DL, LF\n\
INT 21H\n\
POP DX\n\
POP CX\n\
POP BX\n\
POP AX\n\
RET\n\
println ENDP\n";

	finalCode += "\nEND MAIN";
	return finalCode;
}



#line 198 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ELSE = 258,
    IF = 259,
    FOR = 260,
    WHILE = 261,
    DO = 262,
    BREAK = 263,
    INT = 264,
    CHAR = 265,
    FLOAT = 266,
    DOUBLE = 267,
    PRINTLN = 268,
    VOID = 269,
    RETURN = 270,
    SWITCH = 271,
    CASE = 272,
    DEFAULT = 273,
    CONTINUE = 274,
    ASSIGNOP = 275,
    NOT = 276,
    LPAREN = 277,
    RPAREN = 278,
    LTHIRD = 279,
    RTHIRD = 280,
    COMMA = 281,
    SEMICOLON = 282,
    LCURL = 283,
    RCURL = 284,
    CONST_INT = 285,
    CONST_FLOAT = 286,
    CONST_CHAR = 287,
    ADDOP = 288,
    MULOP = 289,
    INCOP = 290,
    DECOP = 291,
    RELOP = 292,
    LOGICOP = 293,
    ID = 294,
    LOWER_THAN_ELSE = 295,
    LOWER_THAN_FUNC = 296
  };
#endif
/* Tokens.  */
#define ELSE 258
#define IF 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define PRINTLN 268
#define VOID 269
#define RETURN 270
#define SWITCH 271
#define CASE 272
#define DEFAULT 273
#define CONTINUE 274
#define ASSIGNOP 275
#define NOT 276
#define LPAREN 277
#define RPAREN 278
#define LTHIRD 279
#define RTHIRD 280
#define COMMA 281
#define SEMICOLON 282
#define LCURL 283
#define RCURL 284
#define CONST_INT 285
#define CONST_FLOAT 286
#define CONST_CHAR 287
#define ADDOP 288
#define MULOP 289
#define INCOP 290
#define DECOP 291
#define RELOP 292
#define LOGICOP 293
#define ID 294
#define LOWER_THAN_ELSE 295
#define LOWER_THAN_FUNC 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 135 "1805051.y" /* yacc.c:355  */

     SymbolInfo *symbol;

#line 324 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 341 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   151

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   163,   163,   184,   192,   203,   211,   219,   231,   230,
     255,   278,   282,   277,   368,   367,   424,   453,   462,   478,
     490,   489,   508,   521,   535,   543,   551,   562,   588,   618,
     646,   680,   690,   703,   713,   723,   733,   759,   777,   798,
     819,   837,   855,   863,   875,   896,   932,   941,   970,   978,
    1038,  1046,  1131,  1140,  1178,  1186,  1246,  1268,  1284,  1294,
    1302,  1364,  1373,  1384,  1395,  1407,  1422,  1430,  1439,  1448
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ELSE", "IF", "FOR", "WHILE", "DO",
  "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "PRINTLN", "VOID", "RETURN",
  "SWITCH", "CASE", "DEFAULT", "CONTINUE", "ASSIGNOP", "NOT", "LPAREN",
  "RPAREN", "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON", "LCURL", "RCURL",
  "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "ADDOP", "MULOP", "INCOP",
  "DECOP", "RELOP", "LOGICOP", "ID", "LOWER_THAN_ELSE", "LOWER_THAN_FUNC",
  "$accept", "start", "program", "unit", "func_declaration", "$@1",
  "func_definition", "$@2", "$@3", "$@4", "parameter_list",
  "compound_statement", "$@5", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF -72

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-72)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,   -72,   -72,   -72,    28,     4,   -72,   -72,   -72,   -72,
      -4,   -72,   -72,    10,    -5,    71,    17,    32,     0,   -72,
      47,    23,    19,    34,     4,    55,   -72,    53,   -72,     4,
     -72,   -72,    25,    56,    58,   -72,    61,    57,   -72,    75,
     -72,    93,   -72,   -72,    53,   -72,    81,    83,    87,    88,
      39,    39,    39,   -72,   -72,   -72,    39,    31,   -72,   -72,
      72,    62,   -72,   -72,   -10,    85,   -72,    78,   -14,    79,
     -72,   -72,   -72,    39,   106,    39,    80,    90,    21,   -72,
      95,   -72,    39,    39,    98,   -72,   -72,    39,   -72,   -72,
     -72,    39,    39,    39,    39,   102,   106,   107,   108,   -72,
     -72,   -72,   111,   103,   110,   -72,   -72,    79,   105,   -72,
      93,    39,    93,   113,   -72,    39,   -72,   138,   119,   -72,
     -72,   -72,    93,    93,   -72,   -72
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    24,    25,    26,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    29,     0,     0,     0,     0,     0,    23,
      14,     0,    19,     0,     0,    27,    10,     0,     8,     0,
      18,    30,     0,     0,    20,    15,     0,    17,    12,     0,
      22,     0,     9,    16,     0,    28,     0,     0,     0,     0,
       0,     0,     0,    42,    62,    63,     0,    44,    35,    33,
       0,     0,    31,    34,    59,     0,    46,    48,    50,    52,
      54,    58,    13,     0,     0,     0,     0,     0,    59,    57,
       0,    56,    67,     0,    29,    21,    32,     0,    64,    65,
      43,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      61,    69,     0,    66,     0,    47,    49,    53,    51,    55,
       0,     0,     0,     0,    60,     0,    45,    37,     0,    39,
      40,    68,     0,     0,    38,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   139,   -72,   -72,   -72,   -72,   -72,   -72,
     122,   -24,   -72,    12,     9,   -72,   -72,   -60,   -66,   -51,
     -46,   -71,    52,    54,    59,   -49,   -72,   -72,   -72
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    36,     8,    17,    44,    27,
      21,    58,    41,    59,    60,    14,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,   102,   103
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      78,    86,    79,    35,    77,    78,    80,    81,    96,    10,
      87,   101,     9,     1,    10,     2,   105,     9,     3,    92,
      72,    18,    19,    93,    22,    88,    89,    95,    11,    97,
     111,    78,    15,    22,    16,    13,    78,   104,    37,    25,
      78,    78,    78,    78,   121,   109,    28,    23,    38,    29,
     117,    29,   119,    82,    24,    83,    88,    89,    30,    31,
      51,    52,   124,   125,    78,   118,    46,    47,    48,    54,
      55,     1,    56,     2,    26,    49,     3,    50,    57,    33,
       1,    34,     2,    51,    52,     3,    39,    40,    42,    53,
      34,    85,    54,    55,    20,    56,    43,    46,    47,    48,
      45,    57,     1,    73,     2,    74,    49,     3,    50,    75,
      76,    84,    90,    94,    51,    52,    91,    99,   100,    98,
      53,    34,    16,    54,    55,   110,    56,    51,    52,   115,
     112,   113,    57,    53,   114,   116,    54,    55,    92,    56,
     120,   122,   123,   106,    12,    57,    32,   108,     0,     0,
       0,   107
};

static const yytype_int8 yycheck[] =
{
      51,    61,    51,    27,    50,    56,    52,    56,    74,     0,
      20,    82,     0,     9,     5,    11,    87,     5,    14,    33,
      44,    26,    27,    37,    15,    35,    36,    73,     0,    75,
      96,    82,    22,    24,    24,    39,    87,    83,    29,    39,
      91,    92,    93,    94,   115,    94,    23,    30,    23,    26,
     110,    26,   112,    22,    22,    24,    35,    36,    39,    25,
      21,    22,   122,   123,   115,   111,     4,     5,     6,    30,
      31,     9,    33,    11,    27,    13,    14,    15,    39,    24,
       9,    28,    11,    21,    22,    14,    30,    29,    27,    27,
      28,    29,    30,    31,    23,    33,    39,     4,     5,     6,
      25,    39,     9,    22,    11,    22,    13,    14,    15,    22,
      22,    39,    27,    34,    21,    22,    38,    27,    23,    39,
      27,    28,    24,    30,    31,    23,    33,    21,    22,    26,
      23,    23,    39,    27,    23,    25,    30,    31,    33,    33,
      27,     3,    23,    91,     5,    39,    24,    93,    -1,    -1,
      -1,    92
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    11,    14,    43,    44,    45,    46,    48,    55,
      56,     0,    45,    39,    57,    22,    24,    49,    26,    27,
      23,    52,    56,    30,    22,    39,    27,    51,    23,    26,
      39,    25,    52,    24,    28,    53,    47,    56,    23,    30,
      29,    54,    27,    39,    50,    25,     4,     5,     6,    13,
      15,    21,    22,    27,    30,    31,    33,    39,    53,    55,
      56,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    53,    22,    22,    22,    22,    62,    61,    67,
      62,    67,    22,    24,    39,    29,    59,    20,    35,    36,
      27,    38,    33,    37,    34,    62,    60,    62,    39,    27,
      23,    63,    69,    70,    62,    63,    64,    66,    65,    67,
      23,    60,    23,    23,    23,    26,    25,    59,    62,    59,
      27,    63,     3,    23,    59,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    47,    46,
      46,    49,    50,    48,    51,    48,    52,    52,    52,    52,
      54,    53,    53,    55,    56,    56,    56,    57,    57,    57,
      57,    58,    58,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    67,    68,
      68,    68,    68,    68,    68,    68,    69,    69,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     0,     7,
       5,     0,     0,     8,     0,     6,     4,     3,     2,     1,
       0,     4,     2,     3,     1,     1,     1,     3,     6,     1,
       4,     1,     2,     1,     1,     1,     7,     5,     7,     5,
       5,     3,     1,     2,     1,     4,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     2,     2,     1,     1,
       4,     3,     1,     1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 164 "1805051.y" /* yacc.c:1646  */
    {
				printInLogFile("start : program", numLine);
				symbolName = (yyvsp[0].symbol)->getName();
				symbolType = (yyvsp[0].symbol)->getType();
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				table->printModified(log_file);
				string l;
				l = "Total Lines: " + to_string(numLine) + "\n";
				fprintf(log_file, l.c_str());
				l = "Total Errors: " + to_string(numError) + "\n";
				fprintf(log_file, l.c_str());

				(yyval.symbol)->appendCode((yyvsp[0].symbol)->getCode());
				string codeSnippet = create_template(dataString, (yyval.symbol)->code) + "\n";
				fprintf(code_file, codeSnippet.c_str());
			}
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 185 "1805051.y" /* yacc.c:1646  */
    {
				printInLogFile("program : program unit", numLine);
				symbolName = (yyvsp[-1].symbol)->getName() + (yyvsp[0].symbol)->getName();
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->appendCode((yyvsp[-1].symbol)->getCode() + (yyvsp[0].symbol)->getCode());
			}
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 193 "1805051.y" /* yacc.c:1646  */
    {
				printInLogFile("program : unit", numLine);
				symbolName = (yyvsp[0].symbol)->getName();
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->appendCode((yyvsp[0].symbol)->getCode());
			}
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 204 "1805051.y" /* yacc.c:1646  */
    {
				printInLogFile("unit : var_declaration", numLine);
				symbolName = (yyvsp[0].symbol)->getName() + "\n";
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->appendCode((yyvsp[0].symbol)->getCode());
			}
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 212 "1805051.y" /* yacc.c:1646  */
    {
				printInLogFile("unit : func_declaration", numLine);
				symbolName = (yyvsp[0].symbol)->getName();
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->appendCode((yyvsp[0].symbol)->getCode());
			}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 220 "1805051.y" /* yacc.c:1646  */
    {
				printInLogFile("unit : func_definition", numLine);
				symbolName = (yyvsp[0].symbol)->getName();
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->appendCode((yyvsp[0].symbol)->getCode());
			}
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 231 "1805051.y" /* yacc.c:1646  */
    {
				currentFunction = (yyvsp[-3].symbol)->getName();
				if(table->LookUp(currentFunction) == NULL) {
					SymbolInfo* symbol = new SymbolInfo(currentFunction, "ID");
					symbol->setDataType((yyvsp[-4].symbol)->getName());
					symbol->setKeyType("function");
					for (int i=0; i<parameterList.size(); i++) {
						symbol->addParam(parameterList[i]);
					}
					parameterList.clear();
					table->Insert(*symbol);
				}
				else {
					string error = "Function " + '\"' + currentFunction + '\"' + " declared multiple times\n";
					printError(error, numLine);
				}
			}
#line 1611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 249 "1805051.y" /* yacc.c:1646  */
    {
				printInLogFile("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", numLine);
				symbolName = (yyvsp[-6].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+" "+"("+" "+(yyvsp[-3].symbol)->getName()+" "+")"+" "+";"+"\n";
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
			}
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 256 "1805051.y" /* yacc.c:1646  */
    {
				currentFunction = (yyvsp[-3].symbol)->getName();
				if(table->LookUp(currentFunction) == NULL) {
					SymbolInfo* symbol = new SymbolInfo(currentFunction, "ID");
					symbol->setDataType((yyvsp[-4].symbol)->getName());
					symbol->setKeyType("function");
					table->Insert(*symbol);
				}
				else {
					string error = "Function " + '\"' + currentFunction + '\"' + " declared multiple times\n";
					printError(error, numLine);
				}

				printInLogFile("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", numLine);
				symbolName = (yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+"( );"+"\n";
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
			}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 278 "1805051.y" /* yacc.c:1646  */
    {
				currentFunction = (yyvsp[0].symbol)->getName();
			}
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 282 "1805051.y" /* yacc.c:1646  */
    {
				currentFunction = (yyvsp[-4].symbol)->getName();
				SymbolInfo* s = table->LookUp(currentFunction);
				if(s == NULL) {
					SymbolInfo* symbol = new SymbolInfo(currentFunction, "ID");
					symbol->setDataType((yyvsp[-5].symbol)->getName());
					symbol->setKeyType("function");
					symbol->setParams(parameterList);
					table->Insert(*symbol);
				}
				else {
					for(int i=0; i<completedFunc.size(); i++) {
						if(currentFunction == completedFunc[i]) {
							string l = "Multiple declaration of " + currentFunction;
							printError(l, numLine);
						}
					}
					if(s->getKeyType() != "function"){
						string l = "Multiple declaration of "+currentFunction;
						printError(l, numLine);
					}
					else {
						if ((yyvsp[-5].symbol)->getName() != s->getDataType()){
							string l = "Return type mismatch with function declaration in function "+s->getName();
							printError(l, numLine);
						}
						if (s->getParamsNum() != parameterList.size()) {
							string l = "Total number of arguments mismatch with declaration in function "+currentFunction;
							printError(l, numLine);
						}
						vector<SymbolInfo> parameters = s->getParams();
						int min = parameters.size();
						if (parameterList.size() < min) {
							min = parameterList.size();
						}
						for (int i=0; i<min; i++) {
							if(parameterList[i].getDataType() != parameters[i].getDataType()){
								string l = currentFunction + " parameter type error";
								printError(l, numLine);	
							}
						}
					}
				}
			}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 327 "1805051.y" /* yacc.c:1646  */
    {
				printInLogFile("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement", numLine);
				symbolName = (yyvsp[-7].symbol)->getName()+" "+(yyvsp[-6].symbol)->getName()+" ("+" "+(yyvsp[-3].symbol)->getName()+" )\n"+(yyvsp[0].symbol)->getName();
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");	
				completedFunc.push_back(currentFunction);

				SymbolInfo* s = table->LookUp(currentFunction);
				vector<SymbolInfo> parameters = s->getParams();
				

				(yyval.symbol)->code += currentFunction+" PROC\n";
				for (int i=0; i<parameters.size(); i++) {
					(yyval.symbol)->code += "POP AX\n";
					(yyval.symbol)->code += "MOV "+parameters[i].getVarName()+", AX\n";
				}
				if(currentFunction == "main") {
					(yyval.symbol)->code += "MOV AX, @DATA\n";
					(yyval.symbol)->code += "MOV DS, AX\n";
					(yyval.symbol)->code += "XOR BX, BX\n";
					(yyval.symbol)->code += "XOR CX, CX\n";
				}
				(yyval.symbol)->code += (yyvsp[-7].symbol)->code + (yyvsp[-6].symbol)->code + (yyvsp[-3].symbol)->code + (yyvsp[0].symbol)->code;

				if(currentFunction != "main") {
					if(s->getDataType()!="void"){
						(yyval.symbol)->code += "PUSH AX\n";
					}
					if(parameters.size()>0){
						(yyval.symbol)->code += "RET "+to_string(parameters.size()*2)+"\n";
					}
					else {
						(yyval.symbol)->code += "RET\n";
					}
				}else{
					(yyval.symbol)->code += "\nMOV AH, 4CH\n";
					(yyval.symbol)->code += "INT 21H\n";
				}	
				(yyval.symbol)->code += currentFunction + " ENDP\n"	;
			}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 368 "1805051.y" /* yacc.c:1646  */
    {
				currentFunction = (yyvsp[-2].symbol)->getName();
				if(table->LookUp(currentFunction) == NULL) {
					SymbolInfo* symbol = new SymbolInfo(currentFunction, "ID");
					symbol->setKeyType("function");
					symbol->setDataType((yyvsp[-3].symbol)->getName());
					table->Insert(*symbol);
				}
				else {
					SymbolInfo* symbol = table->LookUp(currentFunction);
					if(symbol->getKeyType() != "function"){
						string l = "Multiple declaration of "+currentFunction;
						printError(l, numLine);
					}
				}
			}
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 385 "1805051.y" /* yacc.c:1646  */
    {
				printInLogFile("func_definition : type_specifier ID LPAREN RPAREN compound_statement", numLine);
				symbolName = (yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+" ("+")\n"+(yyvsp[0].symbol)->getName();
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				completedFunc.push_back(currentFunction);

				(yyval.symbol)->code += currentFunction+" PROC\n";
				if(currentFunction == "main") {
					(yyval.symbol)->code += "MOV AX, @DATA\n";
					(yyval.symbol)->code += "MOV DS, AX\n";
					(yyval.symbol)->code += "XOR BX, BX\n";
					(yyval.symbol)->code += "XOR CX, CX\n";
				}
				else{
					(yyval.symbol)->code += "PUSH AX\n";
					(yyval.symbol)->code += "PUSH BX\n";
					(yyval.symbol)->code += "PUSH CX\n";
					(yyval.symbol)->code += "PUSH DX\n";
				}

				(yyval.symbol)->code += (yyvsp[-5].symbol)->code + (yyvsp[0].symbol)->code;
				
				if(currentFunction != "main"){
					(yyval.symbol)->code += "POP DX\n";
					(yyval.symbol)->code += "POP CX\n";
					(yyval.symbol)->code += "POP BX\n";
					(yyval.symbol)->code += "POP AX\n";
					(yyval.symbol)->code += "RET\n";
				}
				else{
					(yyval.symbol)->code += "MOV AH, 4CH\nINT 21H\n";
				}
				(yyval.symbol)->code += currentFunction + " ENDP\n"	;
			}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 425 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-3].symbol)->getName() + " , " + (yyvsp[-1].symbol)->getName() + " " + (yyvsp[0].symbol)->getName();
				printInLogFile("parameter_list : parameter_list COMMA type_specifier ID", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
				s->setKeyType("variable");
				s->setDataType((yyvsp[-1].symbol)->getName());
				s->setVarName(varProduce());

				int i=0;

				for (; i<parameterList.size(); i++) {
					if(parameterList[i].getName() == s->getName()){
						string l = "Multiple declaration of " + parameterList[i].getName() + " in parameter";
						printError(l, numLine);
						break;
					}
				}
				if(i == parameterList.size()) {   
					parameterList.push_back(*s);

				}
				(yyval.symbol)->code += (yyvsp[-3].symbol)->code + (yyvsp[-1].symbol)->code + (yyvsp[0].symbol)->code;

				dataString.push_back(s->getVarName());
			}
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 454 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-2].symbol)->getName()+" , "+(yyvsp[0].symbol)->getName();
				printInLogFile("parameter_list  : parameter_list COMMA type_specifier", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->code += (yyvsp[-2].symbol)->code + (yyvsp[0].symbol)->code;
			}
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 463 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName();
				printInLogFile("parameter_list  : type_specifier ID", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
				s->setKeyType("variable");
				s->setDataType((yyvsp[-1].symbol)->getName());
				s->setVarName(varProduce());
				parameterList.push_back(*s);
				(yyval.symbol)->code += (yyvsp[-1].symbol)->code + (yyvsp[0].symbol)->code;
				dataString.push_back(s->getName());
			}
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 479 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("parameter_list  : type_specifier", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->code += (yyvsp[0].symbol)->code;
			}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 490 "1805051.y" /* yacc.c:1646  */
    {	
				table->EnterScope();
				for (int i=0; i<parameterList.size(); i++) {
					table->Insert(parameterList[i]);
				}
			}
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 497 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "{\n" + (yyvsp[-1].symbol)->getName() + "}\n";
				printInLogFile("compound_statement : LCURL statements RCURL", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				table->printModified(log_file);
				parameterList.clear();
				table->ExitScope();
				(yyval.symbol)->code += (yyvsp[-1].symbol)->code;
			}
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 509 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "{\n}\n";
				printInLogFile("compound_statement : LCURL statements RCURL", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				table->printModified(log_file);
				parameterList.clear();
			}
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 522 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-2].symbol)->getName() + " " + (yyvsp[-1].symbol)->getName() + " ;";
				printInLogFile("var_declaration : type_specifier declaration_list SEMICOLON", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				if((yyvsp[-2].symbol)->getName() == "void") {
					printError("Variable type cannot be void", numLine);
				}
				(yyval.symbol)->code += (yyvsp[-2].symbol)->code + (yyvsp[-1].symbol)->code;
			}
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 536 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "int";
				printInLogFile("type_specifier : INT", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				currentDataType = symbolName;
			}
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 544 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "float";
				printInLogFile("type_specifier : FLOAT", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				currentDataType = symbolName;
			}
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 552 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "void";
				printInLogFile("type_specifier : VOID", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				currentDataType = symbolName;
			}
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 563 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-2].symbol)->getName() + " , " + (yyvsp[0].symbol)->getName();
				printInLogFile("declaration_list : declaration_list COMMA ID", numLine);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				
				SymbolInfo* s = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
				s->setKeyType("variable");
				s->setDataType(currentDataType);
				s->setVarName(varProduce());
				
				ScopeTable* st = table->getCurrentScope();
				SymbolInfo* temp = st->LookUp(s->getName());
				if (temp != NULL) {
					string l = "Multiple declaration of " + temp->getName();
					printError(l, numLine);
				} 
				else {
					if (currentDataType != "void")
						table->Insert(*s);
				}
				printToken(symbolName);
				if(currentFunction != "global") dataString.push_back(s->getVarName());
				else dataString.push_back(s->getName());
			}
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 589 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-5].symbol)->getName() + " , " + (yyvsp[-3].symbol)->getName() + "[" + (yyvsp[-1].symbol)->getName() + "]";
				printInLogFile("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", numLine);
				
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo((yyvsp[-3].symbol)->getName(), (yyvsp[-3].symbol)->getType());
				s->setKeyType("array");
				s->setDataType(currentDataType);
				s->setVarName(varProduce());
				int size = stoi((yyvsp[-1].symbol)->getName());
				s->setArraySize(size);

				ScopeTable* st = table->getCurrentScope();
				SymbolInfo* temp = st->LookUp(s->getName());
				if (temp != NULL) {
					string l = "Multiple declaration of " + temp->getName();
					printError(l, numLine);
				} 
				else {
					if (currentDataType != "void")
						table->Insert(*s);
				}
				printToken(symbolName);
				if(currentFunction == "global") 
					arraySet.push_back(make_pair((yyvsp[-3].symbol)->getName(), (yyvsp[-1].symbol)->getName()));
				else 
					arraySet.push_back(make_pair(s->getVarName(), (yyvsp[-1].symbol)->getName()));	
			}
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 619 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("declaration_list : ID", numLine);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
				s->setKeyType("variable");
				s->setDataType(currentDataType);
				s->setVarName(varProduce());

				ScopeTable* st = table->getCurrentScope();
				SymbolInfo* temp = st->LookUp(s->getName());
				if (temp != NULL) {
					string l = "Multiple declaration of " + temp->getName();
					printError(l, numLine);
				} 
				else {
					if (currentDataType != "void")
						table->Insert(*s);
				}

				if(currentFunction == "global") 
					dataString.push_back((yyvsp[0].symbol)->getName());
				else dataString.push_back(s->getVarName());
				printToken(symbolName);
			}
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 647 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-3].symbol)->getName() + "[" + (yyvsp[-1].symbol)->getName() + "]";
				printInLogFile("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", numLine);
				
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo((yyvsp[-3].symbol)->getName(), (yyvsp[-3].symbol)->getType());
				s->setKeyType("array");
				s->setDataType(currentDataType);
				s->setVarName(varProduce());
				int size = stoi((yyvsp[-1].symbol)->getName());
				s->setArraySize(size);

				ScopeTable* st = table->getCurrentScope();
				SymbolInfo* temp = st->LookUp(s->getName());
				if (temp != NULL) {
					string l = "Multiple declaration of " + temp->getName();
					printError(l, numLine);
				}
				else {
					if (currentDataType != "void")
						table->Insert(*s);
				}
				printToken(symbolName);
				if(currentFunction == "global") 
					arraySet.push_back(make_pair((yyvsp[-3].symbol)->getName(), (yyvsp[-1].symbol)->getName()));
				else
					arraySet.push_back(make_pair(s->getVarName(), (yyvsp[-1].symbol)->getName()));

			}
#line 2111 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 681 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();

				printInLogFile("statements : statement", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->code += (yyvsp[0].symbol)->code;
			}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 691 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-1].symbol)->getName() + (yyvsp[0].symbol)->getName();

				printInLogFile("statements : statements statement", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->code += (yyvsp[-1].symbol)->code + (yyvsp[0].symbol)->code;
			}
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 704 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName() + "\n";

				printInLogFile("statement : var_declaration", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->code += (yyvsp[0].symbol)->code;
			}
#line 2153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 714 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName() + "\n";

				printInLogFile("statement : expression_statement", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->code += (yyvsp[0].symbol)->code;
			}
#line 2167 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 724 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName() + "\n";

				printInLogFile("statement : compound_statement", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->code += (yyvsp[0].symbol)->code;
			}
#line 2181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 735 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "for ( " + (yyvsp[-4].symbol)->getName() + " " + (yyvsp[-3].symbol)->getName() + " " + (yyvsp[-2].symbol)->getName() + " )\n" + (yyvsp[0].symbol)->getName() + "\n";

				printInLogFile("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				string temp = (yyvsp[-4].symbol)->code;
				string l1 = labelHandler();
				temp += l1 + ":\n";
				temp += (yyvsp[-3].symbol)->code;
				temp += "MOV BX, 0\n";
				temp += "CMP AX, BX\n";
				string l2 = labelHandler();
				temp += "JE " + l2 + "\n";
				temp += (yyvsp[0].symbol)->code;
				temp += (yyvsp[-2].symbol)->code;
				temp += "JMP " + l1 + "\n";
				temp += l2 + ":\n";
				code = temp;

				(yyval.symbol)->code += temp;
			}
#line 2210 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 760 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "if ( " + (yyvsp[-2].symbol)->getName() + " )\n" + (yyvsp[0].symbol)->getName() + "\n";

				printInLogFile("statement : IF LPAREN expression RPAREN statement", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				string l = labelHandler();
				string temp = (yyvsp[-2].symbol)->code;
				temp += "MOV AX, "+(yyvsp[-2].symbol)->getName()+"\n";
				temp += "CMP AX, 0\n";
				temp += "JE " + l + "\n";
				temp += (yyvsp[0].symbol)->code;
				temp += l + ":\n";
				(yyval.symbol)->code += temp;
			}
#line 2232 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 778 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "if ( " + (yyvsp[-4].symbol)->getName() + " )\n" + (yyvsp[-2].symbol)->getName() + "else\n" + (yyvsp[0].symbol)->getName() + "\n";

				printInLogFile("statement : IF LPAREN expression RPAREN statement ELSE statement", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				string l1 = labelHandler();
				string l2 = labelHandler();
				string temp = (yyvsp[-4].symbol)->code;
				temp += "MOV AX, "+(yyvsp[-4].symbol)->getName()+"\n";
				temp += "CMP AX, 0\n";
				temp += "JE " + l1 + "\n";
				temp += (yyvsp[-2].symbol)->code;
				temp += "JMP " + l2 + "\n";
				temp += l1 + ":\n";
				temp += (yyvsp[0].symbol)->code;
				temp += l2 + ":\n";
				(yyval.symbol)->code += temp;
			}
#line 2257 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 799 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "while ( " + (yyvsp[-2].symbol)->getName() + " )\n" + (yyvsp[0].symbol)->getName() + "\n";

				printInLogFile("statement : WHILE LPAREN expression RPAREN statement", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				string l1 = labelHandler();
				string l2 = labelHandler();
				string temp = l1 + ":\n";
				temp += (yyvsp[-2].symbol)->code;
				temp += "MOV AX, "+(yyvsp[-2].symbol)->getName()+"\n";
				temp += "CMP AX, 0\n";
				temp += "JE " + l2 + "\n";
				temp += (yyvsp[0].symbol)->code;
				temp += "JMP " + l1 + "\n";
				temp += l2 + ":\n";
				code = temp;
				(yyval.symbol)->code += temp;
			}
#line 2282 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 820 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "printf ( " + (yyvsp[-2].symbol)->getName() + " );" + "\n";
				printInLogFile("statement : PRINTLN LPAREN ID RPAREN SEMICOLON", numLine);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = table->LookUp((yyvsp[-2].symbol)->getName());
				if(s == NULL) {
					string l = "Undeclared variable "+(yyvsp[-2].symbol)->getName();
					printError(l, numLine);
				}
				printToken(symbolName);
				if(currentFunction == "global")
					code = "MOV AX, " + (yyvsp[-2].symbol)->getName() + "\nCALL println\n";
				else
					code = "MOV AX, " + (yyvsp[-2].symbol)->getVarName() + "\nCALL println\n"; 
				(yyval.symbol)->code += code;
			}
#line 2304 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 838 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "return " + (yyvsp[-1].symbol)->getName() + ";" + "\n";

				printInLogFile("statement : RETURN expression SEMICOLON", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				SymbolInfo* cf = table->LookUp(currentFunction);
				if(cf->getDataType() == "void") {
					printError("returning with a value but in function definition, returning type is void", numLine);
				}
				else if(cf->getDataType() != (yyvsp[-1].symbol)->getDataType()) {
					printError("Function return type error", numLine);
				}
			}
#line 2324 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 856 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = ";";
				printInLogFile("expression_statement : SEMICOLON", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
			}
#line 2336 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 864 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-1].symbol)->getName() + ";";
				printInLogFile("expression_statement : expression SEMICOLON", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->code += (yyvsp[-1].symbol)->code;
			}
#line 2349 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 876 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("variable : ID", numLine);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				SymbolInfo* s = table->LookUp((yyvsp[0].symbol)->getName());
				if(s == NULL){
					printError("Undeclared variable "+symbolName, numLine);
					(yyval.symbol)->setKeyType("variable");
					(yyval.symbol)->setDataType("none");
				}
				else {
					if(s->getKeyType() == "array"){
						string l = "Type mismatch, "+s->getName()+ " is an array";
						printError(l, numLine);		
					}
					(yyval.symbol) = s;
				}
				printToken(symbolName);
			}
#line 2374 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 897 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-3].symbol)->getName() + "[" + (yyvsp[-1].symbol)->getName() + "]";
				printInLogFile("variable : ID LTHIRD expression RTHIRD", numLine);

				SymbolInfo* s = table->LookUp((yyvsp[-3].symbol)->getName());

				if(s == NULL){
					printError("Undeclared variable "+symbolName, numLine);
					(yyval.symbol) = new SymbolInfo(symbolName, "array");
					(yyval.symbol)->setKeyType("array");
					(yyval.symbol)->setDataType("none");
				}
				else {
					if(s->getKeyType() != "array") {
						string l = "Type mismatch, "+s->getName()+ " is not an array";
						printError(l, numLine);		
					}
					if((yyvsp[-1].symbol)->getDataType() != "int") {
						printError("Expression inside third brackets not an integer", numLine);
					}
					(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
					(yyval.symbol)->setKeyType("array");
					(yyval.symbol)->setDataType(s->getDataType());
					(yyval.symbol)->code += (yyvsp[-3].symbol)->code + (yyvsp[-1].symbol)->code;
					(yyval.symbol)->code += "MOV BX, " + (yyvsp[-1].symbol)->getVarName() + "\n";
					(yyval.symbol)->code += "ADD BX, BX\n";
					(yyval.symbol)->setName((yyvsp[-3].symbol)->getVarName() + "[BX]");
				}
				printToken(symbolName);

				
			}
#line 2411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 933 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("expression : logic_expression", numLine);
				printToken(symbolName);

				(yyval.symbol) = (yyvsp[0].symbol);
			}
#line 2423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 942 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-2].symbol)->getName() + " = " + (yyvsp[0].symbol)->getName();
				printInLogFile("expression : variable ASSIGNOP logic_expression", numLine);

				if((yyvsp[-2].symbol)->getDataType() != "" && (yyvsp[0].symbol)->getDataType() != "") {
					if((yyvsp[-2].symbol)->getDataType() == "void" || (yyvsp[0].symbol)->getDataType() == "void") {
						printError("Void function used in expression", numLine);
					}
					else if((yyvsp[-2].symbol)->getDataType() != "none") {
						string d1 = (yyvsp[-2].symbol)->getDataType();
						string d2 = (yyvsp[0].symbol)->getDataType();
						if(d1 != "float" && d2 == "float") {
							printError("Type mismatch", numLine);
						}
					}
				}

				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				SymbolInfo* s = table->LookUp((yyvsp[-2].symbol)->getName());
				(yyval.symbol)->code += (yyvsp[-2].symbol)->code + (yyvsp[0].symbol)->code;
				if((yyvsp[0].symbol)->getName() != (yyvsp[-2].symbol)->getVarName()) {
					(yyval.symbol)->code += "MOV AX, " + (yyvsp[0].symbol)->getName() + "\n";
					(yyval.symbol)->code += "MOV " + (yyvsp[-2].symbol)->getVarName() + ", AX\n";
				}
			}
#line 2454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 971 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("logic_expression : rel_expression", numLine);
				printToken(symbolName);

				(yyval.symbol) = (yyvsp[0].symbol);
			}
#line 2466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 979 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-2].symbol)->getName() + " " + (yyvsp[-1].symbol)->getName() + " " + (yyvsp[0].symbol)->getName();
				printInLogFile("logic_expression : rel_expression LOGICOP rel_expression", numLine);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->setDataType("int");

				if((yyvsp[-2].symbol)->getDataType()=="void" || (yyvsp[0].symbol)->getDataType()=="void" ){
					printError("Void function used in expression", numLine);				
				}
				printToken(symbolName);
				string temp = (yyvsp[-2].symbol)->code + (yyvsp[0].symbol)->code;
				temp += "MOV AX, " + (yyvsp[-2].symbol)->getName() + "\n";
				temp += "MOV BX, " + (yyvsp[0].symbol)->getName() + "\n";

				if((yyvsp[-1].symbol)->getName()=="&&"){
					string l1 = labelHandler();
					string l2 = labelHandler();
					string t1 = varProduce();
					dataString.push_back(t1);

					temp += "CMP AX, 0\n";
					temp += "JE " + l1 + "\n";
					temp += "CMP BX, 0\n";
					temp += "JE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 0\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += l2 + ":\n";
					(yyval.symbol)->setName(t1);
				}
				else if((yyvsp[-1].symbol)->getName()=="||"){
					string l1 = labelHandler();
					string l2 = labelHandler();
					string t1 = varProduce();
					dataString.push_back(t1);

					temp += "CMP AX, 0\n";
					temp += "JNE " + l1 + "\n";
					temp += "CMP BX, 0\n";
					temp += "JNE " + l1 + "\n";
					temp += "MOV AX, 0\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 1\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += l2 + ":\n";
					(yyval.symbol)->setName(t1);
				}
				code = temp;
				(yyval.symbol)->code += temp;
			}
#line 2527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1039 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("rel_expression : simple_expression", numLine);
				printToken(symbolName);

				(yyval.symbol) = (yyvsp[0].symbol);
			}
#line 2539 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1047 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-2].symbol)->getName() + " " + (yyvsp[-1].symbol)->getName() + " " + (yyvsp[0].symbol)->getName();
				printInLogFile("rel_expression : simple_expression RELOP simple_expression", numLine);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->setDataType("int");

				if((yyvsp[-2].symbol)->getDataType()=="void" || (yyvsp[0].symbol)->getDataType()=="void" ){
					printError("Void function used in expression", numLine);				
				}

				printToken(symbolName);

				string temp = (yyvsp[-2].symbol)->code + (yyvsp[0].symbol)->code;
				string l1 = labelHandler();
				string t1 = varProduce();
				string t2 = varProduce();
				dataString.push_back(t1);
				dataString.push_back(t2);

				temp += "MOV AX, 0\n";
				temp += "MOV " + t1 + ", AX\n";
				temp += "MOV " + t2 + ", AX\n";
				temp += "MOV AX, " + (yyvsp[-2].symbol)->getName() + "\n";
				temp += "MOV BX, " + (yyvsp[0].symbol)->getName() + "\n";
				temp += "CMP AX, BX\n";

				if((yyvsp[-1].symbol)->getName() == "==") {
					temp += "JNE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += "MOV " + t2 + ", AX\n";
					temp += l1 + ":\n";
					temp += "MOV AX, "+ t2 + "\n";
				}
				else if((yyvsp[-1].symbol)->getName() == "!="){
					temp += "JE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += "MOV " + t2 + ", AX\n";
					temp += l1 + ":\n";
					temp += "MOV AX, "+ t2 + "\n";
				} 
				else if((yyvsp[-1].symbol)->getName() == ">="){
					temp += "JNGE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += "MOV " + t2 + ", AX\n";
					temp += l1 + ":\n";
					temp += "MOV AX, "+ t2 + "\n";
				}
				else if((yyvsp[-1].symbol)->getName() == "<="){
					temp += "JNLE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += "MOV " + t2 + ", AX\n";
					temp += l1 + ":\n";
					temp += "MOV AX, "+ t2 + "\n";
				}
				else if((yyvsp[-1].symbol)->getName() == ">"){
					temp += "JNG " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += "MOV " + t2 + ", AX\n";
					temp += l1 + ":\n";
					temp += "MOV AX, "+ t2 + "\n";
				}
				else if((yyvsp[-1].symbol)->getName() == "<"){
					temp += "JNL " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "MOV " + t1 + ", AX\n";
					temp += "MOV " + t2 + ", AX\n";
					temp += l1 + ":\n";
					temp += "MOV AX, "+ t2 + "\n";
				}

				code = temp;
				(yyval.symbol)->code += temp;
				(yyval.symbol)->setName(t1);

			}
#line 2625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1132 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("simple_expression : term", numLine);
				printToken(symbolName);

				(yyval.symbol) = (yyvsp[0].symbol);
			}
#line 2637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1141 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-2].symbol)->getName() + " " + (yyvsp[-1].symbol)->getName() + " " + (yyvsp[0].symbol)->getName();
				printInLogFile("simple_expression : simple_expression ADDOP term", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				if((yyvsp[-2].symbol)->getDataType()=="void" || (yyvsp[0].symbol)->getDataType()=="void" ){
					printError("Void function used in expression", numLine);								
				}
				else if((yyvsp[-2].symbol)->getDataType()=="float" || (yyvsp[0].symbol)->getDataType()=="float"){
					(yyval.symbol)->setDataType("float");
				}
				else if((yyvsp[-2].symbol)->getDataType()=="int" || (yyvsp[0].symbol)->getDataType()=="int"){
					(yyval.symbol)->setDataType("int");
				}

				string temp = (yyvsp[-2].symbol)->code + (yyvsp[0].symbol)->code;
				temp += "MOV AX, " + (yyvsp[-2].symbol)->getName() + "\n";
				temp += "MOV BX, " + (yyvsp[0].symbol)->getName() + "\n";
				string t = varProduce();
				dataString.push_back(t);

				if((yyvsp[-1].symbol)->getName() == "+"){
					temp += "ADD AX, BX\n";
					temp += "MOV " + t + ", AX\n";
				}
				else if((yyvsp[-1].symbol)->getName() == "-"){
					temp += "SUB AX, BX\n";
					temp += "MOV " + t + ", AX\n";
				}
				(yyval.symbol)->code += temp;
				(yyval.symbol)->setName(t);
			}
#line 2676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1179 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("term : unary_expression", numLine);
				printToken(symbolName);

				(yyval.symbol) = (yyvsp[0].symbol);
			}
#line 2688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1187 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-2].symbol)->getName() + " " + (yyvsp[-1].symbol)->getName() + " " + (yyvsp[0].symbol)->getName();
				printInLogFile("term : term MULOP unary_expression", numLine);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				if((yyvsp[-2].symbol)->getDataType() == "void" || (yyvsp[0].symbol)->getDataType() == "void" ){
					printError("Void function used in expression", numLine);								
				}
				if((yyvsp[-1].symbol)->getName() == "%") {
					if((yyvsp[-2].symbol)->getDataType() != "int" || (yyvsp[0].symbol)->getDataType() != "int"){
						printError("Non-Integer operand on modulus operator", numLine);			
					}
					if((yyvsp[0].symbol)->getName() == "0"){
						printError("Modulus by Zero", numLine);									
					}
					(yyval.symbol)->setDataType("int");
				}
				else{
					if((yyvsp[-1].symbol)->getName() == "/" && (yyvsp[0].symbol)->getName() == "0"){
						printError("Division by Zero", numLine);
					}
					if((yyvsp[-2].symbol)->getDataType() == "float" || (yyvsp[0].symbol)->getDataType() == "float"){
						(yyval.symbol)->setDataType("float");
					}
					else{
						(yyval.symbol)->setDataType("int");
					}
				}
				printToken(symbolName);
//check here
				string temp = (yyvsp[-2].symbol)->code + (yyvsp[0].symbol)->code;
				temp += "MOV AX, " + (yyvsp[-2].symbol)->getName() + "\n";
				temp += "MOV BX, " + (yyvsp[0].symbol)->getName() + "\n";
				string t = varProduce();
				dataString.push_back(t);
				if((yyvsp[-1].symbol)->getName() == "*"){
					temp += "MUL BX\n";
					temp += "MOV " + t + ", AX\n";
				}
				else if((yyvsp[-1].symbol)->getName() == "/"){
					temp += "XOR DX, DX\n";
					temp += "CWD\n";
					temp += "IDIV BX\n";
					temp += "MOV " + t + ", AX\n";
				}
				else if((yyvsp[-1].symbol)->getName() == "%"){
					temp += "XOR DX, DX\n";
					temp += "CWD\n";
					temp += "IDIV BX\n";
					temp += "MOV " + t + ", DX\n";
				}
				
				(yyval.symbol)->code += temp;
				(yyval.symbol)->setName(t);
			}
#line 2749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1247 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-1].symbol)->getName() + (yyvsp[0].symbol)->getName();
				printInLogFile("unary_expression : ADDOP unary_expression", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->setDataType((yyvsp[0].symbol)->getDataType());
				(yyval.symbol)->code = (yyvsp[0].symbol)->code;
				string t = varProduce();
				dataString.push_back(t);
				if((yyvsp[-1].symbol)->getName() == "-") {
					(yyval.symbol)->code += "MOV AX, " + (yyvsp[0].symbol)->getName() + "\n";
					(yyval.symbol)->code += "NEG AX\n";
					(yyval.symbol)->code += "MOV " + t + ", AX\n";
				}
				else{
					(yyval.symbol)->code += "MOV AX, " + (yyvsp[0].symbol)->getName() + "\n";
					(yyval.symbol)->code += "MOV " + t + ", " + (yyvsp[0].symbol)->getName() + "\n";
				}
				(yyval.symbol)->setName(t);
			}
#line 2775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1269 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = "! " + (yyvsp[0].symbol)->getName();
				printInLogFile("unary_expression : NOT unary_expression", numLine);
				printToken(symbolName);

				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				(yyval.symbol)->setDataType((yyvsp[0].symbol)->getDataType());

				string t = varProduce();
				dataString.push_back(t);
				(yyval.symbol)->code += "MOV AX, " + (yyvsp[0].symbol)->getName() + "\n";
				(yyval.symbol)->code += "NOT AX\n";
				(yyval.symbol)->code += "MOV " + t + ", AX\n";
				(yyval.symbol)->setName(t);
			}
#line 2795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1285 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("unary_expression : factor", numLine);
				printToken(symbolName);

				(yyval.symbol) = (yyvsp[0].symbol);
			}
#line 2807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1295 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("factor : variable", numLine);
				printToken(symbolName);

				(yyval.symbol) = (yyvsp[0].symbol);
			}
#line 2819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1303 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-3].symbol)->getName() +  " ( " + (yyvsp[-1].symbol)->getName() + " )";
				printInLogFile("factor : ID LPAREN argument_list RPAREN", numLine);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");

				calledFunction = (yyvsp[-3].symbol)->getName();

				SymbolInfo* s = table->LookUp((yyvsp[-3].symbol)->getName());
				if(s == NULL){
					if(calledFunction != "println"){
						string l = "Undeclared function " + calledFunction;
						printError(l, numLine);
						parameterList.clear();
					}
				}
				else {
					vector<SymbolInfo> params = s->getParams();
					int size = s->getParamsNum();

					if (size != parameterList.size()) {
						string l = "Total number of arguments mismatch in function " + calledFunction;
						printError(l, numLine);
						if (size > parameterList.size()) size = parameterList.size(); 
					} 
					for(int i=0; i<size; i++){			
						if(params[i].getDataType() != parameterList[i].getDataType()){
							if(params[i].getDataType()=="float" && parameterList[i].getDataType()=="int") {}
							else{
								string l = to_string(i+1) + "th argument mismatch in function " + calledFunction;
								printError(l, numLine);			
								break;
							}
						}
					}							
					
					(yyval.symbol)->setDataType(s->getDataType());
				}
				printToken(symbolName);
				if((yyvsp[-3].symbol)->getName() != "println"){
					for(auto i: parameterList){
						(yyval.symbol)->code += "MOV AX, " + i.getName() + "\n";
						(yyval.symbol)->code += "PUSH AX\n";
					}
					parameterList.clear();
					(yyval.symbol)->code += "CALL " + calledFunction + "\n";
					if (s != NULL && s->getDataType()!="void") {
						(yyval.symbol)->code += "POP AX\n";
						string t = varProduce();
						dataString.push_back(t);
						(yyval.symbol)->code += "MOV " + t + ", AX\n";
						(yyval.symbol)->setName(t);
					}
				}
				else {
					for(auto i: parameterList){
						(yyval.symbol)->code += "MOV AX, " + i.getName() + "\n";
					}
					parameterList.clear();
					(yyval.symbol)->code += "CALL " + calledFunction + "\n";
				}
			}
#line 2885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1365 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = " ( " + (yyvsp[-1].symbol)->getName() + " )";
				printInLogFile("factor : LPAREN expression RPAREN", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo((yyvsp[-1].symbol)->getName(), "NON_TERMINAL");
				(yyval.symbol)->setDataType((yyvsp[-1].symbol)->getDataType());
				(yyval.symbol)->code += (yyvsp[-1].symbol)->code;
			}
#line 2898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1374 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("factor : CONST_INT", numLine);
				printToken(symbolName);
				(yyval.symbol) = (yyvsp[0].symbol);
				(yyval.symbol)->setKeyType("value");
				(yyval.symbol)->setDataType("int");
				code = "MOV AX, " + (yyvsp[0].symbol)->getName() + "\n";
				(yyval.symbol)->code += code;
			}
#line 2913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1385 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("factor : CONST_FLOAT", numLine);
				printToken(symbolName);
				(yyval.symbol) = (yyvsp[0].symbol);
				(yyval.symbol)->setKeyType("value");
				(yyval.symbol)->setDataType("float");
				code = "MOV AX, " + (yyvsp[0].symbol)->getName() + "\n";
				(yyval.symbol)->code += code;
			}
#line 2928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1396 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-1].symbol)->getName() + (yyvsp[0].symbol)->getName();
				printInLogFile("factor : variable INCOP", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				code = "MOV AX, " + (yyvsp[-1].symbol)->getName() + "\n";
				code += "INC AX\n";
				code += "MOV " + (yyvsp[-1].symbol)->getName() + ", AX\n";
				(yyval.symbol)->code += code;
				(yyval.symbol)->setName((yyvsp[-1].symbol)->getName());
			}
#line 2944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1408 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-1].symbol)->getName() + (yyvsp[0].symbol)->getName();
				printInLogFile("factor : variable DECOP", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				code = "MOV AX, " + (yyvsp[-1].symbol)->getName() + "\n";
				code += "DEC AX\n";
				code += "MOV " + (yyvsp[-1].symbol)->getName() + ", AX\n";
				(yyval.symbol)->code += code;
				(yyval.symbol)->setName((yyvsp[-1].symbol)->getName());
			}
#line 2960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1423 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("argument_list : arguments", numLine);
				printToken(symbolName);
				(yyval.symbol) = (yyvsp[0].symbol);
			}
#line 2971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1430 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = " ";
				printInLogFile("argument_list : ", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
			}
#line 2982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1440 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[-2].symbol)->getName() + " , " + (yyvsp[0].symbol)->getName();
				printInLogFile("arguments : arguments COMMA logic_expression", numLine);
				printToken(symbolName);
				(yyval.symbol) = new SymbolInfo(symbolName, "NON_TERMINAL");
				parameterList.push_back(*(yyvsp[0].symbol));
				(yyval.symbol)->code = (yyvsp[-2].symbol)->code + (yyvsp[0].symbol)->code;
			}
#line 2995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1449 "1805051.y" /* yacc.c:1646  */
    {
				symbolName = (yyvsp[0].symbol)->getName();
				printInLogFile("arguments : logic_expression", numLine);
				printToken(symbolName);
				(yyval.symbol) = (yyvsp[0].symbol);
				parameterList.push_back(*(yyvsp[0].symbol));
			}
#line 3007 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3011 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1458 "1805051.y" /* yacc.c:1906  */

int main(int argc,char *argv[])
{
	FILE* fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	yyin=fp;
	yyparse();

	fclose(log_file);
	fclose(error_file);
	fclose(yyin);
	return 0;
}

