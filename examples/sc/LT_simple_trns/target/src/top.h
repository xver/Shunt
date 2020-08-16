#ifndef TOP_H
#define TOP_H


#include "initiator.h"
#include "target.h"
#include "shunt_user_api.h"

SC_MODULE(Top)
{
  Initiator *initiator;
  Memory    *memory;

  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = new Initiator("initiator");
    memory    = new Memory   ("memory");
    initiator->m_socket = shunt_tlm_init_client(MY_PORT,MY_HOST);
    memory->m_socket   = initiator->m_socket;
    // One initiator is bound directly to one target with no intervening bus

    // Bind initiator socket to target socket
    initiator->socket.bind( memory->socket );
  }
};

#endif
