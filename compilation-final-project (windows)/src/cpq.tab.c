
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "cpq.y"

#include <stdio.h>
#include "names.h"
#include "instructions.h"
#include <malloc.h>

extern FILE *yyout;
extern int line;
extern int column;

int error_exist = 0;
name_list *current_symbol = NULL, *next_symbol = NULL;
instruction *curr_ins = NULL;
ins_list *boolist = NULL;
char ident_type;
char compare_type;


/* Line 189 of yacc.c  */
#line 92 "cpq.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     ID = 259,
     START = 260,
     END = 261,
     DECLARATIONS = 262,
     INT = 263,
     FLOAT = 264,
     PRINT = 265,
     READ = 266,
     ASSIGNOP = 267,
     IVAL = 268,
     RVAL = 269,
     IF = 270,
     THEN = 271,
     OTHERWISE = 272,
     WHILE = 273,
     DO = 274,
     FOR = 275,
     ADDOP = 276,
     NUM = 277,
     MULOP = 278,
     OROP = 279,
     ANDOP = 280,
     RELOP = 281
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 21 "cpq.y"

	struct number{
		char value[MAX_CPL_LENGTH];
		char type;
	} num;

	char id[MAX_CPL_LENGTH];
	
	char type;
	
	struct exp{
		instruction *head;
		char last[MAX_CPL_LENGTH];
		char type;
	} expression;
	
	struct bool{
		ins_list *false;
		instruction *head;
	} boolean;

	char arop; 
	
	instruction *stmt;
	
	int relop; 



