#include <stdio.h>
#include <stdlib.h>

/* ---------------------- 二叉树结点定义 ---------------------- */
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/* ---------------------- 栈结构：存放「结点指针」 ----------------------
 * 因为要暂存的是树中结点的「地址」，所以数组元素的类型是 TreeNode*，
 * 而数组名本身又要退化成指针，因此 arr 的类型是「指针的指针」TreeNode**。
 */
typedef struct Stack {
    TreeNode **arr;   /* 动态数组：每个格子存放一个 TreeNode* */
    int top;          /* 栈顶下标；top == -1 表示空栈 */
    int capacity;     /* 栈的容量上限 */
} Stack;

/* 创建栈：先分配 Stack 结构体本身，再分配它内部的数组 */
Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));                 /* 结构体本体：一个 top + 一个 capacity + 一个指针 */
    stack->arr = malloc(sizeof(TreeNode *) * capacity);    /* 底层数组：capacity 个 TreeNode* 大小的空间 */
    stack->top = -1;          /* 空栈的标志：栈顶下标为 -1 */
    stack->capacity = capacity;
    return stack;
}

/* 判断栈是否为空：top 仍停在 -1 就说明一个元素都没进来 */
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

/* 入栈：把 node 压到栈顶 */
void push(Stack *stack, TreeNode *node) {
    if (stack->top == stack->capacity - 1) {   /* 栈满保护：越界了就直接放弃这次入栈 */
        return;
    }
    stack->arr[++stack->top] = node;           /* 先让 top 自增，再把 node 放到新的栈顶位置 */
}

/* 出栈：返回栈顶元素，并让 top 下移一格 */
TreeNode *pop(Stack *stack) {
    if (isEmpty(stack)) {      /* 空栈没有东西可弹，返回 NULL 让调用方判断 */
        return NULL;
    }
    return stack->arr[stack->top--];   /* 先取出栈顶元素，再让 top 减 1（先返回后位移） */
}

/* ============================================================
 * 前序遍历（非递归）：根 -> 左 -> 右
 *
 * 思路：把「递归时函数调用栈自动保存的事情」改为手动用我们自己的栈来做。
 *   1. 先把根结点入栈；
 *   2. 循环：弹出栈顶结点并访问它（这就是"根"）；
 *      然后先把「右孩子」入栈，再把「左孩子」入栈；
 *   3. 由于栈是「后进先出」，后压进去的左孩子会先被弹出，
 *      所以访问顺序自然是 根 -> 左 -> 右，正好是前序。
 * ============================================================ */
void preorderTraversal(TreeNode *root) {
    if (root == NULL) {                 /* 空树：无事可做 */
        printf("(空树)\n");
        return;
    }

    Stack *stack = createStack(100);    /* 建一个容量为 100 的栈（够用即可） */

    push(stack, root);                  /* 起点：根结点入栈 */

    while (!isEmpty(stack)) {           /* 栈不空，就还有结点没访问 */
        TreeNode *cur = pop(stack);     /* 弹出当前结点 */
        printf("%d ", cur->val);        /* 访问它（前序：遇到就输出） */

        /* 注意顺序不可颠倒：先压右，再压左。
         * 这样左孩子位于栈顶，下一轮会先被弹出，满足"先左后右"。 */
        if (cur->right != NULL) {
            push(stack, cur->right);
        }
        if (cur->left != NULL) {
            push(stack, cur->left);
        }
    }

    free(stack->arr);   /* 释放底层数组 */
    free(stack);        /* 释放栈结构体本身，避免内存泄漏 */
    printf("\n");
}

/* ---------------------- 辅助函数：创建一个新结点 ---------------------- */
TreeNode *newNode(int val) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* ============================= 主函数 ============================= */
int main(void) {
    /* 手工搭一棵测试树：
     *          1
     *        /   \
     *       2     3
     *      / \     \
     *     4   5     6
     * 前序结果应为：1 2 4 5 3 6
     */
    TreeNode *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("前序遍历（非递归）：");
    preorderTraversal(root);

    /* 再测一棵只有单链的树：7 -> 8 -> 9（全在左子树上）
     * 前序结果应为：7 8 9
     */
    TreeNode *chain = newNode(7);
    chain->left = newNode(8);
    chain->left->left = newNode(9);

    printf("前序遍历（非递归）：");
    preorderTraversal(chain);

    printf("前序遍历（非递归）：");
    preorderTraversal(NULL);    /* 空树测试 */

    return 0;
}
