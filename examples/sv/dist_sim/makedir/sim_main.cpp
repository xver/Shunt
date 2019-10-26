#include "Vshunt_verilator_dpi.h"
#include "verilated.h"
#include "verilated_vcd_c.h"


int main(int argc, char **argv, char **env) {
  int i;
  int clk_main;
  // Current simulation time (64-bit unsigned)
  vluint64_t main_time = 0;

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vshunt_verilator_dpi* top_sim = new Vshunt_verilator_dpi;
  // init trace dump
  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top_sim->trace (tfp, 1000);// Trace 1000 levels of hierarchy
  tfp->open ("top_sim.vcd");
  // initialize simulation inputs
  top_sim->clk_i = 1;
  while (!Verilated::gotFinish()) { 
    top_sim->clk_i = !top_sim->clk_i;
    top_sim->eval(); 
    tfp->flush();
    tfp->dump(main_time);
    main_time++;  // Time passes...
  }
  // Destroy model
  if (tfp) { tfp->close(); tfp = NULL; }
  delete top_sim; top_sim = NULL;
  exit(0);
  //   // run simulation for 1000 clock periods
  //   for (i=0; i<1000; i++) {
  //     // dump variables into VCD file and toggle clock
  //     for (clk_main=0; clk_main<2; clk_main++) {
  //       tfp->dump (2*i+clk_main);
  //       top->clk_i = !top->clk_i;
  //       top->eval ();
  //     }
  //     if (Verilated::gotFinish())  exit(0);
  //   }
  //   tfp->close();
  //exit(0);
}

