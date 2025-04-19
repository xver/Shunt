/**
 * File: initiator.h
 * 
 * Module: Initiator
 * 
 * Description: A SystemC initiator component for TLM-2 socket communication.
 *              This module acts as a server in a client-server model, generating 
 *              TLM transactions and handling communication with a client.
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
 *          In the client-server model, this acts as the server side.
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
   * Establishes server socket, creates transactions,
   * and handles the communication flow until complete.
   */
  void thread_process()
  {
    int m_socket=0;
    // TLM-2 generic payload transaction, reused across calls to b_transport
    m_socket = shunt_tlm_init_server(MY_PORT);
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay = sc_time(10, SC_NS);

    // Generate a random sequence of reads and writes
    for (int i = 32; i < 96; i += 4)
    {

      tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
      if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;

      // Initialize 8 out of the 10 attributes, byte_enable_length and extensions being unused
      trans->set_command( cmd );
      trans->set_address( i );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
      trans->set_data_length( 4 );
      trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
      trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
      trans->set_dmi_allowed( false ); // Mandatory initial value
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

      shunt_long_t tlm_extension_id =0;

      //socket->b_transport( *trans, delay );  // Blocking transport call

      shunt_send_b_transport(m_socket,*trans,tlm_extension_id,delay );
      shunt_recv_b_transport(m_socket,*trans,tlm_extension_id, delay );
      cout << "SERVER trans = { " << (cmd ? 'W' : 'R') << ", " << hex << i
                    << " } , data = " << hex << data << " at time " << sc_time_stamp()
                    << " delay = " << delay << endl;
      // Initiator obliged to check response status and delay
      if ( trans->is_response_error() )
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

      // Realize the delay annotated onto the transport call
      wait(delay);
    }
    shunt_tlm_send_command(m_socket,SHUNT_TLM_END_SIM);
    shunt_prim_close_socket(m_socket);
    cout <<"LT_simple_cs test is finished"<<endl;
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
