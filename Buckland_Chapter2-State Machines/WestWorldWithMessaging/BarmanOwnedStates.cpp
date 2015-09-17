#include "BarmanOwnedStates.h"
#include "Barman.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif
int i=0;
//-----------------------------------------------------------------------Global state

BarmanGlobalState* BarmanGlobalState::Instance()
{
  static BarmanGlobalState instance;

  return &instance;
}

void BarmanGlobalState::Enter(Barman* pBarman)
{
	

    
}

void BarmanGlobalState::Execute(Barman* pBarman)
{
	i++;
	if(i==1)
  cout << "\n" << GetNameOfEntity(pBarman->ID()) << ": " << "Le bar est ouvert, je rappelle que les bagarres sont interdites au sein de l'établissement !!!";
}

void BarmanGlobalState::Exit(Barman* pBarman)
{
  
}

bool BarmanGlobalState::OnMessage(Barman* pBarman, const Telegram& msg)
{
  return false;
}



BarmanOwnedStates::BarmanOwnedStates(void)
{
}


BarmanOwnedStates::~BarmanOwnedStates(void)
{
}
