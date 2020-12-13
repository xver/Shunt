//----------------------------------------------------------------------
//
//  Copyright (c) 2007-2008 by Doulos Ltd.
//  Modifications copyright (C) 2020 IC Verimeter Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//----------------------------------------------------------------------

// Version 2  16-June-2008 - updated for TLM-2.0

// Getting Started with TLM-2.0, Tutorial Example 1

// For a full description, see http://www.doulos.com/knowhow/systemc/tlm2

// Shows the generic payload, sockets, and blocking transport interface.
// Shows the responsibilities of initiator and target with respect to the generic payload.
// Has only dummy implementations of the direct memory and debug transaction interfaces.
// Does not show the non-blocking transport interface.
//----------------------------------------------------------------------
//Modifications Notes:
//This example was adjusted to demonstrate blocking TLM 2.0 transfer over TCP/IP communication
//with b_trasport call task modification.
//see the readme file for details.
#include "top.h"

int sc_main(int argc, char* argv[])
{
  Top top("top");
  sc_start();
  return 0;
}
