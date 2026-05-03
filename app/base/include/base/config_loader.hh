// MIT License
//
// Copyright (c) 2026 ケイト
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#ifndef CONFIG_LOADER_HH
#define CONFIG_LOADER_HH

#include <cstdint>
#include <string>

/**
 * Can disable exceptions in
 * compiler flags and/or explicitly disable the library's use of them by setting the option
 * #TOML_EXCEPTIONS to 0. In either case, the parsing functions return a
 * toml::parse_result instead of a toml::table:
 *
 *  only necessary if you've left them enabled in your compiler #include <toml++/toml.hpp>
 * */
#define TOML_EXCEPTIONS 0

#include <any>
#include <filesystem>

#include <toml++/toml.hpp>

#include <ankerl/unordered_dense.h>

namespace gen {

    class config {
    public:
        virtual ~config() = default;

        virtual auto load( const std::filesystem::path& filePath ) -> void = 0;

        template<typename T>
        auto Get( const std::string& key, const T& defaultValue = {} ) -> T {
            const auto it{ m_data.find( key ) };
            if ( it != m_data.end() ) {
                if ( auto* val{ std::any_cast<T>( &it->second ) } ) {
                    return *val;
                }
            }

            return defaultValue;
        }

    protected:
        ankerl::unordered_dense::map<std::string, std::any> m_data{};
    };

} // namespace gen

#endif // CONFIG_LOADER_HH
