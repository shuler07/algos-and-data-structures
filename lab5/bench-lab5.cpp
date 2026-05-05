#include <benchmark/benchmark.h>
#include <random>

extern "C" {
    #include "lab5.h"
}

// Бенчмарк: Создание и работа Краскала на случайном графе
static void BM_Kruskal_Performance(benchmark::State& state) {
    int n = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming();
        Graph gr;
        graphCreate(&gr, n);
        
        for (int i = 0; i < n - 1; ++i) {
            graphAddEdge(&gr, i, i + 1, rand() % 100 + 1);
        }
        for (int i = 0; i < n; ++i) {
            int u = rand() % n;
            int v = rand() % n;
            if (u != v) graphAddEdge(&gr, u, v, rand() % 100 + 1);
        }
        state.ResumeTiming();

        Graph mst = graphKruskal(&gr);
    }
    state.SetComplexityN(state.range(0));
}

// Запускаем от 8 до 512 вершин
BENCHMARK(BM_Kruskal_Performance)->Range(8, 512)->Complexity();

// Бенчмарк: Только поиск в DSU (Path Compression)
static void BM_DSU_Find(benchmark::State& state) {
    int n = 1000;
    DSU dsu;
    dsuCreate(&dsu, n);
    for (int i = 0; i < n - 1; i++) dsuUnion(&dsu, i, i + 1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(dsuFind(&dsu, 0));
    }
    free(dsu.parent);
}

BENCHMARK(BM_DSU_Find);

int main(int argc, char** argv) {
    printf("Platform: Windows 11 x64\n");
    printf("RAM: 16GB DDR4 (System Total)\n");
    printf("----------------------------------------------------------\n");

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return 0;
}
