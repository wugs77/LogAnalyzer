#include<iostream>
#include<exception>
#include<fstream>
#include<stdexcept>

#include"LogReader.h"
#include"LogAnalyzer.h"
using namespace std;

int main(int args,char* argv[]){

    try{
        if(args!=2){
            throw invalid_argument("参数数量错误");
        }

        string filename=argv[1];

        LogReader reader(filename);

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