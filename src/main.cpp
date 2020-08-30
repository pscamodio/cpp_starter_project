#include <iostream>
#include <spdlog/spdlog.h>
#include <fmt/format.h>

int main()
{
  spdlog::info("Hello {}!", "World");
  std::cout << fmt::format("Hello {}!", "World");
  return 0;
}
