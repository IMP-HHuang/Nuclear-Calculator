//  data.cpp   读取存储核素信息的文件，匹配并存储数据
//#pragma once
//#ifndef DATA_H
//#define DATA_H

#include <string>
#include <fstream>
#include<iostream>
#include "data.h"

using namespace std;
/*
class data
{
	public:
		data();
		string name[150];   //核素名称
		double mass[150][350];  //核素质量  第一维是质子数Z，第二维是质量数A
		double error[150][350];
		bool flag[150][350];
};
*/
data::data()
{
	for(int i=0; i<150; i++)
	{
		for(int j = 0; j<350; j++)
		{
				error[i][j] = 0;
				flag[i][j] = 0;
				mass[i][j] = 1000.0;
		}
	}	
	//读取核素名称文件
	ifstream filein_name("./data/name.txt");
	if(!filein_name)
	{
		cout<<"Cannot open name.txt"<<endl;
		return;
	}
	for(int i=1; i<=120; i++)
	{
		filein_name>>name[i];
		if(filein_name.eof()) break;
	}
//	cout<<"name.txt"<<endl;
	filein_name.close();
	//读取核素质量文件
	ifstream filein_mass("./data/mass.txt");
	if(!filein_mass)
	{
		cout<<"Cannot open mass.txt"<<endl;
		return;
	}
	int Zn = 0;
	int A_min = 0, A_max = 0; 
	string temp;
	while(!filein_mass.eof())
	{
		filein_mass>>Zn>>A_min>>A_max;
//		getline(filein_mass, temp);  //读取并丢弃文件中的无用信息
		for(int i=A_min; i<=A_max; i++)
		{
			filein_mass>>mass[Zn][i];
//			cout<<Zn<<"  "<<i<<"   "<<mass[Zn][i]<<endl;
		}
		for(int i=A_min; i<=A_max; i++)
		{
			filein_mass>>error[Zn][i];
//			cout<<Zn<<"  "<<i<<"   "<<error[Zn][i]<<endl;
		}
		for(int i=A_min; i<=A_max; i++)
		{
			filein_mass>>flag[Zn][i];   //1---Experiment 0 Theory
//			cout<<Zn<<"  "<<i<<"   "<<flag[Zn][i]<<endl;
		}
	}
//	cout<<"mass.txt"<<endl;
	filein_mass.close();
}
//#endif
