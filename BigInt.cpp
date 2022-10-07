#include "BigInt.h"

void BigInt::del_lead_zeros(BigInt &inp_bi) {
    while (inp_bi.number.size() > 1 && inp_bi.number.back() == 0)
        inp_bi.number.pop_back();
    if (inp_bi.number[0] == 0 && inp_bi.number.size() == 1)
        inp_bi.sign = '+';
}

BigInt::BigInt() = default;

BigInt::BigInt(int inp_int) {
    long long num = (long long) inp_int;
    if (num == 0)
        number.push_back(0);
    else {
        if (num < 0) {
            sign = '-';
            num = -(long long) inp_int;
        }

        while (num > 0) {
            number.push_back((int) (num % syst));
            num /= syst;
        }
        del_lead_zeros(*this);
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
    del_lead_zeros(*this);
}

BigInt::BigInt(const BigInt &inp_bi) {
    number = inp_bi.number;
    sign = inp_bi.sign;
}

BigInt::~BigInt() = default;

BigInt &BigInt::operator=(const BigInt &inp_bi) = default;

BigInt BigInt::operator~() const {
    BigInt tmp = *this;
    ++tmp;
    return -tmp;
}

BigInt &BigInt::operator++() {
    BigInt one(1);
    *this += one;
    return *this;
}

const BigInt BigInt::operator++(int) {
    BigInt tmp = *this;
    ++*this;
    return tmp;
}

BigInt &BigInt::operator--() {
    BigInt one(1);
    *this -= one;
    return *this;
}

const BigInt BigInt::operator--(int) {
    BigInt tmp = *this;
    --*this;
    return tmp;
}

BigInt &BigInt::operator+=(const BigInt &inp_bi) {
    if (this->sign == '+' && inp_bi.sign == '-')
        *this -= -inp_bi;
    else if (this->sign == '-' && inp_bi.sign == '+') {
        BigInt copy = inp_bi;
        *this = (copy -= -(*this));
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

            if (number[i] >= syst) {
                carry = 1;
                number[i] -= syst;
            } else
                carry = 0;
        }
    }
    return *this;
}

BigInt &BigInt::operator-=(const BigInt &inp_bi) {
    if (inp_bi.sign == '-')
        *this += (-inp_bi);
    else if (this->sign == '-')
        *this = (-((-*this) += inp_bi));
    else if (*this < inp_bi) {
        BigInt copy = inp_bi;
        *this = -(copy -= *this);
    } else {
        int carry = 0;
        int max_len = (int) this->number.size();
        for (int i = 0; (i < max_len || carry != 0); i++) {
            if (i < inp_bi.number.size())
                this->number[i] -= carry + inp_bi.number[i];
            else
                this->number[i] -= carry;

            if (this->number[i] < 0) {
                carry = 1;
                this->number[i] += syst;
            } else
                carry = 0;
        }
    }
    del_lead_zeros(*this);
    return *this;
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
    this->number = res;
    del_lead_zeros(*this);
    return *this;
}

BigInt BigInt::abs(const BigInt &inp_bi) {
    BigInt copy = inp_bi;
    copy.sign = '+';
    return copy;
}

BigInt BigInt::bin_search(const BigInt &tmp, const BigInt &divider) {
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
    BigInt divisible = *this, divider = abs(inp_bi);
    BigInt zero_res(0);

    if (inp_bi.number[0] == 0 && inp_bi.number.size() == 1)
        throw std::invalid_argument("Division by zero");

    if (abs(divisible) < divider) {
        *this = zero_res;
        return *this;
    }
    BigInt res, cur, quotient;
    res.number.resize(this->number.size());

    for (int i = (int) this->number.size() - 1; i >= 0; i--) {
        cur.number.insert(cur.number.begin(), this->number[i]);
        del_lead_zeros(cur);
        quotient = bin_search(cur, divider);
        res.number[i] = quotient.number[0];
        cur -= (quotient * divider);
    }
    this->number = res.number;
    this->sign = (this->sign == inp_bi.sign) ? '+' : '-';
    del_lead_zeros(*this);
    return *this;
}

BigInt &BigInt::operator%=(const BigInt &inp_bi) {
    BigInt div = *this / inp_bi;
    *this -= div * inp_bi;
    return *this;
}

std::string dec_to_bin(BigInt dec_num, char sign) { //return reversed bin notation
    if (sign == '-')
        dec_num--;
    BigInt zero(0), bin(2);
    std::string result;
    if (dec_num == zero) {
        result.push_back('0');
        return result;
    }
    while (dec_num > zero) {
        result.push_back(char((dec_num % bin).operator int() + '0'));
        dec_num /= bin;
    }
    return result;
}

std::string completion(std::string dec_num, char sign, int max_len) {
    for (int i = 0; i < max_len; i++)
        if (dec_num.size() == i)
            dec_num.push_back(sign == '+' ? '0' : '1');
        else if (sign == '-')
            dec_num[i] = ((dec_num[i] == '1') ? '0' : '1');   //inverse bits
    return dec_num;
}

BigInt BigInt::bin_to_dec(const std::string &bin_num, char sign) {
    BigInt result(0), one(1), bin(2);
    if (sign == '+')
        for (char c: bin_num) {
            if (c == '1')
                result += one;
            one *= bin;
        }
    else {
        for (char c: bin_num) {
            if (c == '0')
                result += one;
            one *= bin;
        }
        result++;
    }
    result.sign = sign;
    return result;
}

