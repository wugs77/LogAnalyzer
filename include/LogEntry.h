#ifndef LOGENTRY_H
#define LOGENTRY_H

#include<string>
using namespace std;

class LogEntry{
private:
    string timestamp;//时间戳
    string level;//日志等级
    string message;//日志消息

public:
    //初始化日志
    LogEntry(
        string time,
        string lev,
        string msg
    );

    //获取日志
    string getter_time();
    string getter_level() const;
    string getter_msg() const;
    
    //打印日志
    void print();

    //判断日志
    bool isError() const;
    bool isValid() const;

};

#endif