#include <iostream>
#include <benchmark/benchmark.h>
#include <random>
#include <array>
#include <numeric>

#include "shared.hpp"

using namespace std::literals::string_literals;

inline char tolower( const char c )
{
    return c >= 'A' && c <= 'Z' ? static_cast<char>( c ^ 32 ) : c;
}

static bool SameTextStdEqual(const std::string_view a,
                             const std::string_view b)
{
    if (b.length() != a.length()) return false;
    return std::equal(a.begin(), a.end(), b.begin(),
                      [](const unsigned char c1, const unsigned char c2)
                      {
                          return c1 == c2 || tolower(c1) == tolower(c2);
                      });
}

static bool SameTextForLoop(const std::string_view S1, const std::string_view S2)
{
    if (S1.length() != S2.length()) return false;
    for (size_t i{}; i < S1.length(); i++)
    {
        if (S1[i] != S2[i] && tolower(S1[i]) != tolower(S2[i]))
            return false;
    }
    return true;
}

static void BenchStdEqual(benchmark::State& state)
{
    InitStrings();
    for (auto _ : state)
    {
        int cnt = std::accumulate(
            strs.begin(), strs.end(), 0,
            [](const int sum, const std::string& s2)
            {
                return sum + SameTextStdEqual(s, s2);
            });
        benchmark::DoNotOptimize(cnt);
    }
}

BENCHMARK(BenchStdEqual);

static void BenchForLoop(benchmark::State& state)
{
    InitStrings();
    for (auto _ : state)
    {
        int cnt = std::accumulate(
            strs.begin(), strs.end(), 0,
            [](const int sum, const std::string& s2)
            {
                return sum + SameTextForLoop(s, s2);
            });
        benchmark::DoNotOptimize(cnt);
    }
}

BENCHMARK(BenchForLoop);

BENCHMARK_MAIN();
