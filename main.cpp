#include <iostream>
//#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits.h>
//#include <windows.h>

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

    ~BigInt();

    BigInt &operator=(const BigInt &);  //возможно присваивание самому себе!

    BigInt operator~() const;

    BigInt &operator++();

    const BigInt operator++(int);

    BigInt &operator--();

    const BigInt operator--(int);

    BigInt &operator+=(const BigInt &);

    BigInt &operator*=(const BigInt &);

    BigInt &operator-=(const BigInt &);

    BigInt &operator/=(const BigInt &);

    BigInt &operator^=(const BigInt &);

    BigInt &operator%=(const BigInt &);

//    BigInt &operator&=(const BigInt &);
//
//    BigInt &operator|=(const BigInt &);
//
    BigInt operator+() const;  // unary +

    BigInt &operator-();  // unary -

    bool operator==(const BigInt &) const;

    bool operator!=(const BigInt &) const;

    bool operator<(const BigInt &) const;

    bool operator>(const BigInt &) const;

    bool operator<=(const BigInt &) const;

    bool operator>=(const BigInt &) const;

    explicit operator int() const; //???????

    explicit operator std::string() const;

    size_t size() const;  // size in bytes
};

BigInt operator+(const BigInt &, const BigInt &);

BigInt operator-(const BigInt &, const BigInt &);

BigInt operator*(const BigInt &, const BigInt &);

BigInt operator/(const BigInt &, const BigInt &);

BigInt operator^(const BigInt &, const BigInt &);

BigInt operator%(const BigInt &, const BigInt &);

//BigInt operator&(const BigInt&, const BigInt&);
//BigInt operator|(const BigInt&, const BigInt&);

std::ostream &operator<<(std::ostream &o, const BigInt &i);

BigInt::BigInt() {
    number.push_back(0);
}

