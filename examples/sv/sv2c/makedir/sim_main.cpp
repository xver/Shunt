#include "Vcs_common.h"
#include "verilated.h"
int main(int argc, char **argv, char **env) {
  Verilated::commandArgs(argc, argv);
  Vcs_common* top = new Vcs_common;
  while (!Verilated::gotFinish()) { top->eval(); }
  delete top;
  exit(0);
}
