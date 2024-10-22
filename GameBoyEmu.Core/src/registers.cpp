#include "gameboyemucore/registers.h"

namespace GameBoyEmuCore {

void Registers::set_half_carry_flag_from_byte_result(uint8_t old_value,
                                                     uint8_t result,
                                                     int8_t value) {
  if (((old_value ^ value ^ result) & 0x10) == 0x10) {
    half_carry = 1;
  } else {
    half_carry = 0;
  }
}

} // namespace GameBoyEmuCore
