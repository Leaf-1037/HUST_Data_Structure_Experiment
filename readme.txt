upd:

二叉树先序遍历非递归版本已改动。头歌上未写非递归版本。

代码如下：

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

四则EXE文件在各自的文件夹下。

感谢老师的批阅！