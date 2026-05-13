#include <CLI/CLI.hpp>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <format>
#include <fstream>
#include <isocline.h>
#include <memory>
#include <string>
#include <utility>

void init_project(CLI::App *init_subcommand) {
  std::unique_ptr<char> project_name;

  char *project_name_raw;
  while ((project_name_raw = ic_readline("Project Name (CamelCase)")) == NULL ||
         strlen(project_name_raw) == 0) {
    ic_println("[ansi-yellow]Input error");
    if (project_name_raw == NULL) {
      return;
    }
  }
  project_name = std::unique_ptr<char>(project_name_raw);

  std::unique_ptr<char> executable_name;

  char *executable_name_raw;
  while ((executable_name_raw = ic_readline("Executable (snake_case)")) ==
             NULL ||
         strlen(executable_name_raw) == 0) {
    ic_println("[ansi-yellow]Input error");
    if (executable_name_raw == NULL) {
      return;
    }
  }
  executable_name = std::unique_ptr<char>(executable_name_raw);

  std::string root_cmake_body = std::format(
    #include "root_cmake.h"
    , project_name.get());

  const auto project_path = std::filesystem::current_path().append(std::string(project_name.get()) + "/");
  if(std::filesystem::exists(project_path)){
    std::filesystem::remove_all(project_path);
  }
  std::filesystem::create_directories(project_path);

  const auto root_cmake_path = project_path / "CMakeLists.txt";
  std::ofstream root_cmake_stream(root_cmake_path);
  root_cmake_stream << root_cmake_body;
  root_cmake_stream.close();

  const auto gitignore_path = project_path / ".gitignore";
  std::ofstream gitignore_stream(gitignore_path);
  gitignore_stream << 
    #include "gitignore.h"
  ;
  gitignore_stream.close();

  const auto clangd_path = project_path / ".clangd";
  std::ofstream clangd_stream(clangd_path);
  clangd_stream << 
    #include "root_clangd.h"
  ;
  clangd_stream.close();

  auto src_path = project_path / "src/";
  std::filesystem::create_directories(src_path);

  std::string src_cmake_body = std::format(
    #include "src_cmake.h"
    , executable_name.get());

  auto src_cmake_path = src_path / "CMakeLists.txt";
  std::ofstream src_cmake_stream(src_cmake_path);
  src_cmake_stream << src_cmake_body;
  src_cmake_stream.close();

  auto main_path = src_path / "main.cpp";
  std::ofstream main_stream(main_path);
  main_stream << 
    #include "init_main.h"
  ;
  main_stream.close();

  ic_printf("[ansi-green]Initiated %s\n", project_path.c_str());
}

int main(int argc, char *argv[]) {
  CLI::App app{"The missing C++ project manager"};
  argv = app.ensure_utf8(argv);

  CLI::App *init_subcommand = app.add_subcommand("init", "Make a new project");
  app.require_subcommand();

  try {
    app.parse(argc, argv);
  } catch (const CLI ::ParseError &e) {
    return app.exit(e);
  };

  if (app.got_subcommand(init_subcommand)) {
    init_project(init_subcommand);
  }
  return 0;
}
