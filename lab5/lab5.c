#include <stdio.h>
#include <stdbool.h>
#include "lab5.h"


void prepareInitGraph(Graph *gr, bool *isInit) {
    int vertices;
    printf(" => Vertices count: ");
    scanf("%d", &vertices);
    *isInit = graphCreate(gr, vertices);
};

void prepareAddEdge(Graph *gr) {
    int a, b, len;
    printf(" => Two vertices: ");
    scanf("%d %d", &a, &b);
    printf(" => Edge length: ");
    scanf("%d", &len);
    graphAddEdge(gr, a, b, len);
};

void showSystemMessage(bool isInit) {
    printf("Graph [ %s ]\n", isInit ? "Init" : "Not init");
    printf("--------------------\n");
    printf("[1] Initialize graph\n");
    printf("[2] Add edge\n");
    printf("[3] Print graph\n");
    printf("[4] Kruskal\n");
    printf("--------------------\n");
    printf("[0] Exit program\n");
};

int main() {
    Graph graph;
    bool isInit = false;

    int option;
    while (true) {
        showSystemMessage(isInit);
        scanf("%d", &option);
        switch (option) {
            case 0:
                return 0;
            case 1:
                prepareInitGraph(&graph, &isInit);
                break;
            case 2:
                if (!isInit) {
                    printf("<< Init graph firstly >>\n");
                    break;
                };
                prepareAddEdge(&graph);
                break;
            case 3:
                if (!isInit) {
                    printf("<< Init graph firstly >>\n");
                    break;
                };
                graphPrint(&graph);
                break;
            case 4:
                if (!isInit) {
                    printf("<< Init graph firstly >>\n");
                    break;
                };
                graph = graphKruskal(&graph);
                break;
            default:
                printf("<< Unknown command: %d >>\n", option);
                break;
        };
    };

    return 0;
};
