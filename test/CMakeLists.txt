include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(test_lzw test_lzw.c)
add_executable(test_colour_table test_colour_table.c)

target_link_libraries(test_lzw cmocka automata_lib)
target_link_libraries(test_colour_table cmocka automata_lib)

add_test(NAME test_lzw COMMAND test_lzw)
add_test(NAME test_colour_table COMMAND test_colour_table)