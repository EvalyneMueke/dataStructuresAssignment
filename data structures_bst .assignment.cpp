#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to construct a binary search tree from in-order and post-order traversal outputs
struct TreeNode* bst_construct(int* inorder, int* postorder, int inorder_start, int inorder_end, int postorder_start, int postorder_end) {
    if (inorder_start > inorder_end || postorder_start > postorder_end) {
        return NULL;
    }

    // Create the root node
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = postorder[postorder_end];

    // Find the root node's index in the in-order traversal
    int root_index;
    for (root_index = inorder_start; root_index <= inorder_end; root_index++) {
        if (inorder[root_index] == root->val) {
            break;
        }
    }

    // Construct left and right subtrees recursively
    root->left = bst_construct(inorder, postorder, inorder_start, root_index - 1, postorder_start, postorder_start + (root_index - inorder_start) - 1);
    root->right = bst_construct(inorder, postorder, root_index + 1, inorder_end, postorder_start + (root_index - inorder_start), postorder_end - 1);

    return root;
}

// Function to traverse the binary search tree in breadth-first-search (DFS) traversal and print each element
void bfs_traverse(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Create a queue for BFS traversal
    struct TreeNode* queue[1000];
    int front = 0, rear = -1;
    queue[++rear] = root;

    while (front <= rear) {
        struct TreeNode* current = queue[front++];
        printf("%d ", current->val);

        if (current->left != NULL) {
            queue[++rear] = current->left;
        }

        if (current->right != NULL) {
            queue[++rear] = current->right;
        }
    }
}

int main() {
    // Given in-order and post-order traversal outputs
    int inorder[] = {5, 10, 15, 20, 25, 30, 45};
    int postorder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inorder) / sizeof(inorder[0]);

    // Construct the binary search tree
    struct TreeNode* root = bst_construct(inorder, postorder, 0, n - 1, 0, n - 1);

    // Traverse and print the binary search tree in breadth-first-search (DFS) traversal
    printf("Breadth-first-search (DFS) traversal:\n");
    bfs_traverse(root);
    printf("\n");

    return 0;
}

