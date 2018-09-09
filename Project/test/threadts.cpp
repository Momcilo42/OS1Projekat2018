#include "test.h"

class test : public Thread {
public:
	test() : Thread(1024, 40){}
};

void writelista(){	//preko head
	ListItem *current = lista->head;
	cout<<"Lista:"<<endl;
	while(current != 0) {cout<<current->content->id<<endl; current = current->next;}
	cout<<"------------------------"<<endl;
}

void tst_thread()
{
	lista = new List();
	ListItem *current;
	test *t;
	PCB *p;
	for(int i = 0; i < 10; i++){
		t = new test();
		t->start();
	}
	writelista();
	p = lista->get(4);
	cout<<p->id<<endl;
	delete lista;
	cout<<"!!!THE END!!!";
}
