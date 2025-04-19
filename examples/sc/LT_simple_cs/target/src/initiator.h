/**
 * File: initiator.h
 * 
 * Module: Initiator
 * 
 * Description: A SystemC initiator component for TLM-2 socket communication.
 *              This module acts as a client in a client-server model, generating 
 *              TLM transactions and sending them through the socket.
 * 
 * Project: LT_simple_cs - Loosely Timed simple client-server example
 */
#ifndef INITIATOR_H
#define INITIATOR_H

#include <systemc>
#include <iostream>
#include "shunt_tlm.h"
#include "shunt_define.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;
using namespace shunt_tlm;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"


/**
 * Class: Initiator
 * 
 * Purpose: Initiator module generating generic payload transactions.
 *          Acts as a TLM-2 transaction initiator that communicates 
 *          with a target/memory component over a socket connection.
 */
struct Initiator: sc_module
{
  /**
   * Variable: socket
   * 
   * TLM-2 socket, defaults to 32-bits wide, base protocol.
   * Used to send transactions to the target/memory component.
   */
  tlm_utils::simple_initiator_socket<Initiator> socket;
  
  /**
   * Variable: m_socket
   * 
   * Socket file descriptor for network communication.
   * Initialized during the thread process.
   */
  int m_socket=0;
  
  /**
   * Function: Initiator
   * 
   * Creates an initiator module with a named socket and
   * registers the thread_process function as a SystemC thread.
   */
  SC_CTOR(Initiator)
  : socket("socket")  // Construct and name socket
  {
    SC_THREAD(thread_process);
  }

  /**
   * Function: thread_process
   * 
   * Main execution thread of the initiator module.
   * Establishes connection with the server, creates transactions,
   * and handles the communication flow until simulation ends.
   */
  void thread_process()
  {
    // TLM-2 generic payload transaction, reused across calls to b_transport
    m_socket = shunt_tlm_init_client(MY_PORT,MY_HOST);
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay; // = sc_time(10, SC_NS);
    int end_sim =0;
    int i=0;

    // Generate a random sequence of reads and writes
    //for (int i = 32; i < 96; i += 4)

    while(!end_sim) {
      //tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
      //if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;

      // Initialize 8 out of the 10 attributes, byte_enable_length and extensions being unused
      //trans->set_command( cmd );
      //trans->set_address( i );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
      //trans->set_data_length( 4 );
      //trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
      trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
      //trans->set_dmi_allowed( false ); // Mandatory initial value
      //trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value
      //
      shunt_long_t tlm_extension_id =0;
      shunt_recv_b_transport(m_socket,*trans,tlm_extension_id,delay );

      if (trans->get_command() != (unsigned int)SHUNT_TLM_END_SIM) {
          socket->b_transport( *trans, delay );  // Blocking transport call
          // Initiator obliged to check response status and delay
          if ( trans->is_response_error() )
              SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

          tlm::tlm_command cmd =  trans->get_command();
          cout << "CLIENT trans = { " << (cmd ? 'W' : 'R') << ", " << hex << i
               << " } , data = " << hex << data << " at time " << sc_time_stamp()
           << " delay = " << delay << endl;

          // Realize the delay annotated onto the transport call
          wait(delay);
          shunt_send_b_transport(m_socket,*trans,tlm_extension_id,delay );
          ++i;
      }
      else end_sim =1;
    }
    shunt_prim_close_socket(m_socket);
  }

  /**
   * Variable: data
   * 
   * Internal data buffer used by initiator with generic payload.
   * Stores the data that is sent or received during transactions.
   */
  int data;
};

#endif
