#include <iostream>
#include "hilang.h"

using namespace std;

int main()
{
//    std::string source = "for (int i = 0; i < 5; i++) { a++; }";

//    auto result = tokenize(source);
    int i = 0;
    cout << match({_plus, _minus, __this}, {{"+"}, {"-"}, {"-"}, {"+"}}, i);

    return 0;
}
