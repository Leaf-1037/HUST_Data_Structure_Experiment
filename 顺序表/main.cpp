#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "def.h"
#include "opt.h"

LISTS Lists;

void menuBar(){
    //system("cls");
    //list_read!
    printf("--------------- MENU BAR ---------------\n");
    printf("|                                      |\n");
    printf("|  FORMAT: <OPERATION> <KEY1> <KEY2>.. |\n");
    printf("|  1. LISTINIT L     2. LISTDESTROY L  |\n");
    printf("|  3. LISTCLR L      4. LISTEMPTY L    |\n");
    printf("|  5. LISTLEN L      6. GETELEM L I    |\n");
    printf("|  7. LOCATEELEM L E 8. ELEMPRIOR L E  |\n");
    printf("|  9. ELEMNEXT L E   10.LISTINS L I E  |\n");
    printf("|  11.LISTDEL L I    12.SHOWLIST L     |\n");
    printf("|  13.MENU           14.MAXSUBARRAY L  |\n");
    printf("|  15.SUBARRAYNUM L  16.LISTSORT L     |\n");
    printf("|  17.SAVELIST L F   18.LOADLIST L F   |\n");
    printf("|  19.EXIT                             |\n");
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

int main()
{
    initialBar();
    menuBar();
    char opt[80], opt1[80], opt2[80], opt3[80], state;
    printf(">>> ");
    scanf("%s", opt);
    while(strcmp(opt, "EXIT") != 0){
        if (strcmp(opt, "LISTINIT") == 0){
            scanf("%s", opt1);
            state = AddList(Lists, opt1);
            if (state == ERROR) printf(">>> ERROR: INVALID LIST! \n");
        }
        else if (strcmp(opt, "LISTDESTROY") == 0){
            scanf("%s", opt1);
            state = RemoveList(Lists, opt1);
            if (state == ERROR) printf(">>> ERROR: LISTNAME NOT FOUND! \n");
        }
        else if (strcmp(opt, "LISTCLR") == 0){
            scanf("%s", opt1);
            state = LocateList(Lists, opt1);
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = ClearList(Lists.elem[p].L);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
        }
        else if (strcmp(opt, "LISTEMPTY") == 0){
            scanf("%s", opt1);
            state = LocateList(Lists, opt1);
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = ListEmpty(Lists.elem[p].L);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            else if (q == TRUE) printf(">>> TRUE! \n");
            else if (q == FALSE) printf(">>> FALSE! \n");
        }
        else if (strcmp(opt, "LISTLEN") == 0){
            scanf("%s", opt1);
            state = LocateList(Lists, opt1);
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = ListLength(Lists.elem[p].L);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            else printf(">>> %s LEN is %d \n", Lists.elem[p].name, q);
        }
        else if (strcmp(opt, "GETELEM") == 0){
            scanf("%s", opt1);
            scanf("%s", opt2);
            state = LocateList(Lists, opt1);
            int tmp = atoi(opt2);
            if (tmp == 0) {
                printf(">>> ERROR: INVALID NUMBER! \n");
                goto PPP;
            }
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int ee;
            int q = GetElem(Lists.elem[p].L, tmp, ee);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            if (q == ERROR) printf(">>> ERROR: INVALID NUMBER! \n");
            else printf(">>> Elem is %d \n", ee);
        }
        else if (strcmp(opt, "LOCATEELEM") == 0){
            scanf("%s", opt1);
            scanf("%s", opt2);
            state = LocateList(Lists, opt1);
            int tmp = atoi(opt2);
            if (tmp == 0) {
                printf(">>> ERROR: INVALID NUMBER! \n");
                goto PPP;
            }
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = LocateElem(Lists.elem[p].L, tmp);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            if (q == 0) printf(">>> NOT FOUND! \n");
            else if (q > 0) printf(">>> Elem is #%d \n", q);
        }
        else if (strcmp(opt, "ELEMPRIOR") == 0){
            scanf("%s", opt1);
            scanf("%s", opt2);
            state = LocateList(Lists, opt1);
            int tmp = atoi(opt2);
            if (tmp == 0) {
                printf(">>> ERROR: INVALID NUMBER! \n");
                goto PPP;
            }
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int ee;
            int q = PriorElem(Lists.elem[p].L, tmp, ee);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            if (q == ERROR) printf(">>> ERROR: INVALID NUMBER! \n");
            else if (q > 0) printf(">>> Elem is %d \n", ee);
        }
        else if (strcmp(opt, "ELEMNEXT") == 0){
            scanf("%s", opt1);
            scanf("%s", opt2);
            state = LocateList(Lists, opt1);
            int tmp = atoi(opt2);
            if (tmp == 0) {
                printf(">>> ERROR: INVALID NUMBER! \n");
                goto PPP;
            }
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int ee;
            int q = NextElem(Lists.elem[p].L, tmp, ee);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            if (q == ERROR) printf(">>> ERROR: INVALID NUMBER! \n");
            else if (q > 0) printf(">>> Elem is %d \n", ee);
        }
        else if (strcmp(opt, "LISTINS") == 0){
            scanf("%s", opt1);
            scanf("%s", opt2);
            scanf("%s", opt3);
            state = LocateList(Lists, opt1);
            int tmp = atoi(opt2), tmp2 = atoi(opt3);
            if (tmp == 0 || tmp2 == 0) {
                printf(">>> ERROR: INVALID NUMBER! \n");
                goto PPP;
            }
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = ListInsert(Lists.elem[p].L, tmp, tmp2);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            if (q == ERROR) printf(">>> ERROR: INVALID NUMBER! \n");
        }
        else if (strcmp(opt, "LISTDEL") == 0){
            scanf("%s", opt1);
            scanf("%s", opt2);
            state = LocateList(Lists, opt1);
            int tmp = atoi(opt2);
            if (tmp == 0) {
                printf(">>> ERROR: INVALID NUMBER! \n");
                goto PPP;
            }
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int ee;
            int q = ListDelete(Lists.elem[p].L, tmp, ee);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            if (q == ERROR) printf(">>> ERROR: INVALID NUMBER! \n");
        }
        else if (strcmp(opt, "SHOWLIST") == 0){
            scanf("%s", opt1);
            state = LocateList(Lists, opt1);
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = ListTraverse(Lists.elem[p].L);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
        }
        else if (strcmp(opt, "MENU") == 0){
            menuBar();
        }
        else if (strcmp(opt, "MAXSUBARRAY") == 0){
            scanf("%s", opt1);
            state = LocateList(Lists, opt1);
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = MaxSubArray(Lists.elem[p].L);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            else printf(">>> MAX = %d \n", q);
        }
        else if (strcmp(opt, "SUBARRAYNUM") == 0){
            scanf("%s", opt1);
            scanf("%s", opt2);
            state = LocateList(Lists, opt1);
            int tmp = atoi(opt2);
            if (tmp == 0) {
                printf(">>> ERROR: INVALID NUMBER! \n");
                goto PPP;
            }
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = SubArrayNum(Lists.elem[p].L, tmp);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            else printf(">>> COUNT = %d \n", q);
        }
        else if (strcmp(opt, "LISTSORT") == 0){
            scanf("%s", opt1);
            state = LocateList(Lists, opt1);
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = sortList(Lists.elem[p].L);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            else printf(">>> SORT SUCCEEDED! \n");
        }
        else if (strcmp(opt, "SAVELIST") == 0){
            scanf("%s", opt1);
            scanf("%s", opt2);
            state = LocateList(Lists, opt1);
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = SaveList(Lists.elem[p].L, opt2);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            else printf(">>> SAVED! \n");
        }
        else if (strcmp(opt, "LOADLIST") == 0){
            scanf("%s", opt1);
            scanf("%s", opt2);
            state = LocateList(Lists, opt1);
            if (state == 0) {
                printf(">>> ERROR: LISTNAME NOT FOUND! \n");
                goto PPP;
            }
            int p = state - 1;
            int q = LoadList(Lists.elem[p].L, opt2);
            if (q == INFEASIBLE) printf(">>> ERROR: INFEASIBLE! \n");
            else printf(">>> READ! \n");
        }

        else printf(">>> INVALID INPUT_OPERATION! \n");
    PPP:
        memset(opt, 0, sizeof opt);
        printf(">>> ");
        scanf("%s", opt);
    }
    printf("-------- THANK YOU FOR USING! --------");
    return 0;
}
