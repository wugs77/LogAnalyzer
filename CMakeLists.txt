cmake_minimum_required(VERSION 3.15)
project(LogAnalyzer)
#设置c++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#设置输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#设置头文件路径
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

#添加子目录
add_subdirectory(src)
add_subdirectory(app)


