#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "def.h"
#include "opt.h"
//#include <iostream>
#include <stack>
//#include <cstring>
#include <vector>
#include <queue>
#define MAXN 100

using namespace std;

ALGraph G;

ALGraph G1[20];
int available[20];
int totot=0;

int g[40][40];

void MatrixTransformer(ALGraph G){
    for (int i = 0;i<20;++i)
        for (int j=0;j<20;++j)
        g[i][j]=0;
    for (int i=0;i<G.vexnum;++i)
    {
        ArcNode *p=G.vertices[i].firstarc;
        while(p){
            g[i][p->adjvex]=1;
            p=p->nextarc;
        }
    }
}

int anss[20];

status VerticesSetLessThanK(ALGraph G,KeyType v,int k){
    MatrixTransformer(G);
    int p=Get_v_index(G,v);
    for (int i = 0;i<20;++i) anss[i]=0;
    if (p==-1) return ERROR;
    anss[p]=1;
    for (int i = 1;i < k;++i){
        for (int j = 0;j < 20;++j)
        if (anss[j]==1){
            for (int k=0;k<20;++k)
                if (g[j][k]==1) anss[k] = 1;
        }
    }
    return OK;
}

stack<int> stk;
vector<int> p[MAXN];
int low[MAXN], dfn[MAXN], vis[MAXN], ans[MAXN];
int tot = 0, sum = 0;

void VectorTransformer(ALGraph G){
    for(int i=0;i<20;++i)
        p[i].clear();
    for (int i=0;i<G.vexnum;++i)
    {
        ArcNode *t=G.vertices[i].firstarc;
        while(t){
            p[i].push_back(t->adjvex);
            t=t->nextarc;
        }
    }
}

