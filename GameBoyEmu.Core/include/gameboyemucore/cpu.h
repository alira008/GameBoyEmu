#pragma once
#include "memory.h"
#include "registers.h"
#include <array>
#include <cstdint>
#include <functional>

namespace GameBoyEmuCore {

class Cpu {
public:
private:
  Registers registers_{};
  Memory memory_{};

  /* instruction set */
  void nop();
  void ld_bc_nn();
  void ld_bc_a();
  void inc_bc();
  void inc_b();
  void dec_b();
  void ld_b_n();
  void rlca();
  void ld_nn_sp();
  void add_hl_bc();
  void ld_a_bc();
  void dec_bc();
  void inc_c();
  void dec_c();
  void ld_c_n();
  void rrca();
};

} // namespace GameBoyEmuCore
