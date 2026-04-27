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

#ifndef TESTER_APP_HH
#define TESTER_APP_HH

#include <unordered_map>
#include <string>

#include <taskflow/taskflow.hpp>

#include <base/application.hh>
#include <base/gentree.hh>

namespace tester {

    struct test_report {
        std::string graph_name{};
        std::int32_t node_start{};

        double dfs_time_ms{};
        double bfs_time_ms{};

        double graph_density{};
        std::int32_t graph_nodes{};
        std::int32_t graph_edges{};
    };

    class tester_app : public base::application {
    public:
        auto run( const std::int32_t argc, char **argv ) -> std::int32_t override;

    private:
        auto load_graphs() -> void;
        auto run_tests() -> void;

        tf::Executor m_Executor{};

        std::unordered_map<std::string, base::gentree<std::int32_t>> m_graphs{};
        std::unordered_map<std::string, test_report> m_reports{};
    };
}



#endif //TESTER_APP_HH
