#include <benchmark/benchmark.h>
#include <vector>
#include <string>

extern "C" {
    #include "lab4.h"
}


void BM_AVL_Insertion(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming(); 
        AVLTree tr;
        avlTreeCreate(&tr);
        state.ResumeTiming();

        for (int i = 0; i < state.range(0); ++i) {
            std::string key = std::to_string(i);
            tr.root = avlTreeInsert((char*)key.c_str(), i, tr.root);
        }
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_AVL_Insertion)->Range(8, 1024)->Complexity();


void BM_AVL_Search(benchmark::State& state) {
    AVLTree tr;
    avlTreeCreate(&tr);
    for (int i = 0; i < 1000; ++i) {
        std::string key = std::to_string(i);
        tr.root = avlTreeInsert((char*)key.c_str(), i, tr.root);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(avlTreeSearch((char*)"500", tr.root));
    }
}

BENCHMARK(BM_AVL_Search);


int main(int argc, char** argv) {
    printf("Platform: Windows 11 x64\n");
    printf("RAM: 16GB DDR4 (System Total)\n"); 
    printf("----------------------------------------------------------\n");

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return 0;
}