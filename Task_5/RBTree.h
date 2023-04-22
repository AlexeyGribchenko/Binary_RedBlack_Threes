#pragma once

#include <iostream>


using namespace std;

unsigned long long numberOfRotates = 0;

struct Node
{
    Node* pParent = nullptr;
    Node* pLeft = nullptr;
    Node* pRight = nullptr;
    bool isRed = false;
    int key = -1;
    int position = -1;

    Node() {}
};

class RBTree
{
private:

    void print(Node* pNode, int depth = 0)
    {
        if (pNode->pRight) print(pNode->pRight, depth + 1);

        for (int i = 0; i < depth; i++)
        {
            cout << '\t';
        }
        cout << pNode->key;
        (pNode->isRed) ? cout << " (R)\n" : cout << " (B)\n";

        if (pNode->pLeft) print(pNode->pLeft, depth + 1);
    }

public:

    Node* pRoot;

    RBTree()
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
            pRoot = new Node();
            pRoot->key = key;
            pRoot->position = position;
            pRoot->isRed = false;
        }
        else
        {
            Node* pNewNode = new Node();
            pNewNode->key = key;
            pNewNode->position = position;
            Node* pCurNode = pRoot;
            while (pCurNode)
            {
                if (pCurNode->key > key)
                {
                    if (!pCurNode->pLeft)
                    {
                        pNewNode->pParent = pCurNode;
                        pNewNode->isRed = true;
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
                        pNewNode->pParent = pCurNode;
                        pNewNode->isRed = true;
                        pCurNode->pRight = pNewNode;
                        break;
                    }
                    else
                    {
                        pCurNode = pCurNode->pRight;
                    }
                }
            }
            fixAdd(pNewNode);
        }
    }

    void fixAdd(Node* pNode)
    {
        while (pNode != pRoot && pNode->pParent->isRed)
        {
            if (pNode->pParent->pParent)
            {
                Node* pGrandparent = pNode->pParent->pParent;
                Node* pUncle = nullptr;
                if (pNode->pParent == pGrandparent->pRight) // �������� ������ ��� ����
                {
                    if (!pGrandparent->pLeft || pGrandparent->pLeft->isRed == false)
                    {
                        if (pNode == pGrandparent->pRight->pLeft) // �������
                        {
                            rightRotate(pNode->pParent);
                        }
                        pGrandparent->isRed = true;
                        pGrandparent->pRight->isRed = false;
                        leftRotate(pGrandparent);
                    }
                    else
                    {
                        pUncle = pGrandparent->pLeft;

                        pGrandparent->isRed = true;
                        pNode->pParent->isRed = false;
                        pUncle->isRed = false;
                    }
                }
                else // �������� ����� ��� ����
                {
                    if (!pGrandparent->pRight || pGrandparent->pRight->isRed == false)
                    {
                        if (pNode == pGrandparent->pLeft->pRight) // �������
                        {
                            leftRotate(pNode->pParent);
                        }
                        pGrandparent->isRed = true;
                        pGrandparent->pLeft->isRed = false;
                        rightRotate(pGrandparent);
                    }
                    else
                    {
                        pUncle = pGrandparent->pRight;

                        pGrandparent->isRed = true;
                        pNode->pParent->isRed = false;
                        pUncle->isRed = false;
                    }
                }
                pNode = pGrandparent;
            }
            else
            {
                pNode->pParent->isRed = false;
            }
        }
        pRoot->isRed = false;
    }

    void leftRotate(Node* pNode)
    {
        numberOfRotates++;
        Node* pG = pNode;
        Node* pP = pG->pRight;

        pP->pParent = pG->pParent;
        if (pP->pParent == nullptr)
        {
            pRoot = pP;
        }
        else
        {
            if (pP->pParent->pLeft == pG)
            {
                pP->pParent->pLeft = pP;
            }
            else
            {
                pP->pParent->pRight = pP;
            }
        }
        pG->pParent = pP;

        if (pP->pLeft != nullptr)
        {
            pP->pLeft->pParent = pG;
        }

        pG->pRight = pP->pLeft;
        pP->pLeft = pG;
    }

    void rightRotate(Node* pNode)
    {
        numberOfRotates++;
        Node* pG = pNode;
        Node* pP = pG->pLeft;

        pP->pParent = pG->pParent;
        if (pP->pParent == nullptr)
        {
            pRoot = pP;
        }
        else
        {
            if (pP->pParent->pRight == pG)
            {
                pP->pParent->pRight = pP;
            }
            else
            {
                pP->pParent->pLeft = pP;
            }
        }
        pG->pParent = pP;

        if (pP->pRight != nullptr)
        {
            pP->pRight->pParent = pG;
        }

        pG->pLeft = pP->pRight;
        pP->pRight = pG;
    }

    int findElementByKey(int key)
    {
        Node* pTmp = pRoot;

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
        Node* pTmp = pRoot;
        bool isDeleted = false;
        while (pTmp)
        {
            if (pTmp->key == key)
            {
                deleteElement(pTmp);
                isDeleted = true;
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
        return isDeleted;
    }

    void deleteElement(Node* pNode)
    {
        if (pNode->isRed) // ���� ���� �������, �� � ���� ���� 2, ���� 0 ��������
        {
            if (!pNode->pLeft && !pNode->pRight) // ��� �����
            {
                if (pNode->pParent->pLeft == pNode) pNode->pParent->pLeft = nullptr;
                else                                pNode->pParent->pRight = nullptr;
                delete pNode;
            }
            else // ���� ��� ������� - ������� ������������ ���� �����
            {
                Node* pTmp = pNode->pLeft;
                while (pTmp->pRight)
                {
                    pTmp = pTmp->pRight;
                }
                swap(pTmp->key, pNode->key);
                swap(pTmp->position, pNode->position);
                deleteElement(pTmp);
            }
        }
        else
        {
            if (pNode->pLeft && !pNode->pRight) // ���� ������ ����� �������
            {
                swap(pNode->key, pNode->pLeft->key);
                swap(pNode->position, pNode->pLeft->position);
                deleteElement(pNode->pLeft);
            }
            else if (!pNode->pLeft && pNode->pRight) // ���� ������ ������ �������
            {
                swap(pNode->key, pNode->pRight->key);
                swap(pNode->position, pNode->pRight->position);
                deleteElement(pNode->pRight);
            }
            else if (!pNode->pLeft && !pNode->pRight) // ��� �����
            {
                Node* pP = pNode->pParent;
                if (pP->pLeft == pNode) pP->pLeft = nullptr;
                else                    pP->pRight = nullptr;
                delete pNode;
                fixDelete(pP, nullptr);
            }
            else // ���� ��� ������� - ������� ����������� ���� ������
            {
                Node* pTmp = pNode->pRight;
                while (pTmp->pLeft)
                {
                    pTmp = pTmp->pLeft;
                }
                swap(pTmp->key, pNode->key);
                swap(pTmp->position, pNode->position);
                deleteElement(pTmp);
            }
        }
    }

    void fixDelete(Node* pNode, Node* pDel)
    {
        if (pNode->pLeft == pDel) // ������� ����� ����
        {
            Node* pRSon = pNode->pRight;
            if (pNode->isRed == true)
            {
                // �������� �������, ������� ������, ������ ���� �������
                if (pRSon->isRed == false && pRSon->pRight->isRed == true)
                {
                    pNode->isRed = false;
                    pRSon->isRed = true;
                    pRSon->pRight->isRed = false;
                    leftRotate(pNode);
                    return;
                }
                // �������� (������� ����) �������, ������� ������ � ������� �������
                if ((!pRSon->pLeft && !pRSon->pRight) ||(pRSon->pLeft->isRed == false && pRSon->pRight->isRed == false)) // �������� (������� ����) �������, ������� ������ � ������� �������
                {
                    pNode->isRed = false;
                    pRSon->isRed = true;
                    return;
                }
            }
            if (pNode->isRed == false)
            {
                Node* pRSon_LGSon = pRSon->pLeft;
                if (pRSon->isRed == true)
                {
                    // �������� ������, ������ ��� �������, � ������ ����� ������ ��������.
                    if ((!pRSon_LGSon->pRight && !pRSon_LGSon->pLeft) || (pRSon_LGSon->pRight->isRed == false && pRSon_LGSon->pLeft->isRed == false))
                    {
                        pRSon->isRed = false;
                        pRSon_LGSon->isRed = true;
                        leftRotate(pNode);
                        return;
                    }
                    // �������� ������, ������ ��� �������, � ������ ����� ������ ������� �������.
                    if (pRSon_LGSon->pRight->isRed == true)
                    {
                        pRSon_LGSon->pRight->isRed = false;
                        rightRotate(pRSon);
                        leftRotate(pNode);
                        return;
                    }
                }
                if (pRSon->isRed == false)
                {
                    // �������� ������, ������ ��� ������ � ����� ������
                    if ((!pRSon->pRight && !pRSon->pLeft) || (pRSon->pLeft->isRed == false && pRSon->pRight->isRed == false))
                    {
                        pRSon->isRed = true;
                        fixDelete(pNode->pParent, pNode);
                        return;
                    }
                    // �������� ������, ������ ��� ������ � ����� ���� ���� �������
                    if (pRSon_LGSon->isRed == true)
                    {
                        pRSon_LGSon->isRed = false;
                        rightRotate(pRSon);
                        leftRotate(pNode);
                        return;
                    }
                }
            }
        }
        else // ������� ������ ����
        {
            Node* pLSon = pNode->pLeft;
            if (pNode->isRed == true)
            {
                // �������� �������, ������� ������, ����� ���� �������
                if (pLSon->isRed == false && pLSon->pLeft->isRed == true)
                {
                    pNode->isRed = false;
                    pLSon->isRed = true;
                    pLSon->pLeft->isRed = false;
                    rightRotate(pNode);
                    return;
                }
                // �������� (������� ����) �������, ������� ������ � ������� �������
                if ((!pLSon->pLeft && !pLSon->pRight) || (pLSon->pLeft->isRed == false && pLSon->pRight->isRed == false)) // �������� (������� ����) �������, ������� ������ � ������� �������
                {
                    pNode->isRed = false;
                    pLSon->isRed = true;
                    return;
                }
            }
            if (pNode->isRed == false)
            {
                Node* pLSon_RGSon = pLSon->pRight;
                if (pLSon->isRed == true)
                {
                    // �������� ������, ����� ��� �������, � ������� ����� ������ ��������.
                    if ((!pLSon_RGSon->pLeft && !pLSon_RGSon->pRight) || (pLSon_RGSon->pLeft->isRed == false && pLSon_RGSon->pRight->isRed == false))
                    {
                        pLSon->isRed = false;
                        pLSon_RGSon->isRed = true;
                        rightRotate(pNode);
                        return;
                    }
                    // �������� ������, ����� ��� �������, � ������� ����� ����� ������� �������.
                    if (pLSon_RGSon->pLeft->isRed == true)
                    {
                        pLSon_RGSon->pLeft->isRed = false;
                        leftRotate(pLSon);
                        rightRotate(pNode);
                        return;
                    }
                }
                if (pLSon->isRed == false)
                {
                    // �������� ������, ����� ��� ������ � ����� ������
                    if ((!pLSon->pRight && !pLSon->pLeft) || (pLSon->pRight->isRed == false && pLSon->pLeft->isRed == false))
                    {
                        pLSon->isRed = true;
                        fixDelete(pNode->pParent, pNode);
                        return;
                    }
                    // �������� ������, ����� ��� ������ � ������ ���� � ���� �������
                    if (pLSon_RGSon->isRed == true)
                    {
                        pLSon_RGSon->isRed = false;
                        leftRotate(pLSon);
                        rightRotate(pNode);
                        return;
                    }
                }
            }
        }
    }

    void printTree()
    {
        print(pRoot, 0);
    }
};