BigInt::BigInt(long inp_int) {
    if (inp_int == 0)
        number.push_back(0);
    else {
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

    while (number.back() == 0 && number.size() > 1)
        number.pop_back();
    if (number[0] == 0 && number.size() == 1)
        sign = '+';
}

BigInt::BigInt(const BigInt &inp_bi) {
    number = inp_bi.number;
    sign = inp_bi.sign;
}

BigInt::~BigInt() = default;

BigInt &BigInt::operator=(const BigInt &inp_bi) {
    if (this == &inp_bi)
        throw std::invalid_argument("self assigment");
    number = inp_bi.number;
    sign = inp_bi.sign;
    return *this;
}

BigInt &BigInt::operator-=(const BigInt &inp_bi) {
    if (this->sign == '+' && inp_bi.sign == '-') {
        BigInt copy = inp_bi;
        *this += -(copy);
        return *this;
    } else if (this->sign == '-' && inp_bi.sign == '+') {
        BigInt copy = -*this;
        copy += inp_bi;
        *this = -copy;
        return *this;
    } else if (this->sign == '-' && inp_bi.sign == '-') {
        BigInt copy_1 = -*this;
        BigInt copy_2 = inp_bi;
        (-copy_2) -= copy_1;
        *this = copy_2;
        return *this;
    } else {
        BigInt copy_1;
        BigInt copy_2;
        if (*this > inp_bi) {
            copy_1 = *this;
            copy_2 = inp_bi;
        } else if (*this < inp_bi) {
            copy_1 = inp_bi;
            copy_2 = *this;
            copy_1.sign = '-';
        }
        int carry = 0;
        int max_len = (int) copy_1.number.size();
        for (int i = 0; i < max_len || carry != 0; i++) {
            if (i < copy_2.number.size())
                copy_1.number[i] -= carry + copy_2.number[i];
            else
                copy_1.number[i] -= carry;

            if (copy_1.number[i] < 0) {
                carry = 1;
                copy_1.number[i] += syst;
            } else
                carry = 0;
        }
        *this = copy_1;
    }
    return *this;
}

BigInt &BigInt::operator+=(const BigInt &inp_bi) {
    if (this->sign == '+' && inp_bi.sign == '-') {
        BigInt copy = inp_bi;
        *this -= -(copy);
        return *this;
    } else if (this->sign == '-' && inp_bi.sign == '+') {
        BigInt copy_1 = -*this;
        BigInt copy_2 = inp_bi;
        copy_2 -= copy_1;
        *this = copy_2;
        return *this;
    } else {
        int carry = 0;
        int max_len = (int) std::max(number.size(), inp_bi.number.size());
        for (int i = 0; i < max_len || carry != 0; i++) {
            if (i == number.size())
                number.push_back(0);

            if (i < inp_bi.number.size())
                number[i] += carry + inp_bi.number[i];
            else
                number[i] += carry;

            if (number[i] > syst) {
                carry = 1;
                number[i] -= syst;
            } else
                carry = 0;
        }
        return *this;
    }
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

BigInt &BigInt::operator++() {
    BigInt tmp(1);
    *this += tmp;
    return *this;
}

const BigInt BigInt::operator++(int) {
    BigInt tmp = *this;
    ++*this;
    return tmp;
}

BigInt &BigInt::operator--() {
    BigInt tmp(1);
    *this -= tmp;
    return *this;
}

const BigInt BigInt::operator--(int) {
    BigInt tmp = *this;
    --*this;
    return tmp;
}

BigInt BigInt::operator~() const {
    BigInt tmp = *this;
    ++tmp;
    return -tmp;
}

BigInt &BigInt::operator*=(const BigInt &inp_bi) {
    this->sign = (this->sign == inp_bi.sign) ? '+' : '-';
    std::vector<int> res;
    res.resize(this->number.size() + inp_bi.number.size());
    long long tmp, carry = 0;
    int cur = 0, index = 0;
    for (auto i: number) {
        for (auto j: inp_bi.number) {
            tmp = (long long) i * (long long) j + carry + (long long) res[cur];
            res[cur] = (int) (tmp % syst);
            cur++;
            carry = tmp / syst;
        }
        if (carry != 0)
            res[cur] = (int) carry;
        carry = 0;
        index++;
        cur = index;
    }
    while (res.back() == 0 && res.size() > 1)
        res.pop_back();
    this->number = res;
    if (number[0] == 0 && number.size() == 1)
        sign = '+';
    return *this;
}

BigInt abs(BigInt &inp_bi) {
    inp_bi.sign = '+';
    return inp_bi;
}

BigInt bin_search(const BigInt &tmp, const BigInt &divider) {
    if (divider > tmp) {
        BigInt zero_res(0);
        return zero_res;
    }
    int left = 1, right = syst - 1, mid = syst / 2;
    BigInt mid_bi((left + right) / 2);
    while (left <= right) {
        if ((divider * mid_bi) <= tmp)
            left = mid + 1;
        else
            right = mid - 1;
        mid = (left + right) / 2;
        mid_bi.number[0] = mid;
    }
    return mid_bi;
}

BigInt &BigInt::operator/=(const BigInt &inp_bi) {
    BigInt divisible = *this, divider = inp_bi;
    BigInt zero_res(0);

    if (inp_bi.number[0] == 0 && inp_bi.number.size() == 1)
        throw std::invalid_argument("Division by zero");

    if (abs(divisible) < abs(divider)) {
        *this = zero_res;
        return *this;
    }
    BigInt res, cur, quotient;
    res.number.resize(this->number.size());

    for (int i = this->number.size() - 1; i >= 0; i--) {
        cur.number.insert(cur.number.begin(), this->number[i]);
        quotient = bin_search(cur, divider);
        res.number[i] = quotient.number[0];
        cur -= (quotient * divider);
    }
    this->number = res.number;
    if (this->sign != inp_bi.sign) {
        this->sign = '-';
        --*this;
    } else
        this->sign = '+';

    while (number.back() == 0 && number.size() > 1)
        number.pop_back();
    return *this;
}


BigInt &BigInt::operator^=(const BigInt &inp_bi) {
    BigInt one(1);
    BigInt cur = *this;
    BigInt count = inp_bi;
    while (count != one) {
        *this *= cur;
        --count;
    }
    return *this;
}

BigInt &BigInt::operator%=(const BigInt &inp_bi) {
    BigInt div = *this / inp_bi;
    *this -= div * inp_bi;
    return *this;
}

BigInt::operator std::string() const {
    std::stringstream str;
    str << *this;
    return str.str();
}

size_t BigInt::size() const {
    return (this->number.size() + 1);
}

BigInt::operator int() const {
    unsigned long long res;
    res = number.size() == 1 ? this->number[0] : (this->number[0] + this->number[1] * syst);
    if (res <= INT_MAX)
        return (this->sign == '+') ? (int) res : (int) (-1 * res);
    else
        throw std::invalid_argument("number is bigger than int");
}

BigInt operator+(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res += inp_bi_2;
    return res;
};

BigInt operator-(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res -= inp_bi_2;
    return res;
};

BigInt operator*(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res *= inp_bi_2;
    return res;
}

BigInt operator/(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res /= inp_bi_2;
    return res;
}

BigInt operator^(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res ^= inp_bi_2;
    return res;
}

BigInt operator%(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res %= inp_bi_2;
    return res;
}

std::ostream &operator<<(std::ostream &o, const BigInt &inp_bi) {
    BigInt copy = inp_bi;
    if (copy.sign == '-')
        o << copy.sign;
    std::reverse(copy.number.begin(), copy.number.end());
    o << copy.number[0];
    o.fill('0');   // should I return old char ?
    for (int i = 1; i < copy.number.size(); i++)
        o << std::setw(9) << copy.number[i];
    return o;
};

//void PRINT_BI(BigInt &inp_bi) {
//    inp_bi.sign == '-' ? std::cout << inp_bi.sign : std::cout << "";
//    std::reverse(inp_bi.number.begin(), inp_bi.number.end());
//    std::cout << inp_bi.number[0];
//    for (int i = 1; i < inp_bi.number.size(); i++)
//        printf("%09d", inp_bi.number[i]);
//}

int main() {
    try {
//        std::string a,b;
//        std :: cout << "Vvedite dva chisla cherez probel, zatem enter\n";
//        std::cin >> a >> b;
//        BigInt bi1(a);
//        BigInt bi2(b);
//        std :: cout << "Summa ";
//        PRINT_BI(bi1+=bi2);
//        BigInt bi3(a);
//        BigInt bi4(b);
//        std :: cout << "\nRaznost' ";
//        PRINT_BI(bi3-=bi4);
//        BigInt bi5(a);
//        BigInt bi6(b);
//        std :: cout << "\n+1 k pervomu ";
//        PRINT_BI(++bi5);
//        std :: cout << "\n-1 k vtoromu ";
//        PRINT_BI(--bi6);
        BigInt bi1("-1222555222222222200");
        BigInt bi2("555553958998");
        std::cout << (bi1 + bi2) << " " << (bi1 - bi2) << " " << bi1 << " " << " ";
        //std::cout << bi2.operator int();
        std::cout << bi2.operator std::string();
//        int a = 9, b = 14;
//        std::cout << (a & b);

    }
    catch (const std::invalid_argument &err) {
        std::cerr << err.what();
    }
    return 0;
}