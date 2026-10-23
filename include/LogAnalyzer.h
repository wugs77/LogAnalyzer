#ifndef LOGANALYZER
#define LOGANALYZER

#include<iostream>
#include<map>
#include<string>
#include<utility>
#include<vector>
#include<cstddef>
#include"LogEntry.h"


class LogAnalyzer{
private:
    size_t totalCount;
    map<string,int> levelCount;
    map<string,int> errorCount;

public:
    LogAnalyzer();

    void analyze(const vector<LogEntry>&logs,size_t totallines);
    vector<pair<string,int>> getTopError();
    void printResult(ostream&out =cout);
};

#endif