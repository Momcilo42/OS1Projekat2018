#ifndef KERNELSM_H_
#define KERNELSM_H_

#include "semaphor.h"
#include "List.h"
#include "PCB.h"

class KernelSem{
public:
	int value;
	List *blocked; //lista blokiranih niti na semaforu
	KernelSem(int init = 1);
	~KernelSem();
	void signal();
	int wait(int toBlock);
};

#endif /* KERNELSM_H_ */