void tarjan(int u){
//    printf("#%d# ", u);
//    printf("\n");
//    printf("##dfn ");
//    for (int i = 0; i < n; ++i) printf("%d ", dfn[i]);
//    printf("\n");
//    printf("##low ");
//    for (int i = 0; i < n; ++i) printf("%d ", low[i]);
//    printf("\n");
//    printf("\n");

    dfn[u] = low[u] = ++tot;
    vis[u] = 1;
    stk.push(u);
    //return;
    for (int i = 0; i < p[u].size(); ++i){
        int v = p[u][i];

        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (vis[u]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int j = -1;
        printf("##%d: ", ++sum);
        while (u != j) {
            j = stk.top();
            printf("%d ", stk.top());
            vis[stk.top()] = 0;
            stk.pop();
        }
        printf("\n");
    }
}

void ConnectedComponentsNums(ALGraph G){
    VectorTransformer(G);
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(vis,0,sizeof(vis));
    memset(ans,0,sizeof(ans));
    for (int i = 0; i < G.vexnum; ++i)
        if (!dfn[i]) tarjan(i);
}

int tm[20][20];

void MatrixMul(){
    for (int i = 0;i<20;++i)
        for (int j=0;j<20;++j)
        tm[i][j]=0;
    for (int i = 0;i<20;++i)
    for (int j = 0;j<20;++j){
        for (int k=0;k<20;++k)
            tm[i][j]+=g[i][k]*g[k][j];
    }
    for (int i = 0;i<20;++i)
        for (int j=0;j<20;++j)
        g[i][j]=tm[i][j];
}

int ShortestPathLength(ALGraph G,KeyType v,KeyType w){
    int s1=Get_v_index(G,v),s2=Get_v_index(G,w);
    if (s1==-1 || s2==-1) return -1;
    MatrixTransformer(G);
    if (g[s1][s2]) return 1;
    for (int i = 1;i<=G.vexnum;++i){
        MatrixMul();
        if (g[s1][s2]) return i+1;
    }
    return -1;
/********/
}

void menuBar(){
    //system("cls");
    //list_read!
    printf("----------------- -- MENU BAR ------------------\n");
    printf("|                                               |\n");
    printf("|      FORMAT: <OPERATION> <KEY1> <KEY2>..      |\n");
    printf("|  1. CreateCraph        2. DestroyGraph        |\n");
    printf("|  3. LocateVex          4. PutVex              |\n");
    printf("|  5. FirstAdjVex        6. NextAdjVex          |\n");
    printf("|  7. InsertVex          8. DeleteVex           |\n");
    printf("|  9. InsertArc          10.DeleteArc           |\n");
    printf("|  11.DFSTraverse        12.BFSTraverse         |\n");
    printf("|  13.VerticesSetLessThanK 14.ShortestPathLength|\n");
    printf("|  15.ConnectedComponentsNums     16.SaveGraph  |\n");
    printf("|  17.LoadGraph          18.AddGraph            |\n");
    printf("|  19.InitNewGraph       20.RemoveNewGraph      |\n");
    printf("|                Press 0 to exit~               |\n");
    printf("|                                               |\n");
    printf("-------------------- MENU BAR ------------------\n\n");
}

void initialBar(){
    printf("--------------- WELCOME! ---------------\n");
    printf("|                                      |\n");
    printf("|          欢迎来到图的世界！！        |\n");
    printf("|                                      |\n");
    printf("----------------------------------------\n\n");
}

void putError(int state, string str = "NUMBER"){
    if (state == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
    if (state == OVERFLOW) printf(">>> ERROR: OVERFLOW! \n");
    if (state == ERROR) std::cout << ">>> ERROR: INVALID " <<str << "! \n";
    printf(">>>  \n");
}

void visit(VertexType v)
{
    printf(" %d,%s",v.key,v.others);
}

int getopt(){
    getchar();
    getchar();
    system("cls");
    int st;
    printf("\n请输入操作符：\n");
    scanf("%d", &st);
    return st;
}

int main()
{
    memset(available,0,sizeof(available));
    initialBar();
    menuBar();
    getchar();
    int ps,ans;
    while (ps=getopt()){
        if(ps==1){
                printf("请输入数据：\n");
            VertexType V[30];
            KeyType VR[100][2];
            int i=0;
            do {
                scanf("%d%s",&V[i].key,V[i].others);
            } while(V[i++].key!=-1);
            i=0;
            do {
                scanf("%d%d",&VR[i][0],&VR[i][1]);
            } while(VR[i++][0]!=-1);
            if (CreateCraph(G,V,VR)==ERROR) printf("输入数据错，无法创建\n");
            else printf("成功！\n");
        }
        if(ps==2){
            DestroyGraph(G);
            printf("销毁成功！\n");
        }
        if(ps==3){
            printf("请输入关键词：\n");
            int uu;
            scanf("%d", &uu);
            int ans=LocateVex(G,uu);
            printf("\n位序为%d\n",ans);
        }
        if(ps==4){
            printf("请输入关键词和所赋的新值（用空格间隔）：\n");
            int uu;
            VertexType vlu;
            scanf("%d%d%s", &uu,&vlu.key,vlu.others);
            int ans=PutVex(G,uu,vlu);
            if (ans==ERROR) printf("赋值失败！\n");
            else printf("赋值成功！\n");
        }
        if(ps==5){
            printf("请输入关键词：\n");
            int uu;
            scanf("%d", &uu);
            int ans=FirstAdjVex(G,uu);
            if (ans==-1) printf("不存在！\n");
            else printf("第一邻接点为%d！\n",ans);
        }
        if(ps==6){
            printf("请输入两个关键词：\n");
            int uu,vv;
            scanf("%d%d", &uu,&vv);
            int ans=NextAdjVex(G,uu,vv);
            if (ans==-1) printf("不存在！\n");
            else printf("下一邻接点为%d！\n",ans);
        }
        if(ps==7){
            printf("请输入关键词：\n");
            VertexType uu;
            scanf("%d%s", &uu.key,uu.others);
            int ans=InsertVex(G,uu);
            if (ans==ERROR) printf("插入失败！\n");
            else printf("插入成功！\n");
        }
        if(ps==8){
            printf("请输入关键词：\n");
            int uu;
            scanf("%d", &uu);
            int ans=DeleteVex(G,uu);
            if (ans==ERROR) printf("删除失败！\n");
            else printf("删除成功！\n");
        }
        if(ps==9){
            printf("请输入关键词：\n");
            int uu,vv;
            scanf("%d%d", &uu,&vv);
            int ans=InsertArc(G,uu,vv);
            if (ans==ERROR) printf("插入失败！\n");
            else printf("插入成功！\n");
        }
        if(ps==10){
            printf("请输入关键词：\n");
            int uu,vv;
            scanf("%d%d", &uu,&vv);
            int ans=DeleteArc(G,uu,vv);
            if (ans==ERROR) printf("删除失败！\n");
            else printf("删除成功！\n");
        }
        if(ps==11){
            DFSTraverse(G,visit);
        }
        if(ps==12){
            BFSTraverse(G,visit);
        }
        if(ps==13){
            printf("请输入关键词和距离：\n");
            int uu,vv;
            scanf("%d%d", &uu,&vv);
            int ans=VerticesSetLessThanK(G,uu,vv);
            if (ans==ERROR) printf("删除失败！\n");
            else {
                    printf("##");
                for (int i=0;i<G.vexnum;++i) if (anss[i]) printf("%d ",i);
            printf("\n");
            }
        }
        if(ps==14){
            printf("请输入关键词：\n");
            int uu,vv;
            scanf("%d%d", &uu,&vv);
            int ans=ShortestPathLength(G,uu,vv);
            if (ans==-1) printf("不连通！\n");
            else {
                   printf("%d\n",ans);
            }
        }
        if(ps==15){
            ConnectedComponentsNums(G);
        }
        if (ps==16){
            printf("请输入文件名（以Enter结束）：\n");
            char str[80];
            scanf("%s", str);
            SaveGraph(G, str);
            printf("保存成功！\n");
        }
        if (ps==17){
            printf("请输入文件名（以Enter结束）：\n");
            char str[80];
            scanf("%s", str);
            LoadGraph(G, str);
            printf("读取成功！\n");
        }
        if (ps==18) {
            available[totot++]=1;
        }
        if (ps==19) {
            int u;
            scanf("%d",&u);
            if (available[u]==0) continue;
        printf("请输入数据：\n");
            VertexType V[30];
            KeyType VR[100][2];
            int i=0;
            do {
                scanf("%d%s",&V[i].key,V[i].others);
            } while(V[i++].key!=-1);
            i=0;
            do {
                scanf("%d%d",&VR[i][0],&VR[i][1]);
            } while(VR[i++][0]!=-1);
            if (CreateCraph(G1[u],V,VR)==ERROR) printf("输入数据错，无法创建\n");
            else printf("成功！\n");
        }
        if (ps==20) {
            int u;
            scanf("%d",&u);
            available[u]=0;
        }
    }
    printf("\n\n欢迎下次光临哟~\n");
    return 0;
}
