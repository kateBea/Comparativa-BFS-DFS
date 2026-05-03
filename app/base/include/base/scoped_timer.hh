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

#ifndef SCOPED_TIMER_HH
#define SCOPED_TIMER_HH

#include <chrono>
#include <string>
#include <string_view>

namespace base {

    class scoped_timer {
    public:
        explicit scoped_timer(std::string_view name = "", bool print_on_destruction = false);
        ~scoped_timer();

        // Non-copyable
        scoped_timer(const scoped_timer&) = delete;
        scoped_timer& operator=(const scoped_timer&) = delete;

        // Movable
        scoped_timer(scoped_timer&&) noexcept = default;
        scoped_timer& operator=(scoped_timer&&) noexcept = default;

        // Timer management
        auto reset() -> void;
        auto elapsed() const -> double;
        auto name() const -> std::string_view;


    private:
        std::string m_name{};
        bool m_print_on_destruction{};
        std::chrono::high_resolution_clock::time_point m_start{};
    };

#define START_SCOPED_TIMER(name) base::scoped_timer timer##__LINE__{name, true};

}



#endif //SCOPED_TIMER_HH