/* Line 214 of yacc.c  */
#line 184 "cpq.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 196 "cpq.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  179

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,     2,     2,     2,     2,     2,
      33,    32,     2,     2,    31,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    29,    30,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    28,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    12,    20,    28,    34,    37,    38,    39,
      46,    47,    53,    57,    63,    67,    69,    74,    77,    79,
      81,    84,    87,    88,    91,    93,    96,    99,   101,   104,
     107,   110,   115,   120,   125,   130,   134,   139,   146,   153,
     162,   169,   178,   185,   192,   198,   203,   213,   222,   231,
     240,   244,   248,   254,   260,   264,   266,   270,   272,   277,
     281,   285,   287,   291,   293,   297,   299
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,     3,     4,    27,    37,     5,    43,     6,
      28,    -1,     1,    27,    37,     5,    43,     6,    28,    -1,
       3,     4,    27,    37,     5,    43,    28,    -1,     3,     4,
      27,    43,    28,    -1,     7,    38,    -1,    -1,    -1,    38,
      42,    29,    39,    41,    30,    -1,    -1,    42,    29,    40,
      41,    30,    -1,    38,     1,    30,    -1,     1,    42,    29,
      41,    30,    -1,    41,    31,     4,    -1,     4,    -1,    41,
      31,     1,    30,    -1,     1,    31,    -1,     8,    -1,     9,
      -1,     1,    30,    -1,    43,    44,    -1,    -1,    48,    30,
      -1,    49,    -1,    46,    30,    -1,    45,    30,    -1,    50,
      -1,    47,    30,    -1,     1,    30,    -1,     1,    32,    -1,
      10,    33,    55,    32,    -1,    10,    33,     1,    32,    -1,
      11,    33,     4,    32,    -1,    11,    33,     1,    32,    -1,
       4,    12,    55,    -1,     1,    12,    55,    30,    -1,     4,
      12,    13,    33,    55,    32,    -1,     4,    12,    14,    33,
      55,    32,    -1,    15,    33,    52,    32,    16,    44,    17,
      44,    -1,    15,     1,    16,    44,    17,    44,    -1,    15,
      33,    52,    32,    16,    44,     1,    30,    -1,    15,    33,
      52,    32,     1,    30,    -1,    18,    33,    52,    32,    19,
      44,    -1,    18,     1,    19,    44,    30,    -1,    18,    33,
       1,    32,    -1,    20,    33,    47,    30,    52,    30,    51,
      32,    44,    -1,    20,    33,    47,    30,     1,    30,    51,
      32,    -1,    20,    33,    47,    30,    52,    30,     1,    32,
      -1,    20,    33,     1,    30,    52,    30,    51,    32,    -1,
      20,     1,    30,    -1,    27,    43,    28,    -1,     4,    12,
       4,    21,    22,    -1,     4,    12,     4,    23,    22,    -1,
      52,    24,    53,    -1,    53,    -1,    53,    25,    54,    -1,
      54,    -1,    34,    33,    52,    32,    -1,    55,    26,    55,
      -1,    55,    21,    56,    -1,    56,    -1,    56,    23,    57,
      -1,    57,    -1,    33,    55,    32,    -1,     4,    -1,    22,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    95,    95,   102,   103,   104,   107,   108,   111,   111,
     112,   112,   113,   114,   117,   121,   125,   126,   129,   130,
     131,   134,   135,   138,   139,   140,   141,   142,   143,   144,
     145,   148,   153,   156,   164,   167,   168,   171,   176,   182,
     193,   194,   195,   197,   209,   210,   212,   226,   227,   228,
     229,   232,   235,   236,   239,   250,   257,   262,   269,   276,
     287,   292,   300,   305,   313,   319,   333
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ID", "START", "END",
  "DECLARATIONS", "INT", "FLOAT", "PRINT", "READ", "ASSIGNOP", "IVAL",
  "RVAL", "IF", "THEN", "OTHERWISE", "WHILE", "DO", "FOR", "ADDOP", "NUM",
  "MULOP", "OROP", "ANDOP", "RELOP", "'{'", "'}'", "':'", "';'", "','",
  "')'", "'('", "'!'", "$accept", "program", "declarations", "declarlist",
  "$@1", "$@2", "idents", "type", "stmtlist", "stmt", "write_stmt",
  "read_stmt", "assignment_stmt", "val", "control_stmt", "stmt_block",
  "step", "boolexpr", "boolterm", "boolfactor", "expression", "term",
  "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   123,   125,    58,
      59,    44,    41,    40,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    36,    36,    36,    37,    37,    39,    38,
      40,    38,    38,    38,    41,    41,    41,    41,    42,    42,
      42,    43,    43,    44,    44,    44,    44,    44,    44,    44,
      44,    45,    45,    46,    46,    47,    47,    48,    48,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    50,    51,    51,    52,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    57,    57
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     8,     7,     7,     5,     2,     0,     0,     6,
       0,     5,     3,     5,     3,     1,     4,     2,     1,     1,
       2,     2,     0,     2,     1,     2,     2,     1,     2,     2,
       2,     4,     4,     4,     4,     3,     4,     6,     6,     8,
       6,     8,     6,     6,     5,     4,     9,     8,     8,     8,
       3,     3,     5,     5,     3,     1,     3,     1,     4,     3,
       3,     1,     3,     1,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     7,     0,     1,     0,     0,    22,
       0,    18,    19,     0,     0,    22,     0,     0,     0,    20,
       0,     0,     0,    10,     0,    22,     0,     0,     0,     0,
       0,     0,     0,    22,     5,    21,     0,     0,     0,     0,
      24,    27,     0,    12,     8,     0,     0,     0,     0,    29,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,    25,    28,    23,     0,    15,     0,     0,     0,
       3,     0,     4,    65,    66,     0,     0,    61,    63,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     0,    55,
      57,     0,     0,     0,     0,    50,     0,     0,     0,    51,
      17,    13,     0,     0,    11,     2,     0,     0,    36,     0,
       0,     0,    32,    31,    34,    33,     0,     0,     0,     0,
       0,     0,     0,    45,     0,     0,     0,     0,     0,    14,
       9,    64,    60,    62,     0,     0,     0,     0,    54,     0,
       0,    56,    59,    44,     0,     0,     0,     0,    16,    37,
      38,    40,    58,    42,     0,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    39,     0,    49,
      47,    48,     0,     0,    46,     0,     0,    52,    53
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     8,    13,    68,    45,    67,    14,    17,    35,
      36,    37,    38,    39,    40,    41,   162,    88,    89,    90,
      91,    77,    78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -87
