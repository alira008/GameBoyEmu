#pragma once
#include "memory.h"
#include "registers.h"
#include <array>
#include <cstdint>
#include <functional>

namespace GameBoyEmu {
namespace Core {

enum class Instruction : uint8_t;
enum class Instruction16Bit : uint8_t;

class Cpu {
public:
  Cpu();
  uint8_t fetch_current_instruction();
  void execute_instruction(uint8_t opcode);
  const Registers &registers() const;

private:
  static constexpr uint32_t TOTAL_NUMBER_OF_INSTRUCTION = 256;
  Registers registers_{};
  Memory memory_{};
  std::array<std::function<void()>, TOTAL_NUMBER_OF_INSTRUCTION> instructions_;
  std::array<std::function<void()>, TOTAL_NUMBER_OF_INSTRUCTION>
      instructions_16_bit;
  uint32_t total_cycles_{};

  void inc_reg(uint8_t &reg);
  void dec_reg(uint8_t &reg);
  void inc_word_reg(uint16_t &reg);
  void dec_word_reg(uint16_t &reg);
  void ld_reg_n(uint8_t &reg);
  void ld_reg_reg(uint8_t &write_reg, uint8_t read_reg);
  void ld_word_reg_nn(uint16_t &reg);
  void add_reg_reg(uint8_t &write_reg, uint8_t read_reg);
  void adc_reg_reg(uint8_t &write_reg, uint8_t read_reg);
  void sub_reg_reg(uint8_t &write_reg, uint8_t read_reg);
  void sbc_reg_reg(uint8_t &write_reg, uint8_t read_reg);
  void and_reg_reg(uint8_t &write_reg, uint8_t read_reg);
  void xor_reg_reg(uint8_t &write_reg, uint8_t read_reg);
  void or_reg_reg(uint8_t &write_reg, uint8_t read_reg);
  void cp_reg_reg(uint8_t &write_reg, uint8_t read_reg);
  void rst(uint8_t addr);
  void pop_stack_into_reg_16(uint16_t &reg);
  void push_onto_stack_reg_16(uint16_t content);
  void rlc(uint8_t &reg);
  void rrc(uint8_t &reg);
  void rl(uint8_t &reg);
  void rr(uint8_t &reg);
  void sla(uint8_t &reg);
  void sra(uint8_t &reg);
  void swap(uint8_t &reg);
  void srl(uint8_t &reg);
  void bit(uint8_t &reg, uint8_t bit);
  void bit_hl_ref(uint8_t bit);
  void res(uint8_t &reg, uint8_t bit);
  void res_hl_ref(uint8_t bit);
  void set(uint8_t &reg, uint8_t bit);
  void set_hl_ref(uint8_t bit);
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

  // 16-bit opcode instructions
  void rlc_b();
  void rlc_c();
  void rlc_d();
  void rlc_e();
  void rlc_h();
  void rlc_l();
  void rlc_hl_ref();
  void rlc_a();
  void rrc_b();
  void rrc_c();
  void rrc_d();
  void rrc_e();
  void rrc_h();
  void rrc_l();
  void rrc_hl_ref();
  void rrc_a();

  void rl_b();
  void rl_c();
  void rl_d();
  void rl_e();
  void rl_h();
  void rl_l();
  void rl_hl_ref();
  void rl_a();
  void rr_b();
  void rr_c();
  void rr_d();
  void rr_e();
  void rr_h();
  void rr_l();
  void rr_hl_ref();
  void rr_a();

  void sla_b();
  void sla_c();
  void sla_d();
  void sla_e();
  void sla_h();
  void sla_l();
  void sla_hl_ref();
  void sla_a();
  void sra_b();
  void sra_c();
  void sra_d();
  void sra_e();
  void sra_h();
  void sra_l();
  void sra_hl_ref();
  void sra_a();

  void swap_b();
  void swap_c();
  void swap_d();
  void swap_e();
  void swap_h();
  void swap_l();
  void swap_hl_ref();
  void swap_a();
  void srl_b();
  void srl_c();
  void srl_d();
  void srl_e();
  void srl_h();
  void srl_l();
  void srl_hl_ref();
  void srl_a();

  void bit_0_b();
  void bit_0_c();
  void bit_0_d();
  void bit_0_e();
  void bit_0_h();
  void bit_0_l();
  void bit_0_hl_ref();
  void bit_0_a();
  void bit_1_b();
  void bit_1_c();
  void bit_1_d();
  void bit_1_e();
  void bit_1_h();
  void bit_1_l();
  void bit_1_hl_ref();
  void bit_1_a();

  void bit_2_b();
  void bit_2_c();
  void bit_2_d();
  void bit_2_e();
  void bit_2_h();
  void bit_2_l();
  void bit_2_hl_ref();
  void bit_2_a();
  void bit_3_b();
  void bit_3_c();
  void bit_3_d();
  void bit_3_e();
  void bit_3_h();
  void bit_3_l();
  void bit_3_hl_ref();
  void bit_3_a();

