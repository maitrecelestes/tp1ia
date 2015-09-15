#include "Banker.h"

bool Banker::HandleMessage(const Telegram& msg)
{
  return b_pStateMachine->HandleMessage(msg);
}


void Banker::Update()
{
  SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);

  b_iThirst += 1;
  
  b_pStateMachine->Update();
}


bool Banker::Thirsty()const
{
  if (b_iThirst >= ThirstLevelBanker){return true;}

  return false;
}

bool Banker::Fatigued()const
{
  if (b_iFatigue > TirednessThresholdBanker)
  {
    return true;
  }

  return false;
}


banker::banker(void)
{
}


banker::~banker(void)
{
}
