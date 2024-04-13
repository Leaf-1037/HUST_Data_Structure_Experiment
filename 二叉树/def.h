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
typedef int KeyType;
typedef struct {
    KeyType  key;
    char others[20];
} TElemType; //������������Ͷ���


typedef struct BiTNode{  //����������Ķ���
    TElemType  data;
    struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

#endif // DEF_H_INCLUDED
