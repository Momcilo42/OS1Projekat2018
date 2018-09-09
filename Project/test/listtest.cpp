#include "test.h"

void tst_list()
{
	lista = new List();
	PCB *tst;
	ListItem *itm;
	for(int i = 0; i < 10; i++){
		tst = new PCB();
		lista->add(tst);
	}
	itm = lista->head;
	while(itm != 0) {cout<<itm->content->id<<endl; itm = itm->next;}
	tst = lista->get(8);
	lista->remove(8);
	cout<<"IZBACEN ID:"<<tst->id<<endl;
	delete tst;
	itm = lista->head;
	while(itm != 0) {cout<<itm->content->id<<endl; itm = itm->next;}
	delete lista;
	cout<<"Happy end"<<endl;
}
