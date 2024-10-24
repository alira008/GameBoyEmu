#pragma once
#include "memory.h"
#include "registers.h"
#include <array>
#include <cstdint>
#include <functional>

namespace GameBoyEmu {
namespace Core {

enum class Instruction;

class Cpu {
public:
  Cpu();

private:
  Registers registers_{};
  Memory memory_{};
  std::array<std::function<void()>, 32> instructions_;

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

  void stop();
  void ld_de_nn();
  void ld_de_a();
  void inc_de();
  void inc_d();
  void dec_d();
  void ld_d_n();
  void rla();
  void jr_s8();
  void add_hl_de();
  void ld_a_de();
  void dec_de();
  void inc_e();
  void dec_e();
  void ld_e_n();
  void rra();
};

enum class Instruction {
  Nop,
  LdBCNN,
  LdBCA,
  IncBC,
  IncB,
  DecB,
  LdBN,
  Rlca,
  LdNNSP,
  AddHLBC,
  LdABC,
  DecBC,
  IncC,
  DecC,
  LdCN,
  Rrca,

  Stop,
  LdDENN,
  LdDEA,
  IncDE,
  IncD,
  DecD,
  LdDN,
  Rla,
  JrS8,
  AddHLDE,
  LdADE,
  DecDE,
  IncE,
  DecE,
  LdEN,
  Rra,
};

} // namespace Core
} // namespace GameBoyEmu
