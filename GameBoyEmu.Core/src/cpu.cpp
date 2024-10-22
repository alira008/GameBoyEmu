#include <gameboyemucore/cpu.h>
#include <iostream>

namespace GameBoyEmuCore {

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

} // namespace GameBoyEmuCore
