#include "gameboyemu/core/cpu.h"
#include <functional>
#include <iostream>

namespace GameBoyEmu {
namespace Core {

Cpu::Cpu()
    : instructions_{
          std::bind(&Cpu::nop, this),         std::bind(&Cpu::ld_bc_nn, this),
          std::bind(&Cpu::ld_bc_a, this),     std::bind(&Cpu::inc_bc, this),
          std::bind(&Cpu::inc_b, this),       std::bind(&Cpu::dec_b, this),
          std::bind(&Cpu::ld_b_n, this),      std::bind(&Cpu::rlca, this),
          std::bind(&Cpu::ld_nn_sp, this),    std::bind(&Cpu::add_hl_bc, this),
          std::bind(&Cpu::ld_a_bc, this),     std::bind(&Cpu::dec_bc, this),
          std::bind(&Cpu::inc_c, this),       std::bind(&Cpu::dec_c, this),
          std::bind(&Cpu::ld_c_n, this),      std::bind(&Cpu::rrca, this),

          std::bind(&Cpu::stop, this),        std::bind(&Cpu::ld_de_nn, this),
          std::bind(&Cpu::ld_de_a, this),     std::bind(&Cpu::inc_de, this),
          std::bind(&Cpu::inc_d, this),       std::bind(&Cpu::dec_d, this),
          std::bind(&Cpu::ld_d_n, this),      std::bind(&Cpu::rla, this),
          std::bind(&Cpu::jr_s8, this),       std::bind(&Cpu::add_hl_de, this),
          std::bind(&Cpu::ld_a_de, this),     std::bind(&Cpu::dec_de, this),
          std::bind(&Cpu::inc_e, this),       std::bind(&Cpu::dec_e, this),
          std::bind(&Cpu::ld_e_n, this),      std::bind(&Cpu::rra, this),

          std::bind(&Cpu::jr_nz_s8, this),    std::bind(&Cpu::ld_hl_nn, this),
          std::bind(&Cpu::ld_hl_inc_a, this), std::bind(&Cpu::inc_hl, this),
          std::bind(&Cpu::inc_h, this),       std::bind(&Cpu::dec_h, this),
          std::bind(&Cpu::ld_h_n, this),      std::bind(&Cpu::daa, this),
          std::bind(&Cpu::jr_z_s8, this),     std::bind(&Cpu::add_hl_hl, this),
          std::bind(&Cpu::ld_a_hl_inc, this), std::bind(&Cpu::dec_hl, this),
          std::bind(&Cpu::inc_l, this),       std::bind(&Cpu::dec_l, this),
          std::bind(&Cpu::ld_l_n, this),      std::bind(&Cpu::cpl, this),

          std::bind(&Cpu::jr_nc_s8, this),    std::bind(&Cpu::ld_sp_nn, this),
          std::bind(&Cpu::ld_hl_dec_a, this), std::bind(&Cpu::inc_sp, this),
          std::bind(&Cpu::inc_hl_ref, this),  std::bind(&Cpu::dec_hl_ref, this),
          std::bind(&Cpu::ld_hl_n, this),     std::bind(&Cpu::scf, this),
          std::bind(&Cpu::jr_c_s8, this),     std::bind(&Cpu::add_hl_sp, this),
          std::bind(&Cpu::ld_a_hl_dec, this), std::bind(&Cpu::dec_sp, this),
          std::bind(&Cpu::inc_a, this),       std::bind(&Cpu::dec_a, this),
          std::bind(&Cpu::ld_a_n, this),      std::bind(&Cpu::ccf, this),
      } {}

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

} // namespace Core
} // namespace GameBoyEmu
