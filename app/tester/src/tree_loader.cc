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


#include <fstream>
#include <sstream>
#include <cstdint>

#include <tree_loader.hh>
#include <base/logger.hh>


namespace tester {

    auto tree_loader::load_from_file(const std::filesystem::path uri) -> base::gentree<int> {
        base::gentree<std::int32_t> tree{};

        // Aquí iría la lógica para leer el archivo y cargar los datos en el árbol.
        // Por ahora, simplemente devolvemos un árbol vacío.
        std::ifstream file{ uri };

        if (!file.is_open()) {
            LOG_ERROR("No se pudo abrir el archivo: " + uri.string());
            return tree;
        }

        std::string line{};

        bool reading_edges{ false };

        while (std::getline(file, line)) {

            // saltar lineas vacias
            // aunque no es algo que se espera
            if (line.empty()) {
                continue;
            }

            // las lineas con edges tienes 3 caracteres o más (ej: "1 2")
            reading_edges = line.size() >= 3;

            std::istringstream iss{ line };
            std::int32_t a{};
            std::int32_t b{};

            if (!reading_edges) {
                iss >> a;
                tree.add_vertex(a);
            } else if (iss >> a >> b) {
                tree.add_edge(a, b);
            }
        }

        return tree;
    }
}