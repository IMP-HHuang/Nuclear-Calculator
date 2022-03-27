#ifndef DATA_H
#define DATA_H

//  data.h   读取存储核素信息的文件，匹配并存储数据
//#pragma once

#include <string>
#include <fstream>
#include<iostream>

using namespace std;

class data
{
	public:
		data();
		string name[150];   //核素名称
		double mass[150][350];  //核素质量  第一维是质子数Z，第二维是质量数A
		double error[150][350];
		bool flag[150][350];
};
#endif
