//===========================================================================//
//   Project: Projekat iz Operativnih sistema 1
//   File:    user.h
//   Date:    Jun 2018
//   Parametri za pokretanje:
//        arg[1] - velicina bafera
//        arg[2] - Broj niti
//        arg[3] - TIME_SLICE za proizvodjace
//===========================================================================//



#ifndef _OS1_USER_H_
#define _OS1_USER_H_


//---------------------------------------------------------------------------//
//  Signalizira kraj za Producer i Consumer preko Keyevent
//---------------------------------------------------------------------------//
extern volatile int theEnd;
int userMain (int argc, char* argv[]);

//---------------------------------------------------------------------------//
#endif  // _OS1_USER_H_

