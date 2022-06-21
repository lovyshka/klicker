cmake_minimum_required(VERSION 3.20)
project(klicker)

set(CMAKE_CXX_STANDARD 23)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics window system audio)


add_executable(klicker main.cpp)
target_link_libraries(klicker PUBLIC  sfml-graphics sfml-audio sfml-window sfml-system)

enable_testing()
add_subdirectory(doctest)

add_executable(klicker_tst tst/test.cpp)
target_link_libraries(klicker_tst PUBLIC doctest sfml-graphics sfml-audio sfml-window sfml-system)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/openal32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/audio DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Fonts/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Fonts/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/graphics/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/graphics/)