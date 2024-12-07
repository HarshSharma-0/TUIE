#include "parser.hpp"
#include "Tokens.hpp"
#include <filesystem>

int OPEN_APP::parser(std::filesystem::path &appxml) {
  appxml /= __APP_ENTRY;
  if (std::filesystem::exists(appxml) == false) {
    return -1;
  }
  return 1;
}
