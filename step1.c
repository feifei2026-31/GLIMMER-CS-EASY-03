#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE_SIZE 100
/*
 * 顺序存储二叉树结点
 * - data：结点数据
 * - used：当前位置是否有结点
 */
typedef struct {
    int data;
    bool used;
} SeqTreeNode;

/*
 * 顺序存储二叉树
 * - nodes：结点数组
 * - size：数组最大容量
 */
typedef struct {
    SeqTreeNode nodes[MAX_TREE_SIZE];
    int size;
} SeqBiTree;

/*
 * 初始化二叉树
 * 容量置为 MAX_TREE_SIZE，所有位置的 used 置为 false（空），data 置为 0。
 * 注意：数组下标 0 位置不使用，根结点固定放在下标 1 处。
 */
void init_tree(SeqBiTree *tree) {
    if (tree == NULL) {
        return;
    }
    tree->size = MAX_TREE_SIZE;
    for (int i = 0; i < tree->size; i++) {
        tree->nodes[i].data = 0;
        tree->nodes[i].used = false;
    }
}

/*
 * 创建根结点
 * 根结点固定在下标 1 处。若树为空（有效）或该位置已被占用则返回 false。
 */
bool set_root(SeqBiTree *tree, int value) {
    if (tree == NULL) {
        return false;
    }
    if (1 >= tree->size) {          /* 容量不足，理论上不会发生 */
        return false;
    }
    if (tree->nodes[1].used) {      /* 根结点已存在，不再覆盖 */
        return false;
    }
    tree->nodes[1].data = value;
    tree->nodes[1].used = true;
    return true;
}

/*
 * 创建左孩子
 * parent_node 为父结点下标，左孩子下标 = 2 * parent_node。
 * 校验：父结点必须存在；孩子下标不能越界；孩子位置必须为空。
 */
bool set_left_child(SeqBiTree *tree, int parent_node, int value) {
    if (tree == NULL) {
        return false;
    }
    if (parent_node < 1 || parent_node >= tree->size) {   /* 父结点下标非法 */
        return false;
    }
    if (!tree->nodes[parent_node].used) {                 /* 父结点不存在 */
        return false;
    }
    int pos = 2 * parent_node;                            /* 左孩子下标 */
    if (pos >= tree->size) {                              /* 越界 */
        return false;
    }
    if (tree->nodes[pos].used) {                          /* 该位置已有结点 */
        return false;
    }
    tree->nodes[pos].data = value;
    tree->nodes[pos].used = true;
    return true;
}

/*
 * 创建右孩子
 * parent_node 为父结点下标，右孩子下标 = 2 * parent_node + 1。
 * 校验规则与左孩子一致。
 */
bool set_right_child(SeqBiTree *tree, int parent_node, int value) {
    if (tree == NULL) {
        return false;
    }
    if (parent_node < 1 || parent_node >= tree->size) {
        return false;
    }
    if (!tree->nodes[parent_node].used) {
        return false;
    }
    int pos = 2 * parent_node + 1;                        /* 右孩子下标 */
    if (pos >= tree->size) {
        return false;
    }
    if (tree->nodes[pos].used) {
        return false;
    }
    tree->nodes[pos].data = value;
    tree->nodes[pos].used = true;
    return true;
}

/*
 * 层序遍历
 * 按数组下标 1,2,3,... 顺序打印：used 为 true 打印 data，否则打印 -1。
 * 第 k 层的下标范围是 [2^(k-1), 2^k - 1]，所以只要在下标 2^k - 1 处换行，
 * 就能做到"每打印完一层换行"，且每行恰好是一个完整的层。
 */
void level_order(SeqBiTree *tree) {
    if (tree == NULL) {
        return;
    }

    /* 1. 找到最后一个有效结点的下标 last，据此得到树的层数 */
    int last = 0;
    for (int i = 1; i < tree->size; i++) {
        if (tree->nodes[i].used) {
            last = i;
        }
    }
    if (last == 0) {                 /* 空树，无输出 */
        return;
    }

    /* 2. 层数 depth：满足 2^depth - 1 >= last 的最小值；该层结束下标即 2^depth - 1 */
    int depth = 0;
    while ((1 << depth) - 1 < last) {
        depth++;
    }
    int total = (1 << depth) - 1;    /* 打印到本层末尾，保证每行都是完整的一层 */

    /* 3. 沿数组下标顺序打印，在每层末尾换行 */
    int level_end = 1;               /* 当前层最后一个结点下标：第 k 层为 2^k - 1 */
    for (int i = 1; i <= total; i++) {
        if (tree->nodes[i].used) {
            printf("%d", tree->nodes[i].data);
        } else {
            printf("-1");
        }

        if (i == level_end) {        /* 本层打印完毕 */
            printf("\n");
            level_end = level_end * 2 + 1;   /* 进入下一层 */
        } else {
            printf(" ");                     /* 同层元素用空格分隔 */
        }
    }
}

int main(void)
{
    SeqBiTree tree3;
    init_tree(&tree3);
    set_root(&tree3, 1);
    set_left_child(&tree3, 1, 2);
    set_right_child(&tree3, 1, 3);
    set_left_child(&tree3, 2,4);
    set_right_child(&tree3, 2, 5);
    set_left_child(&tree3, 3, 6);
    set_right_child(&tree3, 3, 7);
    level_order(&tree3);
    return 0;
}