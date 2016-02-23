#include <stdlib.h>
#include <stdio.h>

typedef void* opaque;
typedef struct tnode_s 
{
    int            data;
    struct tnode_s *left;
    struct tnode_s *right;
} tnode;

#define GO_LEFT  -1
#define GO_RIGHT  1
#define GO_DONE   0 
int keyComp(tnode *existing, tnode *new)
{
    if (existing->data < new->data)
        return GO_RIGHT;
    else if (existing->data > new->data)
        return GO_LEFT;
    else
        return GO_DONE; 
}

tnode *newNode(int data)
{
    tnode *new = (tnode *)malloc(sizeof(tnode));
    new->left = new->right = NULL;
    new->data = data;
}

tnode *insertNode(tnode *node, tnode *new)
{
    if (node == NULL)
        return new;

    switch (keyComp(node, new)) {
    case GO_LEFT:
        node->left = insertNode(node->left, new);
        break;
    case GO_RIGHT:
        node->right = insertNode(node->right, new);
        break;
    default:
        break;
    }

    return node;
}

int printInorder(tnode *node)
{
    if (node == NULL)
        return 0;

    printInorder(node->left);
    printf(" %d ", node->data);
    printInorder(node->right);

    return 1;
}

int maxDepth(tnode *node)
{
    int a, b, max;

    if (node == NULL)
        return 0;

    a = maxDepth(node->left);
    b = maxDepth(node->right);
    max = (a > b) ? a : b;     

   return (max + 1);
}

int printLevelOrder(tnode *node, int level)
{
    if (node == NULL) return;

    if (level == 0) {
        printf(" %d ", node->data);
    } else {
        level--;
        printLevelOrder(node->left, level);
        printLevelOrder(node->right, level);
    }
}

int main(void)
{
    tnode *root = NULL, *node = NULL;
    int  list[] = {10, 5 , 13, 22, 11, 9, 15, 30, 29, 44};
    int i;

    for (i = 0; i < (sizeof(list)/sizeof(list[0])); i++) {
        node = newNode(list[i]);
        insertNode(root, node);
        if (root == NULL)
            root = node;
    }
    
    printf("Inorder Traversal:\n");
    printInorder(root);
    printf("\n");
    printf("Levelorder Traversal: %d\n", maxDepth(root));
    for (i = 0; i < maxDepth(root); i++) {
        printLevelOrder(root, i);
        printf("\n");
    }
}
