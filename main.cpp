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
//    const BigInt operator++(BigInt) const;
//
//    BigInt &operator--();
//
//    const BigInt operator--(int) const;
//
    BigInt &operator+=(const BigInt &);

//
//    BigInt &operator*=(const BigInt &);
//
    BigInt &operator-=(const BigInt &);

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
    BigInt &operator-();  // unary -
//
    bool operator==(const BigInt &) const;

//
    bool operator!=(const BigInt &) const;

//
    bool operator<(const BigInt &) const;

//
    bool operator>(const BigInt &) const;

//
    bool operator<=(const BigInt &) const;

//
    bool operator>=(const BigInt &) const;
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

    while (number[0] == 0)
        number.erase(number.begin());
    if (number[0] == 0)
        sign = '+';
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

    while (number[number.size() - 1] == 0 && number.size() > 1)
        number.erase(number.end() - 1);
    if (number[0] == 0)
        sign = '+';
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

BigInt &BigInt::operator+=(const BigInt &inp_bi) {
    //if(sign!=inp_bi.sign)
    //minus;

    int carry = 0;
    int max_len = (int) std::max(number.size(), inp_bi.number.size());
    for (int i = 0; i < max_len || carry != 0; i++) {
        if (i == number.size())
            number.push_back(0);
        if (i < inp_bi.number.size())
            number[i] += carry + inp_bi.number[i];
        else
            number[i] += carry;
        if (number[i] > syst)
            carry = 1;
        if (carry != 0)
            number[i] / syst;
    }
    return *this;
}

BigInt &BigInt::operator-=(const BigInt &inp_bi) {

    int carry = 0;
    int max_len = (int) std::max(number.size(), inp_bi.number.size());
    for (int i = 0; i < max_len || carry != 0; i++) {
        if (i == number.size())
            number.push_back(0);
        if (i < inp_bi.number.size())
            number[i] -= carry + inp_bi.number[i];
        else
            number[i] -= carry;
        if (number[i] < 0)
            carry = 1;
        if (carry != 0 && number[i + 1])
            number[i] += syst;
    }

    return *this;
}

BigInt &BigInt::operator-() {
    if (sign == '+')
        sign = '-';
    else
        sign = '+';
    return *this;
}

BigInt BigInt::operator+() const {
    return *this;
}

bool BigInt::operator>(const BigInt &inp_bi) const {
    if (this->sign != inp_bi.sign)
        return (this->sign == '+');
    else if (this->number.size() > inp_bi.number.size())
        return (this->sign == '+');
    for (int i = (int) this->number.size() - 1; i >= 0; i--)
        if (this->number[i] != inp_bi.number[i])
            return (this->number[i] > inp_bi.number[i] && this->sign == '+');
    return false;
}

bool BigInt::operator==(const BigInt &inp_bi) const {
    if (this->number.size() > inp_bi.number.size() || this->sign != inp_bi.sign)
        return false;
    for (int i = (int) this->number.size() - 1; i >= 0; i--)
        if (this->number[i] != inp_bi.number[i])
            return false;
    return true;
}

bool BigInt::operator!=(const BigInt &inp_bi) const {
    return !(*this == inp_bi);
}

bool BigInt::operator<=(const BigInt &inp_bi) const {
    return !(*this > inp_bi);
}

bool BigInt::operator<(const BigInt &inp_bi) const {
    return !(*this > inp_bi || *this == inp_bi);
}

bool BigInt::operator>=(const BigInt &inp_bi) const {
    return !(*this < inp_bi);
}


void PRINT_BI(BigInt &inp_bi) {
    inp_bi.sign == '-' ? std::cout << inp_bi.sign : std::cout << "";
    std::reverse(inp_bi.number.begin(), inp_bi.number.end());
    std::cout << inp_bi.number[0];
    for (int i = 1; i < inp_bi.number.size(); i++) {
        printf("%09d", inp_bi.number[i]);
    }
}


int main() {
    try {
        BigInt bi1("-15423");
        BigInt bi2("1235");
        //PRINT_BI(bi1 += bi2);
        std::cout << (bi1 >= bi2);

    }
    catch (const std::invalid_argument &err) {
        std::cout << err.what();
    }
    return 0;
}