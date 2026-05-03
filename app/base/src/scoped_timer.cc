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


#include <chrono>
#include <iostream>

#include <base/scoped_timer.hh>
#include <base/logger.hh>

namespace base {

    scoped_timer::scoped_timer(std::string_view name, bool print_on_destruction)
        : m_name{ std::move(name) },
          m_print_on_destruction{ print_on_destruction },
          m_start{ std::chrono::high_resolution_clock::now() } {}

    scoped_timer::~scoped_timer() {
        const auto end{ std::chrono::high_resolution_clock::now() };
        const auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(end - m_start).count() };

        if (m_print_on_destruction) {
            LOG_INFO( "[Timer] {} took {} ms", (m_name.empty() ? "Scope" : m_name), duration / 1000.0 );
        }
    }

    auto scoped_timer::reset() -> void {
        m_start = std::chrono::high_resolution_clock::now();
    }

    auto scoped_timer::elapsed() const -> double {
        const auto end{ std::chrono::high_resolution_clock::now() };
        const auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(end - m_start).count() };
        return duration / 1000.0;
    }

    auto scoped_timer::name() const -> std::string_view {
        return m_name;
    }
}// namespace base