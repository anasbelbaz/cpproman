// cpproman converts between Roman numerals and integers, in either direction.
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

static std::string toRoman(int n) {
    static const std::vector<std::pair<int, std::string>> table = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
        {5, "V"},    {4, "IV"},   {1, "I"}};
    std::string out;
    for (const auto& [val, sym] : table)
        while (n >= val) {
            out += sym;
            n -= val;
        }
    return out;
}

static int romanValue(char c) {
    switch (std::toupper(static_cast<unsigned char>(c))) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

static bool fromRoman(const std::string& s, long& out) {
    long total = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        int v = romanValue(s[i]);
        if (v == 0) return false;
        int next = (i + 1 < s.size()) ? romanValue(s[i + 1]) : 0;
        total += (v < next) ? -v : v;
    }
    out = total;
    return true;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: cpproman <integer|roman>...\n";
        return 2;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        bool numeric = !arg.empty();
        for (char c : arg)
            if (!std::isdigit(static_cast<unsigned char>(c))) numeric = false;

        if (numeric) {
            int n = std::stoi(arg);
            if (n <= 0 || n > 3999) {
                std::cerr << "cpproman: " << n << " out of range (1-3999)\n";
                return 1;
            }
            std::cout << toRoman(n) << '\n';
        } else {
            long n;
            if (!fromRoman(arg, n)) {
                std::cerr << "cpproman: invalid Roman numeral: " << arg << '\n';
                return 1;
            }
            std::cout << n << '\n';
        }
    }
    return 0;
}
