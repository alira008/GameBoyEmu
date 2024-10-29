#include "gameboyemu/core/memory.h"
#include <cassert>

namespace GameBoyEmu {
namespace Core {

uint8_t Memory::read_byte(uint16_t addr) const {
  assert(addr > 0 && addr < MAX_SPACE);
  return memory_space_[addr];
}

uint16_t Memory::read_word(uint16_t addr) const {
  assert(addr > 0 && addr < MAX_SPACE);
  return static_cast<uint16_t>(static_cast<uint16_t>(memory_space_[addr])
                               << 8) |
         static_cast<uint16_t>(memory_space_[addr]);
}

void Memory::write_byte(uint16_t addr, uint8_t byte) {
  assert(addr > 0 && addr < MAX_SPACE);
  memory_space_[addr] = byte;
}

void Memory::write_word(uint16_t addr, uint16_t word) {
  assert(addr > 0 && addr < MAX_SPACE);
  memory_space_[addr] = (word & 0xFF00) >> 8;
  memory_space_[addr + 1] = word & 0xFF;
}

} // namespace Core
} // namespace GameBoyEmu
