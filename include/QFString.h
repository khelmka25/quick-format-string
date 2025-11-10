#pragma once

#include <string>
#include <type_traits>

template <std::size_t N, typename char_t = char>
class QFString {
public:
    static constexpr std::size_t capacity() noexcept {
        static_assert(N >= 1, "capacity cannot be negative");
        // always include null term at end of string
        return (N - 1ull);
    }

    QFString() {
        clear();
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

    std::basic_string<char_t> string() const noexcept {
        // array decays to cstr_type
        // https://en.cppreference.com/w/cpp/string/basic_string/basic_string.html
        // Constructs a string with the contents of the range [s, s + count)
        return std::basic_string<char_t>(buffer, size());
    }

    char_t* c_str() const noexcept { return buffer; }

    template <typename... Ti>
    void format(const char_t* format, Ti&& ...ti) & noexcept {
        // int snprintf( char* restrict buffer, size_t bufsz,
        //           const char* restrict format, ... );
        // Writes the results to a character string buffer. At most bufsz - 1 characters are written. The resulting
        // character string will be terminated with a null character, unless bufsz is zero. If bufsz is zero, nothing is
        // written and buffer may be a null pointer, however the return value (number of bytes that would be written not
        // including the null terminator) is still calculated and returned.
        std::snprintf(buffer, N, format, std::forward<Ti>(ti)...);
    }

    template <typename... Ti>
    QFString<N, char_t>&& format(const char_t* format, Ti&& ...ti) && noexcept {
        std::snprintf(buffer, N, format, std::forward<Ti>(ti)...);
        return std::move(*this);
    }

private:
    char_t buffer[N];
};