#ifndef ENTITY_H
#define ENTITY_H
//------------------------------------------------------------------------
//
//  Name:   BaseGameEntity.h
//
//  Desc:   Base class for a game object
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include "messaging/Telegram.h"
#include <mutex>
#include "EntityNames.h"
#include "Time/CrudeTimer.h"


class BaseGameEntity
{

private:

  //every entity must have a unique identifying number
  int          m_ID;

  //this is the next valid ID. Each time a BaseGameEntity is instantiated
  //this value is updated
  static int  m_iNextValidID;

  //this must be called within the constructor to make sure the ID is set
  //correctly. It verifies that the value passed to the method is greater
  //or equal to the next valid ID, before setting the ID and incrementing
  //the next valid ID
  void SetID(int val);
  std::mutex mu;


public:

  BaseGameEntity(int id)
  {
    SetID(id);
  }


  
  void shared_print(int id, std::string msg){
		std::lock_guard<std::mutex> guard(mu);
		std::cout << "\n" << GetNameOfEntity(id) << msg;
	}
  void shared_print(int id, std::string msg, int wealth){
		std::lock_guard<std::mutex> guard(mu);
		std::cout << "\n" << GetNameOfEntity(id) << msg << wealth;
	}
  void shared_printTelegram(int id){
		std::lock_guard<std::mutex> guard(mu);
		std::cout << "\nMessage handled by " << GetNameOfEntity(id) << " at time: " << Clock->GetCurrentTime();
	}

  virtual ~BaseGameEntity(){}

  //all entities must implement an update function
  virtual void  Update()=0;

  //all entities can communicate using messages. They are sent
  //using the MessageDispatcher singleton class
  virtual bool  HandleMessage(const Telegram& msg)=0;

  int           ID()const{return m_ID;}  
};



#endif


