#pragma once
#include <cinttypes>
#include <iostream>


struct int2023_t {
    uint8_t number[253] = {0};
    const static int kBase = 256;
    const static int kLength = 253;
};

static_assert(sizeof(int2023_t) <= 253, "Size of int2023_t must be no higher than 253 bytes");

bool GetSign(const int2023_t number);

int GetIndex(const int2023_t number);

int max(int a, int b);

int2023_t from_int(int32_t i);

int2023_t from_string(const char* buff);

int2023_t GetAbsoluteValue(const int2023_t& number);

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator~(const int2023_t& number);

int2023_t operator-(const int2023_t& number);

int2023_t operator* (const int2023_t& lhs, const int& rhs);

bool operator==(const int2023_t& lhs, const int2023_t& rhs);

bool operator!=(const int2023_t& lhs, const int2023_t& rhs);

bool operator<(const int2023_t& lhs, const int2023_t& rhs);

bool operator<=(const int2023_t& lhs, const int2023_t& rhs);

bool operator>(const int2023_t& lhs, const int2023_t& rhs);

bool operator>=(const int2023_t& lhs, const int2023_t& rhs);

std::ostream& operator<<(std::ostream& stream, const int2023_t& value);
