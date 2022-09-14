#include <iostream>
#include <string>
//#include <basic_string.h>
#include <vector>
#include <algorithm>

#define syst 1000000000

class BigInt {
public:
    char sign = '+';
    std::vector<int> number;
public:
    BigInt();

    explicit BigInt(long);

    explicit BigInt(std::string); // бросать исключение std::invalid_argument при ошибке

    BigInt(const BigInt &);


//
//    ~BigInt();
//
//    BigInt &operator=(const BigInt &);  //возможно присваивание самому себе!
//
//    BigInt operator~() const;
//
    //  BigInt &operator++();
//
//    const BigInt operator++(int) const;
//
//    BigInt &operator--();
//
//    const BigInt operator--(int) const;
//
//    BigInt &operator+=(const BigInt &);
//
//    BigInt &operator*=(const BigInt &);
//
//    BigInt &operator-=(const BigInt &);
//
//    BigInt &operator/=(const BigInt &);
//
//    BigInt &operator^=(const BigInt &);
//
//    BigInt &operator%=(const BigInt &);
//
//    BigInt &operator&=(const BigInt &);
//
//    BigInt &operator|=(const BigInt &);
//
//    BigInt operator+() const;  // unary +
//    BigInt operator-() const;  // unary -
//
//    bool operator==(const BigInt &) const;
//
//    bool operator!=(const BigInt &) const;
//
//    bool operator<(const BigInt &) const;
//
//    bool operator>(const BigInt &) const;
//
//    bool operator<=(const BigInt &) const;
//
//    bool operator>=(const BigInt &) const;
//
//    operator int() const;
//
//    operator std::string() const;
//
//    size_t size() const;  // size in bytes
};

BigInt::BigInt() {
    number.push_back(0);
    sign = '+';
}

BigInt::BigInt(long num1) {
    if (num1 < 0)
        sign = '-';
    num1 = abs(num1);
    while (num1 > 0) {
        number.push_back(num1 % syst);
        num1 = num1 / syst;
    }
    std::reverse(number.begin(), number.end());
}

BigInt::BigInt(std::string num2) {
    if (num2.empty() || (num2[0] == '-' && num2.length() < 2))
        throw std::invalid_argument("string is too short");

    if (num2[0] != '-' && (num2[0] < '0' || num2[0] > '9'))
        throw std::invalid_argument("first symbol is invalid");

    for (int i = 1; i < num2.length(); i++)
        if (num2[i] < '0' || num2[i] > '9')
            throw std::invalid_argument("string contains invalid symbol");

    if (num2[0] == '-') {
        sign = '-';
        num2.erase(0, 1);
    }
    while (num2.length() >= 9) {
        number.push_back(std::stoi(num2.substr(num2.length() - 9, 9)));
        num2.erase(num2.length() - 9, 9);
    }
    if (num2.length() != 0)
        number.push_back(std::stoi(num2));

    std::reverse(number.begin(), number.end());
}

BigInt::BigInt(const BigInt &input_bi) {
    number = input_bi.number;
    sign = input_bi.sign;
}

//BigInt &BigInt::operator++() {

//}




void PRINT_BI(const BigInt &bi) {
    bi.sign == '-' ? std::cout << bi.sign : std::cout << "";
    std::cout << bi.number[0];
    for (int i = 1; i < bi.number.size(); i++) {
        printf("%09d", bi.number[i]);
    }
}


//
//BigInt operator+(const BigInt&, const BigInt&);
//BigInt operator-(const BigInt&, const BigInt&);
//BigInt operator*(const BigInt&, const BigInt&);
//BigInt operator/(const BigInt&, const BigInt&);
//BigInt operator^(const BigInt&, const BigInt&);
//BigInt operator%(const BigInt&, const BigInt&);
//BigInt operator&(const BigInt&, const BigInt&);
//BigInt operator|(const BigInt&, const BigInt&);
//
//
//std::ostream& operator<<(std::ostream& o, const BigInt& i);
int main() {
    try {
        BigInt bi("0000000000112300000000");

        PRINT_BI(bi);
    }
    catch (const std::invalid_argument &err) {
        std::cout << err.what();
    }
    return 0;
}