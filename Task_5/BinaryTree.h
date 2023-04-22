#pragma once

#include <iostream>
#include "BinFileManagment.h"

using namespace std;

struct BinaryNode
{
    BinaryNode* pLeft = nullptr;
    BinaryNode* pRight = nullptr;
    int key = -1;
    int position = -1;

    BinaryNode() {}
};

class BinaryTree
{
private:

    BinaryNode* pRoot;

    void print(BinaryNode* pNode, int depth = 0)
    {
        if (pNode->pRight) print(pNode->pRight, depth + 1);

        for (int i = 0; i < depth; i++)
        {
            cout << '\t';
        }
        cout << pNode->key << endl;

        if (pNode->pLeft) print(pNode->pLeft, depth + 1);
    }

    void deleteElement(BinaryNode* pParent, BinaryNode* pNode)
    {
        BinaryNode* pTmp = pNode;

        if (!pNode->pLeft && !pNode->pRight)
        {
            if (pNode != pRoot)
            {
                if (pParent->pLeft == pNode) { pParent->pLeft = nullptr; }
                else { pParent->pRight = nullptr; }
            }
            delete pNode;
        }
        else if (pNode->pLeft && !pNode->pRight) // только левый
        {
            if (pNode == pRoot)
            {
                pRoot = pNode->pLeft;
            }
            else
            {
                if (pParent->pLeft == pNode) { pParent->pLeft = pNode->pLeft; }
                else { pParent->pRight = pNode->pLeft; }
            }
            delete pNode;
        }
        else if (!pNode->pLeft && pNode->pRight) // только правый
        {
            if (pNode == pRoot)
            {
                pRoot = pNode->pRight;
            }
            else
            {
                if (pParent->pLeft == pNode) { pParent->pLeft = pNode->pRight; }
                else { pParent->pRight = pNode->pRight; }
            }
            delete pNode;
        }
        else if (pNode->pLeft && pNode->pRight) // оба ребенка
        {
            BinaryNode* pAnotherTmp = pNode->pLeft;
            pParent = pNode;
            while (pAnotherTmp->pRight)
            {
                pParent = pAnotherTmp;
                pAnotherTmp = pAnotherTmp->pRight;
            }
            swap(pAnotherTmp->key, pNode->key);
            swap(pAnotherTmp->position, pNode->position);
            deleteElement(pParent, pAnotherTmp);
        }
    }

public:

    BinaryTree()
    {
        pRoot = nullptr;
    }

    void buildTreeByFile(std::string fileName)
    {
        int position = 1;
        string line;
        Product product;

        fstream file;
        file.open(fileName + ".dat", ios::binary | ios::in);

        if (!file.is_open())
        {
            return;
        }

        while (!file.eof())
        {
            file.read((char*)&product, sizeof(Product));
            this->addElement(product.code, position);
            position++;
        }
    }

    void addElement(int key, int position)
    {
        if (!pRoot)
        {
            pRoot = new BinaryNode();
            pRoot->key = key;
            pRoot->position = position;
        }
        else
        {
            BinaryNode* pNewNode = new BinaryNode();
            pNewNode->key = key;
            pNewNode->position = position;
            BinaryNode* pCurNode = pRoot;
            while (pCurNode)
            {
                if (pCurNode->key > key)
                {
                    if (!pCurNode->pLeft)
                    {
                        pCurNode->pLeft = pNewNode;
                        break;
                    }
                    else
                    {
                        pCurNode = pCurNode->pLeft;
                    }
                }
                else
                {
                    if (!pCurNode->pRight)
                    {
                        pCurNode->pRight = pNewNode;
                        break;
                    }
                    else
                    {
                        pCurNode = pCurNode->pRight;
                    }
                }
            }
        }
    }

    int findElementByKey(int key)
    {
        BinaryNode* pTmp = pRoot;

        while (pTmp)
        {
            if (pTmp->key == key)
            {
                return pTmp->position;
                break;
            }
            else if (key > pTmp->key)
            {
                pTmp = pTmp->pRight;
            }
            else
            {
                pTmp = pTmp->pLeft;
            }
        }
        return -1;
    }

    bool deleteElementByKey(int key)
    {
        BinaryNode* pTmp = pRoot;
        BinaryNode* pParent = pTmp;
        bool isDeleted = false;
        while (pTmp)
        {
            if (pTmp->key == key)
            {
                deleteElement(pParent, pTmp);
                isDeleted = true;
                break;
            }
            else if (key > pTmp->key)
            {
                pParent = pTmp;
                pTmp = pTmp->pRight;
            }
            else
            {
                pParent = pTmp;
                pTmp = pTmp->pLeft;
            }
        }
        return isDeleted;
    }

    void printTree()
    {
        print(pRoot, 0);
    }
};
