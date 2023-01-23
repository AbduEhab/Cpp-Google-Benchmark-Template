#include <Constants.hpp>

#include <benchmark/benchmark.h>

static void rand(benchmark::State &state)
{
  // Code before the loop is not measured
  for (auto _ : state)
  {
    std::rand();
  }
}
BENCHMARK(rand);

static void mt19937(benchmark::State &state)
{
  // Code before the loop is not measured
  for (auto _ : state)
  {
    random(0.0, 1.0);
  }
}
BENCHMARK(mt19937);

BENCHMARK_MAIN();