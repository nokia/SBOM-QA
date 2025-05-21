#include <iostream>
#include <ctime>
#include <string>

#include <fmt/format.h>


int main() {
    cout << hello() << "\n";
    std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
    cout << s << "\n";
}