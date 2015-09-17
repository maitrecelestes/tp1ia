#ifndef BARMAN_OWNED_STATES_H
#define BARMAN_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   BarmanOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Barman class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class Barman;
struct Telegram;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class BarmanGlobalState : public State<Barman>
{  
private:
  
  BarmanGlobalState(){}

  //copy ctor and assignment should be private
  BarmanGlobalState(const BarmanGlobalState&);
  BarmanGlobalState& operator=(const BarmanGlobalState&);
 
public:

  //this is a singleton
  static BarmanGlobalState* Instance();
  
  virtual void Enter(Barman* pBarman);

  virtual void Execute(Barman* pBarman);

  virtual void Exit(Barman* pBarman);

  virtual bool OnMessage(Barman* pBarman, const Telegram& msg);
};

class BarmanOwnedStates
{
public:
	BarmanOwnedStates(void);
	~BarmanOwnedStates(void);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------

#endif