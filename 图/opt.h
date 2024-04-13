#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED


#include <queue>
#include <cstring>

using namespace std;

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int p = 0;
    //G.vertices=(VNode*)malloc(MAX_VERTEX_NUM*sizeof(VNode));
    while(V[p].key!=-1){
        G.vertices[p].data = V[p];
        G.vertices[p].firstarc=NULL;
        for (int i = 0; i < p; ++i)
            if (V[p].key == V[i].key) return ERROR;
        ++p;
        if (p>20) return ERROR;
    }
    if (p==0) return ERROR;
    //return OK;//1
    int t = 0;
    while (VR[t][0] != -1){
        int u=-1;
        for (int i = 0; i < p; ++i){
            if (V[i].key == VR[t][0]) {
                u=i;
                break;
            }
        }
        if (u==-1) return ERROR;
        int v=-1;
        for (int i = 0; i < p; ++i){
            if (V[i].key == VR[t][1]) {
                v=i;
                break;
            }
        }
        if (v==-1) return ERROR;
            ArcNode* ps=G.vertices[u].firstarc,*pp;
            pp=(ArcNode *)malloc(sizeof(ArcNode));
            pp->adjvex=v;
            pp->nextarc=ps;
            G.vertices[u].firstarc=pp;

            ArcNode* pt=G.vertices[v].firstarc;
            pp=(ArcNode *)malloc(sizeof(ArcNode));
            pp->adjvex=u;
            pp->nextarc=pt;
            G.vertices[v].firstarc=pp;
        //printf("%d,%d  ", u, v);
        ++t;
        //printf("%d",t);
    }
    G.vexnum=p;
    G.arcnum=t;
    G.kind=UDG;
    return OK;
    /********** End **********/
}


status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0;i<G.vexnum;++i){
        ArcNode *pt = G.vertices[i].firstarc,*ps;
        while (pt){
            ps=pt->nextarc;
            free(pt);
            pt = ps;
        }

    }
    G.vexnum = 0;
    G.arcnum=0;
    return OK;
    /********** End **********/
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i<G.vexnum;++i)
    if (G.vertices[i].data.key==u) return i;
    return -1;

    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/

    int l=-1;
    for (int i =0;i<G.vexnum;++i)
        if (G.vertices[i].data.key==u)
            l=i;
    if (l==-1) return ERROR;
    for (int i = 0; i<G.vexnum;++i)
        if (i != l && G.vertices[i].data.key==value.key) return ERROR;
    G.vertices[l].data=value;
    return OK;

    /********** End **********/
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < G.vexnum;++i) {
        if (G.vertices[i].data.key == u)
            return G.vertices[i].firstarc->adjvex;
    }
    return -1;
    /********** End **********/
}

int Get_index(ALGraph G,int key)
{
    for(int i=0;i<G.vexnum;i++)
        if(G.vertices[i].data.key==key)
            return i;
    return -1;
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int s1=Get_index(G,v);
    int s2=Get_index(G,w);
    if (s1==-1||s2==-1) return -1;
    ArcNode* p=G.vertices[s1].firstarc;
    while(p && p->nextarc){
        if (p->adjvex==s2) return p->nextarc->adjvex;
        p=p->nextarc;
    }
    return -1;


    /********** End **********/
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int tmp = v.key;
    for (int i = 0; i < G.vexnum;++i)
        if (tmp==G.vertices[i].data.key) return ERROR;
    if (G.vexnum==MAX_VERTEX_NUM) return ERROR;
    G.vertices[G.vexnum].data=v;
    G.vertices[G.vexnum].firstarc=NULL;
    ++G.vexnum;
    return OK;

    /********** End **********/
}

