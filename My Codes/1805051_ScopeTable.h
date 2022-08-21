#ifndef COMPILER_SCOPETABLE_H
#define COMPILER_SCOPETABLE_H

#include "1805051_SymbolInfo.h"
#include <iostream>
#include <sstream>

class ScopeTable
{
    SymbolInfo **table;
    ScopeTable *parentScope;
    int bucketSize, id, children;
    string tableID;

public:
    ScopeTable(int n, ScopeTable *parent = NULL)
    {
        bucketSize = n;
        children = 0;
        if (parent != NULL)
        {
            id = parent->getChildrenNum();
            tableID = parent->getTableID() + "." + to_string(id);
            this->parentScope = parent;
        }
        else
        {
            id = 1;
            tableID = to_string(id);
            parentScope = NULL;
        }

        table = new SymbolInfo *[n];
        for (int i = 0; i < n; i++)
        {
            table[i] = NULL;
        }
    }

    int hashFunc(string name) const
    {
        int index = sdbm(name) % this->bucketSize;
        return index;
    }

    static uint32_t sdbm(string s){
        uint32_t hash = 0;
        for (int i = 0; i < s.length(); i++)
        {
            hash = s[i] + (hash<<6) + (hash<<16) - hash;
        }
        return hash;
    }

    int getChildrenNum() { return children; }

    int getID() { return id; }

    string getTableID() { return tableID; }

    void setChildrenNum(int n) { this->children = n; }

    void increaseChildrenNum(int n) { this->children += n; }

    void decreaseChildrenNum(int n) { this->children -= n; }

    void setID(int n)
    {
        this->id = n;
        string pTableID = this->parentScope->getTableID();
        this->tableID += pTableID + "." + to_string(id);
    }

    void setTableID(string s) { this->tableID = s; }

    ScopeTable *getParentScope() { return this->parentScope; }

    void setParentScope(ScopeTable *p)
    {
        this->parentScope = p;
        string pID = p->getTableID();
        this->id = p->getChildrenNum();
        this->tableID = pID + "." + to_string(id);
    }

    bool Insert(string name, string type, vector<SymbolInfo> params, string dataType="", string keyType="", int paramsNum=0, int arraySize=0, SymbolInfo *next=NULL, string code="", string varName="", bool incDec=false)
    {
        int index = hashFunc(name);

        // if the bucket is blank
        if (table[index] == NULL)
        {
            SymbolInfo *newSymbolInfo = new SymbolInfo(name, type);
            newSymbolInfo->setDataType(dataType);
            newSymbolInfo->setKeyType(keyType);
            newSymbolInfo->setParams(params);
            newSymbolInfo->setParamsNum(paramsNum);
            newSymbolInfo->setArraySize(arraySize);
            newSymbolInfo->setNextSymbolInfo(next);
            newSymbolInfo->setCode(code);
            newSymbolInfo->setIncDec(incDec);
            if(varName == "") newSymbolInfo->setVarName(name);
            else newSymbolInfo->setVarName(varName);
            table[index] = newSymbolInfo;
            return true;
        }

        // collision occurred
        else
        {
            SymbolInfo *root = table[index];
            // if symbol is at level-0
            if (root->getNextSymbolInfo() == NULL && root->getName() == name)
            {
                // duplicate found at level 0
                if (root->getType() == type)
                {
                    return false;
                }
            }

            while (root->getNextSymbolInfo() != NULL)
            {
                if (root->getName() == name)
                {
                    if (root->getType() == type)
                    {
                        return false;
                    }
                }
                root = root->getNextSymbolInfo();
            }
            if (root->getName() == name && root->getType() == type)
                return false;

            SymbolInfo *newSymbolInfo = new SymbolInfo(name, type);
            newSymbolInfo->setDataType(dataType);
            newSymbolInfo->setKeyType(keyType);
            newSymbolInfo->setParams(params);
            newSymbolInfo->setParamsNum(paramsNum);
            newSymbolInfo->setArraySize(arraySize);
            newSymbolInfo->setNextSymbolInfo(next);
            newSymbolInfo->setIncDec(incDec);
            if(varName == "") newSymbolInfo->setVarName(name);
            else newSymbolInfo->setVarName(varName);            
            newSymbolInfo->setCode(code);
            root->setNextSymbolInfo(newSymbolInfo);
            return true;
        }
    }

