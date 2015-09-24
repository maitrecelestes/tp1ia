#include "MinerOwnedStates.h"
#include "fsm/State.h"
#include "Miner.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

bool fight=false;
//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
  static EnterMineAndDigForNugget instance;

  return &instance;
}


void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
	
	
  //if the miner is not already located at the goldmine, he must
  //change location to the gold mine
  if (pMiner->Location() != goldmine)
  {
	pMiner->shared_print(pMiner->ID(), ": Walkin' to the goldmine");
    pMiner->ChangeLocation(goldmine);
  }
}


void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{  
  //Now the miner is at the goldmine he digs for gold until he
  //is carrying in excess of MaxNuggets. If he gets thirsty during
  //his digging he packs up work for a while and changes state to
  //gp to the saloon for a whiskey.
  pMiner->AddToGoldCarried(1);

  pMiner->IncreaseFatigue();
  
	
  pMiner->shared_print(pMiner->ID(), ": Pickin' up a nugget");
  //if enough gold mined, go and put it in the bank
  if (pMiner->PocketsFull())
  {
    pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
  }

  if (pMiner->Thirsty())
  {
    pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
  }
}


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
	
	pMiner->shared_print(pMiner->ID(), ": Ah'm leavin' the goldmine with mah pockets full o' sweet gold");
}


bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
  static VisitBankAndDepositGold instance;

  return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{  
  //on entry the miner makes sure he is located at the bank
  if (pMiner->Location() != bank)
  {
	 
	pMiner->shared_print(pMiner->ID(), ": Goin' to the bank. Yes siree");
    pMiner->ChangeLocation(bank);

	//let the banker know he is at the bank
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pMiner->ID(),        //ID of sender
                              ent_Mathieu,            //ID of recipient
                              Msg_ImatBank,   //the message
                              NO_ADDITIONAL_INFO);    
  }
}


void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
  //deposit the gold
  pMiner->AddToWealth(pMiner->GoldCarried());
    
  pMiner->SetGoldCarried(0);
  
	
	pMiner->shared_print(pMiner->ID(), ": Depositing gold. Total savings now: ", pMiner->Wealth());
  

  //wealthy enough to have a well earned rest?
  if (pMiner->Wealth() >= ComfortLevel)
  {
	  pMiner->shared_print(pMiner->ID(), ": WooHoo! Rich enough for now. Back home to mah li'lle lady");
      
    pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());      
  }

  //otherwise get more gold
  else 
  {
    pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }
}


void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
	
	
	pMiner->shared_print(pMiner->ID(), ": Leavin' the bank");
 
}


bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
  if (pMiner->Location() != shack)
  {
	  
	
	pMiner->shared_print(pMiner->ID(), ": Walkin' home");
    
    pMiner->ChangeLocation(shack); 

    //let the wife know I'm home
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pMiner->ID(),        //ID of sender
                              ent_Elsa,            //ID of recipient
                              Msg_HiHoneyImHome,   //the message
                              NO_ADDITIONAL_INFO);    
  }
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{ 
  //if miner is not fatigued start to dig for nuggets again.
  
	
  if (!pMiner->Fatigued())
  {
	 pMiner->shared_print(pMiner->ID(), ": All mah fatigue has drained away. Time to find more gold!");
     pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }

  else 
  {
    //sleep
    pMiner->DecreaseFatigue();
	pMiner->shared_print(pMiner->ID(), ": ZZZZ... ");
  } 
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{ 
}


bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg)
{
  

   switch(msg.Msg)
   {
   case Msg_StewReady:

	 pMiner->shared_printTelegram(pMiner->ID());
    


	 pMiner->shared_print(pMiner->ID(), ": Okay Hun, ahm a comin'!");
     pMiner->GetFSM()->ChangeState(EatStew::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
  static QuenchThirst instance;

  return &instance;
}

void QuenchThirst::Enter(Miner* pMiner)
{
  if (pMiner->Location() != saloon)
  {    
    pMiner->ChangeLocation(saloon);
	
	

	 pMiner->shared_print(pMiner->ID(), ": Boy, ah sure is thusty! Walking to the saloon");
  }
  pMiner->shared_print(pMiner->ID(), ": Roger! Im thusty! Gimme somethin Right Naw!");

  Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pMiner->ID(),        //ID of sender
                              ent_Roger,            //ID of recipient
                              Msg_ImThirsty,   //the message
                              NO_ADDITIONAL_INFO);  
  Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pMiner->ID(),        //ID of sender
                              ent_Mathieu,            //ID of recipient
                              Msg_ImThirsty,   //the message
                              NO_ADDITIONAL_INFO);  
}

void QuenchThirst::Execute(Miner* pMiner)
{
  pMiner->BuyAndDrinkAWhiskey();
  
  
  pMiner->shared_print(pMiner->ID(), ": That's mighty fine sippin' liquer"); 
  pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());  
}


void QuenchThirst::Exit(Miner* pMiner)
{ 
	if(!fight)
	{
		
		pMiner->shared_print(pMiner->ID(), ": Leaving the saloon, feelin' good"); 
	}
	else
		fight=false;
}


bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
	switch(msg.Msg)
	{
	case  Msg_ImThirsty:
   {
	   fight=true;
    
	 pMiner->shared_print(pMiner->ID(), ": Come at me Banker, I'm ready!"); 
	 pMiner->shared_print(pMiner->ID(), ": Imma gonna punch ya so hard even your dog won't recognise ya!"); 
	 pMiner->GetFSM()->ChangeState(Fighting::Instance());
	 return true;
   }
   }
  return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
  static EatStew instance;

  return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
  pMiner->shared_print(pMiner->ID(), ": Smells Reaaal goood Elsa!"); 
}

void EatStew::Execute(Miner* pMiner)
{
  pMiner->shared_print(pMiner->ID(), ": Tastes real good too!"); 
  pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* pMiner)
{ 
  pMiner->shared_print(pMiner->ID(), ": Thankya li'lle lady. Ah better get back to whatever ah wuz doin'"); 
}


bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}


// Now the banker wants to fight with the miner

Fighting* Fighting::Instance()
{
  static Fighting instance;
  
  return &instance;
}

void Fighting::Enter(Miner* pMiner)
{
  Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pMiner->ID(),        //ID of sender
                              ent_Mathieu,            //ID of recipient
                              Msg_ImThirsty,   //the message
                              NO_ADDITIONAL_INFO);    
  
}

void Fighting::Execute(Miner* pMiner)
{
	
  pMiner->BuyAndDrinkAWhiskey();
  
  pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());  
   
}


void Fighting::Exit(Miner* pMiner)
{ 
	 
	 pMiner->shared_print(pMiner->ID(), ": I won't miss you next time, banker!"); 
}



bool Fighting::OnMessage(Miner* pMiner, const Telegram& msg)
{
	return false;
}

