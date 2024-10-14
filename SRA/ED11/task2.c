/*
*This program give to count of the sub tree of a tree
*Created by: Rushabh Goswami (164992)
*/

#include <stdio.h>
#include <stdlib.h>

/* Structure for a binary tree node */
struct Node {
    int left;   /* left child */
    int right;  /* right child */
};

/* Function to count the number of nodes in the subtree rooted at 'node' */
int countSubtreeNodes(int node, struct Node tree[], int subtree_count[]) {
    /* If the node is 0, return 0 as it's not a valid node */
    if (node == 0) {
        return 0;
    }
    
    /* Recursively count nodes in left and right subtrees */
    int left_count = countSubtreeNodes(tree[node].left, tree, subtree_count);
    int right_count = countSubtreeNodes(tree[node].right, tree, subtree_count);
    
    /* The total number of nodes in the current subtree */
    subtree_count[node] = 1 + left_count + right_count;
    
    return subtree_count[node];
}

int main() {
    int n;
    
    /* Read the number of nodes in the tree */
    printf("\nEnter the number of nodes in the tree: ");
    scanf("%d", &n);
    
    /* Allocate memory for the binary tree and subtree counts */
    struct Node tree[n + 1];
    int subtree_count[n + 1];
    
    /* Read the tree structure */
    printf("Enter the node data (two integers space seperated.) \n");
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &tree[i].left, &tree[i].right);
    }
    
    /* Initialize the subtree count array */
    for (int i = 1; i <= n; i++) {
        subtree_count[i] = 0;
    }
    
    /* Start counting from the root node (node 1) */
    countSubtreeNodes(1, tree, subtree_count);
    
    /* Print the result: the number of nodes in the subtree rooted at each node */
    printf("=====Here is the result=====\n");
    for (int i = 1; i <= n; i++) {
        printf("Number of nodes in the sub tree of node numer %d : ", i);
        printf("%d\n", subtree_count[i]);
    }
    printf("\n");
    
    return 0;
}

