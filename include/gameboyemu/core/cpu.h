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
  std::array<std::function<void()>, 244> instructions_;

  void pop_stack_into_reg_16(uint16_t &reg);
  void push_onto_stack_reg_16(uint16_t content);
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

  void ld_b_b();
  void ld_b_c();
  void ld_b_d();
  void ld_b_e();
  void ld_b_h();
  void ld_b_l();
  void ld_b_hl_ref();
  void ld_b_a();
  void ld_c_b();
  void ld_c_c();
  void ld_c_d();
  void ld_c_e();
  void ld_c_h();
  void ld_c_l();
  void ld_c_hl_ref();
  void ld_c_a();

  void ld_d_b();
  void ld_d_c();
  void ld_d_d();
  void ld_d_e();
  void ld_d_h();
  void ld_d_l();
  void ld_d_hl_ref();
  void ld_d_a();
  void ld_e_b();
  void ld_e_c();
  void ld_e_d();
  void ld_e_e();
  void ld_e_h();
  void ld_e_l();
  void ld_e_hl_ref();
  void ld_e_a();

  void ld_h_b();
  void ld_h_c();
  void ld_h_d();
  void ld_h_e();
  void ld_h_h();
  void ld_h_l();
  void ld_h_hl_ref();
  void ld_h_a();
  void ld_l_b();
  void ld_l_c();
  void ld_l_d();
  void ld_l_e();
  void ld_l_h();
  void ld_l_l();
  void ld_l_hl_ref();
  void ld_l_a();

  void ld_hl_ref_b();
  void ld_hl_ref_c();
  void ld_hl_ref_d();
  void ld_hl_ref_e();
  void ld_hl_ref_h();
  void ld_hl_ref_l();
  void halt();
  void ld_hl_ref_a();
  void ld_a_b();
  void ld_a_c();
  void ld_a_d();
  void ld_a_e();
  void ld_a_h();
  void ld_a_l();
  void ld_a_hl_ref();
  void ld_a_a();

  void add_a_b();
  void add_a_c();
  void add_a_d();
  void add_a_e();
  void add_a_h();
  void add_a_l();
  void add_a_hl_ref();
  void add_a_a();
  void adc_a_b();
  void adc_a_c();
  void adc_a_d();
  void adc_a_e();
  void adc_a_h();
  void adc_a_l();
  void adc_a_hl_ref();
  void adc_a_a();

  void sub_a_b();
  void sub_a_c();
  void sub_a_d();
  void sub_a_e();
  void sub_a_h();
  void sub_a_l();
  void sub_a_hl_ref();
  void sub_a_a();
  void sbc_a_b();
  void sbc_a_c();
  void sbc_a_d();
  void sbc_a_e();
  void sbc_a_h();
  void sbc_a_l();
  void sbc_a_hl_ref();
  void sbc_a_a();

  void and_a_b();
  void and_a_c();
  void and_a_d();
  void and_a_e();
  void and_a_h();
  void and_a_l();
  void and_a_hl_ref();
  void and_a_a();
  void xor_a_b();
  void xor_a_c();
  void xor_a_d();
  void xor_a_e();
  void xor_a_h();
  void xor_a_l();
  void xor_a_hl_ref();
  void xor_a_a();

  void or_a_b();
  void or_a_c();
  void or_a_d();
  void or_a_e();
  void or_a_h();
  void or_a_l();
  void or_a_hl_ref();
  void or_a_a();
  void cp_a_b();
  void cp_a_c();
  void cp_a_d();
  void cp_a_e();
  void cp_a_h();
  void cp_a_l();
  void cp_a_hl_ref();
  void cp_a_a();

  void ret_nz();
  void pop_bc();
  void jp_nz_nn();
  void jp_nn();
  void call_nz_nn();
  void push_bc();
  void add_a_n();
  void rst_0();
  void ret_z();
  void ret();
  void jp_z_nn();
  void call_z_nn();
  void call_nn();
  void adc_a_n();
  void rst_1();

  void ret_nc();
  void pop_de();
  void jp_nc_nn();
  void call_nc_nn();
  void push_de();
  void sub_a_n();
  void rst_2();
  void ret_c();
  void reti();
  void jp_c_nn();
  void call_c_nn();
  void sbc_a_n();
  void rst_3();

  void ld_n_ref_a();
  void pop_hl();
  void ld_c_ref_a();
  void push_hl();
  void and_a_n();
  void rst_4();
  void add_sp_n();
  void jp_hl();
  void ld_nn_ref_a();
  void xor_a_n();
  void rst_5();

  void ld_a_n_ref();
  void pop_af();
  void ld_a_c_ref();
  void di();
  void push_af();
  void or_a_n();
  void rst_6();
  void ld_hl_sp_n();
  void ld_sp_hl();
  void ld_a_nn_ref();
  void e_i();
  void cp_a_n();
  void rst_7();
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

  LdBB,
  LdBC,
  LdBD,
  LdBE,
  LdBH,
  LdBL,
  LdBHlRef,
  LdBA,
  LdCB,
  LdCC,
  LdCD,
  LdCE,
  LdCH,
  LdCL,
  LdCHlRef,
  LdCA,

  LdDB,
  LdDC,
  LdDD,
  LdDE,
  LdDH,
  LdDL,
  LdDHlRef,
  LdDA,
  LdEB,
  LdEC,
  LdED,
  LdEE,
  LdEH,
  LdEL,
  LdEHlRef,
  LdEA,

  LdHB,
  LdHC,
  LdHD,
  LdHE,
  LdHH,
  LdHL,
  LdHHlRef,
  LdHA,
  LdLB,
  LdLC,
  LdLD,
  LdLE,
  LdLH,
  LdLL,
  LdLHlRef,
  LdLA,

  LdHlRefB,
  LdHlRefC,
  LdHlRefD,
  LdHlRefE,
  LdHlRefH,
  LdHlRefL,
  Halt,
  LdHlRefA,
  LdAB,
  LdAC,
  LdAD,
  LdAE,
  LdAH,
  LdAL,
  LdAHlRef,
  LdAA,

  AddAB,
  AddAC,
  AddAD,
  AddAE,
  AddAH,
  AddAL,
  AddAHlRef,
  AddAA,
  AdcAB,
  AdcAC,
  AdcAD,
  AdcAE,
  AdcAH,
  AdcAL,
  AdcAHlRef,
  AdcAA,

  SubAB,
  SubAC,
  SubAD,
  SubAE,
  SubAH,
  SubAL,
  SubAHlRef,
  SubAA,
  SbcAB,
  SbcAC,
  SbcAD,
  SbcAE,
  SbcAH,
  SbcAL,
  SbcAHlRef,
  SbcAA,

  AndAB,
  AndAC,
  AndAD,
  AndAE,
  AndAH,
  AndAL,
  AndAHlRef,
  AndAA,
  XorAB,
  XorAC,
  XorAD,
  XorAE,
  XorAH,
  XorAL,
  XorAHlRef,
  XorAA,

  OrAB,
  OrAC,
  OrAD,
  OrAE,
  OrAH,
  OrAL,
  OrAHlRef,
  OrAA,
  CpAB,
  CpAC,
  CpAD,
  CpAE,
  CpAH,
  CpAL,
  CpAHlRef,
  CpAA,

  RetNZ,
  PopBC,
  JpNZNN,
  JpNN,
  CallNZNN,
  PushBC,
  AddAN,
  Rst0,
  RetZ,
  Ret,
  JpZNN,
  CallZNN,
  CallNN,
  AdcAN,
  Rst1,

  RetNC,
  PopDE,
  JpNCNN,
  CallNCNN,
  PushDE,
  SubAN,
  Rst2,
  RetC,
  Reti,
  JpCNN,
  CallCNN,
  SbcAN,
  Rst3,

  LdNRefA,
  PopHL,
  LdCRefA,
  PushHL,
  AndAN,
  Rst4,
  AddSpN,
  JpHL,
  LdNNRefA,
  XorAN,
  Rst5,

  LdANRef,
  PopAF,
  LdACRef,
  PushAF,
  OrAN,
  Rst6,
  LdHLSPN,
  LdSPHL,
  LdANNRef,
  EI,
  CpAN,
  Rst7,
};

} // namespace Core
} // namespace GameBoyEmu