status DestroyList(ArcNode * f)
{
    if(f==NULL)return INFEASIBLE;
    ArcNode * p=f;
    while(p)
    {
        f=f->nextarc;
        free(p);
        p=f;
    }
    return OK;
}
void DeleteVex_A_Node(ALGraph &G,VNode &Node,int index)
{
    ArcNode * p =Node.firstarc;
    while(Node.firstarc!=NULL && Node.firstarc->adjvex==index)
    {
        G.arcnum--;
        Node.firstarc=Node.firstarc->nextarc;
        free(p);
        p=Node.firstarc;
    }
    if(Node.firstarc==NULL)return;
    ArcNode * q =Node.firstarc->nextarc;
    for(;q!=NULL;)
    {
        if(q->adjvex==index)
        {
            G.arcnum--;
            p->nextarc=q->nextarc;
            free(q);
            q=p->nextarc;
        }
        else
        {
            p=p->nextarc;
            q=q->nextarc;
        }
    }
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int loc=Get_index(G,v);
    if (loc==-1||G.vexnum==1) return ERROR;
    for(int i=0;i<G.vexnum;i++)
    {
        DeleteVex_A_Node(G,G.vertices[i],loc);
    }
    for(int i=0;i<G.vexnum;i++)
    {
        ArcNode * f=G.vertices[i].firstarc;
        for(;f!=NULL;f=f->nextarc)
        {
            if(f->adjvex>loc)
            {
                (f->adjvex)--;
            }
        }
    }
    DestroyList(G.vertices[loc].firstarc);
    for (int i=loc;i<G.vexnum-1;++i)
        G.vertices[i] = G.vertices[i+1];
    --G.vexnum;
    return OK;
    /********** End **********/
}

void DeleteArc_A_Node(VNode &Node,int index)
{
    ArcNode * p =Node.firstarc;
    if(p==NULL)return;
    if(p->adjvex==index)//首个链表节点就是
    {
        Node.firstarc=Node.firstarc->nextarc;
        free(p);
        p=NULL;
        return;
    }
    ArcNode * q =Node.firstarc->nextarc;
    for(;q!=NULL;)
    {
        if(q->adjvex==index)
        {
            p->nextarc=q->nextarc;
            free(q);
            q=p->nextarc;
            break;
        }
        else
        {
            p=p->nextarc;
            q=q->nextarc;
        }
    }
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int s1=Get_index(G,v);
    int s2=Get_index(G,w);
    if (s1==-1 || s2==-1) return ERROR;
    ArcNode *q=G.vertices[s1].firstarc;
    while (q){
        if (q->adjvex==s2) return ERROR;
        q=q->nextarc;
    }

    ArcNode* p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = s2;
    p->nextarc=G.vertices[s1].firstarc;
    G.vertices[s1].firstarc=p;

    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = s1;
    p->nextarc=G.vertices[s2].firstarc;
    G.vertices[s2].firstarc=p;
    ++G.arcnum;
    return OK;
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int s1=Get_index(G,v);
    int s2=Get_index(G,w);
    if (s1==-1 || s2==-1) return ERROR;
    ArcNode *q=G.vertices[s1].firstarc;
    int flag=0;
    while(q){
        if (q->adjvex==s2) flag=1;
        q=q->nextarc;
    }
    if (flag==0) return ERROR;
    DeleteArc_A_Node(G.vertices[s1],s2);
    DeleteArc_A_Node(G.vertices[s2],s1);
    --G.arcnum;
    return OK;
    /********** End **********/
}

int vis2[30];

void dfs(ALGraph G,int n,void (*visit)(VertexType)){
    if (G.vertices[n].data.key==0) return;
    vis2[n]=1;
    visit(G.vertices[n].data);
    ArcNode *p=G.vertices[n].firstarc;
    while(p){
        if(vis2[p->adjvex]==0) {
            vis2[p->adjvex]=1;
            dfs(G,p->adjvex,visit);
        }
        p=p->nextarc;
    }
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    memset(vis2,0,sizeof(vis2));
    for (int i=0;i<G.vexnum;++i)
    {
        if (vis2[i]==0) dfs(G,i,visit);
    }
    return OK;
    /********** End **********/
}

