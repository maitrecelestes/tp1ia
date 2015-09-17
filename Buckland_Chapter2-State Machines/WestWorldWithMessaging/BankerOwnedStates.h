#ifndef BANKER_OWNED_STATES_H
#define BANKER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   BankerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Banker class.
//          Note that a global state has not been implemented.
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Banker;
struct Telegram;


//------------------------------------------------------------------------
//
//  In this state the banker will walk to the bank and do his job. If he 
//  gets thirsty he'll change state to QuenchThirstBanker
//------------------------------------------------------------------------
class EnterBankAndWork : public State<Banker>
{
private:
  
  EnterBankAndWork(){}

  //copy ctor and assignment should be private
  EnterBankAndWork(const EnterBankAndWork&);
  EnterBankAndWork& operator=(const EnterBankAndWork&);
 
public:

  //this is a singleton
  static EnterBankAndWork* Instance();

  virtual void Enter(Banker* banker);

  virtual void Execute(Banker* banker);

  virtual void Exit(Banker* banker);

  virtual bool OnMessage(Banker* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  banker will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeBankerAndSleepTilRested : public State<Banker>
{
private:
  
  GoHomeBankerAndSleepTilRested(){}

  //copy ctor and assignment should be private
  GoHomeBankerAndSleepTilRested(const GoHomeBankerAndSleepTilRested&);
  GoHomeBankerAndSleepTilRested& operator=(const GoHomeBankerAndSleepTilRested&);
 
public:

  //this is a singleton
  static GoHomeBankerAndSleepTilRested* Instance();

  virtual void Enter(Banker* banker);

  virtual void Execute(Banker* banker);

  virtual void Exit(Banker* banker);

  virtual bool OnMessage(Banker* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  banker changes location to the saloon and keeps buying Whiskey until
//  his thirst is quenched. When satisfied he returns to the bank
//  and resumes his job.
//------------------------------------------------------------------------
class QuenchThirstBanker : public State<Banker>
{
private:
  
  QuenchThirstBanker(){}

  //copy ctor and assignment should be private
  QuenchThirstBanker(const QuenchThirstBanker&);
  QuenchThirstBanker& operator=(const QuenchThirstBanker&);
 
public:

  //this is a singleton
  static QuenchThirstBanker* Instance();

  virtual void Enter(Banker* banker);

  virtual void Execute(Banker* banker);

  virtual void Exit(Banker* banker);

  virtual bool OnMessage(Banker* agent, const Telegram& msg);
};

//-------------------------------------------------

class BankerFighting : public State<Banker>
{
private:
  
  BankerFighting(){}

  //copy ctor and assignment should be private
  BankerFighting(const BankerFighting&);
  BankerFighting& operator=(const BankerFighting&);
 
public:

  //this is a singleton
  static BankerFighting* Instance();

  virtual void Enter(Banker* pBanker);

  virtual void Execute(Banker* pBanker);

  virtual void Exit(Banker* pBanker);

  virtual bool OnMessage(Banker* agent, const Telegram& msg);
};

class BankerOwnedStates
{
public:
	BankerOwnedStates(void);
	~BankerOwnedStates(void);
};


#endif