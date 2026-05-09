
add_executable(dystr_test dystr_test.c)

add_executable(byte_array_test bytearray_test.c)


target_link_libraries(dystr_test PUBLIC d_global)

target_link_libraries(byte_array_test PUBLIC d_global)