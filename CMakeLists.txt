cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(Set)

# Define padrão de compilação
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adiciona o executável e os arquivos de código-fonte
add_executable(set
    main.cpp
    Set.hpp
    Node.hpp
)