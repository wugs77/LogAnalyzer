#设置源文件库
file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
#添加库
add_library(log_core STATIC ${SRC})
#链接头文件库
target_include_directories(log_core PUBLIC ${HEAD_PATH})