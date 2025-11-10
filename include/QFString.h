#pragma once

#include <string>
#include <type_traits>

// TODO: investigate using different char types:
// char8_t, char16_t, char32_t
template <std::size_t N, typename char_t = char>
class QFString {
public:
    QFString() { clear(); }

    QFString(const QFString& rhs) { copy(rhs); }

    QFString(QFString&& rhs) { copy(rhs); }

public:
    QFString& operator=(const QFString& rhs) {
        copy(rhs);
        return *this;
    }

    QFString& operator=(QFString&& rhs) {
        copy(rhs);
        return *this;
    }

    bool operator==(const std::string& rhs) {
        // Negative value if lhs appears before rhs in lexicographical order.
        // Zero if lhs and rhs compare equal.
        // Positive value if lhs appears after rhs in lexicographical order.
        return std::strcmp(buffer, rhs.c_str()) == 0;
    }

    bool operator==(const QFString& rhs) { return strcmp(buffer, rhs.c_str()) == 0; }

    bool operator==(const char_t* rhs) { return strcmp(buffer, rhs) == 0; }

public:
    static constexpr std::size_t capacity() noexcept {
        static_assert(N >= 1, "capacity cannot be negative");
        // always include null term at end of string
        return (N - 1ull);
    }

    void clear() {
        auto ptr = buffer;
        // set all chars to zero in do while loop
        do {
            *ptr++ = 0;
        } while (ptr != (buffer + capacity()));
    }

    std::size_t size() const noexcept {
        // number of characters in the string
        auto ptr = buffer;
        // get first part of byte
        while (((*ptr & 0xff) != 0) && (ptr != (buffer + capacity()))) {
            ptr++;
        }
        return ptr - buffer;
    }

    bool empty() const noexcept {
        return size() == 0ull;
    }

    std::basic_string<char_t> string() const noexcept {
        // array decays to cstr_type
        // https://en.cppreference.com/w/cpp/string/basic_string/basic_string.html
        // Constructs a string with the contents of the range [s, s + count)
        return std::basic_string<char_t>(buffer, size());
    }

    const char_t* c_str() const noexcept { return buffer; }

    template <typename... Ti>
    void format(const char_t* fmt, Ti&&... ti) & noexcept {
        // int snprintf( char* restrict buffer, size_t bufsz,
        //           const char* restrict format, ... );
        // Writes the results to a character string buffer. At most bufsz - 1 characters are written. The resulting
        // character string will be terminated with a null character, unless bufsz is zero. If bufsz is zero, nothing is
        // written and buffer may be a null pointer, however the return value (number of bytes that would be written not
        // including the null terminator) is still calculated and returned.
        std::snprintf(buffer, N, fmt, std::forward<Ti>(ti)...);
    }

    template <typename... Ti>
    QFString<N, char_t>&& format(const char_t* fmt, Ti&&... ti) && noexcept {
        std::snprintf(buffer, N, fmt, std::forward<Ti>(ti)...);
        return std::move(*this);
    }

private:
    void copy(QFString&& rhs) noexcept {
        for (auto i = 0ull; i < rhs.capacity(); i++) {
            this->buffer[i] = rhs.buffer[i];
        }
    }

    void copy(const QFString& rhs) noexcept {
        for (auto i = 0ull; i < rhs.capacity(); i++) {
            this->buffer[i] = rhs.buffer[i];
        }
    }

private:
    char_t buffer[N];
};