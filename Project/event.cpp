#include "event.h"
#include "global.h"
#include "kernelev.h"

Event::Event(IVTNo ivtNo)
{
	lock
	this->myImpl = new KernelEv(ivtNo);
	unlock
}

Event::~Event()
{
	delete this->myImpl;
}

void Event::wait()
{
	lock
	this->myImpl->wait();
	unlock
}

void Event::signal()
{
	lock
	this->myImpl->signal();
	unlock
}
