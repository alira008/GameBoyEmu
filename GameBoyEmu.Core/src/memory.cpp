#include "gameboyemucore/memory.h"

namespace GameBoyEmuCore {
uint8_t Memory::read_byte(uint16_t addr) const {}
uint16_t Memory::read_word(uint16_t addr) const {}
void Memory::write_byte(uint16_t addr, uint8_t byte) {}
void Memory::write_word(uint16_t addr, uint16_t word) {}
} // namespace GameBoyEmuCore
