#include "test.h"

class testt : public Thread
{
public:
	testt() : Thread(1024, 20){}
	~testt(){
		waitToComplete();
	}
	void run()
	{
		cout<<"starta "<<running->id<<endl;
		int count = 0;
		Thread::sleep(10);
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

void tst_sleep()
{
	PCB *p;
	testt *t;
	ListItem *itm;
	int i;
	for(i = 0; i<5; i++){t = new testt(); t->start();}
	//dispatch();
	itm = sleeping->head;
	while(itm != 0) {cout<<itm->content->id<<endl; itm = itm->next;}
}
