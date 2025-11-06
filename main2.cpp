#include <benchmark/benchmark.h>
#include <random>
#include <array>
#include <chrono>
#include <numeric>

#include "shared.hpp"

using namespace std::literals::string_literals;

static bool SameTextStdEqual( const std::string_view a,
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



int main2(int argc, char **argv)
{
    auto start = std::chrono::high_resolution_clock::now();
    int cnt;
    for (int i{}; i<10; i++)
    {
        InitStrings();
        cnt = std::accumulate(
        strs.begin(), strs.end(), 0,
        [](const int sum, const std::string& s2) {
            return sum + SameTextStdEqual(s, s2);
        });
        std::cout << cnt << ' ';
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time: " << duration << " ns" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i{}; i<10; i++)
    {
        InitStrings();
        cnt = std::accumulate(
        strs.begin(), strs.end(), 0,
        [](const int sum, const std::string& s2) {
            return sum + SameText2(s, s2);
        });
        std::cout << cnt << ' ';
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time: " << duration << " ns" << std::endl;
    return 0;
}