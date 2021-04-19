#include <iostream>
#include "fstream"
#include "vector"
#include "string.h"
#include "dirent.h"

#include <sys/stat.h>

#define MODE (S_IRWXU | S_IRWXG | S_IRWXO)


using namespace std;



int fileNameFilter(const struct dirent *cur) {
    std::string str(cur->d_name);
    if (str.find(".pcd") != std::string::npos) {
        return 1;
    }
    return 0;
}
//创建文件夹
void mk_dir(string path) {
    //string path1="/home/wayne/CLionProjects/zjg/data4/";
    int nl = 0;
    for (int i = 0; i < 10; ++i) {
        string s12 = to_string(nl);
        string spath = path + s12;

        mkdir(spath.c_str(), MODE);
        nl++;
    }
}
//将找到的pcd文件的路径放到vector中，移动文件到指定文件夹
void Path(string path1,string path2)
{
    std::vector<std::string> ret;
    struct dirent **namelist;
    int n = scandir(path1.c_str(), &namelist, fileNameFilter, alphasort);

    for (int i = 0; i < n; ++i)
    {
        std::string filePath(namelist[i]->d_name);
        ret.push_back(filePath);
        free(namelist[i]);
    }
    free(namelist);
    //创建文件夹
    mk_dir(path2);

//  移动文件
    int nn=0;
    for (int i = 0; i < ret.size(); ++i) {

        if (i%50==0 && i/50>0)
        {
            nn++;
        }

        //移动文件
        string ss = to_string(nn);
        ss +="/";
        string command ="cp ";
        command += "../data1/";
        command += ret.at(i);
        command += " ";
        command += "../data2/";
        command += ss;
        command += ret.at(i);

        system((char *)command.c_str());
        //删除原文件
        string command1 ="rm ";
        command1 += "../data1/";
        command1 += ret.at(i);
        system((char *)command1.c_str());

    }






}



int main() {


    string path1="/home/wayne/CLionProjects/zjg/test05/data1/";
    string path2="/home/wayne/CLionProjects/zjg/test05/data2/";
    Path(path1,path2);


    return 0;
}
