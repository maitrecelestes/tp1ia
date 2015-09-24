#include <fstream>
#include <time.h>
#include "Banker.h"
#include "Barman.h"
#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"
#include <thread>

std::ofstream os;

void startBob(Miner* Bob){
   for(int i = 0;i <30; i++){
	Bob->Update();
    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
   }
}
void startElsa(MinersWife* Elsa){
   for(int i = 0;i <30; i++){
	Elsa->Update();
    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
   }
}
void startMathieu(Banker* Mathieu){
   for(int i = 0;i <30; i++){
	Mathieu->Update();
    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
   }
}
void startRoger(Barman* Roger){
   for(int i = 0;i <30; i++){
	Roger->Update();
    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
   }
}
int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

   //create the banker
  Banker* Mathieu = new Banker(ent_Mathieu);

  //create the barman
  Barman* Roger= new Barman (ent_Roger);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Mathieu);
  EntityMgr->RegisterEntity(Roger);

  // create the thread
  std::thread tBob (startBob,Bob);Sleep(30);
  std::thread tElsa (startElsa,Elsa); Sleep(30);
  std::thread tMathieu(startMathieu,Mathieu); Sleep(30);
  std::thread tRoger (startRoger,Roger); Sleep(30);

	//Synchronize the thread
	tBob.join();
    tElsa.join();
    tMathieu.join();
	tRoger.join();
  

  //tidy up
  delete Bob;
  delete Elsa;
  delete Mathieu;
  delete Roger;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}
