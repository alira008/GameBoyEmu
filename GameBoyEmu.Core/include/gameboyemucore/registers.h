#pragma once
#include <cstdint>

namespace GameBoyEmuCore {

struct Registers {
  union {
    struct {
      uint8_t a;
      union {
        uint8_t f;
        struct {
          uint8_t _unused : 4;
          // flags are in bit 4-7
          uint8_t carry : 1;
          uint8_t half_carry : 1;
          uint8_t subtract : 1;
          uint8_t zero : 1;
        };
      };
    };
    uint16_t af;
  };
  union {
    struct {
      uint8_t b;
      uint8_t c;
    };
    uint16_t bc;
  };
  union {
    struct {
      uint8_t d;
      uint8_t e;
    };
    uint16_t de;
  };
  union {
    struct {
      uint8_t h;
      uint8_t l;
    };
    uint16_t hl;
  };
  uint16_t sp;
  uint16_t pc;

  inline void set_zero_flag_from_byte_result(uint8_t result) {
    zero = static_cast<uint8_t>(result == 0);
  }

  void set_half_carry_flag_from_byte_result(uint8_t old_value, uint8_t result,
                                            int8_t value);
};

} // namespace GameBoyEmuCore
