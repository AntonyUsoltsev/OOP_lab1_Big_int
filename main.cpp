#include <iostream>
#include <string>
#include <utility>

class BigInt {
public:
    std::string number;
public:
    BigInt();

    explicit BigInt(int);

    explicit BigInt(const std::string&); // бросать исключение std::invalid_argument при ошибке

//    BigInt(const BigInt &);
//
//    ~BigInt();
//
//    BigInt &operator=(const BigInt &);  //возможно присваивание самому себе!
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

BigInt::BigInt() = default;

BigInt::BigInt(int num1) {
    number = std::to_string(num1);
}

BigInt::BigInt(const std::string& num2) {
    for(auto c : num2){
        try {
            if (c < '0' || c > '9') {
               // std::cout << "Error";
                throw "invalid_argument";

                // std :: invalid_argument;
            }
        }
        catch(const char* i){
            std::cout << "Error2";
            return;
        }
    }
    number=num2;
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
int main(){
    //BigInt bi("7899");
    BigInt bi(45);
    std :: cout << bi.number;
}