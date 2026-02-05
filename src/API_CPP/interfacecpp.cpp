#include "../../include/API_CPP/interfacecpp.h"

#include <cstring>

void cpp_say_hello()
{
    std::cout << "this is hello from cpp" << std::endl;
}

// void TLog(const std::string &x)
// {
// 	std::cout << "file:" << __FILE__ << " line:" << __LINE__ << " >>" << x;
// }

std::vector<std::string> textSplit(const char * str,char slice){
    std::vector<std::string> result;
    auto b=0;
    auto e=0;
    auto max=strlen(str);
    for(auto i=0;i<max;i++){
        if(str[i] == slice){
            e=i;
            if(b !=e){
                result.push_back(std::string(str+b,e-b));
            }
            b=e+1;
        }
        if(i==max-1){
            if(b!=max){
                result.push_back(std::string(str+b,max-b));
            }
        }
    }
    return result;
}

std::string trim(const std::string &str){
    if(str.empty()){
        return str;
    }
    auto start =str.find_first_not_of(" \t\n\r\f\v");
    if(start == std::string::npos){
        return "";
    }
    auto end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start,end-start +1);

}


int64_t read_line(int64_t offset, char *from, int64_t len, std::string &rt)
{
	int64_t word_count = 0;
	char ch = 0;
	for (int64_t i = offset; i < len; i++)
	{
		ch = from[i];
		word_count++;
		if (ch == '\n')
		{
			break;
		}
	}
	// rt = (std::string(from + offset, word_count));//使用assign,避免不必要的构造与拷贝
    rt.assign(from+offset,word_count);//assign代表赋值,重复使用rt内存
	return word_count;
}