    bool InsertModified(string name, string type) {
        SymbolInfo *symbol = new SymbolInfo(name, type);
        int index = hashFunc(name);

        // if the bucket is blank
        if (table[index] == NULL)
        {
            table[index] = symbol;
            return true;
        }

        // collision occurred
        else
        {
            SymbolInfo *root = table[index];

            while (root->getNextSymbolInfo() != NULL)
            {
                root = root->getNextSymbolInfo();
            }

            root->setNextSymbolInfo(symbol);
            return true;
        }   
    }

    SymbolInfo *LookUp(string symbol)
    {
        int index = hashFunc(symbol);
        SymbolInfo *head = table[index];

        if (head == NULL)
        {
            return NULL;
        }
        else
        {
            int i = 0;
            while (head != NULL)
            {
                if (head->getName() == symbol)
                {
                    return head;
                }
                i++;
                head = head->getNextSymbolInfo();
            }
        }
        return NULL;
    }

    bool Delete(string name)
    {
        int index = hashFunc(name);

        SymbolInfo *head = table[index];
        SymbolInfo *temp, *p, *q;

        if (head == NULL)
        {
            return false;
        }
        else if (head->getNextSymbolInfo() == NULL)
        {
            if (head->getName() == name)
            {
                delete head->getNextSymbolInfo();
                delete head;
                table[index] = NULL;
                
                return true;
            }
            else
            {
                return false;
            }
        }
        else /*  if (head->getNextSymbolInfo() != NULL) */
        {
            if (head->getName() == name)
            {
                temp = table[index];
                table[index] = table[index]->getNextSymbolInfo();
                temp->setNextSymbolInfo(NULL);
                delete temp->getNextSymbolInfo();
                delete temp;
                return true;
            }
            else
            {
                p = head;
                q = head->getNextSymbolInfo();
                int i = 1;

                while (q != NULL)
                {
                    if (q->getName() == name)
                    {
                        p->setNextSymbolInfo(q->getNextSymbolInfo());
                        q->setNextSymbolInfo(NULL);

                        delete q->getNextSymbolInfo();
                        delete q;

                        return true;
                    }
                    else
                    {
                        p = q;
                        q = q->getNextSymbolInfo();
                        i++;
                    }
                }
                return false;
            }
        }
    }

    void Print()
    {
        cout << "ScopeTable # " << this->getTableID() << "\n";
        for (int i = 0; i < bucketSize; i++)
        {
            if (table[i] == NULL)
            {
                continue;
            }
            else
            {
                cout << to_string(i) << " --> ";
                SymbolInfo *temp = table[i];
                while (temp != NULL)
                {
                    cout << " < " << temp->getName() << " : " << temp->getType() << " > ";
                    temp = temp->getNextSymbolInfo();
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void PrintModified(FILE* fp) 
    {
        string line = "ScopeTable # " + this->getTableID() + "\n";
        fprintf(fp, line.c_str());
        
        for (int i = 0; i < bucketSize; i++)
        {
            if (table[i] == NULL)
            {
                continue;
            }
            else
            {
                line = to_string(i) + " --> ";
                fprintf(fp, line.c_str());
                SymbolInfo *temp = table[i];
                while (temp != NULL)
                {
                    line = " < " + temp->getName() + " : " + temp->getType() + " > ";
                    fprintf(fp, line.c_str());
                    temp = temp->getNextSymbolInfo();
                }
            }
            fprintf(fp, "\n");
                
        }
        fprintf(fp, "\n");                
    }

    ~ScopeTable()
    {
        for (int i = 0; i < bucketSize; i++)
        {
            if (table[i] != NULL)
            {
                SymbolInfo *temp = table[i];

                while (temp != NULL)
                {
                    SymbolInfo *p = temp;
                    temp = temp->getNextSymbolInfo();
                    delete p;
                }
            }
        }
        delete[] table;
    }
};

#endif
