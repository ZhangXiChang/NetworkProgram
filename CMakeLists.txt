#Cmake最低版本
cmake_minimum_required(VERSION 3.23.0)

#项目名称
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)#设置当前目录名为目标名
project(PROJECT_NAME)

#子项目
add_subdirectory(client)
add_subdirectory(server)
