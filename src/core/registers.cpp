#include "gameboyemu/core/registers.h"

namespace GameBoyEmu {
namespace Core {

void Registers::set_half_carry_flag_from_byte_result(uint8_t old_value,
                                                     uint8_t result,
                                                     int16_t value) {
  if (((static_cast<int16_t>(old_value) ^ value ^
        static_cast<int16_t>(result)) &
       0x10) == 0x10) {
    half_carry = 1;
  } else {
    half_carry = 0;
  }
}

void Registers::set_half_carry_flag_from_word_result(uint16_t old_value,
                                                     uint16_t result,
                                                     int32_t value) {
  if (((static_cast<int32_t>(old_value) ^ value ^
        static_cast<int32_t>(result)) &
       0x100) == 0x100) {
    half_carry = 1;
  } else {
    half_carry = 0;
  }
}

void Registers::set_carry_flag_from_byte_result(uint8_t old_value,
                                                uint8_t result, int16_t value) {
  if (((static_cast<int16_t>(old_value) ^ value ^
        static_cast<int16_t>(result)) &
       0x100) == 0x100) {
    carry = 1;
  } else {
    carry = 0;
  }
}

void Registers::set_carry_flag_from_word_result(uint16_t old_value,
                                                uint16_t result,
                                                int32_t value) {
  if (((static_cast<int32_t>(old_value) ^ (value) ^
        static_cast<int32_t>(result)) &
       0x10000) == 0x10000) {
    carry = 1;
  } else {
    carry = 0;
  }
}

} // namespace Core
} // namespace GameBoyEmu
