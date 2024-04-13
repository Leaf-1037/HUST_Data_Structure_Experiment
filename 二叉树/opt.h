#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED

#include <cstring>
#include <set>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

set<int> s;

int n = 0, k = 0;

void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (definition[n].key == -1) return OK;
    if (definition[n].key == 0) T = NULL;
    else {
        if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
        if (k >= definition[n].key) return ERROR;
        T->data.key = definition[n].key;
        k++;
        strcpy(T->data.others, definition[n].others);
        n++;
        int state1 = CreateBiTree(T->lchild,definition);
        if (state1 == ERROR) return ERROR;
        n++;
        int state2 = CreateBiTree(T->rchild,definition);
        if (state2 == ERROR) return ERROR;
    }
    return OK;
    /********** End **********/
}

status DestroyBiTree(BiTree &T){
    if (T) {
        free(T);
        return OK;
    }
    return ERROR;

}

status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T){
    if (T->lchild) ClearBiTree(T->lchild);
    if (T->rchild) ClearBiTree(T->rchild);
    free(T);
    T=NULL;
    }
    return OK;

    /********** End **********/
}

int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!T) return 0;
    int p1 = 1, p2 = 1;
    if (T->lchild) p1 += BiTreeDepth(T->lchild);
    if (T->rchild) p2 += BiTreeDepth(T->rchild);
    return (p1>p2?p1:p2);

    /********** End **********/
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T->data.key == e) return T;
    BiTNode *u;
    if (T->lchild && (u=LocateNode(T->lchild, e))) return u;
    if (T->rchild && (u=LocateNode(T->rchild, e))) return u;
    return NULL;

    /********** End **********/
}

status PreOrderSet(BiTree T, KeyType k)
//先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T){
        if (k == T->data.key) return ERROR;
        s.insert(T->data.key);
        status p=PreOrderSet(T->lchild, k);
        status q=PreOrderSet(T->rchild, k);
        if (p==ERROR||q==ERROR) return ERROR;
    }
    return OK;
    /********** End **********/
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    s.clear();
    BiTNode *node = LocateNode(T, e);
    if (!node) return ERROR;
    if (PreOrderSet(T, value.key) == ERROR && value.key != e) return ERROR;
    node->data.key = value.key;
    strcpy(node->data.others, value.others);
    return OK;
    /********** End **********/
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T==NULL) return NULL;
    if (T->lchild && T->lchild->data.key == e) return T->rchild;
    if (T->rchild && T->rchild->data.key == e) return T->lchild;
    BiTree l=NULL, r=NULL;
    if (T->lchild) l=GetSibling(T->lchild, e);
    if (T->rchild) r=GetSibling(T->rchild, e);
    if (l) return l;
    if (r) return r;
    return NULL;
    //return NULL;

    /********** End **********/
}

int flag1 = 1;

status PreOrderTraverse1(BiTree T,TElemType c)
//先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //if (T->data.key == c.key) flag1 = 0;
    if (T){
        if (T->data.key == c.key) flag1 = 0;
        PreOrderTraverse1(T->lchild, c);
        PreOrderTraverse1(T->rchild, c);
    }
    return OK;
    /********** End **********/
}

