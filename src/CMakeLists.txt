set(MYPROJECT_SRC main.cpp)
add_executable(myproject ${MYPROJECT_SRC})

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(myproject
  PRIVATE
  project_default
  PUBLIC
  spdlog::spdlog
)

