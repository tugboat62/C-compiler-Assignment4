#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include "1805051_ScopeTable.h"

class SymbolTable
{
    ScopeTable *currentScope;
    int size;
    int count;

public:
    SymbolTable(int s)
    {
        this->size = s;
        this->count = 1;
        this->currentScope = new ScopeTable(size);
    }

    void setCurrentScope(ScopeTable *p)
    {
        this->currentScope = p;
    }

    ScopeTable *getCurrentScope()
    {
        return this->currentScope;
    }

    int getCurrentScopeID()
    {
        return currentScope->getID();
    }

    void EnterScope()
    {
        count++;
        currentScope->increaseChildrenNum(1);
        ScopeTable *newScopeTable = new ScopeTable(this->size, currentScope);
        currentScope = newScopeTable;
    }

    void ExitScope()
    {
        ScopeTable *temp = currentScope;
        currentScope = temp->getParentScope();
        delete temp;
    }

    bool Insert(string s, string type)
    {
        vector<SymbolInfo> params;
        if (currentScope->Insert(s, type, params))
            return true;
        return false;
    }

    bool Insert(SymbolInfo symbol) 
    {
        return currentScope->Insert(symbol.getName(), symbol.getType(), symbol.getParams(), symbol.getDataType(), symbol.getKeyType(), symbol.getParamsNum(), symbol.getArraySize(), symbol.getNextSymbolInfo(), symbol.code, symbol.getVarName(), symbol.getIncDec());
    }

    bool InsertModified(string name, string type)
    {
        if (currentScope->InsertModified(name, type))
            return true;
        return false;
    }

    bool Remove(string s)
    {
        if (currentScope->Delete(s))
            return true;
        return false;
    }

    SymbolInfo *LookUp(string name)
    {
        ScopeTable *temp = currentScope;
        SymbolInfo *symbol;

        while (temp != NULL)
        {
            symbol = temp->LookUp(name);
            if (symbol != NULL)
                return symbol;
            temp = temp->getParentScope();
        }
        
        return NULL;
    }
    
    void printCurrentScopeTable()
    {
        currentScope->Print();
    }

    void printAllScopeTable()
    {
        ScopeTable *temp = currentScope;
        while (temp != NULL)
        {
            temp->Print();
            temp = temp->getParentScope();
        }
    }

    void printModified(FILE* fp) 
    {
        ScopeTable *temp = currentScope;
        while (temp != NULL)
        {
            temp->PrintModified(fp);
            temp = temp->getParentScope();
        }
    }

    ~SymbolTable()
    {
        ScopeTable *p, *q;
        p = currentScope;

        while (p != NULL)
        {
            q = p->getParentScope();
            delete p;
            p = q;
        }
        delete p;
        delete q;
    }
};

#endif
