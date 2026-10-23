#include"LogAnalyzer.h"
#include<iostream>
#include<algorithm>

using namespace std;

LogAnalyzer::LogAnalyzer():totalCount(0){
}

void LogAnalyzer::analyze(const vector<LogEntry>&logs,size_t totallines){
    totalCount=totallines;
    levelCount.clear();
    errorCount.clear();

    for(const LogEntry& log: logs){
        string level=log.getter_level();
        levelCount[level]++;

        if(log.isError()){
            string message=log.getter_msg();
            errorCount[message]++;
        }
    }
}

vector<pair<string,int>> LogAnalyzer::getTopError(){
    vector<pair<string,int>>errors(errorCount.begin(),errorCount.end());

    sort(errors.begin(),errors.end(),[](const pair<string,int>&a,const pair<string,int>&b){
        if(a.second!=b.second)
        {
            return a.second>b.second;
        }

        return a.first<b.first;
        }
    );
    
    if(errors.size()>3){
        errors.resize(3);
    }

    return errors;
}

void LogAnalyzer::printResult(ostream&out){
    out<<"========== 日志报告分析 =========="<<endl;
    out<<"文件总行数："<<totalCount<<endl;

    out<<"\n========== 日志等级统计 ========="<<endl;

    for(const auto&item:levelCount){
        out<<item.first<<"："<<item.second<<endl;
    }

    int totalErrors=0;
    auto it =levelCount.find("ERROR");
    
    if(it!=levelCount.end()){
        totalErrors=it->second;
    }

    out<<"\nERROR 日志总次数："<<totalErrors<<endl;
    out<<"\n========= Top 3 错误 ==========="<<endl;
    
    auto topErrors=getTopError();

    if (topErrors.empty())
    {
        out << "没有错误日志。" << endl;
    }
    else
    {
        for (size_t i = 0; i < topErrors.size(); ++i)
        {
            out << i + 1 << ". "
                 << topErrors[i].first
                 << " —— "
                 << topErrors[i].second
                 << " 次"
                 << endl;
        }
    }

    out << "=================================" << endl;
}
