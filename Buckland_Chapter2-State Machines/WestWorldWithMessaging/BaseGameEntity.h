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
#include "misc/ConsoleUtils.h"


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


  // ALL THE COUT IS HERE, FOR PROTECTING THEM
 
  void shared_print(int id, std::string msg, int wealth=0){
		std::lock_guard<std::mutex> guard(mu);
		color (id);
		if (wealth==0){
			std::cout << "\n" << GetNameOfEntity(id) << msg;
		} else {
			std::cout << "\n" << GetNameOfEntity(id) << msg << wealth;
		}
	}
  void shared_printTelegram(){
		std::lock_guard<std::mutex> guard(mu);
		SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		std::cout << "Message not handled";
	}
  void shared_printTelegramWarning(int id){
		std::lock_guard<std::mutex> guard(mu);
		SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		std::cout << "\nWarning! No Receiver with ID of " << id << " found";
	}
  void shared_printTelegram(int id){
		std::lock_guard<std::mutex> guard(mu);
		SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		std::cout << "\nMessage handled by " << GetNameOfEntity(id) << " at time: " << Clock->GetCurrentTime();
	}
   void shared_printTelegram(int id, std::string msg){
		std::lock_guard<std::mutex> guard(mu);
		SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		std::cout << "\nQueued telegram ready for dispatch: Sent to " << GetNameOfEntity(id) << ". Msg is " << msg;
	}
   void shared_printTelegram(int idSender, int idReceiver, std::string msg){
		std::lock_guard<std::mutex> guard(mu);
		SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		std::cout << "\nDelayed telegram from " << GetNameOfEntity(idSender) << " recorded at time " << Clock->GetCurrentTime() << " for " << GetNameOfEntity(idReceiver) << ". Msg is "<< msg;
	}
   void shared_printTelegramInstant(int idSender, int idReceiver, std::string msg){
		std::lock_guard<std::mutex> guard(mu);
		SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		std::cout << "\nInstant telegram dispatched at time: " << Clock->GetCurrentTime()<< " by " << GetNameOfEntity(idSender) << " for " << GetNameOfEntity(idReceiver) << ". Msg is "<< msg;
	}

   

void color (int id){
	if (id==1||id==3){
		 SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	}
	if (id==0){
		 SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);
	} 
	if (id==2){
		 SetTextColor(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	}
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


