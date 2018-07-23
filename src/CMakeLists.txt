add_library(
  automata_lib
  grid.c
  gifgen/code_table.c
  gifgen/lzw.c  
  gifgen/gifgen.c
)
add_executable(automata main.c)
target_link_libraries(automata automata_lib)
