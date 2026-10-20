#include<stdio.h>
#include<stdlib.h>
typedef struct rbTree
{
    struct rbTree * left;
    struct rbTree * right;
    int val;
}rbTree;

rbTree* initNode(int val)
{
    rbTree* node = (rbTree*)malloc(sizeof(rbTree));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}
rbTree* buildTree(rbTree* T)
{
    int a;
    printf("请输入数字:");
    scanf("%d", &a);
    if(a==-1)
    {
        T=NULL;
        return T;
    }else{
        T=initNode(a);
        T->left = buildTree(T->left);
        T->right = buildTree(T->right);
    }
    return T;
}
void preorder(rbTree* T)
{
    if(T == NULL)
    return;
    else{
        printf("%d", T->val);
        preorder(T->left);
        preorder(T->right);
    }
}
void miorder(rbTree* T)
{
    if(T == NULL)
    return;
    else{
        miorder(T->left);
        printf("%d",T->val);
        miorder(T->right);
    }
}
void backorder(rbTree* T)
{
    if(T == NULL)
    return;
    else{
        backorder(T->left);
        backorder(T->right);
        printf("%d", T->val);
    }
}
int treeTall(rbTree* T)
{
    if (T==NULL)
    return 0;
    else{
        int leftheight=treeTall(T->left);
        int rightheight=treeTall(T->right);
        int height=leftheight>rightheight?leftheight:rightheight;
        return height + 1;
    }
}
void test()
{
    rbTree* T=NULL;
    T=buildTree(T);
    printf("\n先序遍历:\n");
    preorder(T);
    printf("\n中序遍历:\n");
    miorder(T);
    printf("\n后序遍历\n");
    backorder(T);
    printf("\n树的高度是:%d", treeTall(T));
    printf("\n");
}
int main()
{
    test();
    return 0;
}