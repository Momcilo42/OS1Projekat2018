#include "kernelev.h"

KernelEv::KernelEv(IVTNo ivtNo) {
	this->ivtno = ivtNo;
	this->value = 0;
	this->blocked = 0;
	this->created = running;
	IVTEntry::IVTable[ivtNo]->event = this;
}

KernelEv::~KernelEv() {
	IVTEntry::IVTable[this->ivtno]->event = 0;
}

void KernelEv::wait() {
	if(this->created == running){
		if(this->value)this->value = 0;
		else {
			running->state = 2;
			this->blocked = running;
			dispatch();
		}
	}
}

void KernelEv::signal() {
	if(!this->blocked)this->value = 1;
	else {
		this->blocked->state = 1;
		Scheduler::put(this->blocked);
		this->blocked = 0;
	}
}
