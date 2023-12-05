#include "number.h"

void ErrorHandler() {
    std::cerr << "Undefined Behaviour";
    exit(EXIT_FAILURE);
}

bool GetSign(const int2023_t number) {
    if ((number.number[252] >> (sizeof(number.number[252]) * 8 - 1)) & 1) {
        return true;
    }
    return false;
}

int GetIndex(const int2023_t number) {
    for (int i = int2023_t::kLength-1; i >= 0; --i) {
        if (number.number[i]!=0) {
            return i;
        }
    }
    return 0;
}

int max(int a, int b) {
    if (a >= b) {
        return a;
    }
    return b;
}

int2023_t from_int(int32_t i) {
    int2023_t num;
    bool is_negative = false;
    if (i<0) {
        is_negative = true;
        i = -i;
    }
    for (int j = 0; j < int2023_t::kLength; ++j) {
        num.number[j] = i % int2023_t::kBase;
        i /= int2023_t::kBase;
    }
    if (is_negative) {
        num = -num;
    }
    return num;
}

int2023_t from_string(const char* buff) {
    int2023_t result;
    int2023_t base = from_int(10);
    int i = 0;
    bool is_negative = false;
    if (buff[0] == '-') {
        ++i;
        is_negative = true;
    }
    for (; i < strlen(buff); ++i) {
        if (isdigit(buff[i])) {
            result = result * base + from_int(buff[i] - '0');
        } else {
            ErrorHandler();
        }
    }
    if (is_negative) {
        result = -result;
    }
    return result;
}

int2023_t GetAbsoluteValue(const int2023_t& number) {
    if (GetSign(number)) {
        return -number;
    }
    return number;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    if (GetSign(lhs)) {
        if (GetSign(rhs)) {
            return -(-lhs + (-rhs));
        }
        return rhs - (-lhs);
    } else if(GetSign(rhs)) {
        return lhs - (-rhs);
    }
    int carry = 0;
    int temporary = 0;
    int2023_t result;
    int max_index = max(GetIndex(lhs), GetIndex(rhs));
    for (int i = 0; i <= max_index || carry; ++i) {
        temporary = lhs.number[i] + carry + rhs.number[i];
        result.number[i] = lhs.number[i] + carry + rhs.number[i];
        carry = temporary >= int2023_t::kBase;
        if (carry != 0) {
            result.number[i] = temporary - int2023_t::kBase;
        }
    }
    return result;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    if (GetSign(rhs)) {
        return lhs + (-rhs);
    } else if (GetSign(lhs)) {
        return -(-lhs + rhs);
    } else if (lhs < rhs) {
        return -(rhs - lhs);
    }
    int carry = 0;
    int temporary = 0;
    int2023_t result;
    int max_index = max(GetIndex(lhs), GetIndex(rhs));
    for (size_t i = 0; i <= max_index || carry; ++i) {
        temporary = lhs.number[i] - carry - rhs.number[i];
        result.number[i] = lhs.number[i] - carry - rhs.number[i];
        carry = temporary < 0;
    }
    return result;
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;
    int2023_t absolute_lhs = GetAbsoluteValue(lhs);
    int2023_t absolute_rhs = GetAbsoluteValue(rhs);
    int max_index = max(GetIndex(lhs), GetIndex(rhs));
    for (int i = 0; i <= max_index; ++i) {
        int carry = 0;
        for (int j = 0; j <= max_index || carry; ++j) {
            long long current = result.number[i + j] + absolute_lhs.number[i] * 1LL * absolute_rhs.number[j] + carry;
            result.number[i + j] = current % int2023_t::kBase;
            carry = current / int2023_t::kBase;
        }
    }
    if (GetSign(result)) {
        ErrorHandler();
    }
    bool is_negative = !(GetSign(lhs) == GetSign(rhs));
    if (is_negative && result != from_int(0)) {
        result = -result;
    }
    return result;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result = from_int(0) ,current_value;
    int2023_t absolute_lhs = GetAbsoluteValue(lhs), absolute_rhs = GetAbsoluteValue(rhs);
    if (absolute_rhs == from_int(0)){
        ErrorHandler();
    }
    int max_index = max(GetIndex(absolute_lhs), GetIndex(absolute_rhs));
    for (int i = max_index; i >= 0 ; --i) {
        int left = -1, right = int2023_t::kBase;
        while (left + 1 < right)
        {
            result.number[i] = (left + right) / 2;
            current_value = result * absolute_rhs;
            if (GetSign(current_value)) {
                right = result.number[i];
            }
            if (current_value == lhs){
                return result;
            } else if (current_value > absolute_lhs) {
                right = result.number[i];
            }
            else {
                left = result.number[i];
            }
        }
        result.number[i] = left;
    }
    bool is_negative = (GetSign(lhs) == GetSign(rhs));
    if (!is_negative && result != from_int(0)) {
        result = -result;
    }
    return result;
}

int2023_t operator~(const int2023_t& number) {
    int2023_t result;
    for (int i = 0; i < int2023_t::kLength; ++i) {
        result.number[i] = ~number.number[i];
    }
    return result;
}

int2023_t operator-(const int2023_t& number) {
    int2023_t result;
    result = ~number;
    result.number[0] += 1;
    return result;
}

int2023_t operator*(const int2023_t& lhs, const int& rhs) {
    int2023_t result;
    int r = 0;
    for (int i = 0; i < int2023_t::kLength || r; i++)
    {
        result.number[i] = lhs.number[i] * rhs + r;
        r = result.number[i] / int2023_t::kBase;
        result.number[i] -= r * int2023_t::kBase;
    }
    return result;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
    if (GetSign(lhs)!=GetSign(rhs))
    {
        return false;
    }
    int max_index = max(GetIndex(lhs), GetIndex(rhs));
    for (int i = 0; i <= max_index; i++) {
        if (lhs.number[i] != rhs.number[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    if (lhs == rhs) {
        return false;
    }
    return true;
}

bool operator<(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t negative = from_int(-1);
    int max_index = max(GetIndex(lhs), GetIndex(rhs));
    if (lhs == rhs) {
        return false;
    }
    if (GetSign(lhs)) {
        if (GetSign(rhs)) {
            return (negative * lhs) < (negative * rhs);
        }
        return true;
    }
    if (GetSign(rhs)) {
        return false;
    }
    for (int i = max_index; i >= 0; --i) {
        if (lhs.number[i]!=rhs.number[i]) {
            return lhs.number[i] < rhs.number[i];
        }
    }
    return false;
}

bool operator<=(const int2023_t& lhs, const int2023_t& rhs) {
    if (lhs < rhs || lhs == rhs) {
        return true;
    }
    return false;
}

bool operator>(const int2023_t& lhs, const int2023_t& rhs) {
    if (!(lhs <= rhs)) {
        return true;
    }
    return false;
}

bool operator>=(const int2023_t& lhs, const int2023_t& rhs) {
    if (lhs > rhs || lhs == rhs) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
    int2023_t result = value;
    if (GetSign(value)) {
        stream << '-';
        result = -value;
    }
    int max_index = GetIndex(value);
    for (int i = max_index; i >= 0; --i) {
        stream << static_cast<unsigned int>(value.number[i]);
    }
    return stream;
}
