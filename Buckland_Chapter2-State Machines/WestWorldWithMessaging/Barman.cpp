#include "Barman.h"


bool Barman::HandleMessage(const Telegram& msg)
{
  return bar_pStateMachine->HandleMessage(msg);
}


void Barman::Update()
{
  bar_pStateMachine->Update();
}