#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED

#include <string.h>
#include <math.h>

status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if (L.elem != NULL){
        return INFEASIBLE;
    }
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof (ElemType));
    if (!L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    if (L.length) return FALSE;
    return TRUE;
}

status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    return L.length;
}

status GetElem(SqList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length) return ERROR;
    e = *(L.elem + i - 1);
    return OK;
}

int LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; ++i){
        if (*(L.elem + i) == e)
            return i + 1;
    }
    return 0;
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    for (int i = 1; i < L.length; ++i){
        if (*(L.elem + i) == e) {
            pre = *(L.elem + i - 1);
            return OK;
        }
    }
    return ERROR;
}

status NextElem(SqList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length - 1; ++i){
        if (*(L.elem + i) == e) {
            next = *(L.elem + i + 1);
            return OK;
        }
    }
    return ERROR;
}

status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length + 1) return ERROR;
    if (L.length >= L.listsize){
        ElemType *newbase = (ElemType * )realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof (ElemType));
        if (!newbase) exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    ElemType *q = L.elem + i - 1;
    for (ElemType *p = L.elem + L.length - 1; p >= q; --p)
        *(p + 1) = *p;
    *q = e;
    ++L.length;
    return OK;
}

status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length) return ERROR;
    ElemType *p = L.elem + i - 1;
    e = *p;
    for (ElemType *q = L.elem + L.length - 1; p < q; ++p)
        *p = *(p + 1);
    --L.length;
    return OK;
}

status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    ElemType *p = L.elem, *q = L.elem + L.length - 1;
    printf(">>> #");
    for (; p < q; ++p)
        printf("%d ", *p);
    if (L.length) printf("%d", *q);
    printf("\n");
    return OK;
}

status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    FILE *fp = fopen(FileName, "w");
    ElemType *p = L.elem, *q = L.elem + L.length;
    //fprintf(fp, "%d\n", L.length);
    for (; p < q; ++p)
        fprintf(fp, "%d ", *p);
    fprintf(fp, "0");
    fclose(fp);
    return OK;
}
status  LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    //if (L.elem) return INFEASIBLE;
    // ERROR!
    FILE *fp = fopen(FileName, "r");
    L.length = 0;
    L.listsize = 100;
    L.elem = (ElemType * )malloc(LIST_INIT_SIZE * sizeof(ElemType));
    ElemType q;
    fscanf(fp, "%d", &q);
    while (q){
        L.elem[L.length++] = q;
        fscanf(fp, "%d", &q);
    }
    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    if (Lists.length > 10) return ERROR;
    strcpy((Lists.elem + Lists.length)->name, ListName);
    SqList Lp;
    Lp.elem = NULL;
    if (InitList(Lp) == ERROR) return ERROR;
    (Lists.elem + Lists.length)->L = Lp;
    ++Lists.length;
    return OK;
}

status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    for (int i = 0; i < Lists.length; ++i){
        if (strcmp(Lists.elem[i].name, ListName) == 0){
            for (int j = i + 1; j < Lists.length; ++j){
                strcpy(Lists.elem[j - 1].name, Lists.elem[j].name);
                Lists.elem[j - 1].L = Lists.elem[j].L;
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    for (int i = 0; i < Lists.length; ++i){
        if (strcmp(Lists.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}



int MaxSubArray(SqList &L){
    if (!L.elem) return INFEASIBLE;
    int sum[100];
    memset(sum, 0, sizeof sum);
    sum[0] = L.elem[0];
    int maxn = 0;
    for (int i = 1; i < L.length; ++i){
        sum[i] = sum[i - 1] + L.elem[i];
    }
    for (int i = 0; i < L.length; ++i)
        for (int j = i; j < L.length; ++j)
            if (maxn < sum[j] - sum[i]) maxn = sum[j] - sum[i];
    for (int i = 0; i<L.length;++i)
        if (maxn <sum[i]) maxn = sum[i];
    return maxn;
}

int SubArrayNum(SqList &L, int k){
    if (!L.elem) return INFEASIBLE;
    int sum[100];
    memset(sum, 0, sizeof sum);
    sum[0] = L.elem[0];
    int cnt = 0;
    for (int i = 1; i < L.length; ++i){
        sum[i] = sum[i - 1] + L.elem[i];
    }
    for (int i = 0; i < L.length; ++i)
        for (int j = i; j < L.length; ++j)
            if (sum[j] - sum[i] == k) ++cnt;
    return cnt;
}

int sortList(SqList &L){
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; ++i){
        int t = i;
        for (int j = i + 1; j < L.length; ++j)
            if (L.elem[t] > L.elem[j]) t = j;
        int qw;
        qw = L.elem[t];
        L.elem[t] = L.elem[i];
        L.elem[i] = qw;
    }
    return OK;
}

#endif // OPT_H_INCLUDED