  void bit_4_b();
  void bit_4_c();
  void bit_4_d();
  void bit_4_e();
  void bit_4_h();
  void bit_4_l();
  void bit_4_hl_ref();
  void bit_4_a();
  void bit_5_b();
  void bit_5_c();
  void bit_5_d();
  void bit_5_e();
  void bit_5_h();
  void bit_5_l();
  void bit_5_hl_ref();
  void bit_5_a();

  void bit_6_b();
  void bit_6_c();
  void bit_6_d();
  void bit_6_e();
  void bit_6_h();
  void bit_6_l();
  void bit_6_hl_ref();
  void bit_6_a();
  void bit_7_b();
  void bit_7_c();
  void bit_7_d();
  void bit_7_e();
  void bit_7_h();
  void bit_7_l();
  void bit_7_hl_ref();
  void bit_7_a();

  void res_0_b();
  void res_0_c();
  void res_0_d();
  void res_0_e();
  void res_0_h();
  void res_0_l();
  void res_0_hl_ref();
  void res_0_a();
  void res_1_b();
  void res_1_c();
  void res_1_d();
  void res_1_e();
  void res_1_h();
  void res_1_l();
  void res_1_hl_ref();
  void res_1_a();

  void res_2_b();
  void res_2_c();
  void res_2_d();
  void res_2_e();
  void res_2_h();
  void res_2_l();
  void res_2_hl_ref();
  void res_2_a();
  void res_3_b();
  void res_3_c();
  void res_3_d();
  void res_3_e();
  void res_3_h();
  void res_3_l();
  void res_3_hl_ref();
  void res_3_a();

  void res_4_b();
  void res_4_c();
  void res_4_d();
  void res_4_e();
  void res_4_h();
  void res_4_l();
  void res_4_hl_ref();
  void res_4_a();
  void res_5_b();
  void res_5_c();
  void res_5_d();
  void res_5_e();
  void res_5_h();
  void res_5_l();
  void res_5_hl_ref();
  void res_5_a();

  void res_6_b();
  void res_6_c();
  void res_6_d();
  void res_6_e();
  void res_6_h();
  void res_6_l();
  void res_6_hl_ref();
  void res_6_a();
  void res_7_b();
  void res_7_c();
  void res_7_d();
  void res_7_e();
  void res_7_h();
  void res_7_l();
  void res_7_hl_ref();
  void res_7_a();

  void set_0_b();
  void set_0_c();
  void set_0_d();
  void set_0_e();
  void set_0_h();
  void set_0_l();
  void set_0_hl_ref();
  void set_0_a();
  void set_1_b();
  void set_1_c();
  void set_1_d();
  void set_1_e();
  void set_1_h();
  void set_1_l();
  void set_1_hl_ref();
  void set_1_a();

  void set_2_b();
  void set_2_c();
  void set_2_d();
  void set_2_e();
  void set_2_h();
  void set_2_l();
  void set_2_hl_ref();
  void set_2_a();
  void set_3_b();
  void set_3_c();
  void set_3_d();
  void set_3_e();
  void set_3_h();
  void set_3_l();
  void set_3_hl_ref();
  void set_3_a();

  void set_4_b();
  void set_4_c();
  void set_4_d();
  void set_4_e();
  void set_4_h();
  void set_4_l();
  void set_4_hl_ref();
  void set_4_a();
  void set_5_b();
  void set_5_c();
  void set_5_d();
  void set_5_e();
  void set_5_h();
  void set_5_l();
  void set_5_hl_ref();
  void set_5_a();

  void set_6_b();
  void set_6_c();
  void set_6_d();
  void set_6_e();
  void set_6_h();
  void set_6_l();
  void set_6_hl_ref();
  void set_6_a();
  void set_7_b();
  void set_7_c();
  void set_7_d();
  void set_7_e();
  void set_7_h();
  void set_7_l();
  void set_7_hl_ref();
  void set_7_a();
};

enum class Instruction : uint8_t {
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
  CallZNN = 0xCC,
  CallNN,
  AdcAN,
  Rst1,

  RetNC,
  PopDE,
  JpNCNN,
  CallNCNN = 0xD4,
  PushDE,
  SubAN,
  Rst2,
  RetC,
  Reti,
  JpCNN,
  CallCNN = 0xDC,
  SbcAN = 0xDE,
  Rst3,

  LdNRefA,
  PopHL,
  LdCRefA,
  PushHL = 0xE5,
  AndAN,
  Rst4,
  AddSpN,
  JpHL,
  LdNNRefA,
  XorAN = 0xEE,
  Rst5,

