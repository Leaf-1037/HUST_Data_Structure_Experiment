#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED

#include <string.h>
#include <math.h>

status InitList(SqList& L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    if (!L.elem) return INFEASIBLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

status ClearList(SqList& L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    if (!L.elem) return INFEASIBLE;
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (!L.elem) return INFEASIBLE;
    if (L.length) return FALSE;
    return TRUE;
}

status ListLength(SqList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if (!L.elem) return INFEASIBLE;
    return L.length;
}

status GetElem(SqList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length) return ERROR;
    e = *(L.elem + i - 1);
    return OK;
}

int LocateElem(SqList L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
{
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; ++i){
        if (*(L.elem + i) == e)
            return i + 1;
    }
    return 0;
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
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
// Lists��ɾ��һ������ΪListName�����Ա�
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
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
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
