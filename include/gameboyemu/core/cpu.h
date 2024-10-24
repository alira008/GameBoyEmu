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
  std::array<std::function<void()>, 64> instructions_;

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

  void jr_nz_s8();
  void ld_hl_nn();
  void ld_hl_inc_a();
  void inc_hl();
  void inc_h();
  void dec_h();
  void ld_h_n();
  void daa();
  void jr_z_s8();
  void add_hl_hl();
  void ld_a_hl_inc();
  void dec_hl();
  void inc_l();
  void dec_l();
  void ld_l_n();
  void cpl();

  void jr_nc_s8();
  void ld_sp_nn();
  void ld_hl_dec_a();
  void inc_sp();
  void inc_hl_ref();
  void dec_hl_ref();
  void ld_hl_n();
  void scf();
  void jr_c_s8();
  void add_hl_sp();
  void ld_a_hl_dec();
  void dec_sp();
  void inc_a();
  void dec_a();
  void ld_a_n();
  void ccf();
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

  JrNZS8,
  LdHLNN,
  LdHLIncA,
  IncHL,
  IncH,
  DecH,
  LdHN,
  Daa,
  JrZS8,
  AddHLHL,
  LdAHLInc,
  DecDL,
  IncL,
  DecL,
  LdLN,
  CPL,

  JrNCS8,
  LdSPNN,
  LdHLDecA,
  IncSP,
  IncHLRef,
  DecHLRef,
  LdHLRefN,
  Scf,
  JrCS8,
  AddHLSP,
  LdAHLDec,
  DecSP,
  IncA,
  DecA,
  LdAN,
  CCF,
};

} // namespace Core
} // namespace GameBoyEmu
