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
  StateMachine<Banker>*  m_pStateMachine;
  
  location_type         m_Location;


  //the higher the value, the thirstier the miner
  int                   m_iThirst;

  //the higher the value, the more tired the miner
  int                   m_iFatigue;

public:

  Banker(int id):m_Location(shack_banker),
                          m_iThirst(0),
                          m_iFatigue(0),
                          BaseGameEntity(id)
                               
  {
    //set up state machine
    m_pStateMachine = new StateMachine<Banker>(this);
    
    m_pStateMachine->SetCurrentState(GoHomeBankerAndSleepTilRested::Instance());

    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE BANKER */
  }

  ~Banker(){delete m_pStateMachine;}

  //this must be implemented
  void Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  
  StateMachine<Banker>* GetFSM()const{return m_pStateMachine;}


  
  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}
    

  bool          Fatigued()const;
  void          DecreaseFatigue(){m_iFatigue -= 1;}
  void          IncreaseFatigue(){m_iFatigue += 1;}

  bool          Thirsty()const; 
  void          BuyAndDrinkAWhiskey(){m_iThirst = 0;}

};



#endif
