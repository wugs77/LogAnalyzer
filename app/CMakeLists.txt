#创建可执行程序
add_executable(app main.cpp)

#链接日志分析库
target_link_libraries(app PRIVATE log_core)

# 设置 MinGW 编译器的字符编码
if(MINGW)
    target_compile_options(app PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
    )
endif()