cmake_minimum_required(VERSION 3.17)
project(uMario)

set(CMAKE_CXX_STANDARD 17)
# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${uMario_SOURCE_DIR}/CMake")
set(BIN_DIR ${uMario_SOURCE_DIR}/bin)
include(ConfigFlags)
include(WarningSettings)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR})

file(COPY uNext/files DESTINATION .)

include_directories(uNext)

file(GLOB_RECURSE uMario_SOURCES "uNext/*.cpp")
add_executable (uMario ${uMario_SOURCES})

target_link_libraries(uMario
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_MIXER_LIBRARY}
        ea_recommended_config_flags)

install(TARGETS uMario RUNTIME DESTINATION ${BIN_DIR})
