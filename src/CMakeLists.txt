add_library(
  automata_lib
  grid.c
  input.c
  gifgen/code_table.c
  gifgen/lzw.c  
  gifgen/gifgen.c
  gifgen/colour_table.c
  model/conway.c
  model/model.c
)
add_executable(automata main.c)
target_link_libraries(automata automata_lib m)
