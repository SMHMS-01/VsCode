#include <iostream>
#include <windows.h>
#include <stack>
using namespace std;

struct listNode
{
    int value;
    listNode *pNext;
};

unsigned int GetListLength(listNode *phead)
{
    unsigned int length = 0;
    listNode *pNode = phead;
    while (pNode)
    {
        length++;
        pNode = pNode->pNext;
    }
    return length;
}
void addToListTail(listNode **pHead, int value)
{
    listNode *pNew = new listNode();
    pNew->value = value;
    pNew->pNext = nullptr;

    if (*pHead == nullptr)
        *pHead = pNew;
    else
    {
        listNode *pTmpNode = *pHead;
        while ((*pHead)->pNext == nullptr)
            pTmpNode = pTmpNode->pNext;
        pTmpNode->pNext = pNew;
    }
}

void deleteNode(listNode **pHead, int value)
{
    if (pHead == nullptr || *pHead == nullptr)
        return;
    listNode *pToBeDelete = nullptr;
    if ((*pHead)->value == value)
    {
        pToBeDelete = *pHead;
        *pHead = (*pHead)->pNext;
    }
    else
    {
        listNode *pTmpNode = *pHead;
        while (pTmpNode->pNext != nullptr && pTmpNode->pNext->value != value)
            pTmpNode = pTmpNode->pNext;
        // maybe all is't that value,so u need check it out
        if (pTmpNode->pNext != nullptr && pTmpNode->pNext->value == value)
        {
            pToBeDelete = pTmpNode->pNext;
            pTmpNode->pNext = pTmpNode->pNext->pNext;
        }
    }

    if (pToBeDelete != nullptr)
    {
        delete pToBeDelete;
        pToBeDelete = nullptr;
    }
}

void deleteNode(listNode **pHead, listNode *pToBeDelete)
{
    if (!pHead || !pToBeDelete)
        return;
    if (pToBeDelete->pNext)
    {
        listNode *pNext = pToBeDelete->pNext;
        pToBeDelete->value = pNext->value;
        pToBeDelete->pNext = pNext->pNext;
        delete pNext;
        pNext = nullptr;
    }
    else if ((*pHead) == pToBeDelete)
    {
        delete pToBeDelete;
        pToBeDelete = nullptr;
        *pHead = nullptr;
    }
    else
    {
        listNode *pNode = *pHead;
        while (pNode->pNext != pToBeDelete)
            pNode = pNode->pNext;
        if (!pNode->pNext && pNode != pToBeDelete) //已经是尾节点了，并且还不等于，说明不存在该节点
            throw domain_error("it doesn't exist here.\n");
        pNode->pNext = nullptr;
        delete pToBeDelete;
        pToBeDelete = nullptr;
    }
}

void printReversing_Stack(listNode *pHead)
{
    std::stack<listNode *> nodes;
    listNode *pNode = pHead;
    while (pNode != nullptr)
    {
        nodes.push(pNode);
        pNode = pNode->pNext;
    }
    while (!nodes.empty())
    {
        pNode = nodes.top();
        cout << pNode->value << '\t';
        nodes.pop();
    }
}

void printReversing_Recursively(listNode *pHead)
{
    if (pHead != nullptr)
    {
        if (pHead->pNext != nullptr)
            printReversing_Recursively(pHead->pNext);
        cout << pHead->value << '\t';
    }
}

void deleteDuplication(listNode **pHead)
{
    if (!pHead || !(*pHead))
        return;
    listNode *pPreNode = nullptr;
    listNode *pNodeNext = *pHead;
    while (pNodeNext)
    {
        listNode *_pNext = pNodeNext->pNext;
        bool needDelete = false;
        if (_pNext && _pNext->value == pNodeNext->value)
            needDelete = true;

        if (!needDelete)
        {
            pPreNode = pNodeNext;
            pNodeNext = pNodeNext->pNext;
        }
        else
        {
            int value = pNodeNext->value;
            listNode *pToBeDet = pNodeNext;
            while (pToBeDet && pToBeDet->value == value)
            {
                _pNext = pToBeDet->pNext;
                delete pToBeDet;
                pToBeDet = nullptr;
                pToBeDet = _pNext;
            }
            if (!pPreNode)
                *pHead = _pNext;
            else
                pPreNode->pNext = _pNext;
            pNodeNext = _pNext;
        }
    }
}

