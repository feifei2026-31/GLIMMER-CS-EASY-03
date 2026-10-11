#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;                       // 节点存储的数据
    struct TreeNode *left;          // 左子树指针
    struct TreeNode *right;         // 右子树指针
} TreeNode;

TreeNode* create_node(int value) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {             /* 申请失败，不能继续往下写 */
        return NULL;
    }
    node->data = value;             /* 1. 存入数据 */
    node->left = NULL;              /* 2. 左孩子先置空 */
    node->right = NULL;             /* 3. 右孩子先置空 */
    return node;                    /* 4. 把新节点的地址交出去 */
}

void preorder(TreeNode *root) {
    if (root == NULL) {             //前序遍历
        return;
    }
    printf("%d ", root->data);    
    preorder(root->left);          
    preorder(root->right);         
}


void inorder(TreeNode *root) {       //中序遍历
    if (root == NULL) {
        return;
    }
    inorder(root->left);          
    printf("%d ", root->data);     
    inorder(root->right);           
}


void postorder(TreeNode *root) {
    if (root == NULL) {               //后序遍历
        return;
    }
    postorder(root->left);        
    postorder(root->right);         
    printf("%d ", root->data);      
}

int depth(TreeNode *root, int current_depth, int max_depth) {
    if (root == NULL) {                     
        return max_depth;
    }

    if (current_depth > max_depth) {        
        max_depth = current_depth;
    }

    int left  = depth(root->left,  current_depth + 1, max_depth);
    int right = depth(root->right, current_depth + 1, max_depth);

    return (left > right) ? left : right;
}

int main(void) {        //创造结点
    
    TreeNode *n1 = create_node(1);
    TreeNode *n2 = create_node(2);
    TreeNode *n3 = create_node(3);
    TreeNode *n4 = create_node(4);
    TreeNode *n5 = create_node(5);
    TreeNode *n6 = create_node(6);
    TreeNode *n7 = create_node(7);

    if (n1 == NULL || n2 == NULL || n3 == NULL || n4 == NULL ||
        n5 == NULL || n6 == NULL || n7 == NULL) {
        printf("内存申请失败\n");
        free(n1); free(n2); free(n3); free(n4);   /* free(NULL) 是安全的 */
        free(n5); free(n6); free(n7);
        return 1;
    }

    //连接
    n1->left  = n2;    n1->right = n3;     
    n2->left  = n4;    n2->right = n5;     
    n3->left  = n6;    n3->right = n7;      

   
    printf("\n三种递归遍历:\n");
    printf("前序（根→左→右）：");
    preorder(n1);
    printf("\n");

    printf("中序（左→根→右）：");
    inorder(n1);
    printf("\n");

    printf("后序（左→右→根）：");
    postorder(n1);
    printf("\n");

    printf("\n深度统计:\n");
    printf("  整棵树（以 1 为根）：%d 层\n", depth(n1, 1, 0));
    printf("  以 2 为根的左子树  :%d 层\n", depth(n2, 1, 0));
    printf("  以 3 为根的右子树 :%d 层\n", depth(n3, 1, 0));
    printf("  单结点子树(4 号） :%d 层\n", depth(n4, 1, 0));
    printf("  空树(NULL)       :%d 层\n", depth(NULL, 1, 0));

    free(n1); free(n2); free(n3); free(n4);
    free(n5); free(n6); free(n7);

    return 0;
}
