include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(test_lzw test_lzw.c)
add_executable(test_colour_table test_colour_table.c)

target_link_libraries(test_lzw cmocka automata_lib)
target_link_libraries(test_colour_table cmocka automata_lib)

add_test(NAME test_lzw COMMAND test_lzw)
add_test(NAME test_colour_table COMMAND test_colour_table)

add_test(test_lzw_valgrind valgrind
          --suppressions=../../test/valgrind.supp
          --error-exitcode=1 --read-var-info=yes
          --leak-check=full --show-leak-kinds=all
          ./test_lzw)

add_test(test_colour_table_valgrind valgrind
          --suppressions=../../test/valgrind.supp
          --error-exitcode=1 --read-var-info=yes
          --leak-check=full --show-leak-kinds=all
          ./test_colour_table)

add_test(test_full_glider_valgrind valgrind
          --suppressions=../../test/valgrind.supp
          --error-exitcode=1 --read-var-info=yes
          --leak-check=full --show-leak-kinds=all
          ../src/automata test.gif conway-glider 5 1 100 100 50)
          
add_test(test_full_random_valgrind valgrind
          --suppressions=../../test/valgrind.supp
          --error-exitcode=1 --read-var-info=yes
          --leak-check=full --show-leak-kinds=all
          ../src/automata test.gif conway-random 5 1 100 100 50)

add_test(test_full_glider_scale_valgrind valgrind
          --suppressions=../../test/valgrind.supp
          --error-exitcode=1 --read-var-info=yes
          --leak-check=full --show-leak-kinds=all
          ../src/automata test.gif conway-glider 5 2 100 100 50)
  