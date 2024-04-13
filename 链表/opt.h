#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED

#include <string.h>
#include <math.h>
#include <stdio.h>

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L) return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    if (!L) exit(OVERFLOW);
    L->next = NULL;
    return OK;

    /********** End **********/
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L, q;
    while (p){
        q = p->next;
        free(p);
        p = q;
    }
    L = NULL;
    return OK;

    /********** End **********/
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L->next, q;
    while (p){
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
    return OK;

    /********** End **********/
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    if (!L->next) return TRUE;
    return FALSE;

    /********** End **********/
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    int cnt = 0;
    LinkList p = L->next;
    while (p) {
        ++cnt;
        p = p->next;
    }
    return cnt;
    /********** End **********/
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    if (i < 1) return ERROR;
    LinkList p = L->next;
    int cnt = 0;
    while (p && cnt != i){
        ++cnt;
        if (cnt == i) {
            e = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;

    /********** End **********/
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L->next;
    int cnt = 0;
    while (p){
        ++cnt;
        if (p->data == e)
            return cnt;
        p = p->next;
    }
    return ERROR;

    /********** End **********/
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList q = L, p = L->next;
    if (!p) return ERROR;
    if (p->data == e) return ERROR;
    while (p) {
        if (p->data == e) {
            pre = q->data;
            return OK;
        }
        q = p;
        p = p->next;
    }
    return ERROR;

    /********** End **********/
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    if (!L->next) return ERROR;
    LinkList p, q;
    q = L->next; p = q->next;
    while (p && q->data != e){
        q = p;
        p = p->next;
    }
    if (p) {
        next = p->data;
        return OK;
    }
    return ERROR;

    /********** End **********/
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L;
    int cnt = 1;
    while (p && cnt < i){
        p = p->next;
        ++cnt;
    }
    if (i < 1 || p == NULL) return ERROR;
    LinkList q = (LinkList)malloc(sizeof(LNode));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return OK;

    /********** End **********/
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L->next, q = L;
    int j = 1;
    while (p && j < i){
        q = p;
        p = p->next;
        ++j;
    }
    if (i < 1 || !p) return ERROR;
    e = p->data;
    q->next = p->next;
    free(p);
    return OK;


    /********** End **********/
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L->next;
    printf("## ");
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;

    /********** End **********/
}

status reverseList(LinkList L){
    if (!L) return INFEASIBLE;
    int l = ListLength(L);
    for (int i = 1; i <= l/2; ++i){
        int a, b, e;
        GetElem(L,i,a);
        GetElem(L,l - i + 1, b);
        ListDelete(L,i,e);
        ListInsert(L,i,b);
        ListDelete(L,l-i+1,e);
        ListInsert(L,l-i+1,a);
    }
    return OK;
}

status RemoveNthFromEnd(LinkList L,int n){
    if (!L) return INFEASIBLE;
    int l = ListLength(L);
    if (n <= 0 || n > l) return ERROR;
    int e;
    ListDelete(L,l + 1 - n, e);
    return OK;
}

void swap_node(LinkList L, int i, int j){
    if (i == j) return;
    int a, b, e;
        GetElem(L,i,a);
        GetElem(L,j, b);
        ListDelete(L,i,e);
        ListInsert(L,i,b);
        ListDelete(L,j,e);
        ListInsert(L,j,a);
}

status sortList(LinkList L){
    if (!L) return INFEASIBLE;
    int l = ListLength(L);
    for (int i = 1; i <= l;++i){
        int minn,p = i,e;
        GetElem(L,i,minn);
        for (int j = i + 1; j <= l; ++j){
            GetElem(L, j, e);
            if (e < minn){
                minn = e;
                p=j;
            }
        }
        swap_node(L,i,p);
    }
    return OK;
}

status SaveList(LinkList L,const char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (!L) return INFEASIBLE;
    FILE *fp = fopen(FileName, "w");
    LinkList p = L->next;
    while (p) {
        fprintf(fp, "%d ", p->data);
        p = p->next;
    }
    fprintf(fp, "0");
    fclose(fp);
    return OK;

    /********** End 1 **********/
}

status LoadList(LinkList &L,const char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    //if (L) return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    FILE *fp = fopen(FileName, "r");
    LinkList p = L;
    int e;
    fscanf(fp, "%d", &e);
    while (e) {
        p->next = (LinkList)malloc(sizeof(LNode));
        p = p->next;
        p->data = e;
        fscanf(fp, "%d", &e);
    }
    p->next = NULL;
    fclose(fp);
    return OK;

    /********** End 2 **********/
}

status AddList(LISTS &Lists,const char ListName[]){
    LISTS p = (LISTS)malloc(sizeof(LLNode));
    if (p == NULL) exit(-1);
    InitList(p->Lp);
    strcpy(p->name,ListName);
    p->next = Lists->next;
    Lists->next = p;
    return OK;

}

status RemoveList(LISTS &Lists,const char ListName[]){
    if (!Lists) return INFEASIBLE;
    LISTS p = Lists->next, q = Lists;
    //int j = 1;
    while (p){
        if (strcmp(p->name, ListName) == 0){
            q->next = p->next;
            DestroyList(p->Lp);
            free(p);
            return OK;
        }
        q = p;
        p = p->next;
    }
    //if (!p) return ERROR;
    return ERROR;
}

LinkList findList(LISTS l,const char ListName[]){
    LISTS p = l->next;
    while (p){
        if (strcmp(ListName, p->name) == 0) return p->Lp;
        p = p->next;
    }
    return NULL;
}

int LocateList(LISTS l, const char ListName[]){
    LISTS p = l->next;
    int cnt = 0;
    while (p){
        ++cnt;
        if (strcmp(ListName, p->name) == 0) return cnt;
        p = p->next;
    }
    return 0;
}

#endif // OPT_H_INCLUDED
