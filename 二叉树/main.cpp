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
    printf("|        ��ӭ���������������磡��      |\n");
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
    printf("\n�������������\n");
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
            printf("������������������� ��-1����.\n");
            TElemType definition[100];
            int i=0;
            do {
                scanf("%d%s",&definition[i].key,definition[i].others);
            } while (definition[i++].key!=-1);
            ans=CreateBiTree(T,definition);
            if (ans == OK) printf("�����ɹ���\n");
            if (ans == ERROR) printf("����ʧ�ܣ�\n");
        }
        if (ps==2){
            ans=DestroyBiTree(T);
            if (ans == OK) printf("���ٳɹ���\n");
            if (ans == ERROR) printf("����ʧ�ܣ���Ϊ�գ�\n");
        }
        if (ps==3){
            ans=ClearBiTree(T);
            if (ans == OK) printf("��ճɹ���\n");
            if (ans == ERROR) printf("����ʧ�ܣ���Ϊ�գ�\n");
        }
        if (ps==4){
            ans=BiTreeDepth(T);
            if (ans==0) printf("�ö�����Ϊ�գ�\n");
            else printf("�ö������ǿգ�\n");
        }
        if (ps==5){
            ans=BiTreeDepth(T);
            printf("�ö�����֮���Ϊ��%d\n",ans);
        }
        if (ps==6){
                int e;
            printf("������ý��ؼ��ʣ�\n");
            scanf("%d", &e);
            BiTree nodePtr = LocateNode(T, e);
            printf("��������ַ��##%u\n�������%s\n�����ֵ��%d\n",nodePtr,nodePtr->data.others,nodePtr->data.key);

        }
        if (ps==7){
            TElemType v;
            int e;
            printf("������ý��ؼ��ʣ�\n");
            scanf("%d", &e);
            printf("������ý��֮�¹ؼ��ֺ������ƣ���Enter��������\n");
            scanf("%d %s", v.key, v.others);
            ans=Assign(T,e,v);
            if (ans==ERROR) printf("����ʧ�ܣ�δ�ҵ��ý�㣡\n");
            if (ans==OK) printf("���³ɹ���");

        }
        if (ps==8){
            int e;
            printf("������ý��ؼ��ʣ�\n");
            scanf("%d", &e);
            BiTree nodePtr = GetSibling(T, e);
            printf("�ֵܽ�������ַ��##%u\n�ֵܽ������%s\n�ֵܽ����ֵ��%d\n",nodePtr,nodePtr->data.others,nodePtr->data.key);

        }
        if (ps==9){
            TElemType v;
            int e;
            printf("��������ؼ��ʣ�\n");
            scanf("%d", &e);
            printf("������LRֵ��\n");
            int lr;
            scanf("%d", &lr);
            printf("�����������֮�ؼ��ֺ����ƣ���Enter��������\n");
            scanf("%d %s", v.key, v.others);
            ans=InsertNode(T,e,lr,v);
            if (ans==ERROR) printf("����ʧ�ܣ�δ�ҵ��ý�㣡\n");
            if (ans==OK) printf("���³ɹ���");
        }
        if (ps==10){
            int e;
            printf("������ý��ؼ��ʣ�\n");
            scanf("%d", &e);
            ans=DeleteNode(T,e);
            if (ans == OK) printf("ɾ���ɹ���\n");
            if (ans == ERROR) printf("ɾ��ʧ�ܣ�δ�ҵ���Ӧ��㣡\n");
        }
        if (ps==11){
            printf("�����ǿ������������������Щ�ÿ��İ�~ �������ǰ�����Ŷ~\n");
            printf("\n## ");
            PreOrderTraverse(T,visit);
            printf("\n\n �� ������Щ��~\n");
        }
        if (ps==12){
             printf("�����ǿ������������������Щ�ÿ��İ�~ ��������������Ŷ~\n");
            printf("\n## ");
            InOrderTraverse(T,visit);
            printf("\n\n �� ������Щ��~\n");
        }
        if (ps==13){
            printf("�����ǿ������������������Щ�ÿ��İ�~ ������Ǻ������Ŷ~\n");
            printf("\n## ");
            PostOrderTraverse(T,visit);
            printf("\n\n �� ������Щ��~\n");
        }
        if (ps==14){
            printf("�����ǿ������������������Щ�ÿ��İ�~ ������ǲ������Ŷ~\n");
            printf("\n## ");
            LevelOrderTraverse(T,visit);
            printf("\n\n �� ������Щ��~\n");
        }
        if (ps==15){
            ans = MaxPathSum(T);
            printf("�ö����������·���ͣ��Թؼ���ֵ�ƣ���%d\n",ans);
        }
        if (ps==16){
            int e1;
            printf("��������1�ؼ��ʣ�\n");
            scanf("%d", &e1);
            int e2;
            printf("��������2�ؼ��ʣ�\n");
            scanf("%d", &e2);
            BiTree nodePtr = LowestCommonAncestor(T,e1,e2);
            printf("��������ַ��##%u\n�������%s\n�����ֵ��%d\n",nodePtr,nodePtr->data.others,nodePtr->data.key);

        }
        if (ps==17){
            InvertTree(T);
            printf("���³ɹ���");
        }
        if (ps==18){
            printf("�������ļ�������Enter��������\n");
            char str[80];
            scanf("%s", str);
            SaveBiTree(T, str);
            printf("����ɹ���\n");
        }
        if (ps==19){
            printf("�������ļ�������Enter��������\n");
            char str[80];
            scanf("%s", str);
            LoadBiTree(T, str);
            printf("��ȡ�ɹ���\n");
        }
        if (ps == 20){
            menuBar();
            getchar();
        }
    }
    printf("\n\n��ӭ�´ι���Ӵ~\n");
    return 0;
}