  LdANRef,
  PopAF,
  LdACRef,
  DI,
  PushAF = 0xF5,
  OrAN,
  Rst6,
  LdHLSPN,
  LdSPHL,
  LdANNRef,
  EI,
  CpAN = 0xFE,
  Rst7,
};

enum class Instruction16Bit : uint8_t {
  RlcB,
  RlcC,
  RlcD,
  RlcE,
  RlcH,
  RlcL,
  RlcHLRef,
  RlcA,
  RrcB,
  RrcC,
  RrcD,
  RrcE,
  RrcH,
  RrcL,
  RrcHLRef,
  RrcA,

  RlB,
  RlC,
  RlD,
  RlE,
  RlH,
  RlL,
  RlHLRef,
  RlA,
  RrB,
  RrC,
  RrD,
  RrE,
  RrH,
  RrL,
  RrHLRef,
  RrA,

  SlaB,
  SlaC,
  SlaD,
  SlaE,
  SlaH,
  SlaL,
  SlaHLRef,
  SlaA,
  SraB,
  SraC,
  SraD,
  SraE,
  SraH,
  SraL,
  SraHLRef,
  SraA,

  SwapB,
  SwapC,
  SwapD,
  SwapE,
  SwapH,
  SwapL,
  SwapHLRef,
  SwapA,
  SrlB,
  SrlC,
  SrlD,
  SrlE,
  SrlH,
  SrlL,
  SrlHLRef,
  SrlA,

  Bit0B,
  Bit0C,
  Bit0D,
  Bit0E,
  Bit0H,
  Bit0L,
  Bit0HLRef,
  Bit0A,
  Bit1B,
  Bit1C,
  Bit1D,
  Bit1E,
  Bit1H,
  Bit1L,
  Bit1HLRef,
  Bit1A,

  Bit2B,
  Bit2C,
  Bit2D,
  Bit2E,
  Bit2H,
  Bit2L,
  Bit2HLRef,
  Bit2A,
  Bit3B,
  Bit3C,
  Bit3D,
  Bit3E,
  Bit3H,
  Bit3L,
  Bit3HLRef,
  Bit3A,

  Bit4B,
  Bit4C,
  Bit4D,
  Bit4E,
  Bit4H,
  Bit4L,
  Bit4HLRef,
  Bit4A,
  Bit5B,
  Bit5C,
  Bit5D,
  Bit5E,
  Bit5H,
  Bit5L,
  Bit5HLRef,
  Bit5A,

  Bit6B,
  Bit6C,
  Bit6D,
  Bit6E,
  Bit6H,
  Bit6L,
  Bit6HLRef,
  Bit6A,
  Bit7B,
  Bit7C,
  Bit7D,
  Bit7E,
  Bit7H,
  Bit7L,
  Bit7HLRef,
  Bit7A,

  Res0B,
  Res0C,
  Res0D,
  Res0E,
  Res0H,
  Res0L,
  Res0HLRef,
  Res0A,
  Res1B,
  Res1C,
  Res1D,
  Res1E,
  Res1H,
  Res1L,
  Res1HLRef,
  Res1A,

  Res2B,
  Res2C,
  Res2D,
  Res2E,
  Res2H,
  Res2L,
  Res2HLRef,
  Res2A,
  Res3B,
  Res3C,
  Res3D,
  Res3E,
  Res3H,
  Res3L,
  Res3HLRef,
  Res3A,

  Res4B,
  Res4C,
  Res4D,
  Res4E,
  Res4H,
  Res4L,
  Res4HLRef,
  Res4A,
  Res5B,
  Res5C,
  Res5D,
  Res5E,
  Res5H,
  Res5L,
  Res5HLRef,
  Res5A,

  Res6B,
  Res6C,
  Res6D,
  Res6E,
  Res6H,
  Res6L,
  Res6HLRef,
  Res6A,
  Res7B,
  Res7C,
  Res7D,
  Res7E,
  Res7H,
  Res7L,
  Res7HLRef,
  Res7A,

  Set0B,
  Set0C,
  Set0D,
  Set0E,
  Set0H,
  Set0L,
  Set0HLRef,
  Set0A,
  Set1B,
  Set1C,
  Set1D,
  Set1E,
  Set1H,
  Set1L,
  Set1HLRef,
  Set1A,

  Set2B,
  Set2C,
  Set2D,
  Set2E,
  Set2H,
  Set2L,
  Set2HLRef,
  Set2A,
  Set3B,
  Set3C,
  Set3D,
  Set3E,
  Set3H,
  Set3L,
  Set3HLRef,
  Set3A,

  Set4B,
  Set4C,
  Set4D,
  Set4E,
  Set4H,
  Set4L,
  Set4HLRef,
  Set4A,
  Set5B,
  Set5C,
  Set5D,
  Set5E,
  Set5H,
  Set5L,
  Set5HLRef,
  Set5A,

  Set6B,
  Set6C,
  Set6D,
  Set6E,
  Set6H,
  Set6L,
  Set6HLRef,
  Set6A,
  Set7B,
  Set7C,
  Set7D,
  Set7E,
  Set7H,
  Set7L,
  Set7HLRef,
  Set7A,
};

} // namespace Core
} // namespace GameBoyEmu
