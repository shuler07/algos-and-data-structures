#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lab4.h"

void avlTreePrintToFile(Node *root, int space, FILE *out) {
    if (!root) return;
    for (int i = 0; i < space; i++) fprintf(out, " ");
    fprintf(out, "%s: %.2lf\n", root->key, root->value);
    if (root->left) avlTreePrintToFile(root->left, space + 2, out);
    if (root->right) avlTreePrintToFile(root->right, space + 2, out);
}

int main() {
    AVLTree tree;
    avlTreeCreate(&tree);

    FILE *in = fopen("../input.txt", "r");
    FILE *out = fopen("../output.txt", "w");

    if (!in || !out) {
        printf("File open error!\n");
        return 1;
    }

    int option;
    char key[7];
    double value;

    while (fscanf(in, "%d", &option) != EOF) {
        switch (option) {
            case 1:
                fscanf(in, "%6s %lf", key, &value);
                fprintf(out, "1 %s %.2lf\n", key, value);
                tree.root = avlTreeInsert(key, value, tree.root);
                fprintf(out, "Done\n");
                break;

            case 2:
                fscanf(in, "%6s", key);
                fprintf(out, "2 %s\n", key);
                tree.root = avlTreeRemove(key, tree.root);
                fprintf(out, "Removed (if existed)\n");
                break;

            case 3:
                fscanf(in, "%6s", key);
                fprintf(out, "3 %s\n", key);
                Node *found = avlTreeSearch(key, tree.root);
                if (found) fprintf(out, "Found: %.2lf\n", found->value);
                else fprintf(out, "Key not found\n");
                break;

            case 4:
                fprintf(out, "4\n");
                if (tree.root) {
                    avlTreePrintToFile(tree.root, 0, out);
                } else {
                    fprintf(out, "Tree is empty\n");
                }
                break;

            case 0:
                fprintf(out, "0\nProgram exit\n");
                fclose(in);
                fclose(out);
                return 0;

            default:
                fprintf(out, "%d\nUnknown command\n", option);
                break;
        }
        fprintf(out, "--------------------\n");
    }

    fclose(in);
    fclose(out);
    printf("Processing completed. Results in output.txt\n");
    return 0;
}