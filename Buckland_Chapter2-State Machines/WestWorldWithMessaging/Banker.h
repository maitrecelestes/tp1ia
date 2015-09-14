#ifndef BANKER_H
#define BANKER_H
//------------------------------------------------------------------------
//
//  Name:   Banker.h
//
//  Desc:   A class defining a banker.
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "BankerOwnedStates.h"
#include "fsm/StateMachine.h"

//class BankerState
struct Telegram;


//above this value a banker is thirsty
const int ThirstLevelBanker        = 5;
//above this value a banker is sleepy
const int TirednessThresholdBanker = 5;



class Banker : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Banker>*  b_pStateMachine;
  
  location_type         b_Location;


  //the higher the value, the thirstier the miner
  int                   b_iThirst;

  //the higher the value, the more tired the miner
  int                   b_iFatigue;

public:

  Banker(int id):b_Location(shack_banker),
                          b_iThirst(0),
                          b_iFatigue(0),
                          BaseGameEntity(id)
                               
  {
    //set up state machine
    b_pStateMachine = new StateMachine<Banker>(this);
    
    b_pStateMachine->SetCurrentState(GoHomeBankerAndSleepTilRested::Instance());

    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE BANKER */
  }

  ~Banker(){delete b_pStateMachine;}

  //this must be implemented
  void Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  
  StateMachine<Banker>* GetFSM()const{return b_pStateMachine;}


  
  //-------------------------------------------------------------accessors
  location_type Location()const{return b_Location;}
  void          ChangeLocation(location_type loc){b_Location=loc;}
    

  bool          Fatigued()const;
  int			ShowFatigue(){return b_iFatigue;}
  void          DecreaseFatigue(){b_iFatigue -= 1;}
  void          IncreaseFatigue(){b_iFatigue += 1;}

  bool          Thirsty()const; 
  void          BuyAndDrinkAWhiskey(){b_iThirst = 0;}

};



#endif