static const yytype_int16 yypact[] =
{
      21,     9,    90,   101,   102,   104,   -87,   105,   119,    58,
      43,   -87,   -87,   143,   114,   -87,   133,    92,   137,   -87,
     142,   148,   152,   -87,   122,   -87,    68,   161,   150,   151,
      12,    14,    15,   -87,   -87,   -87,   157,   158,   162,   163,
     -87,   -87,   153,   165,   -87,   153,   154,    77,    16,   -87,
     -87,    42,    10,   155,   169,     6,   167,     1,   166,   159,
     107,   -87,   -87,   -87,   -87,   168,   -87,    85,   153,   144,
     -87,   170,   -87,   -87,   -87,    16,    32,   172,   -87,   171,
     173,   176,   175,    36,   177,   178,   135,   179,    -7,   180,
     -87,    63,   135,   181,    67,   -87,    60,   188,   184,   -87,
     -87,   -87,   160,   146,   -87,   -87,    38,    16,   -87,    16,
      16,    16,   -87,   -87,   -87,   -87,   174,     6,     6,    17,
       6,    16,   185,   -87,   182,     6,    16,     8,   186,   -87,
     -87,   -87,   172,   -87,   109,   126,   135,    97,   180,   187,
     135,   -87,   176,   -87,   135,    -3,   189,    55,   -87,   -87,
     -87,   -87,   -87,   -87,    59,   -87,   198,   198,   164,   190,
     135,   191,   192,   193,   194,   195,   -87,   -87,   204,   -87,
     -87,   -87,   135,   149,   -87,   196,   199,   -87,   -87
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,   202,   -87,   -87,   -87,   -42,   156,     4,   -86,
     -87,   -87,   130,   -87,   -87,   -87,    22,   -56,    72,   103,
     -44,   115,   120
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -21
static const yytype_int16 yytable[] =
{
     116,    94,    93,    69,    76,    73,   122,    81,    83,   146,
      73,    82,    73,    54,    73,    56,    58,   118,   139,    24,
      73,   118,     1,    74,     2,   119,   103,   156,    74,    47,
      74,   106,    74,   140,    75,    87,     4,    60,    74,    75,
      87,    75,    87,    75,    18,    55,    73,    57,    59,    75,
     151,    11,    12,   107,   154,    79,    80,   107,   155,   107,
     159,   137,   108,    -7,    74,     7,   134,   135,   113,   145,
     131,   147,    48,    19,   167,    75,   160,   142,    26,   118,
      48,    27,    81,    71,   107,   158,   174,    28,    29,   121,
     125,   118,    30,    26,     5,    31,    27,    32,    49,   124,
      50,     6,    28,    29,    33,    72,    10,    30,    26,     7,
      31,    27,    32,    11,    12,   101,   102,    28,    29,    33,
      34,   118,    30,    26,    15,    31,    27,    32,    46,   152,
     107,     9,    28,    29,    33,    99,    26,    30,    25,    27,
      31,   149,    32,    23,    21,    28,    29,   107,    -6,    33,
      30,    11,    12,    31,    65,    32,    84,    66,   150,    85,
      96,   128,    33,    97,   129,   164,    20,    19,   161,    22,
     175,    42,   176,    51,   104,   102,   130,   102,    43,   163,
     165,    44,    70,    52,    53,    86,    92,    61,    62,    98,
     138,   136,    63,    64,   -20,   109,    95,   107,   105,   100,
     126,   144,   161,   168,   110,   120,   111,   112,   173,   114,
     115,    16,   117,   123,   127,   143,   148,   153,   177,   157,
     166,   178,   132,   141,   169,   170,   171,   172,     0,   133
};

static const yytype_int16 yycheck[] =
{
      86,    57,     1,    45,    48,     4,    92,    51,    52,     1,
       4,     1,     4,     1,     4,     1,     1,    24,     1,    15,
       4,    24,     1,    22,     3,    32,    68,    30,    22,    25,
      22,    75,    22,    16,    33,    34,    27,    33,    22,    33,
      34,    33,    34,    33,     1,    33,     4,    33,    33,    33,
     136,     8,     9,    21,   140,    13,    14,    21,   144,    21,
       1,   117,    30,     5,    22,     7,   110,   111,    32,   125,
      32,   127,    12,    30,   160,    33,    17,   121,     1,    24,
      12,     4,   126,     6,    21,    30,   172,    10,    11,    26,
      30,    24,    15,     1,     4,    18,     4,    20,    30,    32,
      32,     0,    10,    11,    27,    28,     1,    15,     1,     7,
      18,     4,    20,     8,     9,    30,    31,    10,    11,    27,
      28,    24,    15,     1,     5,    18,     4,    20,     6,    32,
      21,    27,    10,    11,    27,    28,     1,    15,     5,     4,
      18,    32,    20,    29,     1,    10,    11,    21,     5,    27,
      15,     8,     9,    18,     1,    20,     1,     4,    32,     4,
       1,     1,    27,     4,     4,     1,    10,    30,     4,    13,
      21,    29,    23,    12,    30,    31,    30,    31,    30,   157,
     158,    29,    28,    33,    33,    16,    19,    30,    30,    59,
     118,    17,    30,    30,    29,    23,    30,    21,    28,    31,
      12,    19,     4,    12,    33,    25,    33,    32,     4,    32,
      32,     9,    33,    32,    30,    30,    30,    30,    22,    30,
      30,    22,   107,   120,    32,    32,    32,    32,    -1,   109
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,    36,    27,     4,     0,     7,    37,    27,
       1,     8,     9,    38,    42,     5,    37,    43,     1,    30,
      42,     1,    42,    29,    43,     5,     1,     4,    10,    11,
      15,    18,    20,    27,    28,    44,    45,    46,    47,    48,
      49,    50,    29,    30,    29,    40,     6,    43,    12,    30,
      32,    12,    33,    33,     1,    33,     1,    33,     1,    33,
      43,    30,    30,    30,    30,     1,     4,    41,    39,    41,
      28,     6,    28,     4,    22,    33,    55,    56,    57,    13,
      14,    55,     1,    55,     1,     4,    16,    34,    52,    53,
      54,    55,    19,     1,    52,    30,     1,     4,    47,    28,
      31,    30,    31,    41,    30,    28,    55,    21,    30,    23,
      33,    33,    32,    32,    32,    32,    44,    33,    24,    32,
      25,    26,    44,    32,    32,    30,    12,    30,     1,     4,
      30,    32,    56,    57,    55,    55,    17,    52,    53,     1,
      16,    54,    55,    30,    19,    52,     1,    52,    30,    32,
      32,    44,    32,    30,    44,    44,    30,    30,    30,     1,
      17,     4,    51,    51,     1,    51,    30,    44,    12,    32,
      32,    32,    32,     4,    44,    21,    23,    22,    22
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 96 "cpq.y"
    {
					(yyvsp[(6) - (8)].stmt) = add_ins((yyvsp[(6) - (8)].stmt),'H',"ALT","","","");
					print_ins((yyvsp[(6) - (8)].stmt));
					free_all_names();
					free_ins_list((yyvsp[(6) - (8)].stmt));
				;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 102 "cpq.y"
    {yyerrok; yyclearin;;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 103 "cpq.y"
    {yyerrok; yyclearin;;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 104 "cpq.y"
    {yyerrok; yyclearin;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 111 "cpq.y"
    {ident_type = (yyvsp[(2) - (3)].type);;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 112 "cpq.y"
    {ident_type = (yyvsp[(1) - (2)].type);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 118 "cpq.y"
    {
					set_idents(ident_type, (yyvsp[(3) - (3)].id));
				;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 122 "cpq.y"
    {	
					set_idents(ident_type, (yyvsp[(1) - (1)].id));
				;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 125 "cpq.y"
    {yyerrok; yyclearin;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 129 "cpq.y"
    {(yyval.type) = (yyvsp[(1) - (1)].type);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 130 "cpq.y"
    {(yyval.type) = (yyvsp[(1) - (1)].type);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 131 "cpq.y"
    {yyerrok; (yyval.type) = 0; yyclearin;;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 134 "cpq.y"
    {(yyval.stmt) = connect_ins((yyvsp[(1) - (2)].stmt), (yyvsp[(2) - (2)].stmt));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 135 "cpq.y"
    {(yyval.stmt) = NULL;;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 138 "cpq.y"
    {(yyval.stmt) = (yyvsp[(1) - (2)].stmt);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 139 "cpq.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 140 "cpq.y"
    {(yyval.stmt) = (yyvsp[(1) - (2)].stmt);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 141 "cpq.y"
    {(yyval.stmt) = (yyvsp[(1) - (2)].stmt);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 142 "cpq.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 143 "cpq.y"
    {(yyval.stmt) = (yyvsp[(1) - (2)].stmt);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 144 "cpq.y"
    {yyerrok; (yyval.stmt) = NULL; yyclearin;;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 145 "cpq.y"
    {yyerrok; (yyval.stmt) = NULL; yyclearin;;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 149 "cpq.y"
    {
					(yyval.stmt) = add_ins((yyvsp[(3) - (4)].expression).head,(yyvsp[(3) - (4)].expression).type,"PRT",(yyvsp[(3) - (4)].expression).last,"","");		
					free_name((yyvsp[(3) - (4)].expression).last);
				;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 153 "cpq.y"
    {yyerrok; (yyval.stmt) = NULL; yyclearin;;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 157 "cpq.y"
    {
					(yyval.stmt) = NULL;
					if(!(current_symbol = search((yyvsp[(3) - (4)].id))))
						yyerror("unknown undentifier, the parameter of read was not defined in the declarations list");
					else
						(yyval.stmt) = add_ins(NULL,current_symbol->type,"INP",current_symbol->name,"","");
				;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 164 "cpq.y"
    {yyerrok; (yyval.stmt) = NULL; yyclearin;;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 167 "cpq.y"
    { (yyval.stmt) = add_assignment_ins((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].expression).last, (yyvsp[(3) - (3)].expression).type, (yyvsp[(3) - (3)].expression).head);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 168 "cpq.y"
    {yyerrok; (yyval.stmt) = NULL; yyclearin;;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 172 "cpq.y"
    {
				(yyval.stmt) = add_val_ins('R','I', (yyvsp[(1) - (6)].id), (yyvsp[(5) - (6)].expression).last, (yyvsp[(5) - (6)].expression).head, (yyvsp[(5) - (6)].expression).type);
			;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 177 "cpq.y"
    {
				(yyval.stmt) = add_val_ins('I', 'R', (yyvsp[(1) - (6)].id), (yyvsp[(5) - (6)].expression).last, (yyvsp[(5) - (6)].expression).head, (yyvsp[(5) - (6)].expression).type);
			;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 183 "cpq.y"
    {	
						(yyval.stmt) = connect_ins((yyvsp[(3) - (8)].boolean).head, (yyvsp[(6) - (8)].stmt));
						(yyval.stmt) = add_ins((yyval.stmt),'J',"UMP","","","");
						boolist = add_jump_to(NULL, last_ins((yyval.stmt)));
						(yyval.stmt) = add_label((yyval.stmt));
						update_label((yyvsp[(3) - (8)].boolean).false, last_ins((yyval.stmt)));
						(yyval.stmt) = connect_ins((yyval.stmt), (yyvsp[(8) - (8)].stmt));
						(yyval.stmt) = add_label((yyval.stmt));
						update_label(boolist, last_ins((yyval.stmt)));
					;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 193 "cpq.y"
    {yyerrok; (yyval.stmt) = NULL; yyclearin;;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 194 "cpq.y"
    {yyerrok; (yyval.stmt) = NULL; yyclearin;;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 195 "cpq.y"
    {yyerrok; (yyval.stmt) = NULL; yyclearin;;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 198 "cpq.y"
    {
						(yyval.stmt) = add_label(NULL);
						(yyval.stmt) = connect_ins((yyval.stmt), (yyvsp[(3) - (6)].boolean).head);
						(yyval.stmt) = connect_ins((yyval.stmt), (yyvsp[(6) - (6)].stmt));
						(yyval.stmt) = add_ins((yyval.stmt),'J',"UMP","","","");
						boolist = add_jump_to(NULL, last_ins((yyval.stmt)));
						update_label(boolist, (yyval.stmt));
						(yyval.stmt) = add_label((yyval.stmt));
						update_label((yyvsp[(3) - (6)].boolean).false, last_ins((yyval.stmt)));
					;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 209 "cpq.y"
    {(yyval.stmt) = NULL; yyerrok; yyclearin;;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 210 "cpq.y"
    {(yyval.stmt) = NULL; yyerrok; yyclearin;;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 213 "cpq.y"
    {
						(yyval.stmt) = add_label((yyvsp[(3) - (9)].stmt));
						curr_ins = last_ins((yyval.stmt));
						(yyval.stmt) = connect_ins((yyval.stmt), (yyvsp[(5) - (9)].boolean).head); 
						(yyval.stmt) = connect_ins((yyval.stmt), (yyvsp[(9) - (9)].stmt));
						(yyval.stmt) = connect_ins((yyval.stmt), (yyvsp[(7) - (9)].stmt));
						(yyval.stmt) = add_ins((yyval.stmt),'J',"UMP","","","");
						boolist = add_jump_to(NULL, last_ins((yyval.stmt)));
						update_label(boolist, curr_ins);
						(yyval.stmt) = add_label((yyval.stmt));
						update_label((yyvsp[(5) - (9)].boolean).false, last_ins((yyval.stmt)));
					;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 226 "cpq.y"
    {(yyval.stmt) = NULL; yyerrok; yyclearin;;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 227 "cpq.y"
    {(yyval.stmt) = NULL; yyerrok; yyclearin;;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 228 "cpq.y"
    {(yyval.stmt) = NULL; yyerrok; yyclearin;;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 229 "cpq.y"
    {(yyval.stmt) = NULL; yyerrok; yyclearin;;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 232 "cpq.y"
    {(yyval.stmt) = (yyvsp[(2) - (3)].stmt);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 235 "cpq.y"
    { (yyval.stmt) = add_step_ins((yyvsp[(4) - (5)].arop), (yyvsp[(1) - (5)].id), (yyvsp[(3) - (5)].id), (yyvsp[(5) - (5)].num).value,(yyvsp[(5) - (5)].num).type); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 236 "cpq.y"
    { (yyval.stmt) = add_step_ins((yyvsp[(4) - (5)].arop), (yyvsp[(1) - (5)].id), (yyvsp[(3) - (5)].id), (yyvsp[(5) - (5)].num).value,(yyvsp[(5) - (5)].num).type); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 240 "cpq.y"
    {
					(yyval.boolean).head = add_ins((yyvsp[(1) - (3)].boolean).head,'J',"UMP","","","");
					boolist = add_jump_to(NULL, last_ins((yyval.boolean).head));
					(yyval.boolean).head = add_label((yyval.boolean).head);
					update_label((yyvsp[(1) - (3)].boolean).false, last_ins((yyval.boolean).head));
					(yyval.boolean).head = connect_ins((yyval.boolean).head, (yyvsp[(3) - (3)].boolean).head);
					add_label((yyval.boolean).head);
					update_label(boolist, last_ins((yyval.boolean).head));
					(yyval.boolean).false = (yyvsp[(3) - (3)].boolean).false;
				;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 251 "cpq.y"
    {
					(yyval.boolean).head = (yyvsp[(1) - (1)].boolean).head;
					(yyval.boolean).false = (yyvsp[(1) - (1)].boolean).false;
				;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 258 "cpq.y"
    {
					(yyval.boolean).head = connect_ins((yyvsp[(1) - (3)].boolean).head,(yyvsp[(3) - (3)].boolean).head);
					(yyval.boolean).false = connect_jump_to((yyvsp[(1) - (3)].boolean).false, (yyvsp[(3) - (3)].boolean).false);
				;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 263 "cpq.y"
    {
					(yyval.boolean).false = (yyvsp[(1) - (1)].boolean).false;
					(yyval.boolean).head = (yyvsp[(1) - (1)].boolean).head;
				;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 270 "cpq.y"
    {
					(yyval.boolean).head = add_ins((yyvsp[(3) - (4)].boolean).head,'J',"UMP","","","");
					(yyval.boolean).false = add_jump_to(NULL, last_ins((yyval.boolean).head));
					add_label((yyval.boolean).head);
					update_label((yyvsp[(3) - (4)].boolean).false, last_ins((yyval.boolean).head));
				;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 277 "cpq.y"
    {
					if((yyvsp[(1) - (3)].expression).type == 'I' && (yyvsp[(3) - (3)].expression).type == 'R') /* comparison between different types - makes cast */
						(yyvsp[(1) - (3)].expression).head = convert_to_r((yyvsp[(1) - (3)].expression).head, (yyvsp[(1) - (3)].expression).last);
					else if((yyvsp[(3) - (3)].expression).type == 'I' && (yyvsp[(1) - (3)].expression).type == 'R')
						(yyvsp[(3) - (3)].expression).head = convert_to_r((yyvsp[(3) - (3)].expression).head, (yyvsp[(3) - (3)].expression).last);
					(yyval.boolean).head = add_relop_ins((yyvsp[(2) - (3)].relop), (yyvsp[(1) - (3)].expression).last, (yyvsp[(3) - (3)].expression).last, (yyvsp[(1) - (3)].expression).head, (yyvsp[(3) - (3)].expression).head, expr_type((yyvsp[(1) - (3)].expression).type, (yyvsp[(3) - (3)].expression).type));
					(yyval.boolean).false = add_jump_to(NULL, last_ins((yyval.boolean).head));
				;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 288 "cpq.y"
    {				
					(yyval.expression).type = expr_type((yyvsp[(1) - (3)].expression).type, (yyvsp[(3) - (3)].expression).type);
					(yyval.expression).head = add_arop_ins((yyvsp[(2) - (3)].arop), (yyval.expression).type, (yyval.expression).last, (yyvsp[(1) - (3)].expression).last, (yyvsp[(3) - (3)].expression).last, (yyvsp[(1) - (3)].expression).type, (yyvsp[(3) - (3)].expression).type, (yyvsp[(1) - (3)].expression).head, (yyvsp[(3) - (3)].expression).head);
				;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 293 "cpq.y"
    {
					(yyval.expression).type = (yyvsp[(1) - (1)].expression).type;
					(yyval.expression).head = (yyvsp[(1) - (1)].expression).head;
					strcpy((yyval.expression).last, (yyvsp[(1) - (1)].expression).last);
				;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 301 "cpq.y"
    {
					(yyval.expression).type = expr_type((yyvsp[(1) - (3)].expression).type, (yyvsp[(3) - (3)].expression).type);
					(yyval.expression).head = add_arop_ins((yyvsp[(2) - (3)].arop), (yyval.expression).type, (yyval.expression).last, (yyvsp[(1) - (3)].expression).last, (yyvsp[(3) - (3)].expression).last, (yyvsp[(1) - (3)].expression).type, (yyvsp[(3) - (3)].expression).type, (yyvsp[(1) - (3)].expression).head, (yyvsp[(3) - (3)].expression).head);
				;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 306 "cpq.y"
    {
					(yyval.expression).type = (yyvsp[(1) - (1)].expression).type;
					(yyval.expression).head = (yyvsp[(1) - (1)].expression).head;
					strcpy((yyval.expression).last, (yyvsp[(1) - (1)].expression).last);
				;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 314 "cpq.y"
    {
					(yyval.expression).type = (yyvsp[(2) - (3)].expression).type;
					(yyval.expression).head = (yyvsp[(2) - (3)].expression).head;
					strcpy((yyval.expression).last,(yyvsp[(2) - (3)].expression).last);
				;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 320 "cpq.y"
    {
					(yyval.expression).head = NULL;
					if(!(current_symbol = search((yyvsp[(1) - (1)].id)))) 
					{
						yyerror("unknown undentifier, the identifier was not defined in the declarations list");
						(yyval.expression).type = 0;
					}
					else
					{
						strcpy((yyval.expression).last, (yyvsp[(1) - (1)].id));
						(yyval.expression).type = current_symbol->type;
					}
				;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 334 "cpq.y"
    {
					strcpy((yyval.expression).last, (yyvsp[(1) - (1)].num).value);
					(yyval.expression).type = (yyvsp[(1) - (1)].num).type;
					(yyval.expression).head = NULL;
				;}
    break;



/* Line 1455 of yacc.c  */
#line 2060 "cpq.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 340 "cpq.y"


int yyerror(char *err)
{
	fprintf(err_file, "ERROR - line %d, column %d: %s\n", line, column, err);
	error_exist = 1;
	return 1;
}

