#include "gameboyemu/core/disassembly.h"
#include "gameboyemu/core/cpu.h"
#include "raylib.h"
#include <string>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

namespace GameBoyEmu {
namespace Core {

constexpr std::string_view WINDOW_NAME = "GameBoyEmu Disassembler";
constexpr int WINDOW_HEIGHT = 800;
constexpr int WINDOW_WIDTH = 1020;

Disassembler::Disassembler(Cpu &cpu) : cpu_(cpu) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME.data());
}
Disassembler::~Disassembler() { CloseWindow(); }
void Disassembler::DrawWindow() {
  BeginDrawing();

  ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

  // raygui: controls drawing
  //----------------------------------------------------------------------------------
  GuiGroupBox((Rectangle){24, 24, 720, 552}, "Disassembler");
  GuiGroupBox((Rectangle){48, 48, 144, 504},
              address_space_group_box_text_.data());
  GuiGroupBox((Rectangle){24, 600, 960, 120}, controls_group_box_text_.data());

  // registers
  //----------------------------------------------------------------------------------
  GuiGroupBox((Rectangle){768, 24, 216, 252}, registers_group_box_text_.data());
  const Registers& registers = cpu_.registers();
  Color z_flag_color = registers.zero ? RED : GRAY;
  Color n_flag_color = registers.subtract ? RED : GRAY;
  Color h_flag_color = registers.half_carry ? RED : GRAY;
  Color c_flag_color = registers.carry ? RED : GRAY;
  DrawText("Flags:", 768 + 8 * 1, 24 + 8, 20, GRAY);
  DrawText("Z", 768 + 64 + 8 * 2, 24 + 8, 20, z_flag_color);
  DrawText("N", 768 + 64 + 8 * 5, 24 + 8, 20, n_flag_color);
  DrawText("H", 768 + 64 + 8 * 8, 24 + 8, 20, h_flag_color);
  DrawText("C", 768 + 64 + 8 * 11, 24 + 8, 20, c_flag_color);
  DrawText("A:", 768 + 8, 24 + 18 + 8, 18, GRAY);
  //----------------------------------------------------------------------------------

  GuiGroupBox((Rectangle){768, 296, 216, 280},
              disassembly_group_box_text_.data());
  GuiGroupBox((Rectangle){216, 48, 500, 504},
              memory_space_group_box_text_.data());
  // GuiTextBox((Rectangle){56, 56, 128, 28}, "0xFF", 130, false);
  DrawText("0x0000", 66, 56, 18, GRAY);
  DrawText("0xFFFF", 66, 78, 18, GRAY);
  DrawText("0xFFFF", 66, 56, 18, GRAY);
  DrawText("0xFFFF", 66, 56, 18, GRAY);
  DrawText("0xFFFF", 66, 56, 18, GRAY);
  DrawText("0xFFFF", 66, 56, 18, GRAY);
  //----------------------------------------------------------------------------------

  EndDrawing();
}
void Disassembler::RunLoop() {
  while (!WindowShouldClose()) {
    DrawWindow();
  }
}

} // namespace Core
} // namespace GameBoyEmu
