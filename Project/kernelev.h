#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "event.h"
#include "PCB.h"

class KernelEv{
public:
	IVTNo ivtno;
	int value;
	PCB *blocked, *created;
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void wait();
	void signal();
};



#endif /* KERNELEV_H_ */
