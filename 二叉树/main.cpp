#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "def.h"
#include "opt.h"

using namespace std;
BiTree T;

void menuBar(){
    //system("cls");
    //list_read!
    printf("----------------- -- MENU BAR ------------------\n");
    printf("|                                              |\n");
    printf("|      FORMAT: <OPERATION> <KEY1> <KEY2>..     |\n");
    printf("|  1. CreateBiTree      2. DestroyBiTree       |\n");
    printf("|  3. ClearBiTree       4. BiTreeEmpty         |\n");
    printf("|  5. BiTreeDepth       6. LocateNode          |\n");
    printf("|  7. Assign            8. GetSibling          |\n");
    printf("|  9. InsertNode        10.DeleteNode          |\n");
    printf("|  11.PreOrderTraverse  12.InOrderTraverse     |\n");
    printf("|  13.PostOrderTraverse 14.LevelOrderTraverse  |\n");
    printf("|  15.MaxPathSum        16.LowestCommonAncestor|\n");
    printf("|  17.InvertTree        18.SaveBiTree          |\n");
    printf("|  19.LoadBiTree        20.Menu                |\n");
    printf("|                                              |\n");
    printf("|                Press 0 to exit~              |\n");
    printf("|                                              |\n");
    printf("-------------------- MENU BAR ------------------\n\n");
}

void initialBar(){
    printf("--------------- WELCOME! ---------------\n");
    printf("|                                      |\n");
    printf("|        欢迎来到二叉树的世界！！      |\n");
    printf("|                                      |\n");
    printf("----------------------------------------\n\n");
}

void putError(int state, string str = "NUMBER"){
    if (state == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
    if (state == OVERFLOW) printf(">>> ERROR: OVERFLOW! \n");
    if (state == ERROR) std::cout << ">>> ERROR: INVALID " <<str << "! \n";
    printf(">>>  \n");
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
    initialBar();
    menuBar();
    getchar();
    int ps,ans;
    while (ps=getopt()){
        if (ps==1){
            printf("请输入二叉树定义序列 以-1结束.\n");
            TElemType definition[100];
            int i=0;
            do {
                scanf("%d%s",&definition[i].key,definition[i].others);
            } while (definition[i++].key!=-1);
            ans=CreateBiTree(T,definition);
            if (ans == OK) printf("创建成功！\n");
            if (ans == ERROR) printf("创建失败！\n");
        }
        if (ps==2){
            ans=DestroyBiTree(T);
            if (ans == OK) printf("销毁成功！\n");
            if (ans == ERROR) printf("销毁失败！树为空！\n");
        }
        if (ps==3){
            ans=ClearBiTree(T);
            if (ans == OK) printf("清空成功！\n");
            if (ans == ERROR) printf("销毁失败！树为空！\n");
        }
        if (ps==4){
            ans=BiTreeDepth(T);
            if (ans==0) printf("该二叉树为空！\n");
            else printf("该二叉树非空！\n");
        }
        if (ps==5){
            ans=BiTreeDepth(T);
            printf("该二叉树之深度为：%d\n",ans);
        }
        if (ps==6){
                int e;
            printf("请输入该结点关键词：\n");
            scanf("%d", &e);
            BiTree nodePtr = LocateNode(T, e);
            printf("结点物理地址：##%u\n结点名：%s\n结点数值：%d\n",nodePtr,nodePtr->data.others,nodePtr->data.key);

        }
        if (ps==7){
            TElemType v;
            int e;
            printf("请输入该结点关键词：\n");
            scanf("%d", &e);
            printf("请输入该结点之新关键字和新名称（以Enter结束）：\n");
            scanf("%d %s", v.key, v.others);
            ans=Assign(T,e,v);
            if (ans==ERROR) printf("更新失败！未找到该结点！\n");
            if (ans==OK) printf("更新成功！");

        }
        if (ps==8){
            int e;
            printf("请输入该结点关键词：\n");
            scanf("%d", &e);
            BiTree nodePtr = GetSibling(T, e);
            printf("兄弟结点物理地址：##%u\n兄弟结点名：%s\n兄弟结点数值：%d\n",nodePtr,nodePtr->data.others,nodePtr->data.key);

        }
        if (ps==9){
            TElemType v;
            int e;
            printf("请输入结点关键词：\n");
            scanf("%d", &e);
            printf("请输入LR值：\n");
            int lr;
            scanf("%d", &lr);
            printf("请输入插入结点之关键字和名称（以Enter结束）：\n");
            scanf("%d %s", v.key, v.others);
            ans=InsertNode(T,e,lr,v);
            if (ans==ERROR) printf("更新失败！未找到该结点！\n");
            if (ans==OK) printf("更新成功！");
        }
        if (ps==10){
            int e;
            printf("请输入该结点关键词：\n");
            scanf("%d", &e);
            ans=DeleteNode(T,e);
            if (ans == OK) printf("删除成功！\n");
            if (ans == ERROR) printf("删除失败！未找到相应结点！\n");
        }
        if (ps==11){
            printf("让我们康康这个二叉树里有哪些好康的叭~ 这次我们前序遍历哦~\n");
            printf("\n## ");
            PreOrderTraverse(T,visit);
            printf("\n\n 呐 就是这些啦~\n");
        }
        if (ps==12){
             printf("让我们康康这个二叉树里有哪些好康的叭~ 这次我们中序遍历哦~\n");
            printf("\n## ");
            InOrderTraverse(T,visit);
            printf("\n\n 呐 就是这些啦~\n");
        }
        if (ps==13){
            printf("让我们康康这个二叉树里有哪些好康的叭~ 这次我们后序遍历哦~\n");
            printf("\n## ");
            PostOrderTraverse(T,visit);
            printf("\n\n 呐 就是这些啦~\n");
        }
        if (ps==14){
            printf("让我们康康这个二叉树里有哪些好康的叭~ 这次我们层序遍历哦~\n");
            printf("\n## ");
            LevelOrderTraverse(T,visit);
            printf("\n\n 呐 就是这些啦~\n");
        }
        if (ps==15){
            ans = MaxPathSum(T);
            printf("该二叉树的最大路径和（以关键数值计）：%d\n",ans);
        }
        if (ps==16){
            int e1;
            printf("请输入结点1关键词：\n");
            scanf("%d", &e1);
            int e2;
            printf("请输入结点2关键词：\n");
            scanf("%d", &e2);
            BiTree nodePtr = LowestCommonAncestor(T,e1,e2);
            printf("结点物理地址：##%u\n结点名：%s\n结点数值：%d\n",nodePtr,nodePtr->data.others,nodePtr->data.key);

        }
        if (ps==17){
            InvertTree(T);
            printf("更新成功！");
        }
        if (ps==18){
            printf("请输入文件名（以Enter结束）：\n");
            char str[80];
            scanf("%s", str);
            SaveBiTree(T, str);
            printf("保存成功！\n");
        }
        if (ps==19){
            printf("请输入文件名（以Enter结束）：\n");
            char str[80];
            scanf("%s", str);
            LoadBiTree(T, str);
            printf("读取成功！\n");
        }
        if (ps == 20){
            menuBar();
            getchar();
        }
    }
    printf("\n\n欢迎下次光临哟~\n");
    return 0;
}
