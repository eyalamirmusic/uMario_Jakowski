add_library(ea_recommended_config_flags INTERFACE)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR (CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC"))
    target_compile_options(ea_recommended_config_flags INTERFACE
            $<IF:$<CONFIG:Debug>,/Od,/O2 /fp:fast> $<$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","MSVC">:/MP> /EHsc)
elseif((CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    target_compile_options(ea_recommended_config_flags INTERFACE
            $<IF:$<CONFIG:Debug>,-g -O0, -Ofast>)
endif()