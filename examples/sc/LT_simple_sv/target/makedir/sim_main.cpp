#include <iostream>
#include "Vcs_common.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <time.h>
#include <sys/time.h>

using namespace std;

vluint64_t main_time = 0;


double sc_time_stamp() {
  return (main_time);
}

int main(int argc, char **argv, char **env) {
  int i;
  int clk_main;

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vcs_common* Target = new Vcs_common;

  // init trace dump
  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  Target->trace (tfp, 1000);// Trace 1000 levels of hierarchy
  tfp->open ("top_sim.vcd");

  // initialize simulation inputs
  Target->clk_i = 1;

  while (!Verilated::gotFinish()) {
    Target->clk_i = !Target->clk_i;
    Target->eval();
    tfp->flush();
    tfp->dump(main_time);
    main_time++;  // Time passes...
  }
  //
  Target->final();
  delete Target; Target = NULL;
  //printf("\n>>>@%0ld sec\n",currentTimeSec.tv_sec-startTime.tv_sec);
  exit(0);
}

