#include <iostream>
#include <benchmark/benchmark.h>
#include <random>
#include <array>

using namespace std::literals::string_literals;

static bool SameText1( const std::string_view a,
                       const std::string_view b )
{
    if( b.length() != a.length() ) return false;
    return std::equal(a.begin(), a.end(), b.begin(),
       []( const unsigned char c1, const unsigned char c2) {
          return c1 == c2 || std::toupper(c1) == std::toupper(c2);
    });
}

static bool SameText2( const std::string_view S1, const std::string_view S2 )
{
    if(S1.length() != S2.length()) return false;
    for(size_t i{}; i<S1.length(); i++)
    {
        if(S1[i] != S2[i] && tolower(S1[i]) != tolower(S2[i]))
            return false;
    }
    return true;
}

const std::string s {"blabunga"s };

std::array<std::string, 1024> strs;

std::string RandomStr()
{
    const std::string chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"s;
    std::string result;
    result.reserve(256);
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, static_cast<int>(chars.size() - 1));
    for (int i = 0; i < 256; ++i) {
        result += chars[distrib(gen)];
    }
    return result;
}

void initstrs()
{
    for(int i{}; i<strs.size(); i++)
        strs[i] = RandomStr();
}

static void Bench1(benchmark::State& state) {
    initstrs();
    for (auto _ : state) {
        int cnt {};
        for(const auto &s2 : strs)
            cnt += SameText1(s, s2);
        benchmark::DoNotOptimize(cnt);
    }
}
// Register the function as a benchmark
BENCHMARK(Bench1);

static void Bench2(benchmark::State& state) {
    initstrs();
    for (auto _ : state) {
        int cnt {};
        for(const auto &s2 : strs)
            cnt += SameText2(s, s2);
        benchmark::DoNotOptimize(cnt);
    }
}
BENCHMARK(Bench2);

BENCHMARK_MAIN();