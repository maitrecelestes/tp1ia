#include "Banker.h"

bool Banker::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Banker::Update()
{
  SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);

  m_iThirst += 1;
  
  m_pStateMachine->Update();
}


bool Banker::Thirsty()const
{
  if (m_iThirst >= ThirstLevelBanker){return true;}

  return false;
}

bool Banker::Fatigued()const
{
  if (m_iFatigue > TirednessThresholdBanker)
  {
    return true;
  }

  return false;
}
