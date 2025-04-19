/**
 * File: target.h
 * 
 * Module: Memory
 * 
 * Description: A SystemC target component for TLM-2 socket communication.
 *              This module represents a simple memory component that responds
 *              to read and write transactions from an initiator.
 * 
 * Project: LT_simple_cs - Loosely Timed simple client-server example
 */
#ifndef TARGET_H
#define TARGET_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"


/**
 * Class: Memory
 * 
 * Purpose: Target module representing a simple memory.
 *          Acts as a TLM-2 transaction target that responds to
 *          read and write commands from an initiator component.
 */
struct Memory: sc_module
{
  /**
   * Variable: socket
   * 
   * TLM-2 socket, defaults to 32-bits wide, base protocol.
   * Used to receive transactions from the initiator component.
   */
  tlm_utils::simple_target_socket<Memory> socket;

  /**
   * Constant: SIZE
   * 
   * Defines the size of the memory array in 32-bit words.
   */
  enum { SIZE = 256 };

  /**
   * Constructor: Memory
   * 
   * Creates a memory module with a named socket,
   * registers the b_transport callback function, and
   * initializes the memory array with random data.
   */
  SC_CTOR(Memory)
  : socket("socket")
  {
    // Register callback for incoming b_transport interface method call
    socket.register_b_transport(this, &Memory::b_transport);

    // Initialize memory with random data
    for (int i = 0; i < SIZE; i++)
      mem[i] = 0xAA000000 | (rand() % 256);
  }

  /**
   * Function: b_transport
   * 
   * TLM-2 blocking transport function that handles read and write transactions.
   * Validates transaction parameters and performs memory operations.
   * 
   * Parameters:
   *   trans - The generic payload transaction object containing command type,
   *           address, data, and other transaction attributes
   *   delay - Timing annotation associated with the transaction
   */
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address() / 4;
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    // Obliged to check address range and check for unsupported features,
    //   i.e. byte enables, streaming, and bursts
    // Can ignore DMI hint and extensions
    // Using the SystemC report handler is an acceptable way of signalling an error

    if (adr >= sc_dt::uint64(SIZE) || byt != 0 || len > 4 || wid < len)
      SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

    // Obliged to implement read and write commands
    if ( cmd == tlm::TLM_READ_COMMAND )
      memcpy(ptr, &mem[adr], len);
    else if ( cmd == tlm::TLM_WRITE_COMMAND )
      memcpy(&mem[adr], ptr, len);

    // Obliged to set response status to indicate successful completion
    trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }

  /**
   * Variable: mem
   * 
   * Memory array that stores the data accessed by read and write transactions.
   * Each element is a 32-bit word.
   */
  int mem[SIZE];
};

#endif
