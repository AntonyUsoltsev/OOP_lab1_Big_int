#ifndef BIG_INT_BIGINT_H
#define BIG_INT_BIGINT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <cmath>

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
    explicit BigInt(int);                   // Constructor from int.
    explicit BigInt(std::string);           // Constructor from string.
    BigInt(const BigInt &);                 // Constructor from BigInt -- copy constructor.
    ~BigInt();                              // Destructor.

    BigInt &operator=(const BigInt &);      // Copy operator
    BigInt operator~() const;               // Bitwise not.

    BigInt &operator++();                   // Prefix unary increment.
    const BigInt operator++(int);           // Postfix unary increment.
    BigInt &operator--();                   // Prefix unary decrement.
    const BigInt operator--(int);           // Postfix unary decrement.

    BigInt &operator+=(const BigInt &);     // Plus assigment.
    BigInt &operator-=(const BigInt &);     // Minus assigment.
    BigInt &operator*=(const BigInt &);     // Multiplication assigment.
    BigInt &operator/=(const BigInt &);     // Division assigment.
    BigInt &operator%=(const BigInt &);     // Mod assigment.
    BigInt &operator^=(const BigInt &);     // XOR assigment.
    BigInt &operator&=(const BigInt &);     // AND assigment.
    BigInt &operator|=(const BigInt &);     // OR assigment.

    BigInt operator+() const;               // Unary plus.
    BigInt operator-() const;               // Unary minus.

    bool operator>(const BigInt &) const;
    bool operator==(const BigInt &) const;
    bool operator!=(const BigInt &) const;
    bool operator<(const BigInt &) const;
    bool operator<=(const BigInt &) const;
    bool operator>=(const BigInt &) const;

    explicit operator int() const;          // From BigInt to int.
    explicit operator std::string() const;  // From BigInt to string.
    size_t size() const;                    // Size in bytes: size of number (in bytes) + 1 byte - size of sign.
};

BigInt operator+(const BigInt &, const BigInt &);
BigInt operator-(const BigInt &, const BigInt &);
BigInt operator*(const BigInt &, const BigInt &);
BigInt operator/(const BigInt &, const BigInt &);
BigInt operator%(const BigInt &, const BigInt &);
BigInt operator^(const BigInt &, const BigInt &);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream &operator<<(std::ostream &, const BigInt &);

#endif //BIG_INT_BIGINT_H