int insert_s=0;
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(insert_s==1)return OK;
    if(T==NULL)return ERROR;
    if(T->data.key==c.key)return ERROR;
    if(LR==-1)
    {
        insert_s=1;
        BiTree new_t=(BiTree)malloc(sizeof(BiTNode));
        new_t->data=c;
        new_t->lchild=NULL;
        new_t->rchild=T;
        T=new_t;
        return OK;
    }
    if(T->data.key==e && (LR==0 || LR==1))
    {
        insert_s=1;
        if(LR==0)
        {
            BiTree new_t=(BiTree)malloc(sizeof(BiTNode));
            new_t->data=c;
            new_t->lchild=NULL;
            new_t->rchild=T->lchild;
            T->lchild=new_t;
            return OK;

        }
        if(LR==1)
        {
            BiTree new_t=(BiTree)malloc(sizeof(BiTNode));
            new_t->data=c;
            new_t->lchild=NULL;
            new_t->rchild=T->rchild;
            T->rchild=new_t;
            return OK;
        }
    }
    else
    {
        status sl=InsertNode(T->lchild,e,LR,c);
        status sr=InsertNode(T->rchild,e,LR,c);
        if(sl==OK || sr==OK)return OK;
        return ERROR;
    }
    return OK;
    /********** End **********/
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL) return;  
    stack<BiTree> s;  
    s.push(T);  
    while (!s.empty()) {  
        BiTree nd = s.top();  
        cout << nd->data << " ";  
        s.pop();  
        if (nd->right != NULL)  
            s.push(nd->right);  
        if (nd->left != NULL)  
            s.push(nd->left);  
    }  
    
    return OK;
    /********** End **********/
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T){
        InOrderTraverse(T->lchild, visit);
        visit(T);
        InOrderTraverse(T->rchild, visit);
    }
    return OK;

    /********** End **********/
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T){
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T);
    }
    return OK;

    /********** End **********/
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    queue<BiTree> q;
    if (T) q.push(T);
    while (!q.empty()){
        BiTree p = q.front();
        q.pop();
        visit(p);
        if (p->lchild) q.push(p->lchild);
        if (p->rchild) q.push(p->rchild);
    }
    return OK;
    /********** End **********/
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!T) return ERROR;
    if (T){
        int flag = 0;
        if (T->data.key == e) flag = 1;
        //if (T->rchild->data.key == e) flag = 2;
        if (flag){
            int deg = 0;
            if (T->lchild) deg +=1;
            if (T->rchild) deg+=2;
            if (deg==0){
                free(T);
                T = NULL;
            }
            if (deg==1) {
                BiTree tmp = T;
                T=T->lchild;free(tmp);tmp = NULL;
            }
            if (deg==2){
                BiTree tmp = T;
                T=T->rchild;free(tmp);tmp = NULL;
            }
            if (deg==3) {
                BiTree tmp=T,x=T->lchild;
                for(;x->rchild!=NULL;x=x->rchild);
                x->rchild=tmp->rchild;
                T=T->lchild;
                free(tmp);
                tmp=NULL;
            }
            return OK;
        }
        if (!flag) {
            status state1, state2;
            state1=DeleteNode(T->lchild, e);
            state2=DeleteNode(T->rchild, e);
            if (state1 == OK||state2 == OK) return OK;
            return ERROR;
        }
    }
    //return ERROR;
    /********** End **********/
}

typedef struct {
    int pos;
    TElemType data;
} HE;

int get_index(BiTree T,BiTree child,int idx)
{
    if(T==NULL)return 0;
    if(T->data.key==child->data.key)
    {
        return idx;
    }
    int gll = get_index(T->lchild,child,idx*2);
    int grr = get_index(T->rchild,child,idx*2+1);
    if(grr>gll)return grr;
    return gll;
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if(T!=NULL)
    {
        FILE *fp;
        int index=1;
        fp=fopen(FileName,"w");
        queue<BiTree> Q;
        Q.push(T);
        BiTree cur;
        while(Q.size())
        {
            cur=Q.front();
            Q.pop();
            if(cur!=NULL)
            {
                fprintf(fp,"%d %d %s ",get_index(T,cur,1),cur->data.key,cur->data.others);
            }
            index++;
            if(cur->lchild!=NULL) Q.push(cur->lchild);
            if(cur->rchild!=NULL) Q.push(cur->rchild);
        }
        fprintf(fp,"0 0 null");
        fclose(fp);
    }
    return OK;

    /********** End 1 **********/
}
status CreateBiTree(BiTree &T,HE definition[])
{
    int i=0,j;
    static BiTNode *st[100];
    while (j=definition[i].pos)
    {
         st[j]=(BiTNode *)malloc(sizeof(BiTNode));
       st[j]->data=definition[i].data;
       st[j]->lchild=NULL;
       st[j]->rchild=NULL;
       if (j!=1)
               if (j%2)   st[j/2]->rchild=st[j];
              else      st[j/2]->lchild=st[j];
       i++;
    }
    T=st[1];
    return OK;
}
status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    int i=0;
    HE definition[100];
    FILE *fp;
    fp=fopen(FileName,"r");
    do {
    fscanf(fp,"%d %d %s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);

    CreateBiTree(T,definition);
    fclose(fp);
    return OK;
}

int MaxPathSum(BiTree T){
    if (!T->lchild && !T->rchild) return T->data.key;
    int ll,rr;
    ll = (T->lchild?MaxPathSum(T->lchild):-INF);
    rr = (T->rchild?MaxPathSum(T->rchild):-INF);
    return std::max(ll,rr) + T->data.key;
}

BiTree LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2){
    if (T->data.key == e1 || T->data.key == e2 || T == NULL) return T;
    BiTree left=LowestCommonAncestor(T->lchild, e1, e2);
    BiTree right=LowestCommonAncestor(T->rchild,e1,e2);
    if (!left && !right) return NULL;
    else if (!left) return right;
    else if (!right) return left;
    else return T;
}

void InvertTree(BiTree &T){
    BiTree tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    if (T->lchild) InvertTree(T->lchild);
    if (T->rchild) InvertTree(T->rchild);
}

#endif // OPT_H_INCLUDED
