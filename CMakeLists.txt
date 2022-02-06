cmake_minimum_required(VERSION 3.17)
project(uMario VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${uMario_SOURCE_DIR}/CMake")
set(BIN_DIR ${uMario_SOURCE_DIR}/bin)
include(ConfigFlags)
include(WarningSettings)
include(CPM)
include(Config)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

CPMAddPackage("gh:eyalamirmusic/cpp_data_structures#main")

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR})

file(COPY Resources DESTINATION .)
file(GLOB_RECURSE uMario_SOURCES "Source/*.cpp")

add_executable (uMario ${uMario_SOURCES})

target_link_libraries(uMario
        PRIVATE
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_MIXER_LIBRARY}
        ea_recommended_config_flags
        ea_data_structures)

target_include_directories(uMario PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Source)

install(TARGETS uMario RUNTIME DESTINATION ${BIN_DIR})
