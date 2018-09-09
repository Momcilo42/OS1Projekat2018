#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "kernelev.h"
#include<dos.h>

typedef void interrupt (*sIntr)(...);

class IVTEntry
{
public:
	static IVTEntry *IVTable[256];
	IVTNo number;
	sIntr old;
	KernelEv *event;
	IVTEntry(IVTNo number, sIntr old);
	~IVTEntry();
	void signal();
	void callOld();
};

#endif /* IVTENTRY_H_ */
