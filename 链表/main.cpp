#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "def.h"
#include "opt.h"
using namespace std;

LISTS Lists;

void menuBar(){
    //system("cls");
    //list_read!
    printf("--------------- MENU BAR ---------------\n");
    printf("|                                      |\n");
    //printf("|  FORMAT: <OPERATION> <KEY1> <KEY2>.. |\n");
    printf("|  1. LISTINIT L     2. LISTDESTROY L  |\n");
    printf("|  3. LISTCLR L      4. LISTEMPTY L    |\n");
    printf("|  5. LISTLEN L      6. GETELEM L I    |\n");
    printf("|  7. LOCATEELEM L E 8. ELEMPRIOR L E  |\n");
    printf("|  9. ELEMNEXT L E   10.LISTINS L I E  |\n");
    printf("|  11.LISTDEL L I    12.SHOWLIST L     |\n");
    printf("|  13.MENU           14.REVERSELIST L  |\n");
    printf("|  15.REMOVEND L I   16.SORTLIST L     |\n");
    printf("|  17.SAVELIST L F   18.LOADLIST L F   |\n");
    printf("|  19.LOCATELIST L   20.EXIT           |\n");
    printf("|                                      |\n");
    printf("--------------- MENU BAR ---------------\n\n");
}

void initialBar(){
    printf("--------------- WELCOME! ---------------\n");
    printf("|                                      |\n");
    printf("|    EXPERIMENT OF LINEAR SEQUENCE.    |\n");
    printf("|                                      |\n");
    printf("----------------------------------------\n\n");
}

void putError(int state, string str = "NUMBER"){
    if (state == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
    if (state == OVERFLOW) printf(">>> ERROR: OVERFLOW! \n");
    if (state == ERROR) std::cout << ">>> ERROR: INVALID " <<str << "! \n";
    printf(">>>  \n");
}

string OptTable[] = {"LISTINIT","LISTDESTROY","LISTCLR","LISTEMPTY","LISTLEN","GETELEM",
    "LOCATEELEM","ELEMPRIOR","ELEMNEXT","LISTINS","LISTDEL","SHOWLIST","MENU","REVERSELIST",
    "REMOVEND","SORTLIST","SAVELIST","LOADLIST","LOCATELIST","EXIT"};

int get_opt(){
    while (1){
        printf(">>> INPUT OPERATOR:\n");
        printf(">>> ");
        string str;
        getline(cin,str);
        stringstream ss(str);
        ss >> str;
        for (int i = 0; i < 20; ++i)
        if (str.compare(OptTable[i]) == 0){
            return i + 1;
        }
        putError(ERROR,"OPERATOR");
    }
}

int get_num(string str = ""){
    printf(">>> INPUT NUMBER:\n");
    printf(">>> ");
    string p;
    getline(cin,p);
    stringstream ss(p);
    int q;
    while(!(ss >> q)){
        putError(ERROR);
        printf(">>> ");
        getline(cin,p);
        ss.clear();
        ss.str("");
        ss << p;
    }
    //printf("#%d#", q);
    return q;
}

string get_str(){
    printf(">>> INPUT NAME(OR FILENAME):\n");
    printf(">>> ");
    string p;
    getline(cin,p);
    stringstream ss(p);
    p = "";
    ss >> p;
    return p;
}

int main()
{
    Lists = (LISTS)malloc(sizeof(LLNode));
    Lists->next = NULL;
    initialBar();
    menuBar();
    int opt,opt1,opt2,state;
    LinkList tmp;
    string strr,strr1;
    while((opt=get_opt())!=20){
        if (opt == 1){
            strr = get_str();
            state=AddList(Lists,strr.c_str());
            putError(state,"LISTNAME");
        }
        if (opt == 2){
            strr = get_str();
            state=RemoveList(Lists,strr.c_str());
            putError(state,"LISTNAME");
        }
        if (opt == 3){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            state=ClearList(tmp);
            putError(state);
        }
        if (opt == 4){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            state=ListEmpty(tmp);
            if (state == TRUE) printf(">>> It's empty!\n>>>\n");
            else if (state == FALSE) printf(">>> It's not empty!\n>>>\n");
            else putError(state);
        }
        if (opt == 5){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            state=ListLength(tmp);
            printf(">>> Its length is %d\n>>>\n", state);
        }
        if (opt == 6){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            opt1=get_num();
            state=GetElem(tmp,opt1,opt2);
            if (state==OK) printf(">>> No.%d Element is %d.\n>>>\n",opt1,opt2);
            else putError(state);
        }
        if (opt == 7){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            opt1=get_num();
            state=LocateElem(tmp,opt1);
            if (state>0) printf(">>> %d Element is No.%d.\n>>>\n",opt1,state);
            putError(state);
        }
        if (opt == 8){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            opt1=get_num();
            state=PriorElem(tmp,opt1,opt2);
            if (state==OK) printf(">>> Prior Element is %d\n",opt2);
            putError(state);
        }
        if (opt == 9){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            opt1=get_num();
            state=NextElem(tmp,opt1,opt2);
            if (state==OK) printf(">>> Next Element is %d\n",opt2);
            putError(state);
        }
        if (opt == 10){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            opt1=get_num();
            opt2=get_num();
            state=ListInsert(tmp,opt1,opt2);
            if (state==OK) printf(">>> Insert Successfully!\n");
            putError(state);
        }
        if (opt == 11){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            opt1=get_num();
            //opt2=get_num();
            state=ListDelete(tmp,opt1,opt2);
            if (state==OK) printf(">>> Delete Successfully!\n>>> It's %d!\n",opt2);
            putError(state);
        }
        if (opt == 12){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            //opt1=get_num();
            //opt2=get_num();
            state=ListTraverse(tmp);
            //if (state==OK) printf(">>> Delete Successfully!\n>>> It's %d!\n",opt2);
            putError(state);
        }
        if (opt == 13){
            menuBar();
        }
        if (opt == 14){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            state=reverseList(tmp);
            putError(state);
        }
        if (opt == 15){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            opt1=get_num();
            //opt2=get_num();
            state=RemoveNthFromEnd(tmp,opt1);
            //if (state==OK) printf(">>> Delete Successfully!\n>>> It's %d!\n",opt2);
            putError(state);
        }
        if (opt == 16){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            putError(sortList(tmp));
        }
        if (opt == 17){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            strr1 = get_str();
            state=SaveList(tmp,strr1.c_str());
            putError(state);
        }
        if (opt == 18){
            strr = get_str();
            tmp=findList(Lists,strr.c_str());
            if (tmp==NULL){
                putError(ERROR,"LISTNAME");
                continue;
            }
            strr1 = get_str();
            state=LoadList(tmp,strr1.c_str());
            putError(state);
        }
        if (opt == 19){
            strr = get_str();
            //tmp=findList(Lists,strr.c_str());
            state=LocateList(Lists,strr.c_str());
            if (state>0) printf(">>> It's located in %d\n", state);
            putError(state);
        }
    }
    printf("Thank you for using!");
    return 0;
}
