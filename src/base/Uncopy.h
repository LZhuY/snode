#ifndef UNCOPY_H
#define UNCOPY_H

namespace SNODE{

	class Uncopy{
	private:
		Uncopy(Uncopy& ori){}
		Uncopy& operator = (Uncopy& rhs){}
	};
}

#endif