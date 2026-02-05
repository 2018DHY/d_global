cmake_minimum_required(VERSION 3.1...4.1)

project(dlib)
message("---------------dlib--------------------")
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_EXTENSIONS ON)#启用C标准扩展,想用POSIX标准扩展

message("--CMAKE_C_COMPILE_FEATURES:${CMAKE_C_COMPILE_FEATURES}")
message("--C_EXTENSIONS: ${C_EXTENSIONS}")
message("--CMAKE_C_EXTENSIONS_DEFAULT:${CMAKE_C_EXTENSIONS_DEFAULT}")


set(c_path_prefix ${CMAKE_CURRENT_SOURCE_DIR}/src/API_C)
set(cpp_path_prefix ${CMAKE_CURRENT_SOURCE_DIR}/src/API_CPP)

set(interface_c_src ${c_path_prefix}/interfacec.c)

add_library(interface_c SHARED ${interface_c_src})
set_target_properties(interface_c PROPERTIES
    LINKER_LANGUAGE C
    POSITION_INDEPENDENT_CODE ON
)
if(MSVC)
    add_compile_options("/utf-8")
    target_compile_definitions(interface_c PUBLIC DLIB_EXPORT)
endif(MSVC)

get_target_property(D_CEXTENSIONS interface_c C_EXTENSIONS)
message("--D_CEXTENSIONS:${D_CEXTENSIONS}")
target_compile_definitions(interface_c PRIVATE _FILE_OFFSET_BITS=64)


set(interface_cpp_src ${cpp_path_prefix}/interfacecpp.cpp)

add_library(interface_cpp SHARED ${interface_cpp_src})
target_link_libraries(interface_cpp PUBLIC interface_c)

set(d_global_src SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/d_global.cpp)

add_library(d_global ${d_global_src})   

target_include_directories(d_global PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(d_global PUBLIC interface_cpp)