#include <iostream>
#include "hilang.h"

using namespace std;

int main()
{
//    std::string source = "for (int i = 0; i < 5; i++) { a++; }";
    std::string source = "(((((4)+5))-x6+7)-8*9)";
    auto result = tokenize(source);
//    for (auto tok : result)
//    {
//        std::cout << tok.value << ".." << token_type(tok) << "\n";
//    }
    int i = 0;
    cout << "Parsed: " << match(Word{_expression}, result, i);
    return 0;
}
