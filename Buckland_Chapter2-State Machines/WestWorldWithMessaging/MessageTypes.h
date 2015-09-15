#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_ImatBank,
  Msg_ImThirsty,
  Msg_IWannaFight
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

	case 2:
    
    return "ImatBank";

	case 3:
    
    return "ImThirsty";

	case 4:
    
    return "IWannaFight";

  default:

    return "Not recognized!";
  }
}

#endif