#include <gtest/gtest.h>

extern "C" {
    #include "lab5.h"
}

// Тест 1: Инициализация и создание
TEST(Lab5, Test1_GraphCreation) {
    Graph gr;
    bool success = graphCreate(&gr, 5);
    ASSERT_TRUE(success);
    EXPECT_EQ(gr.n_vertices, 5);
    EXPECT_EQ(gr.n_edges, 0);
    ASSERT_NE(gr.matrix, nullptr);
    ASSERT_NE(gr.edges, nullptr);
}

// Тест 2: Работа DSU
TEST(Lab5, Test2_DSUFunctionality) {
    DSU dsu;
    dsuCreate(&dsu, 10);
    
    EXPECT_NE(dsuFind(&dsu, 1), dsuFind(&dsu, 2));
    
    dsuUnion(&dsu, 1, 2);
    EXPECT_EQ(dsuFind(&dsu, 1), dsuFind(&dsu, 2));
    
    dsuUnion(&dsu, 2, 3);
    EXPECT_EQ(dsuFind(&dsu, 1), dsuFind(&dsu, 3));
    
    free(dsu.parent);
}

// Тест 3: Краскал на треугольнике (выбор минимальных ребер)
TEST(Lab5, Test3_KruskalSimple) {
    Graph gr;
    graphCreate(&gr, 3);
    
    graphAddEdge(&gr, 0, 1, 10);
    graphAddEdge(&gr, 1, 2, 5);
    graphAddEdge(&gr, 0, 2, 1);
    
    Graph mst = graphKruskal(&gr);

    EXPECT_EQ(mst.n_edges, 2);
    
    int n = mst.n_vertices;
    EXPECT_EQ(mst.matrix[0 * n + 2], 1);
    EXPECT_EQ(mst.matrix[1 * n + 2], 5);
    EXPECT_EQ(mst.matrix[0 * n + 1], 0);
}

// Тест 4: Проверка на отсутствие циклов
TEST(Lab5, Test4_NoCycles) {
    Graph gr;
    graphCreate(&gr, 4);
    graphAddEdge(&gr, 0, 1, 1);
    graphAddEdge(&gr, 1, 2, 1);
    graphAddEdge(&gr, 2, 3, 1);
    graphAddEdge(&gr, 3, 0, 1);
    
    Graph mst = graphKruskal(&gr);
    
    EXPECT_EQ(mst.n_edges, 3);
}

// Тест 5: Несвязный граф (Лес остовных деревьев)
TEST(Lab5, Test5_DisconnectedGraph) {
    Graph gr;
    graphCreate(&gr, 6);
    
    graphAddEdge(&gr, 0, 1, 2);
    graphAddEdge(&gr, 1, 2, 3);
    
    graphAddEdge(&gr, 3, 4, 10);
    graphAddEdge(&gr, 4, 5, 11);
    

    Graph mst = graphKruskal(&gr);
    
    EXPECT_EQ(mst.n_edges, 4);
    
    int n = mst.n_vertices;
    EXPECT_EQ(mst.matrix[0 * n + 3], 0);
    EXPECT_EQ(mst.matrix[2 * n + 5], 0);
    
    EXPECT_EQ(mst.matrix[0 * n + 1], 2);
    EXPECT_EQ(mst.matrix[3 * n + 4], 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
