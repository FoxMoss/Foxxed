add_executable(foxxed
 main.cpp 
)

include(FetchContent)
FetchContent_Declare(
  CLI11 
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.5.0
)
FetchContent_MakeAvailable(CLI11)

FetchContent_Declare(
  isocline
  GIT_REPOSITORY https://github.com/daanx/isocline.git
  GIT_TAG v1.0.9
)

FetchContent_MakeAvailable(isocline)

target_link_libraries(foxxed CLI11::CLI11 isocline)

add_custom_command(TARGET foxxed POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Add clangd to the src directory")

install(TARGETS foxxed DESTINATION bin)
