
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


#ifndef BASE_UTILITY_HH
#define BASE_UTILITY_HH

#include <string>
#include <vector>
#include <initializer_list>

#include <portable-file-dialogs.h>

namespace base {
    struct FileDialogPair {
        std::string description{};
        std::string pattern{};
    };

    [[nodiscard]] inline auto open_file_dialog( const FileDialogPair &filter ) -> std::string {
        auto result = pfd::open_file( filter.description, filter.pattern ).result();
        if ( !result.empty() ) {
            return result[0];
        }
        return {};
    }

    [[nodiscard]] inline auto open_file_dialog( std::initializer_list<FileDialogPair> filters ) -> std::string {
        std::vector<std::string> filter_vec;
        for ( const auto &filter: filters ) {
            filter_vec.push_back( filter.description );
            filter_vec.push_back( filter.pattern );
        }
        auto result = pfd::open_file( "Select a file", "", filter_vec ).result();
        if ( !result.empty() ) {
            return result[0];
        }
        return {};
    }

    [[nodiscard]] inline auto open_folder_dialog() -> std::string {
        auto result{ pfd::select_folder( "Select a folder", pfd::path::home() ).result() };
        if ( !result.empty() ) {
            return result.c_str();
        }
        return {};
    }

}

#endif //BASE_UTILITY_HH