//快慢指针
listNode *FindKthToTail(listNode *pHead, unsigned int k)
{
    if (!pHead || k == 0)
        return nullptr;
    listNode *pAhead = pHead;
    listNode *pBehind = nullptr;

    for (unsigned int i = 0; i < k - 1; i++)
        if (pAhead->pNext)
            pAhead = pAhead->pNext;
        else
            return nullptr;
    pBehind = pHead;
    while (pAhead->pNext)
    {
        pAhead = pAhead->pNext;
        pBehind = pBehind->pNext;
    }
    return pBehind;
}

listNode *MeetingNode(listNode *pHead)
{
    if (!pHead)
        return nullptr;

    listNode *pSlow = pHead;
    if (pSlow == nullptr)
        return nullptr;
    listNode *pFast = pSlow->pNext;
    while (pFast && pSlow)
    {
        if (pFast == pSlow)
            return pFast;

        pSlow = pSlow->pNext;
        pFast = pFast->pNext;
        if (pFast)
            pFast = pFast->pNext;
    }
    return nullptr;
}

listNode *EntryNodeOfLoop(listNode *pHead)
{
    listNode *meetingNode = MeetingNode(pHead);
    if (!meetingNode)
        return nullptr;

    int nodeInLoop = 1;
    listNode *pNode1 = meetingNode;
    while (pNode1->pNext != meetingNode)
    {
        pNode1 = pNode1->pNext;
        ++nodeInLoop;
    }

    pNode1 = pHead;
    for (int i = 0; i < nodeInLoop; ++i)
        pNode1 = pNode1->pNext;
    listNode *pNode2 = pHead;
    while (pNode1 != pNode2)
    {
        pNode1 = pNode1->pNext;
        pNode2 = pNode2->pNext;
    }
    return pNode1;
}

listNode *ReverseList(listNode *pHead)
{
    listNode *pReverseHead = nullptr;
    listNode *pNode = pHead;
    listNode *pPre = nullptr;

    while (pNode)
    {
        listNode *pNext_ = pNode->pNext;
        if (!pNext_)
            pReverseHead = pNode;

        pNode->pNext = pPre;
        pPre = pNode;
        pNode = pNext_;
    }
    return pReverseHead;
}

listNode *Merge(listNode *pHead1, listNode *pHead2)
{
    if (!pHead1)
        return pHead2;
    if (!pHead2)
        return pHead1;
    listNode *pMergeHead = nullptr;
    if (pHead1->value > pHead2->value)
    {
        pMergeHead = pHead1;
        pMergeHead->pNext = Merge(pHead1->pNext, pHead2);
    }
    else
    {
        pMergeHead = pHead2;
        pMergeHead->pNext = Merge(pHead1, pHead2->pNext);
    }
    return pMergeHead;
}

listNode *FindFirstCommonNode(listNode *pHead1, listNode *pHead2)
{
    unsigned int length1 = GetListLength(pHead1);
    unsigned int length2 = GetListLength(pHead2);
    unsigned int LengthDif;

    listNode *pListLong = pHead1;
    listNode *pListShort = pHead2;
    LengthDif = length1 > length2 ? length1 - length2 : length2 - length1;
    pListLong = length1 > length2 ? pHead1 : pHead2;
    pListShort = length1 < length2 ? pHead1 : pHead2;

    for (int i = 0; i < LengthDif; ++i)
        pListLong = pListLong->pNext;
    while (pListLong && pListShort && pListLong != pListShort)
    {
        pListLong = pListLong->pNext;
        pListShort = pListShort->pNext;
    }
    listNode *pFirstCommonNode = pListLong;
    return pFirstCommonNode;
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
