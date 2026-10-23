#ifndef LOGREADER_H
#define LOGREADER_H

#include "LogEntry.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class LogReader{
private:
    string filename;//日志文件路径
    int invalidCount;//非法日志数量
    ifstream file;

public:
    //初始化文件路径
    LogReader(const string &fm);

    //读取全部日志
    vector<LogEntry>read();

    //获取非法日志数量
    int getInvalidCount();

private:
    //打开文件
    bool openfile();

    //解析单行日志
    LogEntry parseLine(const string &line);

    //处理非法日志
    void handleInvalidLine(const string&line,const string &reason);
    
};

#endif
