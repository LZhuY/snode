#ifndef LOG_H
#define LOG_H

#include <iostream>

void LOG(const char* log){
	std::cout<<log<<std::endl;
}

void ERROR(const char* err){
	std::cout<<err<<std::endl;
}

void WRR(const char* wrr){
	std::cout<<wrr<<std::endl;
}

#endif