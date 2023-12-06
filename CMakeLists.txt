cmake_minimum_required(VERSION 3.22)
project(GraphAlgorithm CXX)

# Configurações Globais
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Ativar recursos de hardware específicos (opcional)
if (CMAKE_BUILD_TYPE MATCHES Release)
    # Ative instruções específicas do conjunto de instruções para o seu hardware
    add_compile_options(-march=native)

    # Ative as otimizações no modo de release
    add_compile_options(-O3)
endif()

add_subdirectory(src/app)
add_subdirectory(lib)
