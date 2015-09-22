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
	SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	i++;
	if(i==1)
  cout << "\n" << GetNameOfEntity(pBarman->ID()) << ": " << "The saloon is now opened, don't forget that no fight is allowed!";
}

void BarmanGlobalState::Exit(Barman* pBarman)
{
  
}

bool BarmanGlobalState::OnMessage(Barman* pBarman, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_ImThirsty:	
   {
	SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout <<"\n" << GetNameOfEntity(pBarman->ID()) << ": " << "There you go young thirsty man, something for you to drink!";
	return true;
   }
	case  Msg_IWannaFight:
   {
	SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	 cout << "\n" << GetNameOfEntity(pBarman->ID()) << ": " << "How dare you fighting in my saloon. Imma wipe your ass and kick you outta there";
	 return true;
   }
   }
  return false;
}



BarmanOwnedStates::BarmanOwnedStates(void)
{
}


BarmanOwnedStates::~BarmanOwnedStates(void)
{
}
