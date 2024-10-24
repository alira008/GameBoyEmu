#include "gameboyemu/core/cpu.h"
#include <functional>
#include <iostream>

namespace GameBoyEmu {
namespace Core {

Cpu::Cpu()
    : instructions_{
          std::bind(&Cpu::nop, this),      std::bind(&Cpu::ld_bc_nn, this),
          std::bind(&Cpu::ld_bc_a, this),  std::bind(&Cpu::inc_bc, this),
          std::bind(&Cpu::inc_b, this),    std::bind(&Cpu::dec_b, this),
          std::bind(&Cpu::ld_b_n, this),   std::bind(&Cpu::rlca, this),
          std::bind(&Cpu::ld_nn_sp, this), std::bind(&Cpu::add_hl_bc, this),
          std::bind(&Cpu::ld_a_bc, this),  std::bind(&Cpu::dec_bc, this),
          std::bind(&Cpu::inc_c, this),    std::bind(&Cpu::dec_c, this),
          std::bind(&Cpu::ld_c_n, this),   std::bind(&Cpu::rrca, this),

          std::bind(&Cpu::stop, this),     std::bind(&Cpu::ld_de_nn, this),
          std::bind(&Cpu::ld_de_a, this),  std::bind(&Cpu::inc_de, this),
          std::bind(&Cpu::inc_d, this),    std::bind(&Cpu::dec_d, this),
          std::bind(&Cpu::ld_d_n, this),   std::bind(&Cpu::rla, this),
          std::bind(&Cpu::jr_s8, this),    std::bind(&Cpu::add_hl_de, this),
          std::bind(&Cpu::ld_a_de, this),  std::bind(&Cpu::dec_de, this),
          std::bind(&Cpu::inc_e, this),    std::bind(&Cpu::dec_e, this),
          std::bind(&Cpu::ld_e_n, this),   std::bind(&Cpu::rra, this),
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
  registers_.set_zero_flag_from_byte_result(registers_.a);
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
  registers_.set_zero_flag_from_byte_result(registers_.a);
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

} // namespace Core
} // namespace GameBoyEmu
