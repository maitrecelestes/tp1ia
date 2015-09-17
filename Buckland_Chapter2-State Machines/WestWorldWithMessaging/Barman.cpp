#include "Barman.h"


bool Barman::HandleMessage(const Telegram& msg)
{
  return bar_pStateMachine->HandleMessage(msg);
}


void Barman::Update()
{
  //set text color to green
  SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
 
  bar_pStateMachine->Update();
}