int vis1[30];

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    memset(vis1,0,sizeof(vis1));
    queue<int> q;
    for (int i = 0;i<G.vexnum;++i){
    if (vis1[i]==0) q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if (vis1[u]==0) visit(G.vertices[u].data);
        vis1[u]=1;
        ArcNode *p=G.vertices[u].firstarc;
        while(p){
            if (vis1[p->adjvex]==0) {
                q.push(p->adjvex);
            }
            p=p->nextarc;
        }
    }
    }
    return OK;
    /********** End **********/
}

int Get_v_index(ALGraph G,int key)
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key==key)
        {
            return i;
        }
    }
    return -1;
}

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int p = 0;
    while(V[p].key!=-1){
        G.vertices[p].data = V[p];
        G.vertices[p].firstarc=NULL;
        for (int i = 0; i < p; ++i)
            if (V[p].key == V[i].key) return ERROR;
        ++p;
        if (p>20) return ERROR;
    }
    if (p==0) return ERROR;
    int t = 0;
    while (VR[t][0] != -1){
        int u=-1;
        for (int i = 0; i < p; ++i){
            if (V[i].key == VR[t][0]) {
                u=i;
                break;
            }
        }
        if (u==-1) return ERROR;
        int v=-1;
        for (int i = 0; i < p; ++i){
            if (V[i].key == VR[t][1]) {
                v=i;
                break;
            }
        }
        if (v==-1) return ERROR;


            ArcNode* ps=G.vertices[u].firstarc,*pp;
            pp=(ArcNode *)malloc(sizeof(ArcNode));
            pp->adjvex=v;
            pp->nextarc=ps;
            G.vertices[u].firstarc=pp;

            ArcNode* pt=G.vertices[v].firstarc;
            pp=(ArcNode *)malloc(sizeof(ArcNode));
            pp->adjvex=u;
            pp->nextarc=pt;
            G.vertices[v].firstarc=pp;
        //printf("%d,%d  ", u, v);
        ++t;
    }
    G.vexnum=p;
    G.arcnum=t;
    G.kind=UDG;
    /********** End **********/
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE*fp1;
    fp1=fopen(FileName,"w");
    int i,j,tt=-1;
    int nnn[30][2];
    i=0;
    while(i<G.vexnum)
    {
        fprintf(fp1,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
        ++i;
    }
    i=0;
    fprintf(fp1,"%d null ",tt);
    while(i<G.vexnum)
    {
        for(j=0;j<30;++j)
        {
            nnn[j][0]=-1;
            nnn[j][1]=-1;
        }
        j=0;
        if(G.vertices[i].firstarc!=NULL)
        {
            if(G.vertices[i].data.key<G.vertices[G.vertices[i].firstarc->adjvex].data.key)
            {
                nnn[j][0]=G.vertices[i].data.key;
                nnn[j][1]=G.vertices[G.vertices[i].firstarc->adjvex].data.key;
                ++j;
            }
            ArcNode*p=G.vertices[i].firstarc;
            while(p->nextarc!=NULL)
            {
                p=p->nextarc;
                if(G.vertices[i].data.key<G.vertices[p->adjvex].data.key)
                {
                    nnn[j][0]=G.vertices[i].data.key;
                    nnn[j][1]=G.vertices[p->adjvex].data.key;
                    ++j;
                }
            }
        }
        --j;
        while(j>=0)
        {
           fprintf(fp1,"%d %d ",nnn[j][0],nnn[j][1]);
            --j;
        }
        ++i;
    }
    fprintf(fp1,"%d %d ",tt,tt);
    fclose(fp1);
    return OK;

}

status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    if(G.vexnum!=0) return ERROR;
    VertexType V[30];
    KeyType VR[100][2];
    int i;
    FILE*fp2;
    fp2=fopen(FileName,"r");
    i=0;
    do {
        fscanf(fp2,"%d %s ",&V[i].key,V[i].others);
    } while(V[i++].key!=-1);
    i=0;
    do {
        fscanf(fp2,"%d %d",&VR[i][0],&VR[i][1]);
    } while(VR[i++][0]!=-1);

    fclose(fp2);
    CreateGraph(G,V,VR);
    return OK;
}





#endif // OPT_H_INCLUDED
