#pragma once

#include <array>
#include <stdint.h>

namespace GameBoyEmuCore {

class Memory {
public:
  uint8_t read_byte(uint16_t addr) const;
  uint16_t read_word(uint16_t addr) const;
  void write_byte(uint16_t addr, uint8_t byte);
  void write_word(uint16_t addr, uint16_t word);

private:
  std::array<uint8_t, 0xFFFF> memory_space_;
};

} // namespace GameBoyEmuCore
