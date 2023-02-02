#include <iostream>
#include "hilang.h"

using namespace std;

int main()
{
//    std::string source = "for (int i = 0; i < 5; i++) { a++; }";
    std::string source = "a+b; y+c; v";

    auto result = tokenize(source);
//    for (auto tok : result)
//    {
//        std::cout << tok.value << ".." << token_type(tok) << "\n";
//    }
    parse(result);
    return 0;
}
