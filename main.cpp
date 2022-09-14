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
    BigInt &operator=(const BigInt &);  //возможно присваивание самому себе!
//
//    BigInt operator~() const;
//
//    BigInt &operator++();
//
//    const BigInt operator++(int) const;
//
//    BigInt &operator--();
//
//    const BigInt operator--(int) const;
//
    BigInt &operator+=(const BigInt &);
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
      BigInt operator+() const;  // unary +
      BigInt & operator-();  // unary -
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

BigInt::BigInt() {
    number.push_back(0);
}

BigInt::BigInt(long inp_int) {
    if (inp_int < 0)
        sign = '-';
    inp_int = abs(inp_int);
    while (inp_int > 0) {
        number.push_back(inp_int % syst);
        inp_int = inp_int / syst;
    }

    std::reverse(number.begin(), number.end());

    while (number[0] == 0)
        number.erase(number.begin());
}

BigInt::BigInt(std::string inp_str) {
    if (inp_str.empty() || (inp_str[0] == '-' && inp_str.length() < 2))
        throw std::invalid_argument("string is too short");

    if (inp_str[0] != '-' && (inp_str[0] < '0' || inp_str[0] > '9'))
        throw std::invalid_argument("first symbol is invalid");

    for (int i = 1; i < inp_str.length(); i++)
        if (inp_str[i] < '0' || inp_str[i] > '9')
            throw std::invalid_argument("string contains invalid symbol");

    if (inp_str[0] == '-') {
        sign = '-';
        inp_str.erase(0, 1);
    }
    while (inp_str.length() >= 9) {
        number.push_back(std::stoi(inp_str.substr(inp_str.length() - 9, 9)));
        inp_str.erase(inp_str.length() - 9, 9);
    }
    if (inp_str.length() != 0)
        number.push_back(std::stoi(inp_str));

    std::reverse(number.begin(), number.end());

    while (number[0] == 0 && number.size() > 1)
        number.erase(number.begin());
}

BigInt::BigInt(const BigInt &inp_bi) {
    number = inp_bi.number;
    sign = inp_bi.sign;
}

BigInt &BigInt::operator=(const BigInt &inp_bi) {
    number = inp_bi.number;
    sign = inp_bi.sign;
    return *this;
}

//BigInt &BigInt::operator+=(const BigInt &inp_bi) {
//    int carry = 0;
//    int max_len = std::max(number.size(),inp_bi.number.size());
//    for (int i = )
//
//}

BigInt & BigInt::operator-() {
    if (sign =='+')
        sign = '-';
    else
        sign = '+';
    return *this;
}

BigInt BigInt::operator+() const {
    return *this;
}


void PRINT_BI(const BigInt &inp_bi) {
    inp_bi.sign == '-' ? std::cout << inp_bi.sign : std::cout << "";
    std::cout << inp_bi.number[0];
    for (int i = 1; i < inp_bi.number.size(); i++) {
        printf("%09d", inp_bi.number[i]);
    }
}


int main() {
    try {
        BigInt bi("0000000000000000000000000000001001");

        PRINT_BI(bi);
    }
    catch (const std::invalid_argument &err) {
        std::cout << err.what();
    }
    return 0;
}