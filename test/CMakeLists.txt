include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(automata_test test.c)

target_link_libraries(automata_test cmocka)

add_test(NAME automata_test COMMAND automata_test)