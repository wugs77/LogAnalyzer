#include<iostream>
#include<exception>
#include<fstream>
#include<stdexcept>

#include"LogReader.h"
#include"LogAnalyzer.h"
using namespace std;

int main(){
    try{
        LogReader reader("logs/system.log");

        auto logs=reader.read();

        int invalidCount=reader.getInvalidCount();

        size_t totallines=logs.size()+static_cast<size_t>(invalidCount);

        LogAnalyzer analyzer;
        analyzer.analyze(logs,totallines);

        analyzer.printResult();
        cout<<"非法日志的数量："<<invalidCount<<endl;

        ofstream report("output/report.txt");

        if(!report.is_open()){
            throw runtime_error("无法打开报告文件：output/report.txt");
        }

        analyzer.printResult(report);
        report<<"非法日志的数量："<<invalidCount<<endl;

        report.close();

        if(!report){
            throw runtime_error("报告文件为写入失败");
        }

        cout<<"报告已保存到 output/report.txt"<<endl;
    }
    catch(const exception&e){
        cerr<<"程序运行失败："<<e.what()<<endl;
        return 1;
    }
}