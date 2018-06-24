cmake_minimum_required(VERSION 3.0)
project(automata)
add_executable(
  automata
  main.c
  grid.c
  gifgen/code_table.c
  gifgen/lzw.c  
  gifgen/gifgen.c
)