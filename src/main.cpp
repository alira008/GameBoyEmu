#include "gameboyemu.h"
#include "raylib.h"
#include <iostream>

int main() {
  GameBoyEmu::Core::Cpu cpu{};
  GameBoyEmu::Core::Disassembler disassembler{cpu};
  disassembler.RunLoop();
  return 0;
}
