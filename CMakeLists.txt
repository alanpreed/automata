cmake_minimum_required(VERSION 3.0)
project(automata)
add_executable(
  automata
  main.c
  grid.c
  code_table.c
  lzw.c  
  gifgen.c
)