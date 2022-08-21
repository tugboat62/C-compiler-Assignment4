%{
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

//helps to handle extra assembly codes after return statement
bool intermediaryReturn = false;
bool returnMain = false;

vector<SymbolInfo> parameterList;
vector<string> completedFunc;
string symbolName;
string symbolType;
string calledFunction;
string currentFunction="global";
string code;
string currentDataType = "void";
vector<string> dataString;
vector<SymbolInfo> arguments;
vector<pair<string, string>> arraySet; 


void yyerror(char *s)
{
	//write your code
}

FILE* log_file = fopen("1805051_log.txt", "w");
FILE* error_file = fopen("1805051_error.txt", "w");
FILE* code_file = fopen("code.asm", "w");
FILE* optimized_file = fopen("optimized.asm", "w");
FILE* debug = fopen("debug.txt", "w");

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

void printAssembly(string rule, string codes, int line) {
	string l = "Rule: " + rule + "\n";
	l += "Code after line " + to_string(line) + ": \n\n" + codes + "\n\n";
	fprintf(debug, l.c_str());
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

	finalCode += ";println procedure implementation\n";
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

vector<string> split_string(const string& str,const string& delimiter){
    vector<string> splitted;

    string::size_type pos = 0;
    string::size_type prev = 0;

    while ((pos = str.find(delimiter, prev)) != string::npos){
        splitted.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    splitted.push_back(str.substr(prev));

    return splitted;
}

bool is_valid_string(string a, string b){
    int a_idx = a.find("MOV");
    int b_idx = b.find("MOV");

    if((a_idx!=string::npos)&&(b_idx!=string::npos)){
        if((a.find(",")!=string::npos)&&(b.find(",")!=string::npos)){
            return true;
        }
    }
    return false;
}

string optimize(string codes) {
	string result;
    int i;
    bool lastFlag = false;
    int idx;

    vector<string>v1;
    vector<string>v2;

    vector<string>splitted_code =split_string(codes,"\n");

     // extra newlines from the splitted string are removed here
    for(auto x: splitted_code){
        if(x!=""){
            v1.push_back(x);
		}
	}

	splitted_code.clear();
	for(auto x:v1){
		splitted_code.push_back(x);
	}

	v1.clear();
    for( i=0;i<splitted_code.size();i++){
        idx = i;

        if(i!=splitted_code.size()-1){
            if(is_valid_string(splitted_code[i],splitted_code[i+1])){
                string temp1 = splitted_code[i].substr(splitted_code[i].find(" ")+1,splitted_code[i].length()-1);
                string temp2 = splitted_code[i+1].substr(splitted_code[i+1].find(" ")+1,splitted_code[i].length()-1);

                v1 = split_string(temp1,",");
                v2 = split_string(temp2,",");

                if((v1[0]==v2[1])&&(v1[1]==v2[0])){
                    i++;
                }

                if((idx+1)==splitted_code.size()){
                    lastFlag = true;
                }
            }
        }

        if(!lastFlag){
            result += splitted_code[idx]+"\n";
        }
        else{
            lastFlag = false;
        }
    }
    return result;
}

%}



%union {
     SymbolInfo *symbol;
}

%token ELSE IF FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE PRINTLN
%token VOID RETURN SWITCH CASE DEFAULT CONTINUE
%token ASSIGNOP NOT LPAREN RPAREN LTHIRD RTHIRD COMMA SEMICOLON LCURL RCURL
%token<symbol>CONST_INT
%token<symbol>CONST_FLOAT
%token<symbol>CONST_CHAR
%token<symbol>ADDOP
%token<symbol>MULOP
%token<symbol>INCOP
%token<symbol>DECOP
%token<symbol>RELOP
%token<symbol>LOGICOP
%token<symbol>ID

%type<symbol> start program unit var_declaration func_declaration func_definition type_specifier parameter_list compound_statement declaration_list statements statement expression_statement variable expression rel_expression logic_expression simple_expression term unary_expression factor argument_list arguments

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start : program 
			{
				printInLogFile("start : program", numLine);
				symbolName = $1->getName();
				symbolType = $1->getType();
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				table->printModified(log_file);
				string l;
				l = "Total Lines: " + to_string(numLine) + "\n";
				fprintf(log_file, l.c_str());
				l = "Total Errors: " + to_string(numError) + "\n";
				fprintf(log_file, l.c_str());

				$$->appendCode($1->getCode());
				string codeSnippet = create_template(dataString, $$->code) + "\n";
				string s = "start : program\n";
				fprintf(debug, s.c_str());
				fprintf(debug, codeSnippet.c_str());
				fprintf(code_file, codeSnippet.c_str());
				s = optimize(codeSnippet);
				fprintf(optimized_file, s.c_str());
			}
;


program : program unit 
			{
				printInLogFile("program : program unit", numLine);
				symbolName = $1->getName() + $2->getName();
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->appendCode($1->getCode() + $2->getCode());
				printAssembly("program : program unit",$$->code, numLine);

			}
| unit
			{
				printInLogFile("program : unit", numLine);
				symbolName = $1->getName();
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->appendCode($1->getCode());
				printAssembly("program : unit", $$->code, numLine);

			}
;


unit : var_declaration
			{
				printInLogFile("unit : var_declaration", numLine);
				symbolName = $1->getName() + "\n";
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->appendCode($1->getCode());
				printAssembly("unit : var_declaration",$$->code, numLine);

			}
| func_declaration
			{
				printInLogFile("unit : func_declaration", numLine);
				symbolName = $1->getName();
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->appendCode($1->getCode());
				printAssembly("unit : func_declaration", $$->code, numLine);

			}
| func_definition
			{
				printInLogFile("unit : func_definition", numLine);
				symbolName = $1->getName();
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->appendCode($1->getCode());
				printAssembly("unit : func_definition", $$->code, numLine);

			}
;


func_declaration : type_specifier ID LPAREN parameter_list RPAREN 
			{
				currentFunction = $2->getName();
				if(table->LookUp(currentFunction) == NULL) {
					SymbolInfo* symbol = new SymbolInfo(currentFunction, "ID");
					symbol->setDataType($1->getName());
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
SEMICOLON
			{
				printInLogFile("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", numLine);
				symbolName = $1->getName()+" "+$2->getName()+" "+"("+" "+$4->getName()+" "+")"+" "+";"+"\n";
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
			}
| type_specifier ID LPAREN RPAREN SEMICOLON
			{
				currentFunction = $2->getName();
				if(table->LookUp(currentFunction) == NULL) {
					SymbolInfo* symbol = new SymbolInfo(currentFunction, "ID");
					symbol->setDataType($1->getName());
					symbol->setKeyType("function");
					table->Insert(*symbol);
				}
				else {
					string error = "Function " + '\"' + currentFunction + '\"' + " declared multiple times\n";
					printError(error, numLine);
				}

				printInLogFile("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", numLine);
				symbolName = $1->getName()+" "+$2->getName()+" "+"( );"+"\n";
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
			}
;


func_definition : type_specifier ID LPAREN parameter_list RPAREN
			{
				currentFunction = $2->getName();
				SymbolInfo* s = table->LookUp(currentFunction);
				if(s == NULL) {
					SymbolInfo* symbol = new SymbolInfo(currentFunction, "ID");
					symbol->setDataType($1->getName());
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
						if ($1->getName() != s->getDataType()){
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
compound_statement
			{
				printInLogFile("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement", numLine);
				symbolName = $1->getName()+" "+$2->getName()+" ("+" "+$4->getName()+" )\n"+$7->getName();
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");	
				completedFunc.push_back(currentFunction);

				SymbolInfo* s = table->LookUp(currentFunction);
				vector<SymbolInfo> parameters = s->getParams();
				
				$$->code += "; start of function "+currentFunction+"\n";
				code = currentFunction+" PROC\n";
				
				code += "POP CX\n";

				code += ";Assigning each variables with the values passed as function parameters\n";
				for (int i=parameters.size()-1; i>=0; i--) {
					code += "POP AX\n";
					code += "MOV "+parameters[i].getVarName()+", AX\n";
				}
				parameterList.clear();
				code += "PUSH CX\n";

				if(currentFunction == "main") {
					code += "MOV AX, @DATA\n";
					code += "MOV DS, AX\n";
					code += "XOR BX, BX\n";
					code += "XOR CX, CX\n";
				}
				else{
					code += "PUSH AX\n";
					code += "PUSH BX\n";
					code += "PUSH CX\n";
					code += "PUSH DX\n";
				}

				code += $1->code + $2->code + $4->code + $7->code;
				if(s->getDataType() == "void") {
					code += "POP DX\n";
					code += "POP CX\n";
					code += "POP BX\n";
					code += "POP AX\n";
					code += "RET\n";
					code += currentFunction+" ENDP\n";
				}
				if(currentFunction == "main" && returnMain == false) {
					code += "MOV AH, 4CH\n";
					code += "INT 21H\n";
					code += currentFunction+" ENDP\n";
				}
				$$->code += code;
				returnMain = false;
				printAssembly("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement",$$->code, numLine);

			}	
| type_specifier ID LPAREN RPAREN 
			{
				currentFunction = $2->getName();
				if(table->LookUp(currentFunction) == NULL) {
					SymbolInfo* symbol = new SymbolInfo(currentFunction, "ID");
					symbol->setKeyType("function");
					symbol->setDataType($1->getName());
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
compound_statement
			{
				printInLogFile("func_definition : type_specifier ID LPAREN RPAREN compound_statement", numLine);
				symbolName = $1->getName()+" "+$2->getName()+" ("+")\n"+$6->getName();
				printToken(symbolName);

				SymbolInfo* s = table->LookUp(currentFunction);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				completedFunc.push_back(currentFunction);

				code = ";start of function "+currentFunction+"\n";
				code += currentFunction+" PROC\n";
				if(currentFunction == "main") {
					code += "MOV AX, @DATA\n";
					code += "MOV DS, AX\n";
					code += "XOR BX, BX\n";
					code += "XOR CX, CX\n";
				}
				else{
					code += "PUSH AX\n";
					code += "PUSH BX\n";
					code += "PUSH CX\n";
					code += "PUSH DX\n";
				}

				printAssembly("func_definition : type_specifier ID LPAREN RPAREN compound_statement",$6->code, numLine);
				code += $6->code;

				if(s->getDataType() == "void") {
					code += "POP DX\n";
					code += "POP CX\n";
					code += "POP BX\n";
					code += "POP AX\n";
					code += "RET\n";
					code += currentFunction+" ENDP\n";
				}
				if(currentFunction == "main" && returnMain == false) {
					code += "MOV AH, 4CH\n";
					code += "INT 21H\n";
					code += currentFunction+" ENDP\n";
				}
				$$->code += code; 
				returnMain = false;
				printAssembly("func_definition : type_specifier ID LPAREN RPAREN compound_statement",$$->code, numLine);

			}
;


parameter_list : parameter_list COMMA type_specifier ID
			{
				symbolName = $1->getName() + " , " + $3->getName() + " " + $4->getName();
				printInLogFile("parameter_list : parameter_list COMMA type_specifier ID", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo($4->getName(), $4->getType());
				s->setKeyType("variable");
				s->setDataType($3->getName());
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
				$$->code += $1->code + $3->code;
				$$->code += ";variable "+s->getVarName()+" declared for local variable "+s->getName()+"\n";
				$$->code += $4->code;
				
				dataString.push_back(s->getVarName());
				printAssembly("parameter_list : parameter_list COMMA type_specifier ID",$$->code, numLine);

			}
| parameter_list COMMA type_specifier
			{
				symbolName = $1->getName()+" , "+$3->getName();
				printInLogFile("parameter_list  : parameter_list COMMA type_specifier", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += $1->code + $3->code;
			}
| type_specifier ID
			{
				symbolName = $1->getName()+" "+$2->getName();
				printInLogFile("parameter_list  : type_specifier ID", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo($2->getName(), $2->getType());
				s->setKeyType("variable");
				s->setDataType($1->getName());
				s->setVarName(varProduce());
				parameterList.push_back(*s);
				$$->code += ";variable "+s->getVarName()+" declared for local variable "+s->getName()+"\n";
				$$->code += $1->code + $2->code;
				dataString.push_back(s->getVarName());
				printAssembly("parameter_list  : type_specifier ID", $$->code, numLine);

			}
| type_specifier
			{
				symbolName = $1->getName();
				printInLogFile("parameter_list  : type_specifier", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += $1->code;
				
			}
;


compound_statement : LCURL 
			{	
				table->EnterScope();
				for (int i=0; i<parameterList.size(); i++) {
					table->Insert(parameterList[i]);
				}
			}
statements RCURL
			{
				symbolName = "{\n" + $3->getName() + "}\n";
				printInLogFile("compound_statement : LCURL statements RCURL", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				table->printModified(log_file);
				parameterList.clear();
				table->ExitScope();
				$$->code += $3->code;
				printAssembly("compound_statement : LCURL statements RCURL", $$->code, numLine);

			}
| LCURL RCURL
			{
				symbolName = "{\n}\n";
				printInLogFile("compound_statement : LCURL statements RCURL", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				table->printModified(log_file);
				parameterList.clear();
			}
;


var_declaration : type_specifier declaration_list SEMICOLON
			{
				symbolName = $1->getName() + " " + $2->getName() + " ;";
				printInLogFile("var_declaration : type_specifier declaration_list SEMICOLON", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				if($1->getName() == "void") {
					printError("Variable type cannot be void", numLine);
				}
				$$->code += $1->code + $2->code;
				printAssembly("var_declaration : type_specifier declaration_list SEMICOLON",$$->code, numLine);

			}
;

type_specifier : INT
			{
				symbolName = "int";
				printInLogFile("type_specifier : INT", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				currentDataType = symbolName;
			}
| FLOAT
			{
				symbolName = "float";
				printInLogFile("type_specifier : FLOAT", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				currentDataType = symbolName;
			}
| VOID
			{
				symbolName = "void";
				printInLogFile("type_specifier : VOID", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				currentDataType = symbolName;
			}
;


declaration_list : declaration_list COMMA ID
			{
				symbolName = $1->getName() + " , " + $3->getName();
				printInLogFile("declaration_list : declaration_list COMMA ID", numLine);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				
				SymbolInfo* s = new SymbolInfo($3->getName(), $3->getType());
				s->setKeyType("variable");
				s->setDataType(currentDataType);
				if(currentFunction != "global") 
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
				$$->code += ";variable "+s->getVarName()+" declared for local variable "+s->getName()+"\n";
				dataString.push_back(s->getVarName());
				printAssembly("declaration_list : declaration_list COMMA ID",$$->code, numLine);

			}
| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
			{
				symbolName = $1->getName() + " , " + $3->getName() + "[" + $5->getName() + "]";
				printInLogFile("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", numLine);
				
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo($3->getName(), $3->getType());
				s->setKeyType("array");
				s->setDataType(currentDataType);
				if(currentFunction != "global")
					s->setVarName(varProduce());
				int size = stoi($5->getName());
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
				$$->code += ";variable "+s->getVarName()+" declared for local variable "+s->getName()+"\n"; 
				arraySet.push_back(make_pair(s->getVarName(), $5->getName()));
				printAssembly("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD",$$->code, numLine);
	
			}
| ID
			{
				symbolName = $1->getName();
				printInLogFile("declaration_list : ID", numLine);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo($1->getName(), $1->getType());
				s->setKeyType("variable");
				s->setDataType(currentDataType);
				if(currentFunction != "global")
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
				$$->code += ";variable "+s->getVarName()+" declared for local variable "+s->getName()+"\n";
				dataString.push_back(s->getVarName());
				printToken(symbolName);
				printAssembly("declaration_list : ID",$$->code, numLine);

			}
| ID LTHIRD CONST_INT RTHIRD
			{
				symbolName = $1->getName() + "[" + $3->getName() + "]";
				printInLogFile("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", numLine);
				
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = new SymbolInfo($1->getName(), $1->getType());
				s->setKeyType("array");
				s->setDataType(currentDataType);
				if(currentFunction != "global")
					s->setVarName(varProduce());
				int size = stoi($3->getName());
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
				$$->code += ";variable "+s->getVarName()+" declared for local variable "+s->getName()+"\n";
				arraySet.push_back(make_pair(s->getVarName(), $3->getName()));
				printAssembly("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD",$$->code, numLine);

			}
;


statements : statement
			{
				symbolName = $1->getName();

				printInLogFile("statements : statement", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += $1->code;
				printAssembly("statements : statement",$$->code, numLine);

			}
| statements statement
			{
				symbolName = $1->getName() + $2->getName();

				printInLogFile("statements : statements statement", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += $1->code;
				if(intermediaryReturn == true){
					$$->code += $2->code;
					intermediaryReturn = false;
					returnMain = true;
				} else {
					if(returnMain == false){
						$$->code += $2->code;
					}
				}
				printAssembly("statements : statements statement",$$->code, numLine);

			}
;


statement : var_declaration
			{
				symbolName = $1->getName() + "\n";

				printInLogFile("statement : var_declaration", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += $1->code;
				printAssembly("statement : var_declaration",$$->code, numLine);

			}
| expression_statement
			{
				symbolName = $1->getName() + "\n";

				printInLogFile("statement : expression_statement", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += $1->code;
				printAssembly("statement : expression_statement",$$->code, numLine);

			}
| compound_statement
			{
				symbolName = $1->getName() + "\n";

				printInLogFile("statement : compound_statement", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += $1->code;
				printAssembly("statement : compound_statement",$$->code, numLine);

			}
| FOR LPAREN expression_statement expression_statement expression
RPAREN statement
			{
				symbolName = "for ( " + $3->getName() + " " + $4->getName() + " " + $5->getName() + " )\n" + $7->getName() + "\n";

				printInLogFile("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				$$->code += ";start of for loop\n";
				string temp = $3->code;
				string l1 = labelHandler();
				temp += l1 + ":\n";
				temp += $4->code;
				temp += "MOV BX, 0\n";
				temp += "CMP AX, BX\n";
				string l2 = labelHandler();
				temp += "JE " + l2 + "\n";
				temp += $7->code;
				temp += $5->code;
				temp += "JMP " + l1 + "\n";
				temp += l2 + ":\n";
				code = temp;

				$$->code += temp;
				$$->code += ";end of for loop\n";
				printAssembly("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement",$$->code, numLine);

			}
| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
			{
				symbolName = "if ( " + $3->getName() + " )\n" + $5->getName() + "\n";

				printInLogFile("statement : IF LPAREN expression RPAREN statement", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += ";if statement\n";
				string l = labelHandler();
				string temp = $3->code;
				temp += "CMP AX, 0\n";
				temp += "JE " + l + "\n";
				temp += $5->code;
				temp += l + ":\n";
				$$->code += temp;
				$$->code += ";end of if statement\n";
				printAssembly("statement : IF LPAREN expression RPAREN statement",$$->code, numLine);

			}
| IF LPAREN expression RPAREN statement ELSE statement
			{
				symbolName = "if ( " + $3->getName() + " )\n" + $5->getName() + "else\n" + $7->getName() + "\n";

				printInLogFile("statement : IF LPAREN expression RPAREN statement ELSE statement", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				string l1 = labelHandler();
				string l2 = labelHandler();
				$$->code += ";start of if else statement\n";
				string temp = $3->code;
				temp += "CMP AX, 0\n";
				temp += "JE " + l1 + "\n";
				temp += $5->code;
				temp += "JMP " + l2 + "\n";
				temp += l1 + ":\n";
				temp += $7->code;
				temp += l2 + ":\n";
				$$->code += temp;
				$$->code += ";end of if else statement\n";
				printAssembly("statement : IF LPAREN expression RPAREN statement ELSE statement",$$->code, numLine);

			}
| WHILE LPAREN expression RPAREN statement
			{
				symbolName = "while ( " + $3->getName() + " )\n" + $5->getName() + "\n";

				printInLogFile("statement : WHILE LPAREN expression RPAREN statement", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				string l1 = labelHandler();
				string l2 = labelHandler();
				string temp = l1 + ":\n";
				$$->code += ";start of while statement\n";
				if(!$3->getIncDec())
					temp += $3->code;
				else temp += "MOV AX, "+$3->getVarName()+"\n";
				temp += "CMP AX, 0\n";
				temp += "JE " + l2 + "\n";
				if($3->getIncDec())
					temp += $3->code;
				temp += $5->code;
				temp += "JMP " + l1 + "\n";
				temp += l2 + ":\n";
				if($3->getIncDec())
					temp += $3->code;
				code = temp;
				$$->code += temp;
				$$->code += ";end of while statement\n";
				printAssembly("statement : WHILE LPAREN expression RPAREN statement",$$->code, numLine);

			}
| PRINTLN LPAREN ID RPAREN SEMICOLON
			{
				symbolName = "printf ( " + $3->getName() + " );" + "\n";
				printInLogFile("statement : PRINTLN LPAREN ID RPAREN SEMICOLON", numLine);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				SymbolInfo* s = table->LookUp($3->getName());
				if(s == NULL) {
					string l = "Undeclared variable "+$3->getName();
					printError(l, numLine);
				}
				printToken(symbolName);
				$$->code += ";calling function println\n";
				$$->code += "MOV AX, " + $3->getVarName() + "\nCALL println\n"; 
				printAssembly("statement : PRINTLN LPAREN ID RPAREN SEMICOLON",$$->code, numLine);

			}
| RETURN expression SEMICOLON
			{
				symbolName = "return " + $2->getName() + ";" + "\n";

				intermediaryReturn = true;
				printInLogFile("statement : RETURN expression SEMICOLON", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				SymbolInfo* cf = table->LookUp(currentFunction);
				if(cf->getDataType() == "void") {
					printError("returning with a value but in function definition, returning type is void", numLine);
				}
				else if(cf->getDataType() != $2->getDataType()) {
					printError("Function return type error", numLine);
				}
				$$->code += ";restoring the register and returning from function\n";
				if(currentFunction != "main"){
					$$->code += "POP DX\n";
					$$->code += "POP CX\n";
					$$->code += "POP BX\n";
					$$->code += "POP AX\n";
					if(cf->getDataType()!="void"){
						$$->code += $2->code;
						$$->code += "POP CX\n";
						$$->code += "PUSH AX\n";
						$$->code += "PUSH CX\n";
					}
					$$->code += "RET\n";
				}
				else{
					$$->code += "MOV AH, 4CH\nINT 21H\n";
				}
				$$->code += currentFunction + " ENDP\n"	; 
				printAssembly("statement : RETURN expression SEMICOLON",$$->code, numLine);

			}
;

expression_statement : SEMICOLON
			{
				symbolName = ";";
				printInLogFile("expression_statement : SEMICOLON", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
			}
| expression SEMICOLON
			{
				symbolName = $1->getName() + ";";
				printInLogFile("expression_statement : expression SEMICOLON", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += $1->code;
				printAssembly("expression_statement : expression SEMICOLON",$$->code, numLine);
				
			}
;


variable : ID
			{
				symbolName = $1->getName();
				printInLogFile("variable : ID", numLine);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				SymbolInfo* s = table->LookUp($1->getName());
				if(s == NULL){
					printError("Undeclared variable "+symbolName, numLine);
					$$->setKeyType("variable");
					$$->setDataType("none");
				}
				else {
					if(s->getKeyType() == "array"){
						string l = "Type mismatch, "+s->getName()+ " is an array";
						printError(l, numLine);		
					}
					$$ = $1;
					$$->setVarName(s->getVarName());
				}
				printToken(symbolName);
				printAssembly("variable : ID",$$->code, numLine);

			}
| ID LTHIRD expression RTHIRD
			{
				symbolName = $1->getName() + "[" + $3->getName() + "]";
				printInLogFile("variable : ID LTHIRD expression RTHIRD", numLine);

				SymbolInfo* s = table->LookUp($1->getName());

				if(s == NULL){
					printError("Undeclared variable "+symbolName, numLine);
					$$ = new SymbolInfo(symbolName, "array");
					$$->setKeyType("array");
					$$->setDataType("none");
				}
				else {
					if(s->getKeyType() != "array") {
						string l = "Type mismatch, "+s->getName()+ " is not an array";
						printError(l, numLine);		
					}
					if($3->getDataType() != "int") {
						printError("Expression inside third brackets not an integer", numLine);
					}
					$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
					$$->setKeyType("array");
					$$->setDataType(s->getDataType());
					$$->code += $1->code + $3->code;
					$$->code += "MOV SI, offset "+ s->getVarName() + "\n";
					$$->code += "ADD AX, AX\n";
					$$->code += "ADD SI, AX\n";
					$$->setVarName("[SI]");
				}
				printToken(symbolName);

				printAssembly("variable : ID LTHIRD expression RTHIRD",$$->code, numLine);
			}
;


expression : logic_expression
			{
				symbolName = $1->getName();
				printInLogFile("expression : logic_expression", numLine);
				printToken(symbolName);

				$$ = $1;
				printAssembly("expression : logic_expression",$$->code, numLine);
			}
      //start from here	
| variable ASSIGNOP logic_expression
			{
				symbolName = $1->getName() + " = " + $3->getName();
				printInLogFile("expression : variable ASSIGNOP logic_expression", numLine);

				if($1->getDataType() != "" && $3->getDataType() != "") {
					if($1->getDataType() == "void" || $3->getDataType() == "void") {
						printError("Void function used in expression", numLine);
					}
					else if($1->getDataType() != "none") {
						string d1 = $1->getDataType();
						string d2 = $3->getDataType();
						if(d1 != "float" && d2 == "float") {
							printError("Type mismatch", numLine);
						}
					}
				}

				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				SymbolInfo* s = table->LookUp($1->getName());
				$$->code += ";assigning "+$3->getVarName()+" to "+$1->getVarName()+"\n";
				$$->code += $1->code + $3->code;
				$$->code += "MOV " + $1->getVarName() + ", AX\n";
				printAssembly("expression : variable ASSIGNOP logic_expression",$$->code, numLine);
			}
;

logic_expression : rel_expression
			{
				symbolName = $1->getName();
				printInLogFile("logic_expression : rel_expression", numLine);
				printToken(symbolName);

				$$ = $1;
				printAssembly("logic_expression : rel_expression",$$->code, numLine);
			}
| rel_expression LOGICOP rel_expression
			{
				symbolName = $1->getName() + " " + $2->getName() + " " + $3->getName();
				printInLogFile("logic_expression : rel_expression LOGICOP rel_expression", numLine);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->setDataType("int");

				if($1->getDataType()=="void" || $3->getDataType()=="void" ){
					printError("Void function used in expression", numLine);				
				}

				$$->code += ";evaluating logic expression\n";
				printToken(symbolName);
				string temp = $1->code;
				temp += "PUSH BX\n";
				temp += "MOV BX, AX\n";
				temp += $3->code;

				if($2->getName()=="&&"){
					string l1 = labelHandler();
					string l2 = labelHandler();
					$$->code += ";evaluating logic expression with && operator\n";
					temp += "CMP BX, 0\n";
					temp += "JE " + l1 + "\n";
					temp += "CMP AX, 0\n";
					temp += "JE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 0\n";
					temp += l2 + ":\n";
				}
				else if($2->getName()=="||"){
					string l1 = labelHandler();
					string l2 = labelHandler();
					$$->code += ";evaluating logic expression with || operator\n";
					temp += "CMP BX, 0\n";
					temp += "JNE " + l1 + "\n";
					temp += "CMP AX, 0\n";
					temp += "JNE " + l1 + "\n";
					temp += "MOV AX, 0\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 1\n";
					temp += l2 + ":\n";
				}
				code = temp;
				$$->code += temp;
				$$->code += "POP BX\n";
				printAssembly("logic_expression : rel_expression LOGICOP rel_expression",$$->code, numLine);
			}
;


rel_expression : simple_expression
			{
				symbolName = $1->getName();
				printInLogFile("rel_expression : simple_expression", numLine);
				printToken(symbolName);

				$$ = $1;
				printAssembly("rel_expression : simple_expression",$$->code, numLine);
			}
| simple_expression RELOP simple_expression
			{
				symbolName = $1->getName() + " " + $2->getName() + " " + $3->getName();
				printInLogFile("rel_expression : simple_expression RELOP simple_expression", numLine);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->setDataType("int");

				if($1->getDataType()=="void" || $3->getDataType()=="void" ){
					printError("Void function used in expression", numLine);				
				}

				printToken(symbolName);

				$$->code += ";evaluating relational expression\n";
				string temp = $1->code;
				temp += "PUSH BX\n";
				temp += "MOV BX, AX\n";
				temp += $3->code;
				string l1 = labelHandler();
				string l2 = labelHandler();
				temp += "CMP BX, AX\n";
				
				// if BX RELOP AX
				if($2->getName() == "==") {
					$$->code += ";evaluating relational expression with == operator\n";
					temp += "JNE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 0\n";
					temp += l2 + ":\n";
				}
				else if($2->getName() == "!="){
					$$->code += ";evaluating relational expression with != operator\n";
					temp += "JE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 0\n";
					temp += l2 + ":\n";
				} 
				else if($2->getName() == ">="){
					$$->code += ";evaluating relational expression with >= operator\n";
					temp += "JNGE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 0\n";
					temp += l2 + ":\n";
				}
				else if($2->getName() == "<="){
					$$->code += ";evaluating relational expression with <= operator\n";
					temp += "JNLE " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 0\n";
					temp += l2 + ":\n";
				}
				else if($2->getName() == ">"){
					$$->code += ";evaluating relational expression with > operator\n";
					temp += "JNG " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 0\n";
					temp += l2 + ":\n";
				}
				else if($2->getName() == "<"){
					$$->code += ";evaluating relational expression with < operator\n";
					temp += "JNL " + l1 + "\n";
					temp += "MOV AX, 1\n";
					temp += "JMP " + l2 + "\n";
					temp += l1 + ":\n";
					temp += "MOV AX, 0\n";
					temp += l2 + ":\n";
				}

				code = temp;
				$$->code += temp;
				$$->code += "POP BX\n";
				printAssembly("rel_expression : simple_expression RELOP simple_expression",$$->code, numLine);
			}
;


simple_expression : term
			{
				symbolName = $1->getName();
				printInLogFile("simple_expression : term", numLine);
				printToken(symbolName);

				$$ = $1;
				printAssembly("simple_expression : term",$$->code, numLine);
			}
			//start reading from here
| simple_expression ADDOP term
			{
				symbolName = $1->getName() + " " + $2->getName() + " " + $3->getName();
				printInLogFile("simple_expression : simple_expression ADDOP term", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				if($1->getDataType()=="void" || $3->getDataType()=="void" ){
					printError("Void function used in expression", numLine);								
				}
				else if($1->getDataType()=="float" || $3->getDataType()=="float"){
					$$->setDataType("float");
				}
				else if($1->getDataType()=="int" || $3->getDataType()=="int"){
					$$->setDataType("int");
				}

				$$->code += ";evaluating simple expression "+symbolName+"\n";

				string temp = $1->code;
				temp += "PUSH BX\n";
				temp += "MOV BX, AX\n";
				temp +=  $3->code;
				
				if($2->getName() == "+"){
					temp += "ADD AX, BX\n";
				}
				else if($2->getName() == "-"){
					temp += "SUB BX, AX\n";
					temp += "MOV AX, BX\n";
				}
				$$->code += temp;
				$$->code += "POP BX\n";
				printAssembly("simple_expression : simple_expression ADDOP term",$$->code, numLine);
			}
;


term : unary_expression
			{
				symbolName = $1->getName();
				printInLogFile("term : unary_expression", numLine);
				printToken(symbolName);

				$$ = $1;
				printAssembly("term : unary_expression",$$->code, numLine);
			}
| term MULOP unary_expression
			{
				symbolName = $1->getName() + " " + $2->getName() + " " + $3->getName();
				printInLogFile("term : term MULOP unary_expression", numLine);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				if($1->getDataType() == "void" || $3->getDataType() == "void" ){
					printError("Void function used in expression", numLine);								
				}
				if($2->getName() == "%") {
					if($1->getDataType() != "int" || $3->getDataType() != "int"){
						printError("Non-Integer operand on modulus operator", numLine);			
					}
					if($3->getName() == "0"){
						printError("Modulus by Zero", numLine);									
					}
					$$->setDataType("int");
				}
				else{
					if($2->getName() == "/" && $3->getName() == "0"){
						printError("Division by Zero", numLine);
					}
					if($1->getDataType() == "float" || $3->getDataType() == "float"){
						$$->setDataType("float");
					}
					else{
						$$->setDataType("int");
					}
				}
				printToken(symbolName);
//check here
				$$->code += ";evaluating term "+symbolName+"\n";
				string temp = $1->code;
				temp += "PUSH BX\n";
				temp += "MOV BX, AX\n";
				temp += $3->code;
				temp += "PUSH CX\n";
				temp += "MOV CX, AX\n";
				temp += "MOV AX, BX\n";
				temp += "MOV BX, CX\n";
				temp += "POP CX\n";

				if($2->getName() == "*"){
					temp += "MUL BX\n";
				}
				else if($2->getName() == "/"){
					temp += "XOR DX, DX\n";
					temp += "CWD\n";
					temp += "IDIV BX\n";
				}
				else if($2->getName() == "%"){
					temp += "XOR DX, DX\n";
					temp += "CWD\n";
					temp += "IDIV BX\n";
					temp += "MOV AX, DX\n";
				}
				$$->code += temp;
				$$->code += "POP BX\n";
				printAssembly("term : term MULOP unary_expression",$$->code, numLine);
			}
;


unary_expression : ADDOP unary_expression
			{
				symbolName = $1->getName() + $2->getName();
				printInLogFile("unary_expression : ADDOP unary_expression", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->setDataType($2->getDataType());
				$$->code = $2->code;
				$$->code += ";evaluating unary_expression "+symbolName+"\n";
				
				if($1->getName() == "-") {
					$$->code += "NEG AX\n";
				}
				printAssembly("unary_expression : ADDOP unary_expression",$$->code, numLine);
			}
| NOT unary_expression
			{
				symbolName = "! " + $2->getName();
				printInLogFile("unary_expression : NOT unary_expression", numLine);
				printToken(symbolName);

				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->setDataType($2->getDataType());
				$$->code += ";evaluating unary_expression "+symbolName+"\n";
				$$->code += "MOV AX, " + $2->getVarName() + "\n";
				$$->code += "NOT AX\n";
				printAssembly("unary_expression : NOT unary_expression",$$->code, numLine);
			}
| factor
			{
				symbolName = $1->getName();
				printInLogFile("unary_expression : factor", numLine);
				printToken(symbolName);

				$$ = $1;
				printAssembly("unary_expression : factor", $$->code, numLine);
			}
;

factor : variable
			{
				symbolName = $1->getName();
				printInLogFile("factor : variable", numLine);
				printToken(symbolName);
				$$ = $1;
				$$->code += "MOV AX, " + $1->getVarName() + "\n";
				printAssembly("factor : variable", $$->code, numLine);
			}
| ID LPAREN argument_list RPAREN
			{
				symbolName = $1->getName() +  " ( " + $3->getName() + " )";
				printInLogFile("factor : ID LPAREN argument_list RPAREN", numLine);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");

				calledFunction = $1->getName();

				SymbolInfo* s = table->LookUp($1->getName());

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
					
					$$->setDataType(s->getDataType());
				}
				printToken(symbolName);
				if($1->getName() != "println"){
					$$->code += $3->code;
					arguments.clear();
					$$->code += "CALL " + calledFunction + "\n";
					if (s != NULL && s->getDataType()!="void") {
						$$->code += ";saving the returned value\n";
						$$->code += "POP AX\n";
					}
				}
				else {
					$$->code += ";calling the function "+calledFunction+"\n";
					$$->code += $3->code;
					for(int i=0; i<arguments.size(); i++) {
						$$->code += "POP AX\n";
					}
					arguments.clear();
					$$->code += "CALL " + calledFunction + "\n";
				}
				printAssembly("factor : ID LPAREN argument_list RPAREN",$$->code, numLine);
			}
| LPAREN expression RPAREN
			{
				symbolName = " ( " + $2->getName() + " )";
				printInLogFile("factor : LPAREN expression RPAREN", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo($2->getName(), "NON_TERMINAL");
				$$->setDataType($2->getDataType());
				$$->code += $2->code;
				printAssembly("factor : LPAREN expression RPAREN",$$->code, numLine);
			}
| CONST_INT
			{
				symbolName = $1->getName();
				printInLogFile("factor : CONST_INT", numLine);
				printToken(symbolName);
				$$ = $1;
				$$->setKeyType("value");
				$$->setDataType("int");
				code = "MOV AX, " + $1->getName() + "\n";
				$$->code += code;
			}
| CONST_FLOAT
			{
				symbolName = $1->getName();
				printInLogFile("factor : CONST_FLOAT", numLine);
				printToken(symbolName);
				$$ = $1;
				$$->setKeyType("value");
				$$->setDataType("float");
				code = "MOV AX, " + $1->getName() + "\n";
				$$->code += code;
			}
| variable INCOP
			{
				symbolName = $1->getName() + $2->getName();
				printInLogFile("factor : variable INCOP", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += ";incrementing the variable "+$1->getVarName()+"\n";
				code = "MOV AX, " + $1->getVarName() + "\n";
				code += "INC AX\n";
				code += "MOV " + $1->getVarName() + ", AX\n";
				$$->code += code;
				$$->setName($1->getVarName());
				$$->setVarName($1->getVarName());
				$$->setIncDec(true);
				printAssembly("factor : variable INCOP",$$->code, numLine);
			}
| variable DECOP
			{
				symbolName = $1->getName() + $2->getName();
				printInLogFile("factor : variable DECOP", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				$$->code += ";decrementing the variable "+$1->getVarName()+"\n";
				code = "MOV AX, " + $1->getVarName() + "\n";
				code += "DEC AX\n";
				code += "MOV " + $1->getVarName() + ", AX\n";
				$$->code += code;
				$$->setName($1->getVarName());
				$$->setVarName($1->getVarName());
				$$->setIncDec(true);
				printAssembly("factor : variable DECOP",$$->code, numLine);
			}
;


argument_list : arguments
			{
				symbolName = $1->getName();
				printInLogFile("argument_list : arguments", numLine);
				printToken(symbolName);
				$$ = $1;
				printAssembly("argument_list : arguments",$$->code, numLine);
			}
|
			{
				symbolName = " ";
				printInLogFile("argument_list : ", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				
			}
;


arguments : arguments COMMA logic_expression
			{
				symbolName = $1->getName() + " , " + $3->getName();
				printInLogFile("arguments : arguments COMMA logic_expression", numLine);
				printToken(symbolName);
				$$ = new SymbolInfo(symbolName, "NON_TERMINAL");
				arguments.push_back(*$3);
				$$->code = $1->code + $3->code;
				$$->code += "PUSH AX\n";
				printAssembly("arguments : arguments COMMA logic_expression",$$->code, numLine);
			}
| logic_expression
			{
				symbolName = $1->getName();
				printInLogFile("arguments : logic_expression", numLine);
				printToken(symbolName);
				$$ = $1;
				$$->code += "PUSH AX\n";
				arguments.push_back(*$1);
				printAssembly("arguments : logic_expression",$$->code, numLine);
			}
;

%%
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
	fclose(code_file);
	fclose(optimized_file);
	fclose(yyin);
	return 0;
}

