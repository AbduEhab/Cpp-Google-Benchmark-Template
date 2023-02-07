#include <Constants.hpp>

#include <benchmark/benchmark.h>

static void itr_sqrt(benchmark::State &state)
{
  // Code inside this loop is measured repeatedly
  for (auto _ : state)
  {
    float n = random(0.0f, 100000.0f);
    // Extract the exponent and mantissa
    int32_t bits = *reinterpret_cast<int32_t *>(&n);
    int32_t exponent = ((bits >> 23) & 0xff) - 127;
    int32_t mantissa = bits & 0x7fffff;

    // Normalize the mantissa
    while (mantissa & 0x400000)
    {
      mantissa <<= 1;
      exponent--;
    }
    mantissa &= 0x3fffff;

    // Initialize the approximation
    float x = n;

    // Iterate until the approximation converges
    for (int i = 0; i < 10; i++)
    {
      // Compute a new approximation
      float y = (x + n / x) / 2;

      // Check if the approximation has converged
      if (std::abs(x - y) < 0.00001)
      {
        break;
      }

      // Update the approximation
      x = y;
    }

    // Combine the exponent and mantissa to produce the final result
    int32_t result = ((exponent + 127) << 23) | mantissa;
    float f = *reinterpret_cast<float *>(&result);

    benchmark::DoNotOptimize(f);
  }
}
// Register the function as a benchmark
BENCHMARK(itr_sqrt);

static void sqrt(benchmark::State &state)
{
  for (auto _ : state)
  {
    float n = random(0.0f, 100000.0f);

    float f = std::sqrt(n);

    benchmark::DoNotOptimize(f);
  }
}
BENCHMARK(sqrt);

BENCHMARK_MAIN();