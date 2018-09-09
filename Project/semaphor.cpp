#include "semaphor.h"
#include "global.h"
#include "kernelsm.h"

Semaphore::Semaphore(int init)
{
	lock
	this->myImpl = new KernelSem(init);
	unlock
}

Semaphore::~Semaphore()
{
	lock
	delete this->myImpl;
	unlock
}

int Semaphore::wait(int toBlock)
{
	lock
	int i = this->myImpl->wait(toBlock);
	unlock
	return i;
}

void Semaphore::signal()
{
	lock
	this->myImpl->signal();
	unlock
}

int Semaphore::val() const
{
	lock
	int i = this->myImpl->value;
	unlock
	return i;
}
