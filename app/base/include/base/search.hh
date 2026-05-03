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

#ifndef SEARCH_HH
#define SEARCH_HH

#include <cstdint>
#include <base/gentree.hh>

#include <ankerl/unordered_dense.h>

namespace base {

    // devuelve true si el target existe en el árbol usando BFS
    auto exists_bfs(const gentree<std::int32_t> tree, std::int32_t target) -> bool;

    // devuelve true si el target existe en el árbol usando DFS
    auto exists_dfs(const gentree<std::int32_t>& tree, std::int32_t target) -> bool;

    // devuelve -1 si no existe camino, 0 si startpoint == endpoint, o la longitud del camino entre ambos nodos usando BFS
    auto search_bfs(const gentree<std::int32_t>& tree, std::int32_t startpoint, std::int32_t endpoint) -> std::int32_t;

    // devuelve -1 si no existe camino, 0 si startpoint == endpoint, o la longitud del camino entre ambos nodos usando DFS
    auto search_dfs(const gentree<std::int32_t>& tree, std::int32_t startpoint, std::int32_t endpoint) -> std::int32_t;

    // Encuentra y muestra la red de nodos conectados a startpoint usando BFS
    auto find_network_bfs(const gentree<std::int32_t>& tree, std::int32_t startpoint) -> ankerl::unordered_dense::set<std::int32_t>;

    // Encuentra y muestra la red de nodos conectados a startpoint usando DFS
    auto find_network_dfs(const gentree<std::int32_t>& tree, std::int32_t startpoint) -> ankerl::unordered_dense::set<std::int32_t>;
}

#endif //SEARCH_HH