BigInt &BigInt::operator|=(const BigInt &inp_bi) {
    std::string bin_num_1 = dec_to_bin(abs(*this), this->sign);
    std::string bin_num_2 = dec_to_bin(abs(inp_bi), inp_bi.sign);
    int max_len = (int) std::max(bin_num_1.length(), bin_num_2.length());
    bin_num_1 = completion(bin_num_1, this->sign, max_len);
    bin_num_2 = completion(bin_num_2, inp_bi.sign, max_len);
    std::string result;
    for (int i = 0; i < max_len; i++)
        result.push_back(((bin_num_1[i] == '1') || (bin_num_2[i] == '1')) ? '1' : '0');
    this->sign = (this->sign == '-' || inp_bi.sign == '-') ? '-' : '+';
    *this = bin_to_dec(result, this->sign);
    del_lead_zeros(*this);
    return *this;
}

BigInt &BigInt::operator^=(const BigInt &inp_bi) {
    std::string bin_num_1 = dec_to_bin(abs(*this), this->sign);
    std::string bin_num_2 = dec_to_bin(abs(inp_bi), inp_bi.sign);
    int max_len = (int) std::max(bin_num_1.length(), bin_num_2.length());
    bin_num_1 = completion(bin_num_1, this->sign, max_len);
    bin_num_2 = completion(bin_num_2, inp_bi.sign, max_len);
    std::string result;
    for (int i = 0; i < max_len; i++)
        result.push_back((bin_num_1[i] == bin_num_2[i]) ? '0' : '1');
    this->sign = (this->sign == inp_bi.sign) ? '+' : '-';
    *this = bin_to_dec(result, this->sign);
    del_lead_zeros(*this);
    return *this;
}

BigInt &BigInt::operator&=(const BigInt &inp_bi) {
    std::string bin_num_1 = dec_to_bin(abs(*this), this->sign);
    std::string bin_num_2 = dec_to_bin(abs(inp_bi), inp_bi.sign);
    int max_len = (int) std::max(bin_num_1.length(), bin_num_2.length());
    bin_num_1 = completion(bin_num_1, this->sign, max_len);
    bin_num_2 = completion(bin_num_2, inp_bi.sign, max_len);
    std::string result;
    for (int i = 0; i < max_len; i++)
        result.push_back(((bin_num_1[i] == '1') && (bin_num_2[i] == '1')) ? '1' : '0');
    this->sign = (this->sign == '-' && inp_bi.sign == '-') ? '-' : '+';
    *this = bin_to_dec(result, this->sign);
    del_lead_zeros(*this);
    return *this;
}

BigInt BigInt::operator+() const {
    return *this;
}

BigInt BigInt::operator-() const {
    BigInt copy = *this;
    copy.sign = (copy.sign == '+') ? '-' : '+';
    return copy;
}

bool BigInt::operator>(const BigInt &inp_bi) const {
    if (this->sign != inp_bi.sign)
        return (this->sign == '+');
    else if (this->number.size() > inp_bi.number.size())
        return (this->sign == '+');
    else if (this->number.size() < inp_bi.number.size())
        return (this->sign == '-');
    for (int i = (int) this->number.size() - 1; i >= 0; i--)
        if (this->number[i] != inp_bi.number[i]) {
            if (this->sign == '+')
                return (this->number[i] > inp_bi.number[i]);
            return (this->number[i] < inp_bi.number[i]);
        }
    return false;
}

bool BigInt::operator==(const BigInt &inp_bi) const {
    if (this->number.size() != inp_bi.number.size() || this->sign != inp_bi.sign)
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
    return !((*this > inp_bi) || (*this == inp_bi));
}

bool BigInt::operator>=(const BigInt &inp_bi) const {
    return !(*this < inp_bi);
}

BigInt::operator int() const {
    unsigned long long res;
    res = (this->number.size() == 1) ? number[0] : ((long long) number[1] * syst + (long long) number[0]);
    if (res <= INT_MAX)
        return (this->sign == '+') ? (int) res : (int) (-1 * res);
    else
        throw std::invalid_argument("Number is bigger than int");
}

BigInt::operator std::string() const {
    std::stringstream str;
    str << *this;
    return str.str();
}

size_t BigInt::size() const {
    return (this->number.size() + 1);
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

BigInt operator%(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res %= inp_bi_2;
    return res;
}

BigInt operator^(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res ^= inp_bi_2;
    return res;
}

BigInt operator&(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res &= inp_bi_2;
    return res;
}

BigInt operator|(const BigInt &inp_bi_1, const BigInt &inp_bi_2) {
    BigInt res = inp_bi_1;
    res |= inp_bi_2;
    return res;
}

std::ostream &operator<<(std::ostream &o, const BigInt &inp_bi) {
    BigInt copy = inp_bi;
    if (copy.sign == '-')
        o << copy.sign;
    //std::reverse(copy.number.begin(), copy.number.end());
    o << copy.number[copy.number.size() - 1];
    //o.fill('0');               // should I return old char ?
    for (int i = (int) copy.number.size() - 2; i >= 0; i--)
        o << std::setw(9) << std::setfill('0') << copy.number[i];
    return o;
}