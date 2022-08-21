/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
    LOWER_THAN_ELSE = 295
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 232 "1805051.y" /* yacc.c:1909  */

     SymbolInfo *symbol;

#line 138 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
