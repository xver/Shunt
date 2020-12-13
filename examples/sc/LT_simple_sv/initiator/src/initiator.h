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


// Initiator module generating generic payload transactions

struct Initiator: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_initiator_socket<Initiator> socket;
  int m_socket=0;
  int start_sim=0;
  int end_sim=0;

  SC_CTOR(Initiator)
  : socket("socket")  // Construct and name socket
  {
    SC_THREAD(thread_process);
  }

  void thread_process()
  {

    // TLM-2 generic payload transaction, reused across calls to b_transport
    m_socket = shunt_tlm_init_server(MY_PORT);
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay;
    shunt_tlm_command command;
    shunt_recv_b_transport(m_socket,*trans,delay);
    command = (shunt_tlm_command)trans->get_command();
    cout<<"SERVER: SHUNT_TLM_START_SIM command="<<hex <<command<<endl;

    delay = sc_time(10, SC_NS);

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

      //socket->b_transport( *trans, delay );  // Blocking transport call
      shunt_send_b_transport(m_socket,*trans, delay );
      shunt_recv_b_transport(m_socket,*trans, delay );
      cout << "SERVER trans recv = { " << (cmd ? 'W' : 'R') << ", " << hex << i
       << " } , data = " << hex << data << " at time " << sc_time_stamp()
       << " delay = " << delay
       << " response = "<< trans->is_response_error()<< endl;
      // Initiator obliged to check response status and delay
      if ( trans->is_response_error() )
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

      // Realize the delay annotated onto the transport call
      wait(delay);
    }
    shunt_tlm_send_command(m_socket,SHUNT_TLM_END_SIM);
    shunt_prim_close_socket(m_socket);
    cout <<"LT_simple_sv test is finished"<<endl;
  }

  // Internal data buffer used by initiator with generic payload
  int data;
};

#endif
