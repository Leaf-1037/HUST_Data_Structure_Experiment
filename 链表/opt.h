#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED

#include <string.h>
#include <math.h>
#include <stdio.h>

status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L) return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    if (!L) exit(OVERFLOW);
    L->next = NULL;
    return OK;

    /********** End **********/
}

status DestroyList(LinkList &L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    if (!L->next) return TRUE;
    return FALSE;

    /********** End **********/
}

int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
