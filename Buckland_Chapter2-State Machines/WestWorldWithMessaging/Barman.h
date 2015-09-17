#ifndef BARMAN_H
#define BARMAN_H
//------------------------------------------------------------------------
//
//  Name:   Barman.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "BarmanOwnedStates.h"
#include "fsm/StateMachine.h"

struct Telegram;


class Barman : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Barman>* bar_pStateMachine;

  location_type   bar_Location;

 


public:

  Barman(int id):bar_Location(saloon),
                     BaseGameEntity(id)
                                        
  {
    //set up the state machine
    bar_pStateMachine = new StateMachine<Barman>(this);


    bar_pStateMachine->SetGlobalState(BarmanGlobalState::Instance());
  }

  ~Barman(){delete bar_pStateMachine;}


  //this must be implemented
  void          Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  StateMachine<Barman>* GetFSM()const{return bar_pStateMachine;}

  //----------------------------------------------------accessors
  location_type Location()const{return bar_Location;}
  void          ChangeLocation(location_type loc){bar_Location=loc;}

   
};

#endif

