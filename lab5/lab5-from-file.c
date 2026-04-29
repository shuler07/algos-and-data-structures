#include <stdio.h>
#include <stdbool.h>
#include "lab5.h"


void graphPrintToFile(Graph *gr, FILE *out) {
    int n = gr->n_vertices;

    fprintf(out, "    ");
    for (int i = 0; i < n; i++) fprintf(out, "%3d ", i);

    for (int i = 0; i < n; i++) {
        fprintf(out, "\n%3d ", i);
        for (int j = 0; j < n; j++) fprintf(out, "%3d ", gr->matrix[i * n + j]);
    }

    fprintf(out, "\n");
}

int main() {
    FILE *in = fopen("../input.txt", "r");
    FILE *out = fopen("../output.txt", "w");

    if (!in || !out) {
        printf("<< File open error >>\n");
        return 1;
    };

    Graph graph;
    int n;
    fscanf(in, "%d", &n);
    graphCreate(&graph, n);

    int option;
    int a, b, len;

    while (fscanf(in, "%d", &option) != EOF) {
        switch (option) {
            case 2:
                fscanf(in, "%d %d %d", &a, &b, &len);
                fprintf(out, "2 %d %d %d\n", a, b, len);
                graphAddEdge(&graph, a, b, len);
                fprintf(out, "Added (if not existed)\n");
                break;
            case 3:
                fprintf(out, "3\n");
                graphPrintToFile(&graph, out);
                break;
            case 4:
                fprintf(out, "4\n");
                graph = graphKruskal(&graph);
                fprintf(out, "Graph transformed\n");
                break;
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
};
