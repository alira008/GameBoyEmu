#include "gameboyemu/core/cpu.h"
#include <functional>
#include <iostream>

namespace GameBoyEmu {
namespace Core {

Cpu::Cpu()
    : instructions_{
          std::bind(&Cpu::nop, this),
          std::bind(&Cpu::ld_bc_nn, this),
          std::bind(&Cpu::ld_bc_a, this),
          std::bind(&Cpu::inc_bc, this),
          std::bind(&Cpu::inc_b, this),
          std::bind(&Cpu::dec_b, this),
          std::bind(&Cpu::ld_b_n, this),
          std::bind(&Cpu::rlca, this),
          std::bind(&Cpu::ld_nn_sp, this),
          std::bind(&Cpu::add_hl_bc, this),
          std::bind(&Cpu::ld_a_bc, this),
          std::bind(&Cpu::dec_bc, this),
          std::bind(&Cpu::inc_c, this),
          std::bind(&Cpu::dec_c, this),
          std::bind(&Cpu::ld_c_n, this),
          std::bind(&Cpu::rrca, this),

          std::bind(&Cpu::stop, this),
          std::bind(&Cpu::ld_de_nn, this),
          std::bind(&Cpu::ld_de_a, this),
          std::bind(&Cpu::inc_de, this),
          std::bind(&Cpu::inc_d, this),
          std::bind(&Cpu::dec_d, this),
          std::bind(&Cpu::ld_d_n, this),
          std::bind(&Cpu::rla, this),
          std::bind(&Cpu::jr_s8, this),
          std::bind(&Cpu::add_hl_de, this),
          std::bind(&Cpu::ld_a_de, this),
          std::bind(&Cpu::dec_de, this),
          std::bind(&Cpu::inc_e, this),
          std::bind(&Cpu::dec_e, this),
          std::bind(&Cpu::ld_e_n, this),
          std::bind(&Cpu::rra, this),

          std::bind(&Cpu::jr_nz_s8, this),
          std::bind(&Cpu::ld_hl_nn, this),
          std::bind(&Cpu::ld_hl_inc_a, this),
          std::bind(&Cpu::inc_hl, this),
          std::bind(&Cpu::inc_h, this),
          std::bind(&Cpu::dec_h, this),
          std::bind(&Cpu::ld_h_n, this),
          std::bind(&Cpu::daa, this),
          std::bind(&Cpu::jr_z_s8, this),
          std::bind(&Cpu::add_hl_hl, this),
          std::bind(&Cpu::ld_a_hl_inc, this),
          std::bind(&Cpu::dec_hl, this),
          std::bind(&Cpu::inc_l, this),
          std::bind(&Cpu::dec_l, this),
          std::bind(&Cpu::ld_l_n, this),
          std::bind(&Cpu::cpl, this),

          std::bind(&Cpu::jr_nc_s8, this),
          std::bind(&Cpu::ld_sp_nn, this),
          std::bind(&Cpu::ld_hl_dec_a, this),
          std::bind(&Cpu::inc_sp, this),
          std::bind(&Cpu::inc_hl_ref, this),
          std::bind(&Cpu::dec_hl_ref, this),
          std::bind(&Cpu::ld_hl_n, this),
          std::bind(&Cpu::scf, this),
          std::bind(&Cpu::jr_c_s8, this),
          std::bind(&Cpu::add_hl_sp, this),
          std::bind(&Cpu::ld_a_hl_dec, this),
          std::bind(&Cpu::dec_sp, this),
          std::bind(&Cpu::inc_a, this),
          std::bind(&Cpu::dec_a, this),
          std::bind(&Cpu::ld_a_n, this),
          std::bind(&Cpu::ccf, this),

          std::bind(&Cpu::ld_b_b, this),
          std::bind(&Cpu::ld_b_c, this),
          std::bind(&Cpu::ld_b_d, this),
          std::bind(&Cpu::ld_b_e, this),
          std::bind(&Cpu::ld_b_h, this),
          std::bind(&Cpu::ld_b_l, this),
          std::bind(&Cpu::ld_b_hl_ref, this),
          std::bind(&Cpu::ld_b_a, this),
          std::bind(&Cpu::ld_c_b, this),
          std::bind(&Cpu::ld_c_c, this),
          std::bind(&Cpu::ld_c_d, this),
          std::bind(&Cpu::ld_c_e, this),
          std::bind(&Cpu::ld_c_h, this),
          std::bind(&Cpu::ld_c_l, this),
          std::bind(&Cpu::ld_c_hl_ref, this),
          std::bind(&Cpu::ld_c_a, this),

          std::bind(&Cpu::ld_d_b, this),
          std::bind(&Cpu::ld_d_c, this),
          std::bind(&Cpu::ld_d_d, this),
          std::bind(&Cpu::ld_d_e, this),
          std::bind(&Cpu::ld_d_h, this),
          std::bind(&Cpu::ld_d_l, this),
          std::bind(&Cpu::ld_d_hl_ref, this),
          std::bind(&Cpu::ld_d_a, this),
          std::bind(&Cpu::ld_e_b, this),
          std::bind(&Cpu::ld_e_c, this),
          std::bind(&Cpu::ld_e_d, this),
          std::bind(&Cpu::ld_e_e, this),
          std::bind(&Cpu::ld_e_h, this),
          std::bind(&Cpu::ld_e_l, this),
          std::bind(&Cpu::ld_e_hl_ref, this),
          std::bind(&Cpu::ld_e_a, this),

          std::bind(&Cpu::ld_h_b, this),
          std::bind(&Cpu::ld_h_c, this),
          std::bind(&Cpu::ld_h_d, this),
          std::bind(&Cpu::ld_h_e, this),
          std::bind(&Cpu::ld_h_h, this),
          std::bind(&Cpu::ld_h_l, this),
          std::bind(&Cpu::ld_h_hl_ref, this),
          std::bind(&Cpu::ld_h_a, this),
          std::bind(&Cpu::ld_l_b, this),
          std::bind(&Cpu::ld_l_c, this),
          std::bind(&Cpu::ld_l_d, this),
          std::bind(&Cpu::ld_l_e, this),
          std::bind(&Cpu::ld_l_h, this),
          std::bind(&Cpu::ld_l_l, this),
          std::bind(&Cpu::ld_l_hl_ref, this),
          std::bind(&Cpu::ld_l_a, this),

          std::bind(&Cpu::ld_hl_ref_b, this),
          std::bind(&Cpu::ld_hl_ref_c, this),
          std::bind(&Cpu::ld_hl_ref_d, this),
          std::bind(&Cpu::ld_hl_ref_e, this),
          std::bind(&Cpu::ld_hl_ref_h, this),
          std::bind(&Cpu::ld_hl_ref_l, this),
          std::bind(&Cpu::halt, this),
          std::bind(&Cpu::ld_hl_ref_a, this),
          std::bind(&Cpu::ld_a_b, this),
          std::bind(&Cpu::ld_a_c, this),
          std::bind(&Cpu::ld_a_d, this),
          std::bind(&Cpu::ld_a_e, this),
          std::bind(&Cpu::ld_a_h, this),
          std::bind(&Cpu::ld_a_l, this),
          std::bind(&Cpu::ld_a_hl_ref, this),
          std::bind(&Cpu::ld_a_a, this),

          std::bind(&Cpu::add_a_b, this),
          std::bind(&Cpu::add_a_c, this),
          std::bind(&Cpu::add_a_d, this),
          std::bind(&Cpu::add_a_e, this),
          std::bind(&Cpu::add_a_h, this),
          std::bind(&Cpu::add_a_l, this),
          std::bind(&Cpu::add_a_hl_ref, this),
          std::bind(&Cpu::add_a_a, this),
          std::bind(&Cpu::adc_a_b, this),
          std::bind(&Cpu::adc_a_c, this),
          std::bind(&Cpu::adc_a_d, this),
          std::bind(&Cpu::adc_a_e, this),
          std::bind(&Cpu::adc_a_h, this),
          std::bind(&Cpu::adc_a_l, this),
          std::bind(&Cpu::adc_a_hl_ref, this),
          std::bind(&Cpu::adc_a_a, this),

          std::bind(&Cpu::sub_a_b, this),
          std::bind(&Cpu::sub_a_c, this),
          std::bind(&Cpu::sub_a_d, this),
          std::bind(&Cpu::sub_a_e, this),
          std::bind(&Cpu::sub_a_h, this),
          std::bind(&Cpu::sub_a_l, this),
          std::bind(&Cpu::sub_a_hl_ref, this),
          std::bind(&Cpu::sub_a_a, this),
          std::bind(&Cpu::sbc_a_b, this),
          std::bind(&Cpu::sbc_a_c, this),
          std::bind(&Cpu::sbc_a_d, this),
          std::bind(&Cpu::sbc_a_e, this),
          std::bind(&Cpu::sbc_a_h, this),
          std::bind(&Cpu::sbc_a_l, this),
          std::bind(&Cpu::sbc_a_hl_ref, this),
          std::bind(&Cpu::sbc_a_a, this),

          std::bind(&Cpu::and_a_b, this),
          std::bind(&Cpu::and_a_c, this),
          std::bind(&Cpu::and_a_d, this),
          std::bind(&Cpu::and_a_e, this),
          std::bind(&Cpu::and_a_h, this),
          std::bind(&Cpu::and_a_l, this),
          std::bind(&Cpu::and_a_hl_ref, this),
          std::bind(&Cpu::and_a_a, this),
          std::bind(&Cpu::xor_a_b, this),
          std::bind(&Cpu::xor_a_c, this),
          std::bind(&Cpu::xor_a_d, this),
          std::bind(&Cpu::xor_a_e, this),
          std::bind(&Cpu::xor_a_h, this),
          std::bind(&Cpu::xor_a_l, this),
          std::bind(&Cpu::xor_a_hl_ref, this),
          std::bind(&Cpu::xor_a_a, this),

          std::bind(&Cpu::or_a_b, this),
          std::bind(&Cpu::or_a_c, this),
          std::bind(&Cpu::or_a_d, this),
          std::bind(&Cpu::or_a_e, this),
          std::bind(&Cpu::or_a_h, this),
          std::bind(&Cpu::or_a_l, this),
          std::bind(&Cpu::or_a_hl_ref, this),
          std::bind(&Cpu::or_a_a, this),
          std::bind(&Cpu::cp_a_b, this),
          std::bind(&Cpu::cp_a_c, this),
          std::bind(&Cpu::cp_a_d, this),
          std::bind(&Cpu::cp_a_e, this),
          std::bind(&Cpu::cp_a_h, this),
          std::bind(&Cpu::cp_a_l, this),
          std::bind(&Cpu::cp_a_hl_ref, this),
          std::bind(&Cpu::cp_a_a, this),

          std::bind(&Cpu::ret_nz, this),
          std::bind(&Cpu::pop_bc, this),
          std::bind(&Cpu::jp_nz_nn, this),
          std::bind(&Cpu::jp_nn, this),
          std::bind(&Cpu::call_nz_nn, this),
          std::bind(&Cpu::push_bc, this),
          std::bind(&Cpu::add_a_n, this),
          std::bind(&Cpu::rst_0, this),
          std::bind(&Cpu::ret_z, this),
          std::bind(&Cpu::ret, this),
          std::bind(&Cpu::jp_z_nn, this),
          std::bind(&Cpu::call_z_nn, this),
          std::bind(&Cpu::call_nn, this),
          std::bind(&Cpu::adc_a_n, this),
          std::bind(&Cpu::rst_1, this),

          std::bind(&Cpu::ret_nc, this),
          std::bind(&Cpu::pop_de, this),
          std::bind(&Cpu::jp_nc_nn, this),
          std::bind(&Cpu::call_nc_nn, this),
          std::bind(&Cpu::push_de, this),
          std::bind(&Cpu::sub_a_n, this),
          std::bind(&Cpu::rst_2, this),
          std::bind(&Cpu::ret_c, this),
          std::bind(&Cpu::reti, this),
          std::bind(&Cpu::jp_c_nn, this),
          std::bind(&Cpu::call_c_nn, this),
          std::bind(&Cpu::sbc_a_n, this),
          std::bind(&Cpu::rst_3, this),

          std::bind(&Cpu::ld_n_ref_a, this),
          std::bind(&Cpu::pop_hl, this),
          std::bind(&Cpu::ld_c_ref_a, this),
          std::bind(&Cpu::push_hl, this),
          std::bind(&Cpu::and_a_n, this),
          std::bind(&Cpu::rst_4, this),
          std::bind(&Cpu::add_sp_n, this),
          std::bind(&Cpu::jp_hl, this),
          std::bind(&Cpu::ld_nn_ref_a, this),
          std::bind(&Cpu::xor_a_n, this),
          std::bind(&Cpu::rst_5, this),

          std::bind(&Cpu::ld_a_n_ref, this),
          std::bind(&Cpu::pop_af, this),
          std::bind(&Cpu::ld_a_c_ref, this),
          std::bind(&Cpu::di, this),
          std::bind(&Cpu::push_af, this),
          std::bind(&Cpu::or_a_n, this),
          std::bind(&Cpu::rst_6, this),
          std::bind(&Cpu::ld_hl_sp_n, this),
          std::bind(&Cpu::ld_sp_hl, this),
          std::bind(&Cpu::ld_a_nn_ref, this),
          std::bind(&Cpu::e_i, this),
          std::bind(&Cpu::cp_a_n, this),
          std::bind(&Cpu::rst_7, this),
      } {}

void Cpu::pop_stack_into_reg_16(uint16_t &reg) {
  uint8_t sp_content = memory_.read_byte(registers_.sp);
  // load sp_content to lower order by of pc
  reg &= 0xFF00;
  reg |= sp_content;
  ++registers_.sp;
  sp_content = memory_.read_byte(registers_.sp);
  // load new sp_content to higher order by of pc
  reg &= 0xFF;
  reg |= (sp_content << 8);
  ++registers_.sp;
}

void Cpu::push_onto_stack_reg_16(uint16_t content) {
  registers_.sp -= 2;
  memory_.write_word(registers_.sp, registers_.pc + 3);
  registers_.pc = content;
}

void Cpu::nop() { ++registers_.pc; }

void Cpu::ld_bc_nn() {
  registers_.bc = memory_.read_word(registers_.pc + 1);
  registers_.pc += 3;
}

void Cpu::ld_bc_a() {
  memory_.write_byte(registers_.bc, registers_.a);
  ++registers_.pc;
}

void Cpu::inc_bc() {
  ++registers_.bc;
  ++registers_.pc;
}

void Cpu::inc_b() {
  uint8_t old_value = registers_.b++;

  registers_.set_zero_flag_from_byte_result(registers_.b);
  registers_.set_half_carry_flag_from_byte_result(old_value, registers_.b, 1);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::dec_b() {
  uint8_t old_value = registers_.b--;
  registers_.set_zero_flag_from_byte_result(registers_.b);
  registers_.set_half_carry_flag_from_byte_result(old_value, registers_.b, -1);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::ld_b_n() {
  registers_.b = memory_.read_byte(registers_.pc + 1);
  registers_.pc += 2;
}

void Cpu::rlca() {
  uint8_t bit7 = (registers_.a & 0x8) >> 7;
  registers_.a = static_cast<uint8_t>(registers_.a << 1) | bit7;
  registers_.zero = 0;
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  ++registers_.pc;
}

void Cpu::ld_nn_sp() {
  uint16_t address = memory_.read_word(registers_.sp + 1);
  memory_.write_word(address, registers_.sp);
  registers_.pc += 3;
}

void Cpu::add_hl_bc() {
  uint16_t old_hl = registers_.hl;
  registers_.hl = registers_.bc + registers_.hl;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_hl, registers_.hl,
                                                  registers_.bc);
  registers_.set_carry_flag_from_word_result(old_hl, registers_.hl,
                                             registers_.bc);
  ++registers_.pc;
}

void Cpu::ld_a_bc() {
  uint8_t content = memory_.read_byte(registers_.bc);
  memory_.write_byte(registers_.a, content);
  ++registers_.pc;
}

void Cpu::dec_bc() {
  --registers_.bc;
  ++registers_.pc;
}

void Cpu::inc_c() {
  uint8_t old_c = registers_.c++;
  registers_.set_half_carry_flag_from_word_result(old_c, registers_.c, 1);
  registers_.set_zero_flag_from_byte_result(registers_.c);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::dec_c() {
  uint8_t old_c = registers_.c--;
  registers_.set_half_carry_flag_from_word_result(old_c, registers_.c, -1);
  registers_.set_zero_flag_from_byte_result(registers_.c);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::ld_c_n() {
  registers_.c = memory_.read_byte(registers_.pc + 1);
  registers_.pc += 2;
}

void Cpu::rrca() {
  uint8_t bit0 = registers_.c & 0x1;
  registers_.c = (registers_.c >> 1) | static_cast<uint8_t>(bit0 << 7);
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  ++registers_.pc;
}

// todo: finish this function
void Cpu::stop() { registers_.pc += 2; }

void Cpu::ld_de_nn() {
  registers_.de = memory_.read_word(registers_.pc + 1);
  registers_.pc += 3;
}

void Cpu::ld_de_a() {
  memory_.write_byte(registers_.de, registers_.a);
  ++registers_.pc;
}

void Cpu::inc_de() {
  ++registers_.de;
  ++registers_.pc;
}

void Cpu::inc_d() {
  uint8_t old_value = registers_.d++;

  registers_.set_zero_flag_from_byte_result(registers_.d);
  registers_.set_half_carry_flag_from_byte_result(old_value, registers_.d, 1);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::dec_d() {
  uint8_t old_value = registers_.d--;
  registers_.set_zero_flag_from_byte_result(registers_.d);
  registers_.set_half_carry_flag_from_byte_result(old_value, registers_.d, -1);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::ld_d_n() {
  registers_.d = memory_.read_byte(registers_.pc + 1);
  registers_.pc += 2;
}

void Cpu::rla() {
  uint8_t bit7 = (registers_.a & 0x8) >> 7;
  registers_.a = static_cast<uint8_t>(registers_.a << 1) | registers_.carry;
  registers_.zero = 0;
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  ++registers_.pc;
}

void Cpu::jr_s8() {
  uint16_t steps = memory_.read_word(registers_.pc + 1);
  registers_.pc += steps;
  registers_.pc += 2;
}

void Cpu::add_hl_de() {
  uint16_t old_hl = registers_.hl;
  registers_.hl = registers_.de + registers_.hl;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_hl, registers_.hl,
                                                  registers_.de);
  registers_.set_carry_flag_from_word_result(old_hl, registers_.hl,
                                             registers_.de);
  ++registers_.pc;
}

void Cpu::ld_a_de() {
  uint8_t content = memory_.read_byte(registers_.de);
  memory_.write_byte(registers_.a, content);
  ++registers_.pc;
}

void Cpu::dec_de() {
  --registers_.de;
  ++registers_.pc;
}

void Cpu::inc_e() {
  uint8_t old_e = registers_.e++;
  registers_.set_half_carry_flag_from_word_result(old_e, registers_.e, 1);
  registers_.set_zero_flag_from_byte_result(registers_.e);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::dec_e() {
  uint8_t old_e = registers_.e--;
  registers_.set_half_carry_flag_from_word_result(old_e, registers_.e, -1);
  registers_.set_zero_flag_from_byte_result(registers_.e);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::ld_e_n() {
  registers_.e = memory_.read_byte(registers_.pc + 1);
  registers_.pc += 2;
}

void Cpu::rra() {
  uint8_t bit0 = registers_.c & 0x1;
  registers_.c =
      (registers_.c >> 1) | static_cast<uint8_t>(registers_.carry << 7);
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  ++registers_.pc;
}

void Cpu::jr_nz_s8() {
  if (!registers_.zero) {
    uint16_t steps = memory_.read_word(registers_.pc + 1);
    registers_.pc += steps;
  }
  registers_.pc += 2;
}

void Cpu::ld_hl_nn() {
  registers_.hl = memory_.read_word(registers_.pc + 1);
  registers_.pc += 3;
}

void Cpu::ld_hl_inc_a() {
  memory_.write_byte(registers_.hl++, registers_.a);
  ++registers_.pc;
}

void Cpu::inc_hl() {
  ++registers_.hl;
  ++registers_.pc;
}

void Cpu::inc_h() {
  uint8_t old_h = registers_.h++;

  registers_.set_zero_flag_from_byte_result(registers_.h);
  registers_.set_half_carry_flag_from_byte_result(old_h, registers_.h, 1);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::dec_h() {
  uint8_t old_h = registers_.h--;
  registers_.set_zero_flag_from_byte_result(registers_.h);
  registers_.set_half_carry_flag_from_byte_result(old_h, registers_.h, -1);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::ld_h_n() {
  registers_.d = memory_.read_byte(registers_.pc + 1);
  registers_.pc += 2;
}

void Cpu::daa() {
  // subtraction
  if (registers_.subtract) {
    if (registers_.carry) {
      registers_.a -= 0x60;
    }
    if (registers_.half_carry) {
      registers_.a -= 0x6;
    }
  }
  // addition
  else {
    if (registers_.carry || registers_.a > 0x99) {
      registers_.a += 0x60;
      registers_.carry = 1;
    }
    if (registers_.half_carry || (registers_.a & 0xF) > 0x9) {
      registers_.a += 0x6;
    }
  }
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.half_carry = 0;
  ++registers_.pc;
}

void Cpu::jr_z_s8() {
  if (registers_.zero) {
    uint16_t steps = memory_.read_word(registers_.pc + 1);
    registers_.pc += steps;
  }
  registers_.pc += 2;
}

void Cpu::add_hl_hl() {
  uint16_t old_hl = registers_.hl;
  registers_.hl = registers_.hl + registers_.hl;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_hl, registers_.hl,
                                                  registers_.hl);
  registers_.set_carry_flag_from_word_result(old_hl, registers_.hl,
                                             registers_.hl);
  ++registers_.pc;
}

void Cpu::ld_a_hl_inc() {
  uint8_t content = memory_.read_byte(registers_.hl++);
  memory_.write_byte(registers_.a, content);
  ++registers_.pc;
}

void Cpu::dec_hl() {
  --registers_.hl;
  ++registers_.pc;
}

void Cpu::inc_l() {
  uint8_t old_l = registers_.l++;
  registers_.set_half_carry_flag_from_word_result(old_l, registers_.l, 1);
  registers_.set_zero_flag_from_byte_result(registers_.l);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::dec_l() {
  uint8_t old_l = registers_.l--;
  registers_.set_half_carry_flag_from_word_result(old_l, registers_.l, -1);
  registers_.set_zero_flag_from_byte_result(registers_.l);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::ld_l_n() {
  registers_.l = memory_.read_byte(registers_.pc + 1);
  registers_.pc += 2;
}

void Cpu::cpl() {
  registers_.a = ~registers_.a;
  registers_.subtract = 1;
  registers_.half_carry = 1;
  ++registers_.pc;
}

void Cpu::jr_nc_s8() {
  if (!registers_.carry) {
    uint16_t steps = memory_.read_word(registers_.pc + 1);
    registers_.pc += steps;
  }
  registers_.pc += 2;
}

void Cpu::ld_sp_nn() {
  registers_.sp = memory_.read_word(registers_.pc + 1);
  registers_.pc += 3;
}

void Cpu::ld_hl_dec_a() {
  memory_.write_byte(registers_.hl--, registers_.a);
  ++registers_.pc;
}

void Cpu::inc_sp() {
  ++registers_.sp;
  ++registers_.pc;
}

void Cpu::inc_hl_ref() {
  uint16_t old_hl_content = memory_.read_word(registers_.hl);
  uint16_t new_hl_content = old_hl_content + 1;
  memory_.write_word(registers_.hl, new_hl_content);

  registers_.set_zero_flag_from_word_result(new_hl_content);
  registers_.set_half_carry_flag_from_word_result(old_hl_content,
                                                  new_hl_content, 1);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::dec_hl_ref() {
  uint16_t old_hl_content = memory_.read_word(registers_.hl);
  uint16_t new_hl_content = old_hl_content - 1;
  memory_.write_word(registers_.hl, new_hl_content);

  registers_.set_zero_flag_from_word_result(new_hl_content);
  registers_.set_half_carry_flag_from_word_result(old_hl_content,
                                                  new_hl_content, -1);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::ld_hl_n() {
  uint8_t content = memory_.read_byte(registers_.pc + 1);
  memory_.write_byte(registers_.hl, content);
  registers_.pc += 2;
}

void Cpu::scf() {
  registers_.carry = 1;
  registers_.half_carry = 0;
  registers_.subtract = 0;
}

void Cpu::jr_c_s8() {
  if (registers_.carry) {
    uint16_t steps = memory_.read_word(registers_.pc + 1);
    registers_.pc += steps;
  }
  registers_.pc += 2;
}

void Cpu::add_hl_sp() {
  uint16_t old_hl = registers_.hl;
  registers_.hl = registers_.hl + registers_.sp;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_hl, registers_.hl,
                                                  registers_.sp);
  registers_.set_carry_flag_from_word_result(old_hl, registers_.hl,
                                             registers_.sp);
  ++registers_.pc;
}

void Cpu::ld_a_hl_dec() {
  uint8_t content = memory_.read_byte(registers_.hl--);
  memory_.write_byte(registers_.a, content);
  ++registers_.pc;
}

void Cpu::dec_sp() {
  --registers_.sp;
  ++registers_.pc;
}

void Cpu::inc_a() {
  uint8_t old_a = registers_.a++;
  registers_.set_half_carry_flag_from_word_result(old_a, registers_.a, 1);
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::dec_a() {
  uint8_t old_a = registers_.a--;
  registers_.set_half_carry_flag_from_word_result(old_a, registers_.a, -1);
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::ld_a_n() {
  registers_.a = memory_.read_byte(registers_.pc + 1);
  registers_.pc += 2;
}

void Cpu::ccf() {
  registers_.carry = !registers_.carry;
  registers_.subtract = 0;
  registers_.half_carry = 0;
  ++registers_.pc;
}

void Cpu::ld_b_b() {
  registers_.b = registers_.b;
  ++registers_.pc;
}
void Cpu::ld_b_c() {
  registers_.b = registers_.c;
  ++registers_.pc;
}
void Cpu::ld_b_d() {
  registers_.b = registers_.d;
  ++registers_.pc;
}
void Cpu::ld_b_e() {
  registers_.b = registers_.e;
  ++registers_.pc;
}
void Cpu::ld_b_h() {
  registers_.b = registers_.h;
  ++registers_.pc;
}
void Cpu::ld_b_l() {
  registers_.b = registers_.l;
  ++registers_.pc;
}
void Cpu::ld_b_hl_ref() { registers_.b = memory_.read_byte(registers_.hl); }
void Cpu::ld_b_a() {
  registers_.b = registers_.a;
  ++registers_.pc;
}
void Cpu::ld_c_b() {
  registers_.c = registers_.b;
  ++registers_.pc;
}
void Cpu::ld_c_c() {
  registers_.c = registers_.c;
  ++registers_.pc;
}
void Cpu::ld_c_d() {
  registers_.c = registers_.d;
  ++registers_.pc;
}
void Cpu::ld_c_e() {
  registers_.c = registers_.e;
  ++registers_.pc;
}
void Cpu::ld_c_h() {
  registers_.c = registers_.h;
  ++registers_.pc;
}
void Cpu::ld_c_l() {
  registers_.c = registers_.l;
  ++registers_.pc;
}
void Cpu::ld_c_hl_ref() { registers_.c = memory_.read_byte(registers_.hl); }
void Cpu::ld_c_a() {
  registers_.c = registers_.a;
  ++registers_.pc;
}

void Cpu::ld_d_b() {
  registers_.d = registers_.b;
  ++registers_.pc;
}
void Cpu::ld_d_c() {
  registers_.d = registers_.c;
  ++registers_.pc;
}
void Cpu::ld_d_d() {
  registers_.d = registers_.d;
  ++registers_.pc;
}
void Cpu::ld_d_e() {
  registers_.d = registers_.e;
  ++registers_.pc;
}
void Cpu::ld_d_h() {
  registers_.d = registers_.h;
  ++registers_.pc;
}
void Cpu::ld_d_l() {
  registers_.d = registers_.l;
  ++registers_.pc;
}
void Cpu::ld_d_hl_ref() { registers_.d = memory_.read_byte(registers_.hl); }
void Cpu::ld_d_a() {
  registers_.d = registers_.a;
  ++registers_.pc;
}
void Cpu::ld_e_b() {
  registers_.e = registers_.b;
  ++registers_.pc;
}
void Cpu::ld_e_c() {
  registers_.e = registers_.c;
  ++registers_.pc;
}
void Cpu::ld_e_d() {
  registers_.e = registers_.d;
  ++registers_.pc;
}
void Cpu::ld_e_e() {
  registers_.e = registers_.e;
  ++registers_.pc;
}
void Cpu::ld_e_h() {
  registers_.e = registers_.h;
  ++registers_.pc;
}
void Cpu::ld_e_l() {
  registers_.e = registers_.l;
  ++registers_.pc;
}
void Cpu::ld_e_hl_ref() { registers_.e = memory_.read_byte(registers_.hl); }
void Cpu::ld_e_a() {
  registers_.e = registers_.a;
  ++registers_.pc;
}

void Cpu::ld_h_b() {
  registers_.h = registers_.b;
  ++registers_.pc;
}
void Cpu::ld_h_c() {
  registers_.h = registers_.c;
  ++registers_.pc;
}
void Cpu::ld_h_d() {
  registers_.h = registers_.d;
  ++registers_.pc;
}
void Cpu::ld_h_e() {
  registers_.h = registers_.e;
  ++registers_.pc;
}
void Cpu::ld_h_h() {
  registers_.h = registers_.h;
  ++registers_.pc;
}
void Cpu::ld_h_l() {
  registers_.h = registers_.l;
  ++registers_.pc;
}
void Cpu::ld_h_hl_ref() { registers_.h = memory_.read_byte(registers_.hl); }
void Cpu::ld_h_a() {
  registers_.h = registers_.a;
  ++registers_.pc;
}
void Cpu::ld_l_b() {
  registers_.l = registers_.b;
  ++registers_.pc;
}
void Cpu::ld_l_c() {
  registers_.l = registers_.c;
  ++registers_.pc;
}
void Cpu::ld_l_d() {
  registers_.l = registers_.d;
  ++registers_.pc;
}
void Cpu::ld_l_e() {
  registers_.l = registers_.e;
  ++registers_.pc;
}
void Cpu::ld_l_h() {
  registers_.l = registers_.h;
  ++registers_.pc;
}
void Cpu::ld_l_l() {
  registers_.l = registers_.l;
  ++registers_.pc;
}
void Cpu::ld_l_hl_ref() { registers_.l = memory_.read_byte(registers_.hl); }
void Cpu::ld_l_a() {
  registers_.l = registers_.a;
  ++registers_.pc;
}

void Cpu::ld_hl_ref_b() {
  memory_.write_byte(registers_.hl, registers_.b);
  ++registers_.pc;
}

void Cpu::ld_hl_ref_c() {
  memory_.write_byte(registers_.hl, registers_.c);
  ++registers_.pc;
}

void Cpu::ld_hl_ref_d() {
  memory_.write_byte(registers_.hl, registers_.d);
  ++registers_.pc;
}

void Cpu::ld_hl_ref_e() {
  memory_.write_byte(registers_.hl, registers_.e);
  ++registers_.pc;
}

void Cpu::ld_hl_ref_h() {
  memory_.write_byte(registers_.hl, registers_.h);
  ++registers_.pc;
}

void Cpu::ld_hl_ref_l() {
  memory_.write_byte(registers_.hl, registers_.l);
  ++registers_.pc;
}

// todo: finish this func
void Cpu::halt() { ++registers_.pc; }

void Cpu::ld_hl_ref_a() {
  registers_.f = registers_.a;
  ++registers_.pc;
}

void Cpu::ld_a_b() {
  registers_.a = registers_.b;
  ++registers_.pc;
}

void Cpu::ld_a_c() {
  registers_.a = registers_.c;
  ++registers_.pc;
}

void Cpu::ld_a_d() {
  registers_.a = registers_.d;
  ++registers_.pc;
}

void Cpu::ld_a_e() {
  registers_.a = registers_.e;
  ++registers_.pc;
}

void Cpu::ld_a_h() {
  registers_.a = registers_.h;
  ++registers_.pc;
}

void Cpu::ld_a_l() {
  registers_.a = registers_.l;
  ++registers_.pc;
}

void Cpu::ld_a_hl_ref() { registers_.a = memory_.read_byte(registers_.hl); }

void Cpu::ld_a_a() {
  registers_.a = registers_.a;
  ++registers_.pc;
}

void Cpu::add_a_b() {
  uint8_t old_a = registers_.a;
  registers_.a += registers_.b;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.b);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.b);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::add_a_c() {
  uint8_t old_a = registers_.a;
  registers_.a += registers_.b;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.c);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.c);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::add_a_d() {
  uint8_t old_a = registers_.a;
  registers_.a += registers_.d;

  registers_.set_zero_flag_from_byte_result(registers_.d);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.d);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.d);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::add_a_e() {
  uint8_t old_a = registers_.a;
  registers_.a += registers_.e;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.e);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.e);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::add_a_h() {
  uint8_t old_a = registers_.a;
  registers_.a += registers_.h;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.h);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.h);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::add_a_l() {
  uint8_t old_a = registers_.a;
  registers_.a += registers_.l;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.l);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.l);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::add_a_hl_ref() {
  uint8_t old_a = registers_.a;
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  registers_.a += hl_content;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  hl_content);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, hl_content);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::add_a_a() {
  uint8_t old_a = registers_.a;
  registers_.a += registers_.a;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.a);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.a);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::adc_a_b() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.b + registers_.carry;
  registers_.a += operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::adc_a_c() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.c + registers_.carry;
  registers_.a += operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::adc_a_d() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.d + registers_.carry;
  registers_.a += operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::adc_a_e() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.e + registers_.carry;
  registers_.a += operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::adc_a_h() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.h + registers_.carry;
  registers_.a += operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::adc_a_l() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.l + registers_.carry;
  registers_.a += operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::adc_a_hl_ref() {
  uint8_t old_a = registers_.a;
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  uint8_t operand = hl_content + registers_.carry;
  registers_.a += operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::adc_a_a() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.a + registers_.carry;
  registers_.a += operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 0;
  ++registers_.pc;
}

void Cpu::sub_a_b() {
  uint8_t old_a = registers_.a;
  registers_.a -= registers_.b;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.b);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.b);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sub_a_c() {
  uint8_t old_a = registers_.a;
  registers_.a -= registers_.c;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.c);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.c);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sub_a_d() {
  uint8_t old_a = registers_.a;
  registers_.a -= registers_.d;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.d);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.d);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sub_a_e() {
  uint8_t old_a = registers_.a;
  registers_.a -= registers_.e;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.e);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.e);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sub_a_h() {
  uint8_t old_a = registers_.a;
  registers_.a -= registers_.h;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.h);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.h);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sub_a_l() {
  uint8_t old_a = registers_.a;
  registers_.a -= registers_.l;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.l);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.l);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sub_a_hl_ref() {
  uint8_t old_a = registers_.a;
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  registers_.a -= hl_content;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  hl_content);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, hl_content);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sub_a_a() {
  uint8_t old_a = registers_.a;
  registers_.a -= registers_.a;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a,
                                                  registers_.a);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, registers_.a);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sbc_a_b() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.b + registers_.carry;
  registers_.a -= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sbc_a_c() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.c + registers_.carry;
  registers_.a -= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sbc_a_d() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.d + registers_.carry;
  registers_.a -= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sbc_a_e() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.e + registers_.carry;
  registers_.a -= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sbc_a_h() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.h + registers_.carry;
  registers_.a -= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sbc_a_l() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.l + registers_.carry;
  registers_.a -= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sbc_a_hl_ref() {
  uint8_t old_a = registers_.a;
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  uint8_t operand = hl_content + registers_.carry;
  registers_.a -= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::sbc_a_a() {
  uint8_t old_a = registers_.a;
  uint8_t operand = registers_.a + registers_.carry;
  registers_.a -= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.subtract = 1;
  ++registers_.pc;
}

void Cpu::and_a_b() {
  registers_.a &= registers_.b;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::and_a_c() {
  registers_.a &= registers_.c;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::and_a_d() {
  registers_.a &= registers_.d;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::and_a_e() {
  registers_.a &= registers_.e;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::and_a_h() {
  registers_.a &= registers_.h;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::and_a_l() {
  registers_.a &= registers_.h;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::and_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  registers_.a &= hl_content;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::and_a_a() {
  registers_.a &= registers_.a;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::xor_a_b() {
  registers_.a ^= registers_.b;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::xor_a_c() {
  registers_.a ^= registers_.c;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::xor_a_d() {
  registers_.a ^= registers_.d;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::xor_a_e() {
  registers_.a ^= registers_.e;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::xor_a_h() {
  registers_.a ^= registers_.h;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::xor_a_l() {
  registers_.a ^= registers_.l;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::xor_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  registers_.a ^= hl_content;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::xor_a_a() {
  registers_.a ^= registers_.a;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::or_a_b() {
  registers_.a |= registers_.b;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::or_a_c() {
  registers_.a |= registers_.c;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::or_a_d() {
  registers_.a |= registers_.d;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::or_a_e() {
  registers_.a |= registers_.e;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::or_a_h() {
  registers_.a |= registers_.h;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::or_a_l() {
  registers_.a |= registers_.l;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::or_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  registers_.a |= hl_content;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::or_a_a() {
  registers_.a |= registers_.a;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
}

void Cpu::cp_a_b() {
  registers_.zero = registers_.a - registers_.b;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                                  registers_.b);
  registers_.set_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                             registers_.b);
  ++registers_.pc;
}

void Cpu::cp_a_c() {
  registers_.zero = registers_.a - registers_.c;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                                  registers_.c);
  registers_.set_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                             registers_.c);
  ++registers_.pc;
}

void Cpu::cp_a_d() {
  registers_.zero = registers_.a - registers_.d;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                                  registers_.d);
  registers_.set_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                             registers_.d);
  ++registers_.pc;
}

void Cpu::cp_a_e() {
  registers_.zero = registers_.a - registers_.e;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                                  registers_.e);
  registers_.set_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                             registers_.e);
  ++registers_.pc;
}

void Cpu::cp_a_h() {
  registers_.zero = registers_.a - registers_.h;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                                  registers_.h);
  registers_.set_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                             registers_.h);
  ++registers_.pc;
}

void Cpu::cp_a_l() {
  registers_.zero = registers_.a - registers_.l;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                                  registers_.l);
  registers_.set_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                             registers_.l);
  ++registers_.pc;
}

void Cpu::cp_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  registers_.zero = registers_.a - hl_content;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                                  hl_content);
  registers_.set_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                             hl_content);
  ++registers_.pc;
}

void Cpu::cp_a_a() {
  registers_.zero = registers_.a - registers_.a;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                                  registers_.a);
  registers_.set_carry_flag_from_byte_result(registers_.a, registers_.zero,
                                             registers_.a);
  ++registers_.pc;
}

void Cpu::ret_nz() {
  if (!registers_.zero) {
    pop_stack_into_reg_16(registers_.pc);
  }
  ++registers_.pc;
}

void Cpu::pop_bc() {
  pop_stack_into_reg_16(registers_.bc);
  ++registers_.pc;
}

void Cpu::jp_nz_nn() {
  if (!registers_.zero) {
    registers_.pc = memory_.read_word(registers_.pc + 1);
  } else {
    registers_.pc += 3;
  }
}

void Cpu::jp_nn() { registers_.pc = memory_.read_word(registers_.pc + 1); }

void Cpu::call_nz_nn() {
  if (!registers_.zero) {
    uint16_t call_address = memory_.read_word(registers_.pc + 1);
    push_onto_stack_reg_16(call_address);
  } else {
    registers_.pc += 3;
  }
}

void Cpu::push_bc() {
  push_onto_stack_reg_16(registers_.bc);
  ++registers_.pc;
}

void Cpu::add_a_n() {
  uint8_t old_a = registers_.a;
  uint8_t operand = memory_.read_byte(registers_.pc + 1);
  registers_.a += operand;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.pc += 2;
}

void Cpu::rst_0() {
  push_onto_stack_reg_16(registers_.pc);
  registers_.pc = 0x00;
}

void Cpu::ret_z() {
  if (registers_.zero) {
    pop_stack_into_reg_16(registers_.pc);
  }
  ++registers_.pc;
}

void Cpu::ret() {
  pop_stack_into_reg_16(registers_.pc);
  ++registers_.pc;
}

void Cpu::jp_z_nn() {
  if (registers_.zero) {
    registers_.pc = memory_.read_word(registers_.pc + 1);
  } else {
    registers_.pc += 3;
  }
}

void Cpu::call_z_nn() {
  if (registers_.zero) {
    uint16_t call_address = memory_.read_word(registers_.pc + 1);
    push_onto_stack_reg_16(call_address);
  } else {
    registers_.pc += 3;
  }
}

void Cpu::call_nn() {
  uint16_t call_address = memory_.read_word(registers_.pc + 1);
  push_onto_stack_reg_16(call_address);
}

void Cpu::adc_a_n() {
  uint8_t old_a = registers_.a;
  uint8_t operand = memory_.read_byte(registers_.pc + 1) + registers_.carry;
  registers_.a += operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.pc += 2;
}

void Cpu::rst_1() {
  push_onto_stack_reg_16(registers_.pc);
  registers_.pc = 0x08;
}

void Cpu::ret_nc() {
  if (!registers_.carry) {
    pop_stack_into_reg_16(registers_.pc);
  }
  ++registers_.pc;
}

void Cpu::pop_de() {
  pop_stack_into_reg_16(registers_.de);
  ++registers_.pc;
}

void Cpu::jp_nc_nn() {
  if (!registers_.carry) {
    registers_.pc = memory_.read_word(registers_.pc + 1);
  } else {
    registers_.pc += 3;
  }
}

void Cpu::call_nc_nn() {
  if (!registers_.carry) {
    uint16_t call_address = memory_.read_word(registers_.pc + 1);
    push_onto_stack_reg_16(call_address);
  } else {
    registers_.pc += 3;
  }
}

void Cpu::push_de() {
  push_onto_stack_reg_16(registers_.de);
  ++registers_.pc;
}

void Cpu::sub_a_n() {
  uint8_t old_a = registers_.a;
  uint8_t operand = memory_.read_byte(registers_.pc + 1);
  registers_.a -= operand;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.pc += 2;
}

void Cpu::rst_2() {
  push_onto_stack_reg_16(registers_.pc);
  registers_.pc = 0x10;
}

void Cpu::ret_c() {
  if (registers_.carry) {
    pop_stack_into_reg_16(registers_.pc);
  }
  ++registers_.pc;
}

void Cpu::reti() {
  // todo finish this func
  ++registers_.pc;
}

void Cpu::jp_c_nn() {
  if (registers_.carry) {
    registers_.pc = memory_.read_word(registers_.pc + 1);
  } else {
    registers_.pc += 3;
  }
}

void Cpu::call_c_nn() {
  if (registers_.carry) {
    uint16_t call_address = memory_.read_word(registers_.pc + 1);
    push_onto_stack_reg_16(call_address);
  } else {
    registers_.pc += 3;
  }
}

void Cpu::sbc_a_n() {
  uint8_t old_a = registers_.a;
  uint8_t operand = memory_.read_byte(registers_.pc + 1) + registers_.carry;
  registers_.a -= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.pc += 2;
}

void Cpu::rst_3() {
  push_onto_stack_reg_16(registers_.pc);
  registers_.pc = 0x18;
}

void Cpu::ld_n_ref_a() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  memory_.write_byte(0xFF00 | imm_op, registers_.a);
  registers_.pc += 2;
}

void Cpu::pop_hl() {
  pop_stack_into_reg_16(registers_.hl);
  ++registers_.pc;
}

void Cpu::ld_c_ref_a() {
  uint8_t address =
      memory_.read_byte(static_cast<uint8_t>(0xFF00) | registers_.c);
  memory_.write_byte(address, registers_.a);
  ++registers_.pc;
}

void Cpu::push_hl() {
  push_onto_stack_reg_16(registers_.hl);
  ++registers_.pc;
}

void Cpu::and_a_n() {
  uint8_t old_a = registers_.a;
  uint8_t operand = memory_.read_byte(registers_.pc + 1);
  registers_.a &= operand;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.set_carry_flag_from_byte_result(old_a, registers_.a, operand);
  registers_.pc += 2;
}

void Cpu::rst_4() {
  push_onto_stack_reg_16(registers_.pc);
  registers_.pc = 0x20;
}

void Cpu::add_sp_n() {
  uint16_t old_sp = registers_.sp;
  int8_t operand = static_cast<int8_t>(memory_.read_byte(registers_.pc + 1));
  registers_.sp += operand;
  registers_.zero = 0;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_sp, registers_.a,
                                                  operand);
  registers_.set_carry_flag_from_word_result(old_sp, registers_.a, operand);
  registers_.pc += 2;
}

void Cpu::jp_hl() { registers_.pc = memory_.read_word(registers_.hl + 1); }

void Cpu::ld_nn_ref_a() {
  uint16_t imm_op = memory_.read_word(registers_.pc + 1);
  memory_.write_byte(imm_op, registers_.a);
  registers_.pc += 2;
}

void Cpu::xor_a_n() {
  uint8_t operand = memory_.read_byte(registers_.pc + 1) + registers_.carry;
  registers_.a ^= operand;

  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  registers_.pc += 2;
}

void Cpu::rst_5() {
  push_onto_stack_reg_16(registers_.pc);
  registers_.pc = 0x28;
}

void Cpu::ld_a_n_ref() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  registers_.a = memory_.read_byte(imm_op);
  registers_.pc += 2;
}

void Cpu::pop_af() {
  pop_stack_into_reg_16(registers_.af);
  ++registers_.pc;
}

void Cpu::ld_a_c_ref() {
  uint8_t content =
      memory_.read_byte(static_cast<uint8_t>(0xFF00) | registers_.c);
  registers_.a = content;
  ++registers_.pc;
}

// todo: finish this func
void Cpu::di() { ++registers_.pc; }

void Cpu::push_af() {
  push_onto_stack_reg_16(registers_.af);
  ++registers_.pc;
}

void Cpu::or_a_n() {
  uint8_t operand = memory_.read_byte(registers_.pc + 1);
  registers_.a |= operand;
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  registers_.pc += 2;
}

void Cpu::rst_6() {
  push_onto_stack_reg_16(registers_.pc);
  registers_.pc = 0x30;
}

void Cpu::ld_hl_sp_n() {
  registers_.hl = static_cast<uint16_t>(
      registers_.sp +
      static_cast<int8_t>(memory_.read_byte(registers_.pc + 1)));
  registers_.pc += 2;
}

void Cpu::ld_sp_hl() {
  registers_.sp = registers_.hl;
  ++registers_.pc;
}

void Cpu::ld_a_nn_ref() {
  uint16_t imm_op = memory_.read_word(registers_.pc + 1);
  registers_.a = memory_.read_byte(imm_op);
  registers_.pc += 2;
}

// todo: finish this func
void Cpu::e_i() { ++registers_.pc; }

void Cpu::cp_a_n() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  uint8_t comp = registers_.a - imm_op;

  registers_.zero = comp == 0;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(registers_.a, comp, imm_op);
  registers_.set_carry_flag_from_byte_result(registers_.a, comp, imm_op);
  registers_.pc += 2;
}

void Cpu::rst_7() {
  push_onto_stack_reg_16(registers_.pc);
  registers_.pc = 0x38;
}

} // namespace Core
} // namespace GameBoyEmu
