add_library(ea_recommended_warning_flags INTERFACE )

function (add_clang_warning warning)
    target_compile_options(ea_recommended_warning_flags INTERFACE "/clang:${warning}")
endfunction()

set(windowsClangWarnings
        -Wall
        -Wunreachable-code
        -Wstrict-aliasing
        -Wuninitialized
        -Wunused-parameter
        -Wconditional-uninitialized
        -Wunused-private-field
        -Wbool-conversion
        -Wextra-semi)

set (clangWarnings ${windowsClangWarnings}
        -Wshadow-all
        -Wshorten-64-to-32
        -Wconversion
        -Wsign-compare
        -Wint-conversion
        -Woverloaded-virtual
        -Wreorder
        -Wconstant-conversion
        -Wsign-conversion
        -Wzero-as-null-pointer-constant
        -Wcast-align
        -Winconsistent-missing-destructor-override
        -Wshift-sign-overflow
        -Wnullable-to-nonnull-conversion
        -Wno-missing-field-initializers
        -Wno-ignored-qualifiers
        -Wswitch-enum
        -Wpedantic)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR (CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC"))
    target_compile_options(ea_recommended_warning_flags INTERFACE "/W4")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        foreach(warning ${windowsClangWarnings})
            add_clang_warning(${warning})
        endforeach()
    endif()

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
    target_compile_options(ea_recommended_warning_flags INTERFACE ${clangWarnings})
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ea_recommended_warning_flags INTERFACE
            -Wall -Wextra -Wstrict-aliasing -Wuninitialized -Wunused-parameter
            -Wsign-compare -Wreorder -Wsign-conversion
            -Wunreachable-code -Wzero-as-null-pointer-constant -Wcast-align
            -Wno-implicit-fallthrough -Wno-maybe-uninitialized
            -Wno-missing-field-initializers -Wno-ignored-qualifiers -Wswitch-enum
            -Wpedantic)

    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "7.0.0")
        target_compile_options(ea_recommended_warning_flags INTERFACE "-Wno-strict-overflow")
    endif()
endif()
