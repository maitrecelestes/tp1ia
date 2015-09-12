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
  case 1:
    
    return "HiHoneyImHome"; 

  case 2:
    
    return "StewReady";

	case 3:
    
    return "ImatBank";

	case 4:
    
    return "ImThirsty";

	case 5:
    
    return "IWannaFight";

  default:

    return "Not recognized!";
  }
}

#endif