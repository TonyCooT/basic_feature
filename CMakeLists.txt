cmake_minimum_required(VERSION 3.0.2)
project(basic_feature)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation message_runtime)

add_service_files(FILES check_step.srv)

generate_messages(DEPENDENCIES std_msgs)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(game src/game.cpp)
target_link_libraries(game ${catkin_LIBRARIES})