#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct{  //˳���˳��ṹ���Ķ���
	      ElemType * elem;
	      int length;
	      int listsize;
         }SqList;

typedef struct{  //���Ա�Ĺ������
     struct { char name[30];
     		  SqList L;
      } elem[10];
      int length;
      int listsize;
 }LISTS;

#endif // DEF_H_INCLUDED
