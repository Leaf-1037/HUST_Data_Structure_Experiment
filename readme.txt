upd:

��������������ǵݹ�汾�ѸĶ���ͷ����δд�ǵݹ�汾��

�������£�

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    // �������ﲹ����룬��ɱ�������
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

����EXE�ļ��ڸ��Ե��ļ����¡�

��л��ʦ�����ģ