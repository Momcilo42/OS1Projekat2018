#include "test.h"

class testa : public Thread
{
public:
	testa() : Thread(1024, 20){}
	~testa(){
		waitToComplete();
	}
	void run()
	{
		cout<<"starta"<<endl;
		int count = 0;
		while(1)
		{
		for(int i = 0; i < 10; i++)
			for(int j = 0; j < 5000; j++)
				for(int k = 0; k < 5000; k++);
		count++;
		if (count == 20){break;}
		cout<<"a-"<<count<<endl;
		}
		cout<<"end a"<<endl;
	}
};
class testb : public Thread
{
public:
	testb() : Thread(1024, 20){}
	~testb(){
		waitToComplete();
	}
	void run()
	{
		cout<<"startb"<<endl;
		int count = 0;
		while(1)
		{
		for(int i = 0; i < 10; i++)
			for(int j = 0; j < 5000; j++)
				for(int k = 0; k < 5000; k++);
		count++;
		if (count == 20){break;}
		cout<<"b-"<<count<<endl;
		}
		cout<<"end b"<<endl;
	}
};

void tst_kontekst()
{
	inic();
	testa *a = new testa();
	testb *b = new testb();
	a->start();
	b->start();
	delete a;
	delete b;
	restore();
}
