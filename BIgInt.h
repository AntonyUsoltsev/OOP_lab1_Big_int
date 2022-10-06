#ifndef BIG_INT_BIGINT_H
#define BIG_INT_BIGINT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <cmath>
#include "gtest/gtest.h"

#define syst 1000000000
class BigInt {
private:
    char sign = '+';
    std::vector<int> number;

    static void del_lead_zeros(BigInt &);
    static BigInt abs(const BigInt&);
    static BigInt bin_to_dec(const std::string&, char);
    static BigInt bin_search(const BigInt&, const BigInt&);
    friend std::ostream &operator<<(std::ostream &, const BigInt &);

public:
    BigInt();
    explicit BigInt(int);
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
    BigInt &operator&=(const BigInt &);
    BigInt &operator|=(const BigInt &);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt &) const;
    bool operator!=(const BigInt &) const;
    bool operator<(const BigInt &) const;
    bool operator>(const BigInt &) const;
    bool operator<=(const BigInt &) const;
    bool operator>=(const BigInt &) const;

    explicit operator int() const;
    explicit operator std::string() const;
    size_t size() const;  // size in bytes
};

BigInt operator+(const BigInt &, const BigInt &);
BigInt operator-(const BigInt &, const BigInt &);
BigInt operator*(const BigInt &, const BigInt &);
BigInt operator/(const BigInt &, const BigInt &);
BigInt operator^(const BigInt &, const BigInt &);
BigInt operator%(const BigInt &, const BigInt &);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);
std::ostream &operator<<(std::ostream &, const BigInt &);


#endif //BIG_INT_BIGINT_H