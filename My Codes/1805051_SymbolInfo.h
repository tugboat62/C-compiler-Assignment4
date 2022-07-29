#ifndef COMPILER_SYMBOLINFO_H
#define COMPILER_SYMBOLINFO_H

#include <string>
#include<vector>

using namespace std;

class SymbolInfo
{
    string name;
    string type;
    string dataType;
    string keyType;
    vector<SymbolInfo> params;
    int paramsNum;
    int arraySize;

    SymbolInfo *next;

public:
    SymbolInfo()
    {
        this->name = "";
        this->type = "";
        this->next = NULL;
        this->dataType = "";
        this->keyType = "";
        this->paramsNum = 0;
        this->arraySize = 0;
    }

    SymbolInfo(string symbolName, string symbolType, SymbolInfo *nextPointer = NULL)
    {
        this->name = symbolName;
        this->type = symbolType;
        this->next = nextPointer;
        this->dataType = "";
        this->keyType = "";
        this->paramsNum = 0;
        this->arraySize = 0;
    }

    string getName() { return this->name; }
    void setName(string newSymbolName) { this->name = newSymbolName; }

    string getType() { return this->type; }
    void setType(string newSymbolType) { this->type = newSymbolType; }
    
    SymbolInfo *getNextSymbolInfo() { return this->next; }
    void setNextSymbolInfo(SymbolInfo *newNextChainingPointer) { this->next = newNextChainingPointer; }
    
    string getDataType() { return dataType; }
    void setDataType(string data) { this->dataType = data; }
    
    string getKeyType() { return keyType; }
    void setKeyType(string key) { this->keyType = key; }
    
    void addParam(SymbolInfo symbol) { 
        params.push_back(symbol);
        paramsNum++;
    }
    vector<SymbolInfo> getParams() { return params; }
    void setParams(vector<SymbolInfo> p) { 
        params = p;
        paramsNum = p.size();
    }
    void setParamsNum(int n) { paramsNum = n; }
    int getParamsNum() { return paramsNum; }
    void clearParams() { params.clear(); } 

    void setArraySize(int s) { arraySize = s; }
    int getArraySize() { return arraySize; }

    ~SymbolInfo()
    {
        // default destructor function
    }
};

#endif