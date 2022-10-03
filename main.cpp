#include "BIgInt.h"

int main() {
    try {
        BigInt bi1("14849498498");
        BigInt bi2("-58898498498489");
        std::cout << (bi1&bi2) << '\n' << (bi1|bi2);
//        std::cout << (bi1-bi2) << '\n';
        //std::cout << (-7 % -3 ) << '\n';
//        std::cout << (bi1 + bi2) << '\n';
//        std::cout << bi2.operator int();
//        std::cout << (bi1<bi2) <<'\n'<<(bi1>bi2) <<'\n'<<(bi1==bi2) ;
//        std::cout << bi2.operator std::string();
//        int a = 9, b = 14;
//        std::cout << (a & b);
    }
    catch (const std::invalid_argument &err) {
        std::cerr << err.what();
    }
    return 0;
}