#pragma once

#include <array>
#include <stdint.h>

namespace GameBoyEmu {
namespace Core {

class Memory {
public:
  Memory();
  uint8_t read_byte(uint16_t addr) const;
  uint16_t read_word(uint16_t addr) const;
  void write_byte(uint16_t addr, uint8_t byte);
  void write_word(uint16_t addr, uint16_t word);

private:
  static constexpr uint16_t MAX_SPACE = 0xFFFF;
  std::array<uint8_t, MAX_SPACE + 1> memory_space_{};
};

} // namespace Core
} // namespace GameBoyEmu
