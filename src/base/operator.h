#ifndef OPERATOR_H
#define OPERATOR_H

namespace SNODE{

class Operator{
public:
	Operator(unsigned long oper):oper_(oper){
	}
private:
	unsigned long oper_;
};

}

#endif