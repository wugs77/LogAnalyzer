#include"LogEntry.h"

#include<iostream>
#include<string>
using namespace std;

//初始化类成员
LogEntry::LogEntry(string time,string lev,string msg){
    timestamp=time;
    level=lev;
    message=msg;
}

//获取时间
string LogEntry::getter_time(){
    return timestamp;
}
//获取等级
string LogEntry::getter_level() const{
    return level;
}
//获取消息
string LogEntry::getter_msg() const{
    return message;
}

//打印日志
void LogEntry::print(){
    cout<<timestamp<<" "<<level<<" "<<message<<endl;
}

//判断是否为错误日志
bool LogEntry::isError() const{
    return level=="ERROR";
}
//判断当前日志条是否有效
bool LogEntry::isValid() const{
    if(timestamp.empty()||
       level.empty()||
       message.empty())
    {
        return false;
    }

    if(level != "TRACE"&&
       level != "DEBUG"&&
       level != "INFO"&&
       level != "WARN"&&
       level != "ERROR"&&
       level != "FATAL"){
        return false;
    }
    
    if(timestamp.size()!=19){
        return false;
    }

    if(timestamp[4]!='-'||
        timestamp[7]!='-'||
        timestamp[10]!=' '||
        timestamp[13]!=':'||
        timestamp[16]!=':'){
            return false;
        }
    for(size_t i=0;i<timestamp.size();++i){
        //跳过空格
        if(i==4||i==7||i==10||i==13||i==16){
            continue;
        }

        if(timestamp[i]<'0'||timestamp[i]>'9'){
            return false;
        }
    }
    
    int year=stoi(timestamp.substr(0,4));
    int month=stoi(timestamp.substr(5,2));
    int day = stoi(timestamp.substr(8, 2));
    int hour = stoi(timestamp.substr(11, 2));
    int minute = stoi(timestamp.substr(14, 2));
    int second = stoi(timestamp.substr(17, 2));

    if (year < 1 || month < 1 || month > 12 ||
        hour > 23 || minute > 59 || second > 59) {
        return false;
    }

    // 5. 检查当月实际天数，包括闰年二月
    int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool leapYear =
        (year % 400 == 0) ||
        (year % 4 == 0 && year % 100 != 0);

    if (leapYear) {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }

    return true;
}