include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(test_lzw test_lzw.c)

target_link_libraries(test_lzw cmocka automata_lib)

add_test(NAME test_lzw COMMAND test_lzw)
