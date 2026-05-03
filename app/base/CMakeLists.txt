cmake_minimum_required(VERSION 3.22)

project(base)

# ======================================
# Language requirements
# ======================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../vendor/unordered_dense/ unordered_dense)
add_subdirectory(../vendor/portable-file-dialogs/ portable-file-dialogs)

file(GLOB SOURCE_FILES src/*.cc)

add_library(base STATIC ${SOURCE_FILES})

# ======================================
# Project directories
# ======================================
target_include_directories(base PRIVATE ./include/)

# ======================================
# Vendor include directories
# ======================================
target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/taskflow)
target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/tomlplusplus/include)
target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/unordered_dense/include)
target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/portable-file-dialogs)

# ======================================
# Vendor links
# ======================================
target_link_libraries(base unordered_dense::unordered_dense)