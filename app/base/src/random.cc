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


#include <random>
#include <stdexcept>
#include <limits>
#include <cstdint>
#include <numeric>
#include <limits>

#include <base/random.hh>

namespace base {

    [[nodiscard]] inline auto get_seed() -> std::random_device& {
        thread_local std::random_device seed{};
        return seed;
    }

    static auto next_int( std::random_device& seed ) -> std::int32_t {
        thread_local std::mt19937_64 mt{ seed() };

        return std::uniform_int_distribution<std::int32_t>{
            (std::numeric_limits<std::int32_t>::min)(),
            (std::numeric_limits<std::int32_t>::max)(),
        }(mt);
    }

    static auto next_real( std::random_device& seed ) -> double {
        thread_local std::mt19937_64 mt{ seed() };

        return std::uniform_real_distribution<double>{
            (std::numeric_limits<double>::min)(),
            (std::numeric_limits<double>::max)(),
        }(mt);
    }

    auto next_int( ) -> std::int32_t {
        return next_int( get_seed() );
    }

    auto next_real( ) -> double {
        return next_real( get_seed() );
    }

    static auto next_int( std::int32_t lowerBound, std::int32_t upperbound, auto& seed ) -> std::int32_t {
        if ( lowerBound > upperbound )
            throw std::runtime_error( "Invalid range for random integer generation" );

        thread_local std::mt19937 mt{ seed() };
        return std::uniform_int_distribution{ lowerBound, upperbound }( mt );
    }

    auto next_int( std::int32_t lowerBound, std::int32_t upperbound ) -> std::int32_t {
        return next_int( lowerBound, upperbound, get_seed() );
    }

    static auto next_real( double lowerBound, double upperbound, auto& seed ) -> double {
        if ( lowerBound > upperbound )
            throw std::runtime_error( "Invalid range for random real generation" );

        thread_local std::mt19937 mt{ seed() };
        return std::uniform_real_distribution{ lowerBound, upperbound }( mt );
    }

    auto next_real( double lowerBound, double upperbound ) -> double {
        return next_real( lowerBound, upperbound, get_seed() );
    }
}