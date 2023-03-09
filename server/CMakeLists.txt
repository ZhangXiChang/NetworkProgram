#目标名
get_filename_component(COMPILE_TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)#设置当前目录名为目标名

#C/C++标准
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

#链接选项
set(CMAKE_EXE_LINKER_FLAGS -static)

#输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/bin)#可执行文件目录

#源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ MAIN_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src PROJECT_SRC)
#编译目标
add_executable(${COMPILE_TARGET_NAME} ${MAIN_SRC} ${PROJECT_SRC})

#头文件
target_include_directories(${COMPILE_TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#LibHV
find_package(libhv CONFIG REQUIRED)
set(LIBHV_LIB hv_static)

#为编译目标链接库
target_link_libraries(${COMPILE_TARGET_NAME} PRIVATE
    ${LIBHV_LIB}
)
