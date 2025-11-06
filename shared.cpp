#include "shared.hpp"
#include <array>
#include <string>
#include <random>

using namespace std::literals::string_literals;

std::array<std::string, 1024> strs;

static std::random_device rd;
static std::mt19937 gen(rd());

std::string RandomStr()
{
    const auto chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"s;
    std::string result;
    result.reserve(256);
    std::uniform_int_distribution distrib(0, static_cast<int>(chars.size() - 1));
    for (int i = 0; i < 256; ++i)
    {
        result += chars[distrib(gen)];
    }
    return result;
}

void InitStrings()
{
    gen.seed(23);
    for (int i{}; i < strs.size(); i++)
        strs[i] = RandomStr();
}