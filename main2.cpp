#include <benchmark/benchmark.h>
#include <random>
#include <array>
#include <chrono>
#include <numeric>

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

const auto s {"blabunga"s };

static std::array<std::string, 1024> strs;

static std::random_device rd;
static std::mt19937 gen(rd());

static std::string RandomStr()
{
    const auto chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"s;
    std::string result;
    result.reserve(256);
    std::uniform_int_distribution distrib(0, static_cast<int>(chars.size() - 1));
    for (int i = 0; i < 256; ++i) {
        result += chars[distrib(gen)];
    }
    return result;
}

static void initstrs()
{
    gen.seed(23);
    for(int i{}; i<strs.size(); i++)
        strs[i] = RandomStr();
}


int main(int argc, char **argv)
{
    auto start = std::chrono::high_resolution_clock::now();
    int cnt;
    for (int i{}; i<10; i++)
    {
        initstrs();
        cnt = std::accumulate(
        strs.begin(), strs.end(), 0,
        [](const int sum, const std::string& s2) {
            return sum + SameText1(s, s2);
        });
        std::cout << cnt << ' ';
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time: " << duration << " ns" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i{}; i<10; i++)
    {
        initstrs();
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