#c function unit test
add_executable(dystr_test ./c_test/dystr_test.c)

add_executable(byte_array_test ./c_test/bytearray_test.c)


target_link_libraries(dystr_test PUBLIC interface_c)

target_link_libraries(byte_array_test PUBLIC interface_c)


#cpp function unit test