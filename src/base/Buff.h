#ifndef BUFF_H
#define BUFF_H

#include <assert.h>
#include <string>
#include <memory>

namespace SNODE{
	const int INTSIZE = sizeof(int);
	const int BUFFMAXSIZE = 1024*8;
	class Buff{
	public:
		Buff():lpos_(0),rpos_(0){}

		void read(std::string& s){
			int sz = 0;
			read(sz);
			s.append(buff_+lpos_, sz);
			lpos_+=sz;
		}
		void read(int& i){
			i = 0;
			//i = (i|buff_[lpos_++]);i = (i<<8);
			//i = (i|buff_[lpos_++]);i = (i<<8);
			//i = (i|buff_[lpos_++]);i = (i<<8);
			//i = (i|buff_[lpos_++]);

			i = buff_[lpos_+3] & 0xff | (buff_[lpos_+2] & 0xff) << 8 | (buff_[lpos_+1] & 0xff) << 16| (buff_[lpos_] & 0xff) << 24;
			lpos_+=4;
			if(lpos_ == rpos_){
				lpos_=0;rpos_=0;
			}
		}

		void write(int& i){
			buff_[rpos_] = (i>>24)&0xff; rpos_++;
			buff_[rpos_] = (i>>16)&0xff; rpos_++;
			buff_[rpos_] = (i>>8)&0xff; rpos_++;
			buff_[rpos_] = (i)&0xff; rpos_++;
		}

		void write(std::string& s){
			int sz = s.size();
			write(sz);
			memcpy(buff_+rpos_, s.data(), sz);
			rpos_ += sz;
		}

		void preappend(int i){
			int sz = rpos_-lpos_;
			if(sz > 0){
				memmove(buff_+lpos_+INTSIZE, buff_+lpos_, sz);
				int tmpr = rpos_;
				int tmpl = lpos_;
				rpos_ = lpos_;
				write(i);
				rpos_ = tmpr+INTSIZE;
				lpos_ = tmpl;
			}else
				write(i);
		}

		void append(char* str, int sz){
			memcpy(buff_+rpos_, str, sz);
			rpos_ += sz;
		}

		template<typename T>
		Buff& operator >> (T& t){
			write(t);
			return *this;
		}
		template<typename T>
		Buff& operator << (T& t){
			read(t);
			return *this;
		}

		bool isComplete(){
			if(curSize_ == 0)
				return false;

			if( size() >= INTSIZE)
				read(curSize_);
			return curSize_>=size();
		}

		void reset(){
			lpos_ = 0;
			rpos_ = 0;
			curSize_=0;
		}

		char* data(){
			return buff_;
		}

		int size(){
			return rpos_-lpos_;
		}

	private:
		char buff_[BUFFMAXSIZE];
		int lpos_;
		int rpos_;
		int curSize_;
	};
}

#endif