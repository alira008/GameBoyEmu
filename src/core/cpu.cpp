#include "gameboyemu/core/cpu.h"
#include <iostream>

namespace GameBoyEmu {
namespace Core {

void Cpu::nop() { ++registers_.pc; }

void Cpu::ld_bc_nn() {
  registers_.bc = memory_.read_word(registers_.pc + 1);
  registers_.pc += 3;
}

void Cpu::ld_bc_a() {
  memory_.write_byte(registers_.bc, registers_.a);
  ++registers_.pc;
}

void Cpu::inc_bc() { ++registers_.pc; }

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

} // namespace Core
} // namespace GameBoyEmu
