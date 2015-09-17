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


std::ofstream os;

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

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Bob->Update();
    Elsa->Update();
	Mathieu->Update();
	Roger->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete Mathieu;
  delete Roger;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}
