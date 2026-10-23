#include"LogReader.h"
#include"LogEntry.h"

#include<stdexcept>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cctype>
using namespace std;

//初始化文件路径
LogReader::LogReader(const string &fm){
    filename=fm;
    invalidCount=0;
}

//文件是否打开
bool LogReader::openfile(){

    if(!file.is_open()){
        file.clear();
        file.open(filename);
    }
    return file.is_open();
}

namespace{
    string trim(const string&text){
        size_t begin=0;
        size_t end=text.size();

        while(begin<end && isspace(static_cast<unsigned char>(text[begin]))){
            ++begin;
        }
        
        while(end>begin && isspace(static_cast<unsigned char>(text[end-1]))){
            --end;
        }

        return text.substr(begin,end-begin);
    }
}
//逐行处理
LogEntry LogReader::parseLine(const string &line){
    size_t pos1=line.find('|');

    if(pos1==string::npos){
        throw runtime_error("日志格式错误：缺少第一个分隔符");
    }

    size_t pos2=line.find('|',pos1+1);

    if(pos2==string::npos){
        throw runtime_error("日志格式错误：缺少第二个分隔符");
    }
    
    string time=trim(line.substr(0,pos1));
    string level=trim(line.substr(pos1+1,pos2-pos1-1));
    string message=trim(line.substr(pos2+1));

    LogEntry log(time,level,message);

    if(!log.isValid()){
        throw runtime_error("日志内容无效");
    }
    
    return log;
}

//处理非法日志
void LogReader::handleInvalidLine(const string&line,const string &reason){
    invalidCount++;
    
    cerr<<"发现错误日志："<<line<<endl;
    cerr<<"错误原因是："<<reason<<endl;

}



//读取全部日志
vector<LogEntry> LogReader::read(){
    invalidCount=0;

    vector<LogEntry>logs;
    if(!openfile()){
        throw runtime_error("无法打开日志："+filename);
    }

    string line;
    
    while(getline(file,line)){
        try{
            LogEntry log=parseLine(line);
            logs.push_back(log);
        }
        catch(const runtime_error&e){
            handleInvalidLine(line,e.what());
        }
    }
    file.close();
    return logs;
}

int LogReader::getInvalidCount(){
    return invalidCount;
}
