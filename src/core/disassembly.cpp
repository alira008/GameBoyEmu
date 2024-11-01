#include "gameboyemu/core/disassembly.h"
#include "gameboyemu/core/cpu.h"
#include "raylib.h"
#include <cstdio>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

namespace GameBoyEmu {
namespace Core {

constexpr std::string_view WINDOW_NAME = "GameBoyEmu Disassembler";
constexpr int WINDOW_HEIGHT = 800;
constexpr int WINDOW_WIDTH = 1020;
constexpr int REG_X_POS = 768;
constexpr int REG_Y_POS = 24;
constexpr int REG_ITEM_PADDING = 8;
constexpr int FLAGS_OFFSET = REG_X_POS + 64;
constexpr int REG_X_OFFSET = REG_X_POS + REG_ITEM_PADDING;
constexpr int REG_Y_INIT_OFFSET = REG_Y_POS + REG_ITEM_PADDING + 4;
constexpr int FLAGS_Y_POS = REG_Y_POS + REG_ITEM_PADDING;
constexpr int FLAG_Y_POS = REG_Y_POS + REG_ITEM_PADDING + 2;
constexpr int REG_FONT_SIZE = 18;
constexpr int FLAG_FONT_SIZE = 20;
constexpr int reg_offset_calc(int initial_offset, int padding, int multiplier) {
  return initial_offset + padding * multiplier;
}

template <typename T>
void output_uint_to_buf(T num, char *buf, std::size_t max_size) {
  int buf_len = std::snprintf(buf, max_size, "0x%X", num);
  if (static_cast<std::size_t>(buf_len) > max_size) {
    buf[0] = 'E';
    buf[1] = 'r';
    buf[2] = 'r';
    buf[3] = 'o';
    buf[4] = 'r';
    buf[5] = '\0';
    buf_len = 5;
  } else {
    buf[buf_len] = '\0';
  }
}

Disassembler::Disassembler(Cpu &cpu) : cpu_(cpu), font_{} {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME.data());
  font_ = LoadFont("resources/roboto_font/Roboto-Regular.ttf");
}
Disassembler::~Disassembler() {
  CloseWindow();
  UnloadFont(font_);
}
void Disassembler::DrawTextWithFont(const char *text, int pos_x, int pos_y,
                                    int font_size, Color color) {
  DrawTextEx(font_, text,
             Vector2{static_cast<float>(pos_x), static_cast<float>(pos_y)},
             static_cast<float>(font_size), 2, GRAY);
}
void Disassembler::DrawWindow() {
  BeginDrawing();

  ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

  // raygui: controls drawing
  //----------------------------------------------------------------------------------
  GuiGroupBox(Rectangle{24, 24, 720, 552}, "Disassembler");
  GuiGroupBox(Rectangle{48, 48, 144, 504}, address_space_group_box_text_);
  GuiGroupBox(Rectangle{24, 600, 960, 120}, controls_group_box_text_);

  // registers
  //----------------------------------------------------------------------------------
  GuiGroupBox(Rectangle{REG_X_POS, REG_Y_POS, 216, 196},
              registers_group_box_text_);

  const Registers &registers = cpu_.registers();
  Color z_flag_color = registers.zero ? RED : GRAY;
  Color n_flag_color = registers.subtract ? RED : GRAY;
  Color h_flag_color = registers.half_carry ? RED : GRAY;
  Color c_flag_color = registers.carry ? RED : GRAY;
  const std::size_t max_buf_len = 6;
  char buf[max_buf_len];

  DrawTextWithFont("Flags:", REG_X_POS + REG_ITEM_PADDING * 1, FLAGS_Y_POS,
                   FLAG_FONT_SIZE, GRAY);
  // DrawText("Flags:", REG_X_POS + REG_ITEM_PADDING * 1, FLAGS_Y_POS,
  //          FLAG_FONT_SIZE, GRAY);
  DrawTextWithFont("Z", reg_offset_calc(FLAGS_OFFSET, REG_ITEM_PADDING, 2), FLAG_Y_POS,
           REG_FONT_SIZE, z_flag_color);
  DrawTextWithFont("N", reg_offset_calc(FLAGS_OFFSET, REG_ITEM_PADDING, 5), FLAG_Y_POS,
           REG_FONT_SIZE, n_flag_color);
  DrawTextWithFont("H", reg_offset_calc(FLAGS_OFFSET, REG_ITEM_PADDING, 8), FLAG_Y_POS,
           REG_FONT_SIZE, h_flag_color);
  DrawTextWithFont("C", reg_offset_calc(FLAGS_OFFSET, REG_ITEM_PADDING, 11), FLAG_Y_POS,
           REG_FONT_SIZE, c_flag_color);
  DrawTextWithFont("A:", REG_X_OFFSET,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 1), 18, GRAY);
  DrawTextWithFont("B:", REG_X_OFFSET,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 2), REG_FONT_SIZE,
           GRAY);
  DrawTextWithFont("C:", REG_X_OFFSET,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 3), REG_FONT_SIZE,
           GRAY);
  DrawTextWithFont("D:", REG_X_OFFSET,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 4), REG_FONT_SIZE,
           GRAY);
  DrawTextWithFont("E:", REG_X_OFFSET,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 5), REG_FONT_SIZE,
           GRAY);
  DrawTextWithFont("H:", REG_X_OFFSET,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 6), REG_FONT_SIZE,
           GRAY);
  DrawTextWithFont("L:", REG_X_OFFSET,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 7), REG_FONT_SIZE,
           GRAY);
  DrawTextWithFont("SP:", REG_X_OFFSET,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 8), REG_FONT_SIZE,
           GRAY);
  DrawTextWithFont("PC:", REG_X_OFFSET,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 9), REG_FONT_SIZE,
           GRAY);

  // register outputs
  output_uint_to_buf(registers.a, buf, max_buf_len);
  DrawTextWithFont(buf, REG_X_OFFSET + 36,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 1), REG_FONT_SIZE,
           GRAY);
  output_uint_to_buf(registers.b, buf, max_buf_len);
  DrawTextWithFont(buf, REG_X_OFFSET + 36,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 2), REG_FONT_SIZE,
           GRAY);
  output_uint_to_buf(registers.c, buf, max_buf_len);
  DrawTextWithFont(buf, REG_X_OFFSET + 36,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 3), REG_FONT_SIZE,
           GRAY);
  output_uint_to_buf(registers.d, buf, max_buf_len);
  DrawTextWithFont(buf, REG_X_OFFSET + 36,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 4), REG_FONT_SIZE,
           GRAY);
  output_uint_to_buf(registers.e, buf, max_buf_len);
  DrawTextWithFont(buf, REG_X_OFFSET + 36,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 5), REG_FONT_SIZE,
           GRAY);
  output_uint_to_buf(registers.h, buf, max_buf_len);
  DrawTextWithFont(buf, REG_X_OFFSET + 36,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 6), REG_FONT_SIZE,
           GRAY);
  output_uint_to_buf(registers.l, buf, max_buf_len);
  DrawTextWithFont(buf, REG_X_OFFSET + 36,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 7), REG_FONT_SIZE,
           GRAY);
  output_uint_to_buf(registers.sp, buf, max_buf_len);
  DrawTextWithFont(buf, REG_X_OFFSET + 36,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 8), REG_FONT_SIZE,
           GRAY);
  output_uint_to_buf(registers.pc, buf, max_buf_len);
  DrawTextWithFont(buf, REG_X_OFFSET + 36,
           reg_offset_calc(REG_Y_INIT_OFFSET, REG_FONT_SIZE, 9), REG_FONT_SIZE,
           GRAY);
  //----------------------------------------------------------------------------------

  GuiGroupBox(Rectangle{768, 240, 216, 336}, disassembly_group_box_text_);
  GuiGroupBox(Rectangle{216, 48, 500, 504}, memory_space_group_box_text_);
  DrawTextWithFont("0x0000", 66, 56, 18, GRAY);
  DrawTextWithFont("0xFFFF", 66, 78, 18, GRAY);
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
