/**
 * File: top.h
 * 
 * Module: Top
 * 
 * Description: Top-level SystemC module that instantiates and connects 
 *              the initiator and memory components.
 * 
 * Project: LT_simple_cs - Loosely Timed simple client-server example
 */
#ifndef TOP_H
#define TOP_H


#include "initiator.h"
#include "target.h"
#include "shunt_user_api.h"

/**
 * Class: Top
 * 
 * Purpose: Top-level SystemC module that instantiates and connects
 *          an initiator component with a memory component.
 *          Creates the basic structure for the TLM-2 communication example.
 */
SC_MODULE(Top)
{
  /**
   * Variable: initiator
   * 
   * Pointer to the Initiator component that generates transactions.
   */
  Initiator *initiator;
  
  /**
   * Variable: memory
   * 
   * Pointer to the Memory component that responds to transactions.
   */
  Memory    *memory;

  /**
   * Constructor: Top
   * 
   * Creates the initiator and memory components and
   * binds their sockets together to enable communication.
   */
  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = new Initiator("initiator");
    memory    = new Memory   ("memory");

    // One initiator is bound directly to one target with no intervening bus

    // Bind initiator socket to target socket
    initiator->socket.bind( memory->socket );
  }
};

#endif
