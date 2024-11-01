#include "gameboyemu/core/cpu.h"
#include <cassert>
#include <functional>
#include <iostream>

namespace GameBoyEmu {
namespace Core {

Cpu::Cpu()
    : instructions_{
          std::bind(&Cpu::nop, this),
          std::bind(&Cpu::ld_bc_nn, this),
          std::bind(&Cpu::ld_bc_a, this),
          std::bind(&Cpu::inc_bc, this),
          std::bind(&Cpu::inc_b, this),
          std::bind(&Cpu::dec_b, this),
          std::bind(&Cpu::ld_b_n, this),
          std::bind(&Cpu::rlca, this),
          std::bind(&Cpu::ld_nn_sp, this),
          std::bind(&Cpu::add_hl_bc, this),
          std::bind(&Cpu::ld_a_bc, this),
          std::bind(&Cpu::dec_bc, this),
          std::bind(&Cpu::inc_c, this),
          std::bind(&Cpu::dec_c, this),
          std::bind(&Cpu::ld_c_n, this),
          std::bind(&Cpu::rrca, this),

          std::bind(&Cpu::stop, this),
          std::bind(&Cpu::ld_de_nn, this),
          std::bind(&Cpu::ld_de_a, this),
          std::bind(&Cpu::inc_de, this),
          std::bind(&Cpu::inc_d, this),
          std::bind(&Cpu::dec_d, this),
          std::bind(&Cpu::ld_d_n, this),
          std::bind(&Cpu::rla, this),
          std::bind(&Cpu::jr_s8, this),
          std::bind(&Cpu::add_hl_de, this),
          std::bind(&Cpu::ld_a_de, this),
          std::bind(&Cpu::dec_de, this),
          std::bind(&Cpu::inc_e, this),
          std::bind(&Cpu::dec_e, this),
          std::bind(&Cpu::ld_e_n, this),
          std::bind(&Cpu::rra, this),

          std::bind(&Cpu::jr_nz_s8, this),
          std::bind(&Cpu::ld_hl_nn, this),
          std::bind(&Cpu::ld_hl_inc_a, this),
          std::bind(&Cpu::inc_hl, this),
          std::bind(&Cpu::inc_h, this),
          std::bind(&Cpu::dec_h, this),
          std::bind(&Cpu::ld_h_n, this),
          std::bind(&Cpu::daa, this),
          std::bind(&Cpu::jr_z_s8, this),
          std::bind(&Cpu::add_hl_hl, this),
          std::bind(&Cpu::ld_a_hl_inc, this),
          std::bind(&Cpu::dec_hl, this),
          std::bind(&Cpu::inc_l, this),
          std::bind(&Cpu::dec_l, this),
          std::bind(&Cpu::ld_l_n, this),
          std::bind(&Cpu::cpl, this),

          std::bind(&Cpu::jr_nc_s8, this),
          std::bind(&Cpu::ld_sp_nn, this),
          std::bind(&Cpu::ld_hl_dec_a, this),
          std::bind(&Cpu::inc_sp, this),
          std::bind(&Cpu::inc_hl_ref, this),
          std::bind(&Cpu::dec_hl_ref, this),
          std::bind(&Cpu::ld_hl_n, this),
          std::bind(&Cpu::scf, this),
          std::bind(&Cpu::jr_c_s8, this),
          std::bind(&Cpu::add_hl_sp, this),
          std::bind(&Cpu::ld_a_hl_dec, this),
          std::bind(&Cpu::dec_sp, this),
          std::bind(&Cpu::inc_a, this),
          std::bind(&Cpu::dec_a, this),
          std::bind(&Cpu::ld_a_n, this),
          std::bind(&Cpu::ccf, this),

          std::bind(&Cpu::ld_b_b, this),
          std::bind(&Cpu::ld_b_c, this),
          std::bind(&Cpu::ld_b_d, this),
          std::bind(&Cpu::ld_b_e, this),
          std::bind(&Cpu::ld_b_h, this),
          std::bind(&Cpu::ld_b_l, this),
          std::bind(&Cpu::ld_b_hl_ref, this),
          std::bind(&Cpu::ld_b_a, this),
          std::bind(&Cpu::ld_c_b, this),
          std::bind(&Cpu::ld_c_c, this),
          std::bind(&Cpu::ld_c_d, this),
          std::bind(&Cpu::ld_c_e, this),
          std::bind(&Cpu::ld_c_h, this),
          std::bind(&Cpu::ld_c_l, this),
          std::bind(&Cpu::ld_c_hl_ref, this),
          std::bind(&Cpu::ld_c_a, this),

          std::bind(&Cpu::ld_d_b, this),
          std::bind(&Cpu::ld_d_c, this),
          std::bind(&Cpu::ld_d_d, this),
          std::bind(&Cpu::ld_d_e, this),
          std::bind(&Cpu::ld_d_h, this),
          std::bind(&Cpu::ld_d_l, this),
          std::bind(&Cpu::ld_d_hl_ref, this),
          std::bind(&Cpu::ld_d_a, this),
          std::bind(&Cpu::ld_e_b, this),
          std::bind(&Cpu::ld_e_c, this),
          std::bind(&Cpu::ld_e_d, this),
          std::bind(&Cpu::ld_e_e, this),
          std::bind(&Cpu::ld_e_h, this),
          std::bind(&Cpu::ld_e_l, this),
          std::bind(&Cpu::ld_e_hl_ref, this),
          std::bind(&Cpu::ld_e_a, this),

          std::bind(&Cpu::ld_h_b, this),
          std::bind(&Cpu::ld_h_c, this),
          std::bind(&Cpu::ld_h_d, this),
          std::bind(&Cpu::ld_h_e, this),
          std::bind(&Cpu::ld_h_h, this),
          std::bind(&Cpu::ld_h_l, this),
          std::bind(&Cpu::ld_h_hl_ref, this),
          std::bind(&Cpu::ld_h_a, this),
          std::bind(&Cpu::ld_l_b, this),
          std::bind(&Cpu::ld_l_c, this),
          std::bind(&Cpu::ld_l_d, this),
          std::bind(&Cpu::ld_l_e, this),
          std::bind(&Cpu::ld_l_h, this),
          std::bind(&Cpu::ld_l_l, this),
          std::bind(&Cpu::ld_l_hl_ref, this),
          std::bind(&Cpu::ld_l_a, this),

          std::bind(&Cpu::ld_hl_ref_b, this),
          std::bind(&Cpu::ld_hl_ref_c, this),
          std::bind(&Cpu::ld_hl_ref_d, this),
          std::bind(&Cpu::ld_hl_ref_e, this),
          std::bind(&Cpu::ld_hl_ref_h, this),
          std::bind(&Cpu::ld_hl_ref_l, this),
          std::bind(&Cpu::halt, this),
          std::bind(&Cpu::ld_hl_ref_a, this),
          std::bind(&Cpu::ld_a_b, this),
          std::bind(&Cpu::ld_a_c, this),
          std::bind(&Cpu::ld_a_d, this),
          std::bind(&Cpu::ld_a_e, this),
          std::bind(&Cpu::ld_a_h, this),
          std::bind(&Cpu::ld_a_l, this),
          std::bind(&Cpu::ld_a_hl_ref, this),
          std::bind(&Cpu::ld_a_a, this),

          std::bind(&Cpu::add_a_b, this),
          std::bind(&Cpu::add_a_c, this),
          std::bind(&Cpu::add_a_d, this),
          std::bind(&Cpu::add_a_e, this),
          std::bind(&Cpu::add_a_h, this),
          std::bind(&Cpu::add_a_l, this),
          std::bind(&Cpu::add_a_hl_ref, this),
          std::bind(&Cpu::add_a_a, this),
          std::bind(&Cpu::adc_a_b, this),
          std::bind(&Cpu::adc_a_c, this),
          std::bind(&Cpu::adc_a_d, this),
          std::bind(&Cpu::adc_a_e, this),
          std::bind(&Cpu::adc_a_h, this),
          std::bind(&Cpu::adc_a_l, this),
          std::bind(&Cpu::adc_a_hl_ref, this),
          std::bind(&Cpu::adc_a_a, this),

          std::bind(&Cpu::sub_a_b, this),
          std::bind(&Cpu::sub_a_c, this),
          std::bind(&Cpu::sub_a_d, this),
          std::bind(&Cpu::sub_a_e, this),
          std::bind(&Cpu::sub_a_h, this),
          std::bind(&Cpu::sub_a_l, this),
          std::bind(&Cpu::sub_a_hl_ref, this),
          std::bind(&Cpu::sub_a_a, this),
          std::bind(&Cpu::sbc_a_b, this),
          std::bind(&Cpu::sbc_a_c, this),
          std::bind(&Cpu::sbc_a_d, this),
          std::bind(&Cpu::sbc_a_e, this),
          std::bind(&Cpu::sbc_a_h, this),
          std::bind(&Cpu::sbc_a_l, this),
          std::bind(&Cpu::sbc_a_hl_ref, this),
          std::bind(&Cpu::sbc_a_a, this),

          std::bind(&Cpu::and_a_b, this),
          std::bind(&Cpu::and_a_c, this),
          std::bind(&Cpu::and_a_d, this),
          std::bind(&Cpu::and_a_e, this),
          std::bind(&Cpu::and_a_h, this),
          std::bind(&Cpu::and_a_l, this),
          std::bind(&Cpu::and_a_hl_ref, this),
          std::bind(&Cpu::and_a_a, this),
          std::bind(&Cpu::xor_a_b, this),
          std::bind(&Cpu::xor_a_c, this),
          std::bind(&Cpu::xor_a_d, this),
          std::bind(&Cpu::xor_a_e, this),
          std::bind(&Cpu::xor_a_h, this),
          std::bind(&Cpu::xor_a_l, this),
          std::bind(&Cpu::xor_a_hl_ref, this),
          std::bind(&Cpu::xor_a_a, this),

          std::bind(&Cpu::or_a_b, this),
          std::bind(&Cpu::or_a_c, this),
          std::bind(&Cpu::or_a_d, this),
          std::bind(&Cpu::or_a_e, this),
          std::bind(&Cpu::or_a_h, this),
          std::bind(&Cpu::or_a_l, this),
          std::bind(&Cpu::or_a_hl_ref, this),
          std::bind(&Cpu::or_a_a, this),
          std::bind(&Cpu::cp_a_b, this),
          std::bind(&Cpu::cp_a_c, this),
          std::bind(&Cpu::cp_a_d, this),
          std::bind(&Cpu::cp_a_e, this),
          std::bind(&Cpu::cp_a_h, this),
          std::bind(&Cpu::cp_a_l, this),
          std::bind(&Cpu::cp_a_hl_ref, this),
          std::bind(&Cpu::cp_a_a, this),

          std::bind(&Cpu::ret_nz, this),
          std::bind(&Cpu::pop_bc, this),
          std::bind(&Cpu::jp_nz_nn, this),
          std::bind(&Cpu::jp_nn, this),
          std::bind(&Cpu::call_nz_nn, this),
          std::bind(&Cpu::push_bc, this),
          std::bind(&Cpu::add_a_n, this),
          std::bind(&Cpu::rst_0, this),
          std::bind(&Cpu::ret_z, this),
          std::bind(&Cpu::ret, this),
          std::bind(&Cpu::jp_z_nn, this),
          nullptr,
          std::bind(&Cpu::call_z_nn, this),
          std::bind(&Cpu::call_nn, this),
          std::bind(&Cpu::adc_a_n, this),
          std::bind(&Cpu::rst_1, this),

          std::bind(&Cpu::ret_nc, this),
          std::bind(&Cpu::pop_de, this),
          std::bind(&Cpu::jp_nc_nn, this),
          nullptr,
          std::bind(&Cpu::call_nc_nn, this),
          std::bind(&Cpu::push_de, this),
          std::bind(&Cpu::sub_a_n, this),
          std::bind(&Cpu::rst_2, this),
          std::bind(&Cpu::ret_c, this),
          std::bind(&Cpu::reti, this),
          std::bind(&Cpu::jp_c_nn, this),
          nullptr,
          std::bind(&Cpu::call_c_nn, this),
          nullptr,
          std::bind(&Cpu::sbc_a_n, this),
          std::bind(&Cpu::rst_3, this),

          std::bind(&Cpu::ld_n_ref_a, this),
          std::bind(&Cpu::pop_hl, this),
          std::bind(&Cpu::ld_c_ref_a, this),
          nullptr,
          nullptr,
          std::bind(&Cpu::push_hl, this),
          std::bind(&Cpu::and_a_n, this),
          std::bind(&Cpu::rst_4, this),
          std::bind(&Cpu::add_sp_n, this),
          std::bind(&Cpu::jp_hl, this),
          std::bind(&Cpu::ld_nn_ref_a, this),
          nullptr,
          nullptr,
          nullptr,
          std::bind(&Cpu::xor_a_n, this),
          std::bind(&Cpu::rst_5, this),

          std::bind(&Cpu::ld_a_n_ref, this),
          std::bind(&Cpu::pop_af, this),
          std::bind(&Cpu::ld_a_c_ref, this),
          std::bind(&Cpu::di, this),
          nullptr,
          std::bind(&Cpu::push_af, this),
          std::bind(&Cpu::or_a_n, this),
          std::bind(&Cpu::rst_6, this),
          std::bind(&Cpu::ld_hl_sp_n, this),
          std::bind(&Cpu::ld_sp_hl, this),
          std::bind(&Cpu::ld_a_nn_ref, this),
          std::bind(&Cpu::e_i, this),
          nullptr,
          nullptr,
          std::bind(&Cpu::cp_a_n, this),
          std::bind(&Cpu::rst_7, this),
      }, instructions_16_bit{
          std::bind(&Cpu::rlc_b, this),
          std::bind(&Cpu::rlc_c, this),
          std::bind(&Cpu::rlc_d, this),
          std::bind(&Cpu::rlc_e, this),
          std::bind(&Cpu::rlc_h, this),
          std::bind(&Cpu::rlc_l, this),
          std::bind(&Cpu::rlc_hl_ref, this),
          std::bind(&Cpu::rlc_a, this),
          std::bind(&Cpu::rrc_b, this),
          std::bind(&Cpu::rrc_c, this),
          std::bind(&Cpu::rrc_d, this),
          std::bind(&Cpu::rrc_e, this),
          std::bind(&Cpu::rrc_h, this),
          std::bind(&Cpu::rrc_l, this),
          std::bind(&Cpu::rrc_hl_ref, this),
          std::bind(&Cpu::rrc_a, this),

          std::bind(&Cpu::rl_b, this),
          std::bind(&Cpu::rl_c, this),
          std::bind(&Cpu::rl_d, this),
          std::bind(&Cpu::rl_e, this),
          std::bind(&Cpu::rl_h, this),
          std::bind(&Cpu::rl_l, this),
          std::bind(&Cpu::rl_hl_ref, this),
          std::bind(&Cpu::rl_a, this),
          std::bind(&Cpu::rr_b, this),
          std::bind(&Cpu::rr_c, this),
          std::bind(&Cpu::rr_d, this),
          std::bind(&Cpu::rr_e, this),
          std::bind(&Cpu::rr_h, this),
          std::bind(&Cpu::rr_l, this),
          std::bind(&Cpu::rr_hl_ref, this),
          std::bind(&Cpu::rr_a, this),

          std::bind(&Cpu::sla_b, this),
          std::bind(&Cpu::sla_c, this),
          std::bind(&Cpu::sla_d, this),
          std::bind(&Cpu::sla_e, this),
          std::bind(&Cpu::sla_h, this),
          std::bind(&Cpu::sla_l, this),
          std::bind(&Cpu::sla_hl_ref, this),
          std::bind(&Cpu::sla_a, this),
          std::bind(&Cpu::sra_b, this),
          std::bind(&Cpu::sra_c, this),
          std::bind(&Cpu::sra_d, this),
          std::bind(&Cpu::sra_e, this),
          std::bind(&Cpu::sra_h, this),
          std::bind(&Cpu::sra_l, this),
          std::bind(&Cpu::sra_hl_ref, this),
          std::bind(&Cpu::sra_a, this),

          std::bind(&Cpu::swap_b, this),
          std::bind(&Cpu::swap_c, this),
          std::bind(&Cpu::swap_d, this),
          std::bind(&Cpu::swap_e, this),
          std::bind(&Cpu::swap_h, this),
          std::bind(&Cpu::swap_l, this),
          std::bind(&Cpu::swap_hl_ref, this),
          std::bind(&Cpu::swap_a, this),
          std::bind(&Cpu::srl_b, this),
          std::bind(&Cpu::srl_c, this),
          std::bind(&Cpu::srl_d, this),
          std::bind(&Cpu::srl_e, this),
          std::bind(&Cpu::srl_h, this),
          std::bind(&Cpu::srl_l, this),
          std::bind(&Cpu::srl_hl_ref, this),
          std::bind(&Cpu::srl_a, this),

          std::bind(&Cpu::bit_0_b, this),
          std::bind(&Cpu::bit_0_c, this),
          std::bind(&Cpu::bit_0_d, this),
          std::bind(&Cpu::bit_0_e, this),
          std::bind(&Cpu::bit_0_h, this),
          std::bind(&Cpu::bit_0_l, this),
          std::bind(&Cpu::bit_0_hl_ref, this),
          std::bind(&Cpu::bit_0_a, this),
          std::bind(&Cpu::bit_1_b, this),
          std::bind(&Cpu::bit_1_c, this),
          std::bind(&Cpu::bit_1_d, this),
          std::bind(&Cpu::bit_1_e, this),
          std::bind(&Cpu::bit_1_h, this),
          std::bind(&Cpu::bit_1_l, this),
          std::bind(&Cpu::bit_1_hl_ref, this),
          std::bind(&Cpu::bit_1_a, this),

          std::bind(&Cpu::bit_2_b, this),
          std::bind(&Cpu::bit_2_c, this),
          std::bind(&Cpu::bit_2_d, this),
          std::bind(&Cpu::bit_2_e, this),
          std::bind(&Cpu::bit_2_h, this),
          std::bind(&Cpu::bit_2_l, this),
          std::bind(&Cpu::bit_2_hl_ref, this),
          std::bind(&Cpu::bit_2_a, this),
          std::bind(&Cpu::bit_3_b, this),
          std::bind(&Cpu::bit_3_c, this),
          std::bind(&Cpu::bit_3_d, this),
          std::bind(&Cpu::bit_3_e, this),
          std::bind(&Cpu::bit_3_h, this),
          std::bind(&Cpu::bit_3_l, this),
          std::bind(&Cpu::bit_3_hl_ref, this),
          std::bind(&Cpu::bit_3_a, this),

          std::bind(&Cpu::bit_4_b, this),
          std::bind(&Cpu::bit_4_c, this),
          std::bind(&Cpu::bit_4_d, this),
          std::bind(&Cpu::bit_4_e, this),
          std::bind(&Cpu::bit_4_h, this),
          std::bind(&Cpu::bit_4_l, this),
          std::bind(&Cpu::bit_4_hl_ref, this),
          std::bind(&Cpu::bit_4_a, this),
          std::bind(&Cpu::bit_5_b, this),
          std::bind(&Cpu::bit_5_c, this),
          std::bind(&Cpu::bit_5_d, this),
          std::bind(&Cpu::bit_5_e, this),
          std::bind(&Cpu::bit_5_h, this),
          std::bind(&Cpu::bit_5_l, this),
          std::bind(&Cpu::bit_5_hl_ref, this),
          std::bind(&Cpu::bit_5_a, this),

          std::bind(&Cpu::bit_6_b, this),
          std::bind(&Cpu::bit_6_c, this),
          std::bind(&Cpu::bit_6_d, this),
          std::bind(&Cpu::bit_6_e, this),
          std::bind(&Cpu::bit_6_h, this),
          std::bind(&Cpu::bit_6_l, this),
          std::bind(&Cpu::bit_6_hl_ref, this),
          std::bind(&Cpu::bit_6_a, this),
          std::bind(&Cpu::bit_7_b, this),
          std::bind(&Cpu::bit_7_c, this),
          std::bind(&Cpu::bit_7_d, this),
          std::bind(&Cpu::bit_7_e, this),
          std::bind(&Cpu::bit_7_h, this),
          std::bind(&Cpu::bit_7_l, this),
          std::bind(&Cpu::bit_7_hl_ref, this),
          std::bind(&Cpu::bit_7_a, this),

          std::bind(&Cpu::res_0_b, this),
          std::bind(&Cpu::res_0_c, this),
          std::bind(&Cpu::res_0_d, this),
          std::bind(&Cpu::res_0_e, this),
          std::bind(&Cpu::res_0_h, this),
          std::bind(&Cpu::res_0_l, this),
          std::bind(&Cpu::res_0_hl_ref, this),
          std::bind(&Cpu::res_0_a, this),
          std::bind(&Cpu::res_1_b, this),
          std::bind(&Cpu::res_1_c, this),
          std::bind(&Cpu::res_1_d, this),
          std::bind(&Cpu::res_1_e, this),
          std::bind(&Cpu::res_1_h, this),
          std::bind(&Cpu::res_1_l, this),
          std::bind(&Cpu::res_1_hl_ref, this),
          std::bind(&Cpu::res_1_a, this),

          std::bind(&Cpu::res_2_b, this),
          std::bind(&Cpu::res_2_c, this),
          std::bind(&Cpu::res_2_d, this),
          std::bind(&Cpu::res_2_e, this),
          std::bind(&Cpu::res_2_h, this),
          std::bind(&Cpu::res_2_l, this),
          std::bind(&Cpu::res_2_hl_ref, this),
          std::bind(&Cpu::res_2_a, this),
          std::bind(&Cpu::res_3_b, this),
          std::bind(&Cpu::res_3_c, this),
          std::bind(&Cpu::res_3_d, this),
          std::bind(&Cpu::res_3_e, this),
          std::bind(&Cpu::res_3_h, this),
          std::bind(&Cpu::res_3_l, this),
          std::bind(&Cpu::res_3_hl_ref, this),
          std::bind(&Cpu::res_3_a, this),

          std::bind(&Cpu::res_4_b, this),
          std::bind(&Cpu::res_4_c, this),
          std::bind(&Cpu::res_4_d, this),
          std::bind(&Cpu::res_4_e, this),
          std::bind(&Cpu::res_4_h, this),
          std::bind(&Cpu::res_4_l, this),
          std::bind(&Cpu::res_4_hl_ref, this),
          std::bind(&Cpu::res_4_a, this),
          std::bind(&Cpu::res_5_b, this),
          std::bind(&Cpu::res_5_c, this),
          std::bind(&Cpu::res_5_d, this),
          std::bind(&Cpu::res_5_e, this),
          std::bind(&Cpu::res_5_h, this),
          std::bind(&Cpu::res_5_l, this),
          std::bind(&Cpu::res_5_hl_ref, this),
          std::bind(&Cpu::res_5_a, this),

          std::bind(&Cpu::res_6_b, this),
          std::bind(&Cpu::res_6_c, this),
          std::bind(&Cpu::res_6_d, this),
          std::bind(&Cpu::res_6_e, this),
          std::bind(&Cpu::res_6_h, this),
          std::bind(&Cpu::res_6_l, this),
          std::bind(&Cpu::res_6_hl_ref, this),
          std::bind(&Cpu::res_6_a, this),
          std::bind(&Cpu::res_7_b, this),
          std::bind(&Cpu::res_7_c, this),
          std::bind(&Cpu::res_7_d, this),
          std::bind(&Cpu::res_7_e, this),
          std::bind(&Cpu::res_7_h, this),
          std::bind(&Cpu::res_7_l, this),
          std::bind(&Cpu::res_7_hl_ref, this),
          std::bind(&Cpu::res_7_a, this),

          std::bind(&Cpu::set_0_b, this),
          std::bind(&Cpu::set_0_c, this),
          std::bind(&Cpu::set_0_d, this),
          std::bind(&Cpu::set_0_e, this),
          std::bind(&Cpu::set_0_h, this),
          std::bind(&Cpu::set_0_l, this),
          std::bind(&Cpu::set_0_hl_ref, this),
          std::bind(&Cpu::set_0_a, this),
          std::bind(&Cpu::set_1_b, this),
          std::bind(&Cpu::set_1_c, this),
          std::bind(&Cpu::set_1_d, this),
          std::bind(&Cpu::set_1_e, this),
          std::bind(&Cpu::set_1_h, this),
          std::bind(&Cpu::set_1_l, this),
          std::bind(&Cpu::set_1_hl_ref, this),
          std::bind(&Cpu::set_1_a, this),

          std::bind(&Cpu::set_2_b, this),
          std::bind(&Cpu::set_2_c, this),
          std::bind(&Cpu::set_2_d, this),
          std::bind(&Cpu::set_2_e, this),
          std::bind(&Cpu::set_2_h, this),
          std::bind(&Cpu::set_2_l, this),
          std::bind(&Cpu::set_2_hl_ref, this),
          std::bind(&Cpu::set_2_a, this),
          std::bind(&Cpu::set_3_b, this),
          std::bind(&Cpu::set_3_c, this),
          std::bind(&Cpu::set_3_d, this),
          std::bind(&Cpu::set_3_e, this),
          std::bind(&Cpu::set_3_h, this),
          std::bind(&Cpu::set_3_l, this),
          std::bind(&Cpu::set_3_hl_ref, this),
          std::bind(&Cpu::set_3_a, this),

          std::bind(&Cpu::set_4_b, this),
          std::bind(&Cpu::set_4_c, this),
          std::bind(&Cpu::set_4_d, this),
          std::bind(&Cpu::set_4_e, this),
          std::bind(&Cpu::set_4_h, this),
          std::bind(&Cpu::set_4_l, this),
          std::bind(&Cpu::set_4_hl_ref, this),
          std::bind(&Cpu::set_4_a, this),
          std::bind(&Cpu::set_5_b, this),
          std::bind(&Cpu::set_5_c, this),
          std::bind(&Cpu::set_5_d, this),
          std::bind(&Cpu::set_5_e, this),
          std::bind(&Cpu::set_5_h, this),
          std::bind(&Cpu::set_5_l, this),
          std::bind(&Cpu::set_5_hl_ref, this),
          std::bind(&Cpu::set_5_a, this),

          std::bind(&Cpu::set_6_b, this),
          std::bind(&Cpu::set_6_c, this),
          std::bind(&Cpu::set_6_d, this),
          std::bind(&Cpu::set_6_e, this),
          std::bind(&Cpu::set_6_h, this),
          std::bind(&Cpu::set_6_l, this),
          std::bind(&Cpu::set_6_hl_ref, this),
          std::bind(&Cpu::set_6_a, this),
          std::bind(&Cpu::set_7_b, this),
          std::bind(&Cpu::set_7_c, this),
          std::bind(&Cpu::set_7_d, this),
          std::bind(&Cpu::set_7_e, this),
          std::bind(&Cpu::set_7_h, this),
          std::bind(&Cpu::set_7_l, this),
          std::bind(&Cpu::set_7_hl_ref, this),
          std::bind(&Cpu::set_7_a, this),
    } {}

const Registers &Cpu::registers() const { return registers_; }

uint8_t Cpu::fetch_current_instruction() {
  uint8_t opcode = memory_.read_byte(registers_.pc);

  assert(opcode > 0 &&
         static_cast<uint32_t>(opcode) < TOTAL_NUMBER_OF_INSTRUCTION);

  return opcode;
}

void Cpu::execute_instruction(uint8_t opcode) {
  // execute 16-bit opcodes
  if (opcode == 0xCB) {
    uint8_t new_opcode = memory_.read_byte(registers_.pc + 1);
    if (new_opcode < instructions_16_bit.size() &&
        instructions_16_bit[new_opcode]) {
      instructions_16_bit[new_opcode]();
    }
  } // execute 8-bit opcodes
  else if (opcode < instructions_.size() && instructions_[opcode]) {
    instructions_[opcode]();
  } else {
    // todo: handle this case
  }
}

void Cpu::inc_reg(uint8_t &reg) {
  uint8_t old_reg = reg++;

  registers_.set_zero_flag_from_byte_result(reg);
  registers_.set_half_carry_flag_from_byte_result(old_reg, reg, 1);
  registers_.subtract = 0;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::dec_reg(uint8_t &reg) {
  uint8_t old_reg = reg--;
  registers_.set_half_carry_flag_from_word_result(old_reg, reg, -1);
  registers_.set_zero_flag_from_byte_result(reg);
  registers_.subtract = 1;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::inc_word_reg(uint16_t &reg) {
  ++reg;
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::dec_word_reg(uint16_t &reg) {
  --reg;
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_reg_n(uint8_t &reg) {
  reg = memory_.read_byte(registers_.pc + 1);
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::ld_reg_reg(uint8_t &write_reg, uint8_t read_reg) {
  write_reg = read_reg;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::ld_word_reg_nn(uint16_t &reg) {
  reg = memory_.read_word(registers_.pc + 1);
  registers_.pc += 3;
  total_cycles_ += 3;
}

void Cpu::add_reg_reg(uint8_t &write_reg, uint8_t read_reg) {
  uint8_t old_reg = write_reg;
  write_reg += read_reg;

  registers_.set_zero_flag_from_byte_result(write_reg);
  registers_.set_half_carry_flag_from_byte_result(old_reg, write_reg, read_reg);
  registers_.set_carry_flag_from_byte_result(old_reg, write_reg, read_reg);
  registers_.subtract = 0;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::adc_reg_reg(uint8_t &write_reg, uint8_t read_reg) {
  uint8_t old_a = write_reg;
  uint8_t operand = read_reg + registers_.carry;
  write_reg += operand;

  registers_.set_zero_flag_from_byte_result(write_reg);
  registers_.set_half_carry_flag_from_byte_result(old_a, write_reg, operand);
  registers_.set_carry_flag_from_byte_result(old_a, write_reg, operand);
  registers_.subtract = 0;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::sub_reg_reg(uint8_t &write_reg, uint8_t read_reg) {
  uint8_t old_a = write_reg;
  write_reg -= read_reg;

  registers_.set_zero_flag_from_byte_result(write_reg);
  registers_.set_half_carry_flag_from_byte_result(old_a, write_reg, read_reg);
  registers_.set_carry_flag_from_byte_result(old_a, write_reg, read_reg);
  registers_.subtract = 1;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::sbc_reg_reg(uint8_t &write_reg, uint8_t read_reg) {
  uint8_t old_a = write_reg;
  uint8_t operand = read_reg + registers_.carry;
  write_reg -= operand;

  registers_.set_zero_flag_from_byte_result(write_reg);
  registers_.set_half_carry_flag_from_byte_result(old_a, write_reg, operand);
  registers_.set_carry_flag_from_byte_result(old_a, write_reg, operand);
  registers_.subtract = 1;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::and_reg_reg(uint8_t &write_reg, uint8_t read_reg) {
  write_reg &= read_reg;
  registers_.set_zero_flag_from_byte_result(write_reg);
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.carry = 0;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::xor_reg_reg(uint8_t &write_reg, uint8_t read_reg) {
  write_reg ^= read_reg;
  registers_.set_zero_flag_from_byte_result(write_reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::or_reg_reg(uint8_t &write_reg, uint8_t read_reg) {
  write_reg |= read_reg;
  registers_.set_zero_flag_from_byte_result(write_reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::cp_reg_reg(uint8_t &write_reg, uint8_t read_reg) {
  registers_.zero = write_reg - read_reg;
  registers_.subtract = 1;
  registers_.set_half_carry_flag_from_byte_result(write_reg, registers_.zero,
                                                  read_reg);
  registers_.set_carry_flag_from_byte_result(write_reg, registers_.zero,
                                             read_reg);
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::rst(uint8_t addr) {
  push_onto_stack_reg_16(registers_.pc);
  registers_.pc = addr;
  total_cycles_ += 4;
}

void Cpu::pop_stack_into_reg_16(uint16_t &reg) {
  uint8_t sp_content = memory_.read_byte(registers_.sp);
  // load sp_content to lower order by of pc
  reg &= 0xFF00;
  reg |= sp_content;
  ++registers_.sp;
  sp_content = memory_.read_byte(registers_.sp);
  // load new sp_content to higher order by of pc
  reg &= 0xFF;
  reg |= (sp_content << 8);
  ++registers_.sp;
}

void Cpu::push_onto_stack_reg_16(uint16_t content) {
  registers_.sp -= 2;
  memory_.write_word(registers_.sp, registers_.pc + 3);
  registers_.pc = content;
}

void Cpu::rlc(uint8_t &reg) {
  uint8_t bit7 = (registers_.a & 0x80) >> 7;
  reg = static_cast<uint8_t>(reg << 1) | bit7;
  registers_.set_zero_flag_from_byte_result(reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::rrc(uint8_t &reg) {
  uint8_t bit0 = reg & 0x1;
  reg = (reg >> 1) | static_cast<uint8_t>(bit0 << 7);
  registers_.set_zero_flag_from_byte_result(reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::rl(uint8_t &reg) {
  uint8_t bit7 = (reg & 0x80) >> 7;
  reg = static_cast<uint8_t>(reg << 1) | registers_.carry;
  registers_.set_zero_flag_from_byte_result(reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::rr(uint8_t &reg) {
  uint8_t bit0 = reg & 0x1;
  reg = (reg >> 1) | static_cast<uint8_t>(registers_.carry << 7);
  registers_.set_zero_flag_from_byte_result(reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::sla(uint8_t &reg) {
  uint8_t bit7 = (reg & 0x80) >> 7;
  reg = static_cast<uint8_t>(reg << 1);
  registers_.set_zero_flag_from_byte_result(reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::sra(uint8_t &reg) {
  uint8_t bit0 = reg & 0x1;
  uint8_t bit7 = reg & 0x80;
  reg = (reg >> 1) | bit7;
  registers_.set_zero_flag_from_byte_result(reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::swap(uint8_t &reg) {
  uint8_t lower_bits = static_cast<uint8_t>((reg & 0xF) << 4);
  uint8_t upper_bits = (reg & 0xF0) >> 4;
  reg = lower_bits | upper_bits;
  registers_.set_zero_flag_from_byte_result(reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::srl(uint8_t &reg) {
  uint8_t bit0 = reg & 0x1;
  reg >>= 1;
  registers_.set_zero_flag_from_byte_result(reg);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::bit(uint8_t &reg, uint8_t bit) {
  if (!((reg >> bit) & 0x1)) {
    registers_.zero = 1;
  } else {
    registers_.zero = 0;
  }
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::bit_hl_ref(uint8_t bit) {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  if (!((ref_byte >> bit) & 0x1)) {
    registers_.zero = 1;
  } else {
    registers_.zero = 0;
  }
  registers_.subtract = 0;
  registers_.half_carry = 1;
  registers_.pc += 2;
  total_cycles_ += 3;
}

void Cpu::res(uint8_t &reg, uint8_t bit) {
  reg &= ~(0x1 << bit);
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::res_hl_ref(uint8_t bit) {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t result = ref_byte & ~(0x1 << bit);
  memory_.write_byte(registers_.hl, result);
  registers_.pc += 2;
  total_cycles_ += 4;
}

void Cpu::set(uint8_t &reg, uint8_t bit) {
  reg |= (0x1 << bit);
  registers_.pc += 2;
  total_cycles_ += 2;
}

void Cpu::set_hl_ref(uint8_t bit) {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t result = ref_byte | static_cast<uint8_t>(0x1 << bit);
  memory_.write_byte(registers_.hl, result);
  registers_.pc += 2;
  total_cycles_ += 4;
}

void Cpu::nop() {
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::ld_bc_nn() { ld_word_reg_nn(registers_.bc); }

void Cpu::ld_bc_a() {
  memory_.write_byte(registers_.bc, registers_.a);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::inc_bc() { inc_word_reg(registers_.bc); }

void Cpu::inc_b() { inc_reg(registers_.b); }
void Cpu::dec_b() { dec_reg(registers_.b); }

void Cpu::ld_b_n() { ld_reg_n(registers_.b); }

void Cpu::rlca() {
  uint8_t bit7 = (registers_.a & 0x80) >> 7;
  registers_.a = static_cast<uint8_t>(registers_.a << 1) | bit7;
  registers_.zero = 0;
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::ld_nn_sp() {
  uint16_t address = memory_.read_word(registers_.sp + 1);
  memory_.write_word(address, registers_.sp);
  registers_.pc += 3;
  total_cycles_ += 5;
}

void Cpu::add_hl_bc() {
  uint16_t old_hl = registers_.hl;
  registers_.hl = registers_.bc + registers_.hl;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_hl, registers_.hl,
                                                  registers_.bc);
  registers_.set_carry_flag_from_word_result(old_hl, registers_.hl,
                                             registers_.bc);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_a_bc() {
  uint8_t content = memory_.read_byte(registers_.bc);
  memory_.write_byte(registers_.a, content);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::dec_bc() { dec_word_reg(registers_.bc); }

void Cpu::inc_c() { inc_reg(registers_.c); }

void Cpu::dec_c() { dec_reg(registers_.c); }

void Cpu::ld_c_n() { ld_reg_n(registers_.c); }

void Cpu::rrca() {
  uint8_t bit0 = registers_.c & 0x1;
  registers_.c = (registers_.c >> 1) | static_cast<uint8_t>(bit0 << 7);
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  ++registers_.pc;
  ++total_cycles_;
}

// todo: finish this function
void Cpu::stop() {
  registers_.pc += 2;
  ++total_cycles_;
}

void Cpu::ld_de_nn() { ld_word_reg_nn(registers_.de); }

void Cpu::ld_de_a() {
  memory_.write_byte(registers_.de, registers_.a);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::inc_de() { inc_word_reg(registers_.de); }

void Cpu::inc_d() { inc_reg(registers_.d); }

void Cpu::dec_d() { dec_reg(registers_.d); }

void Cpu::ld_d_n() { ld_reg_n(registers_.d); }

void Cpu::rla() {
  uint8_t bit7 = (registers_.a & 0x80) >> 7;
  registers_.a = static_cast<uint8_t>(registers_.a << 1) | registers_.carry;
  registers_.zero = 0;
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::jr_s8() {
  uint16_t steps = memory_.read_word(registers_.pc + 1);
  registers_.pc += steps;
  registers_.pc += 2;
  total_cycles_ += 3;
}

void Cpu::add_hl_de() {
  uint16_t old_hl = registers_.hl;
  registers_.hl = registers_.de + registers_.hl;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_hl, registers_.hl,
                                                  registers_.de);
  registers_.set_carry_flag_from_word_result(old_hl, registers_.hl,
                                             registers_.de);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_a_de() {
  uint8_t content = memory_.read_byte(registers_.de);
  memory_.write_byte(registers_.a, content);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::dec_de() { dec_word_reg(registers_.de); }

void Cpu::inc_e() { inc_reg(registers_.e); }

void Cpu::dec_e() { dec_reg(registers_.e); }

void Cpu::ld_e_n() { ld_reg_n(registers_.e); }

void Cpu::rra() {
  uint8_t bit0 = registers_.c & 0x1;
  registers_.c =
      (registers_.c >> 1) | static_cast<uint8_t>(registers_.carry << 7);
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::jr_nz_s8() {
  if (!registers_.zero) {
    uint16_t steps = memory_.read_word(registers_.pc + 1);
    registers_.pc += steps;
    total_cycles_ += 3;
  } else {
    total_cycles_ += 2;
  }
  registers_.pc += 2;
}

void Cpu::ld_hl_nn() { ld_word_reg_nn(registers_.hl); }

void Cpu::ld_hl_inc_a() {
  memory_.write_byte(registers_.hl++, registers_.a);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::inc_hl() { inc_word_reg(registers_.hl); }

void Cpu::inc_h() { inc_reg(registers_.h); }

void Cpu::dec_h() { dec_reg(registers_.h); }

void Cpu::ld_h_n() { ld_reg_n(registers_.h); }

void Cpu::daa() {
  // subtraction
  if (registers_.subtract) {
    if (registers_.carry) {
      registers_.a -= 0x60;
    }
    if (registers_.half_carry) {
      registers_.a -= 0x6;
    }
  }
  // addition
  else {
    if (registers_.carry || registers_.a > 0x99) {
      registers_.a += 0x60;
      registers_.carry = 1;
    }
    if (registers_.half_carry || (registers_.a & 0xF) > 0x9) {
      registers_.a += 0x6;
    }
  }
  registers_.set_zero_flag_from_byte_result(registers_.a);
  registers_.half_carry = 0;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::jr_z_s8() {
  if (registers_.zero) {
    uint16_t steps = memory_.read_word(registers_.pc + 1);
    registers_.pc += steps;
    total_cycles_ += 3;
  } else {
    total_cycles_ += 2;
  }
  registers_.pc += 2;
}

void Cpu::add_hl_hl() {
  uint16_t old_hl = registers_.hl;
  registers_.hl = registers_.hl + registers_.hl;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_hl, registers_.hl,
                                                  registers_.hl);
  registers_.set_carry_flag_from_word_result(old_hl, registers_.hl,
                                             registers_.hl);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_a_hl_inc() {
  uint8_t content = memory_.read_byte(registers_.hl++);
  memory_.write_byte(registers_.a, content);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::dec_hl() { dec_word_reg(registers_.hl); }

void Cpu::inc_l() { inc_reg(registers_.l); }

void Cpu::dec_l() { dec_reg(registers_.l); }

void Cpu::ld_l_n() { ld_reg_n(registers_.l); }

void Cpu::cpl() {
  registers_.a = ~registers_.a;
  registers_.subtract = 1;
  registers_.half_carry = 1;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::jr_nc_s8() {
  if (!registers_.carry) {
    uint16_t steps = memory_.read_word(registers_.pc + 1);
    registers_.pc += steps;
    total_cycles_ += 3;
  } else {
    total_cycles_ += 2;
  }
  registers_.pc += 2;
}

void Cpu::ld_sp_nn() { ld_word_reg_nn(registers_.sp); }

void Cpu::ld_hl_dec_a() {
  memory_.write_byte(registers_.hl--, registers_.a);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::inc_sp() { inc_word_reg(registers_.sp); }

void Cpu::inc_hl_ref() {
  uint16_t old_hl_content = memory_.read_word(registers_.hl);
  uint16_t new_hl_content = old_hl_content + 1;
  memory_.write_word(registers_.hl, new_hl_content);

  registers_.set_zero_flag_from_word_result(new_hl_content);
  registers_.set_half_carry_flag_from_word_result(old_hl_content,
                                                  new_hl_content, 1);
  registers_.subtract = 0;
  ++registers_.pc;
  total_cycles_ += 3;
}

void Cpu::dec_hl_ref() {
  uint16_t old_hl_content = memory_.read_word(registers_.hl);
  uint16_t new_hl_content = old_hl_content - 1;
  memory_.write_word(registers_.hl, new_hl_content);

  registers_.set_zero_flag_from_word_result(new_hl_content);
  registers_.set_half_carry_flag_from_word_result(old_hl_content,
                                                  new_hl_content, -1);
  registers_.subtract = 1;
  ++registers_.pc;
  total_cycles_ += 3;
}

void Cpu::ld_hl_n() {
  uint8_t content = memory_.read_byte(registers_.pc + 1);
  memory_.write_byte(registers_.hl, content);
  registers_.pc += 2;
  total_cycles_ += 3;
}

void Cpu::scf() {
  registers_.carry = 1;
  registers_.half_carry = 0;
  registers_.subtract = 0;
  ++total_cycles_;
}

void Cpu::jr_c_s8() {
  if (registers_.carry) {
    uint16_t steps = memory_.read_word(registers_.pc + 1);
    registers_.pc += steps;
    total_cycles_ += 3;
  } else {
    total_cycles_ += 2;
  }
  registers_.pc += 2;
}

void Cpu::add_hl_sp() {
  uint16_t old_hl = registers_.hl;
  registers_.hl = registers_.hl + registers_.sp;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_hl, registers_.hl,
                                                  registers_.sp);
  registers_.set_carry_flag_from_word_result(old_hl, registers_.hl,
                                             registers_.sp);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_a_hl_dec() {
  uint8_t content = memory_.read_byte(registers_.hl--);
  memory_.write_byte(registers_.a, content);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::dec_sp() { dec_word_reg(registers_.sp); }

void Cpu::inc_a() { inc_reg(registers_.a); }

void Cpu::dec_a() { dec_reg(registers_.a); }

void Cpu::ld_a_n() { ld_reg_n(registers_.a); }

void Cpu::ccf() {
  registers_.carry = !registers_.carry;
  registers_.subtract = 0;
  registers_.half_carry = 0;
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::ld_b_b() { ld_reg_reg(registers_.b, registers_.b); }
void Cpu::ld_b_c() { ld_reg_reg(registers_.b, registers_.c); }
void Cpu::ld_b_d() { ld_reg_reg(registers_.b, registers_.d); }
void Cpu::ld_b_e() { ld_reg_reg(registers_.b, registers_.e); }
void Cpu::ld_b_h() { ld_reg_reg(registers_.b, registers_.h); }
void Cpu::ld_b_l() { ld_reg_reg(registers_.b, registers_.l); }
void Cpu::ld_b_hl_ref() {
  registers_.b = memory_.read_byte(registers_.hl);
  total_cycles_ += 2;
}
void Cpu::ld_b_a() { ld_reg_reg(registers_.b, registers_.a); }
void Cpu::ld_c_b() { ld_reg_reg(registers_.c, registers_.b); }
void Cpu::ld_c_c() { ld_reg_reg(registers_.c, registers_.c); }
void Cpu::ld_c_d() { ld_reg_reg(registers_.c, registers_.d); }
void Cpu::ld_c_e() { ld_reg_reg(registers_.c, registers_.e); }
void Cpu::ld_c_h() { ld_reg_reg(registers_.c, registers_.h); }
void Cpu::ld_c_l() { ld_reg_reg(registers_.c, registers_.l); }
void Cpu::ld_c_hl_ref() {
  registers_.c = memory_.read_byte(registers_.hl);
  total_cycles_ += 2;
}
void Cpu::ld_c_a() { ld_reg_reg(registers_.c, registers_.a); }

void Cpu::ld_d_b() { ld_reg_reg(registers_.d, registers_.b); }
void Cpu::ld_d_c() { ld_reg_reg(registers_.d, registers_.c); }
void Cpu::ld_d_d() { ld_reg_reg(registers_.d, registers_.d); }
void Cpu::ld_d_e() { ld_reg_reg(registers_.d, registers_.e); }
void Cpu::ld_d_h() { ld_reg_reg(registers_.d, registers_.h); }
void Cpu::ld_d_l() { ld_reg_reg(registers_.d, registers_.l); }
void Cpu::ld_d_hl_ref() {
  registers_.d = memory_.read_byte(registers_.hl);
  total_cycles_ += 2;
}
void Cpu::ld_d_a() { ld_reg_reg(registers_.d, registers_.a); }
void Cpu::ld_e_b() { ld_reg_reg(registers_.e, registers_.b); }
void Cpu::ld_e_c() { ld_reg_reg(registers_.e, registers_.c); }
void Cpu::ld_e_d() { ld_reg_reg(registers_.e, registers_.d); }
void Cpu::ld_e_e() { ld_reg_reg(registers_.e, registers_.e); }
void Cpu::ld_e_h() { ld_reg_reg(registers_.e, registers_.h); }
void Cpu::ld_e_l() { ld_reg_reg(registers_.e, registers_.l); }
void Cpu::ld_e_hl_ref() {
  registers_.e = memory_.read_byte(registers_.hl);
  total_cycles_ += 2;
}
void Cpu::ld_e_a() { ld_reg_reg(registers_.e, registers_.a); }

void Cpu::ld_h_b() { ld_reg_reg(registers_.h, registers_.b); }
void Cpu::ld_h_c() { ld_reg_reg(registers_.h, registers_.c); }
void Cpu::ld_h_d() { ld_reg_reg(registers_.h, registers_.d); }
void Cpu::ld_h_e() { ld_reg_reg(registers_.h, registers_.e); }
void Cpu::ld_h_h() { ld_reg_reg(registers_.h, registers_.h); }
void Cpu::ld_h_l() { ld_reg_reg(registers_.h, registers_.l); }
void Cpu::ld_h_hl_ref() {
  registers_.h = memory_.read_byte(registers_.hl);
  total_cycles_ += 2;
}
void Cpu::ld_h_a() { ld_reg_reg(registers_.h, registers_.a); }
void Cpu::ld_l_b() { ld_reg_reg(registers_.l, registers_.b); }
void Cpu::ld_l_c() { ld_reg_reg(registers_.l, registers_.c); }
void Cpu::ld_l_d() { ld_reg_reg(registers_.l, registers_.d); }
void Cpu::ld_l_e() { ld_reg_reg(registers_.l, registers_.e); }
void Cpu::ld_l_h() { ld_reg_reg(registers_.l, registers_.h); }
void Cpu::ld_l_l() { ld_reg_reg(registers_.l, registers_.l); }
void Cpu::ld_l_hl_ref() {
  registers_.l = memory_.read_byte(registers_.hl);
  total_cycles_ += 2;
}
void Cpu::ld_l_a() { ld_reg_reg(registers_.l, registers_.a); }

void Cpu::ld_hl_ref_b() {
  memory_.write_byte(registers_.hl, registers_.b);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_hl_ref_c() {
  memory_.write_byte(registers_.hl, registers_.c);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_hl_ref_d() {
  memory_.write_byte(registers_.hl, registers_.d);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_hl_ref_e() {
  memory_.write_byte(registers_.hl, registers_.e);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_hl_ref_h() {
  memory_.write_byte(registers_.hl, registers_.h);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_hl_ref_l() {
  memory_.write_byte(registers_.hl, registers_.l);
  ++registers_.pc;
  total_cycles_ += 2;
}

// todo: finish this func
void Cpu::halt() {
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::ld_hl_ref_a() {
  registers_.f = registers_.a;
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_a_b() { ld_reg_reg(registers_.a, registers_.b); }

void Cpu::ld_a_c() { ld_reg_reg(registers_.a, registers_.c); }

void Cpu::ld_a_d() { ld_reg_reg(registers_.a, registers_.d); }

void Cpu::ld_a_e() { ld_reg_reg(registers_.a, registers_.e); }

void Cpu::ld_a_h() { ld_reg_reg(registers_.a, registers_.h); }

void Cpu::ld_a_l() { ld_reg_reg(registers_.a, registers_.l); }

void Cpu::ld_a_hl_ref() {
  registers_.a = memory_.read_byte(registers_.hl);
  total_cycles_ += 2;
  total_cycles_ += 2;
}

void Cpu::ld_a_a() { ld_reg_reg(registers_.a, registers_.a); }

void Cpu::add_a_b() { add_reg_reg(registers_.a, registers_.b); }

void Cpu::add_a_c() { add_reg_reg(registers_.a, registers_.c); }

void Cpu::add_a_d() { add_reg_reg(registers_.a, registers_.d); }

void Cpu::add_a_e() { add_reg_reg(registers_.a, registers_.e); }

void Cpu::add_a_h() { add_reg_reg(registers_.a, registers_.h); }

void Cpu::add_a_l() { add_reg_reg(registers_.a, registers_.l); }

void Cpu::add_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  add_reg_reg(registers_.a, hl_content);
  ++total_cycles_;
}

void Cpu::add_a_a() { add_reg_reg(registers_.a, registers_.a); }

void Cpu::adc_a_b() { adc_reg_reg(registers_.a, registers_.b); }

void Cpu::adc_a_c() { adc_reg_reg(registers_.a, registers_.c); }

void Cpu::adc_a_d() { adc_reg_reg(registers_.a, registers_.d); }

void Cpu::adc_a_e() { adc_reg_reg(registers_.a, registers_.e); }

void Cpu::adc_a_h() { adc_reg_reg(registers_.a, registers_.h); }

void Cpu::adc_a_l() { adc_reg_reg(registers_.a, registers_.l); }

void Cpu::adc_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  adc_reg_reg(registers_.a, hl_content);
  ++total_cycles_;
}

void Cpu::adc_a_a() { adc_reg_reg(registers_.a, registers_.a); }

void Cpu::sub_a_b() { sub_reg_reg(registers_.a, registers_.b); }

void Cpu::sub_a_c() { sub_reg_reg(registers_.a, registers_.c); }

void Cpu::sub_a_d() { sub_reg_reg(registers_.a, registers_.d); }

void Cpu::sub_a_e() { sub_reg_reg(registers_.a, registers_.e); }

void Cpu::sub_a_h() { sub_reg_reg(registers_.a, registers_.h); }

void Cpu::sub_a_l() { sub_reg_reg(registers_.a, registers_.l); }

void Cpu::sub_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  sub_reg_reg(registers_.a, hl_content);
  ++total_cycles_;
}

void Cpu::sub_a_a() { sub_reg_reg(registers_.a, registers_.a); }

void Cpu::sbc_a_b() { sbc_reg_reg(registers_.a, registers_.b); }

void Cpu::sbc_a_c() { sbc_reg_reg(registers_.a, registers_.c); }

void Cpu::sbc_a_d() { sbc_reg_reg(registers_.a, registers_.d); }

void Cpu::sbc_a_e() { sbc_reg_reg(registers_.a, registers_.e); }

void Cpu::sbc_a_h() { sbc_reg_reg(registers_.a, registers_.h); }

void Cpu::sbc_a_l() { sbc_reg_reg(registers_.a, registers_.l); }

void Cpu::sbc_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  sbc_reg_reg(registers_.a, hl_content);
  ++total_cycles_;
}

void Cpu::sbc_a_a() { sbc_reg_reg(registers_.a, registers_.a); }

void Cpu::and_a_b() { and_reg_reg(registers_.a, registers_.b); }

void Cpu::and_a_c() { and_reg_reg(registers_.a, registers_.c); }

void Cpu::and_a_d() { and_reg_reg(registers_.a, registers_.d); }

void Cpu::and_a_e() { and_reg_reg(registers_.a, registers_.e); }

void Cpu::and_a_h() { and_reg_reg(registers_.a, registers_.h); }

void Cpu::and_a_l() { and_reg_reg(registers_.a, registers_.l); }

void Cpu::and_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  and_reg_reg(registers_.a, hl_content);
  ++total_cycles_;
}

void Cpu::and_a_a() { and_reg_reg(registers_.a, registers_.a); }

void Cpu::xor_a_b() { xor_reg_reg(registers_.a, registers_.b); }

void Cpu::xor_a_c() { xor_reg_reg(registers_.a, registers_.c); }

void Cpu::xor_a_d() { xor_reg_reg(registers_.a, registers_.d); }

void Cpu::xor_a_e() { xor_reg_reg(registers_.a, registers_.e); }

void Cpu::xor_a_h() { xor_reg_reg(registers_.a, registers_.h); }

void Cpu::xor_a_l() { xor_reg_reg(registers_.a, registers_.l); }

void Cpu::xor_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  xor_reg_reg(registers_.a, hl_content);
  ++total_cycles_;
}

void Cpu::xor_a_a() { xor_reg_reg(registers_.a, registers_.a); }

void Cpu::or_a_b() { or_reg_reg(registers_.a, registers_.b); }

void Cpu::or_a_c() { or_reg_reg(registers_.a, registers_.c); }

void Cpu::or_a_d() { or_reg_reg(registers_.a, registers_.d); }

void Cpu::or_a_e() { or_reg_reg(registers_.a, registers_.e); }

void Cpu::or_a_h() { or_reg_reg(registers_.a, registers_.h); }

void Cpu::or_a_l() { or_reg_reg(registers_.a, registers_.l); }

void Cpu::or_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  or_reg_reg(registers_.a, hl_content);
  ++total_cycles_;
}

void Cpu::or_a_a() { or_reg_reg(registers_.a, registers_.a); }

void Cpu::cp_a_b() { cp_reg_reg(registers_.a, registers_.b); }

void Cpu::cp_a_c() { cp_reg_reg(registers_.a, registers_.c); }

void Cpu::cp_a_d() { cp_reg_reg(registers_.a, registers_.d); }

void Cpu::cp_a_e() { cp_reg_reg(registers_.a, registers_.e); }

void Cpu::cp_a_h() { cp_reg_reg(registers_.a, registers_.h); }

void Cpu::cp_a_l() { cp_reg_reg(registers_.a, registers_.l); }

void Cpu::cp_a_hl_ref() {
  uint8_t hl_content = memory_.read_byte(registers_.hl);
  cp_reg_reg(registers_.a, hl_content);
  ++total_cycles_;
}

void Cpu::cp_a_a() { cp_reg_reg(registers_.a, registers_.a); }

void Cpu::ret_nz() {
  if (!registers_.zero) {
    pop_stack_into_reg_16(registers_.pc);
    total_cycles_ += 5;
  } else {
    total_cycles_ += 2;
  }
  ++registers_.pc;
}

void Cpu::pop_bc() {
  pop_stack_into_reg_16(registers_.bc);
  total_cycles_ += 3;
}

void Cpu::jp_nz_nn() {
  if (!registers_.zero) {
    registers_.pc = memory_.read_word(registers_.pc + 1);
    total_cycles_ += 4;
  } else {
    registers_.pc += 3;
    total_cycles_ += 3;
  }
}

void Cpu::jp_nn() {
  registers_.pc = memory_.read_word(registers_.pc + 1);
  total_cycles_ += 4;
}

void Cpu::call_nz_nn() {
  if (!registers_.zero) {
    uint16_t call_address = memory_.read_word(registers_.pc + 1);
    push_onto_stack_reg_16(call_address);
    total_cycles_ += 6;
  } else {
    registers_.pc += 3;
    total_cycles_ += 3;
  }
}

void Cpu::push_bc() {
  push_onto_stack_reg_16(registers_.bc);
  total_cycles_ += 4;
}

void Cpu::add_a_n() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  add_reg_reg(registers_.a, imm_op);
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::rst_0() { rst(0x00); }

void Cpu::ret_z() {
  if (registers_.zero) {
    pop_stack_into_reg_16(registers_.pc);
    total_cycles_ += 5;
  } else {
    total_cycles_ += 2;
    ++registers_.pc;
  }
}

void Cpu::ret() {
  pop_stack_into_reg_16(registers_.pc);
  ++registers_.pc;
  total_cycles_ += 4;
}

void Cpu::jp_z_nn() {
  if (registers_.zero) {
    registers_.pc = memory_.read_word(registers_.pc + 1);
    total_cycles_ += 4;
  } else {
    registers_.pc += 3;
    total_cycles_ += 3;
  }
}

void Cpu::call_z_nn() {
  if (registers_.zero) {
    uint16_t call_address = memory_.read_word(registers_.pc + 1);
    push_onto_stack_reg_16(call_address);
    total_cycles_ += 6;
  } else {
    registers_.pc += 3;
    total_cycles_ += 3;
  }
}

void Cpu::call_nn() {
  uint16_t call_address = memory_.read_word(registers_.pc + 1);
  push_onto_stack_reg_16(call_address);
  total_cycles_ += 6;
}

void Cpu::adc_a_n() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  adc_reg_reg(registers_.a, imm_op);
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::rst_1() { rst(0x08); }

void Cpu::ret_nc() {
  if (!registers_.carry) {
    pop_stack_into_reg_16(registers_.pc);
    total_cycles_ += 5;
  } else {
    total_cycles_ += 2;
    ++registers_.pc;
  }
}

void Cpu::pop_de() {
  pop_stack_into_reg_16(registers_.de);
  total_cycles_ += 3;
}

void Cpu::jp_nc_nn() {
  if (!registers_.carry) {
    registers_.pc = memory_.read_word(registers_.pc + 1);
    total_cycles_ += 4;
  } else {
    registers_.pc += 3;
    total_cycles_ += 3;
  }
}

void Cpu::call_nc_nn() {
  if (!registers_.carry) {
    uint16_t call_address = memory_.read_word(registers_.pc + 1);
    push_onto_stack_reg_16(call_address);
    total_cycles_ += 6;
  } else {
    registers_.pc += 3;
    total_cycles_ += 3;
  }
}

void Cpu::push_de() {
  push_onto_stack_reg_16(registers_.de);
  total_cycles_ += 4;
}

void Cpu::sub_a_n() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  sub_reg_reg(registers_.a, imm_op);
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::rst_2() { rst(0x10); }

void Cpu::ret_c() {
  if (registers_.carry) {
    pop_stack_into_reg_16(registers_.pc);
    total_cycles_ += 5;
  } else {
    total_cycles_ += 2;
    ++registers_.pc;
  }
}

void Cpu::reti() {
  // todo finish this func
  ++registers_.pc;
  total_cycles_ += 4;
}

void Cpu::jp_c_nn() {
  if (registers_.carry) {
    registers_.pc = memory_.read_word(registers_.pc + 1);
    total_cycles_ += 4;
  } else {
    registers_.pc += 3;
    total_cycles_ += 3;
  }
}

void Cpu::call_c_nn() {
  if (registers_.carry) {
    uint16_t call_address = memory_.read_word(registers_.pc + 1);
    push_onto_stack_reg_16(call_address);
    total_cycles_ += 6;
  } else {
    registers_.pc += 3;
    total_cycles_ += 3;
  }
}

void Cpu::sbc_a_n() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  sbc_reg_reg(registers_.a, imm_op);
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::rst_3() { rst(0x18); }

void Cpu::ld_n_ref_a() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  memory_.write_byte(0xFF00 | imm_op, registers_.a);
  registers_.pc += 2;
  total_cycles_ += 3;
}

void Cpu::pop_hl() {
  pop_stack_into_reg_16(registers_.hl);
  total_cycles_ += 3;
}

void Cpu::ld_c_ref_a() {
  uint8_t address =
      memory_.read_byte(static_cast<uint8_t>(0xFF00) | registers_.c);
  memory_.write_byte(address, registers_.a);
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::push_hl() {
  push_onto_stack_reg_16(registers_.hl);
  total_cycles_ += 4;
}

void Cpu::and_a_n() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  and_reg_reg(registers_.a, imm_op);
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::rst_4() { rst(0x20); }

void Cpu::add_sp_n() {
  uint16_t old_sp = registers_.sp;
  int8_t operand = static_cast<int8_t>(memory_.read_byte(registers_.pc + 1));
  registers_.sp += operand;
  registers_.zero = 0;
  registers_.subtract = 0;
  registers_.set_half_carry_flag_from_word_result(old_sp, registers_.a,
                                                  operand);
  registers_.set_carry_flag_from_word_result(old_sp, registers_.a, operand);
  registers_.pc += 2;
  total_cycles_ += 4;
}

void Cpu::jp_hl() {
  registers_.pc = memory_.read_word(registers_.hl + 1);
  ++total_cycles_;
}

void Cpu::ld_nn_ref_a() {
  uint16_t imm_op = memory_.read_word(registers_.pc + 1);
  memory_.write_byte(imm_op, registers_.a);
  registers_.pc += 2;
  total_cycles_ += 4;
}

void Cpu::xor_a_n() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  xor_reg_reg(registers_.a, imm_op);
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::rst_5() { rst(0x28); }

void Cpu::ld_a_n_ref() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  registers_.a = memory_.read_byte(imm_op);
  registers_.pc += 2;
  total_cycles_ += 3;
}

void Cpu::pop_af() {
  pop_stack_into_reg_16(registers_.af);
  total_cycles_ += 3;
}

void Cpu::ld_a_c_ref() {
  uint8_t content =
      memory_.read_byte(static_cast<uint8_t>(0xFF00) | registers_.c);
  registers_.a = content;
  ++registers_.pc;
  total_cycles_ += 2;
}

// todo: finish this func
void Cpu::di() {
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::push_af() {
  push_onto_stack_reg_16(registers_.af);
  total_cycles_ += 4;
}

void Cpu::or_a_n() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  or_reg_reg(registers_.a, imm_op);
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::rst_6() { rst(0x30); }

void Cpu::ld_hl_sp_n() {
  registers_.hl = static_cast<uint16_t>(
      registers_.sp +
      static_cast<int8_t>(memory_.read_byte(registers_.pc + 1)));
  registers_.pc += 2;
  total_cycles_ += 3;
}

void Cpu::ld_sp_hl() {
  registers_.sp = registers_.hl;
  ++registers_.pc;
  total_cycles_ += 2;
}

void Cpu::ld_a_nn_ref() {
  uint16_t imm_op = memory_.read_word(registers_.pc + 1);
  registers_.a = memory_.read_byte(imm_op);
  registers_.pc += 2;
  total_cycles_ += 4;
}

// todo: finish this func
void Cpu::e_i() {
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::cp_a_n() {
  uint8_t imm_op = memory_.read_byte(registers_.pc + 1);
  cp_reg_reg(registers_.a, imm_op);
  ++registers_.pc;
  ++total_cycles_;
}

void Cpu::rst_7() { rst(0x38); }

void Cpu::rlc_b() { rlc(registers_.b); }
void Cpu::rlc_c() { rlc(registers_.c); }
void Cpu::rlc_d() { rlc(registers_.d); }
void Cpu::rlc_e() { rlc(registers_.e); }
void Cpu::rlc_h() { rlc(registers_.h); }
void Cpu::rlc_l() { rlc(registers_.l); }
void Cpu::rlc_hl_ref() {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t bit7 = (ref_byte & 0x8) >> 7;
  uint8_t result = static_cast<uint8_t>(ref_byte << 1) | bit7;
  memory_.write_byte(registers_.hl, result);
  registers_.set_zero_flag_from_byte_result(result);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  registers_.pc += 2;
  total_cycles_ += 2;
}
void Cpu::rlc_a() { rlc(registers_.a); }

void Cpu::rrc_b() { rrc(registers_.b); }
void Cpu::rrc_c() { rrc(registers_.c); }
void Cpu::rrc_d() { rrc(registers_.d); }
void Cpu::rrc_e() { rrc(registers_.e); }
void Cpu::rrc_h() { rrc(registers_.h); }
void Cpu::rrc_l() { rrc(registers_.l); }
void Cpu::rrc_hl_ref() {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t bit0 = ref_byte & 0x1;
  uint8_t result = (ref_byte >> 1) | static_cast<uint8_t>(bit0 << 7);
  memory_.write_byte(registers_.hl, result);
  registers_.set_zero_flag_from_byte_result(result);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  registers_.pc += 2;
  total_cycles_ += 2;
}
void Cpu::rrc_a() { rrc(registers_.a); }

void Cpu::rl_b() { rl(registers_.b); }
void Cpu::rl_c() { rl(registers_.c); }
void Cpu::rl_d() { rl(registers_.d); }
void Cpu::rl_e() { rl(registers_.e); }
void Cpu::rl_h() { rl(registers_.h); }
void Cpu::rl_l() { rl(registers_.l); }
void Cpu::rl_hl_ref() {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t bit7 = (ref_byte & 0x8) >> 7;
  uint8_t result = static_cast<uint8_t>(ref_byte << 1) | registers_.carry;
  memory_.write_byte(registers_.hl, result);
  registers_.set_zero_flag_from_byte_result(result);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  registers_.pc += 2;
  total_cycles_ += 2;
}
void Cpu::rl_a() { rl(registers_.a); }

void Cpu::rr_b() { rr(registers_.b); }
void Cpu::rr_c() { rr(registers_.c); }
void Cpu::rr_d() { rr(registers_.d); }
void Cpu::rr_e() { rr(registers_.e); }
void Cpu::rr_h() { rr(registers_.h); }
void Cpu::rr_l() { rr(registers_.l); }
void Cpu::rr_hl_ref() {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t bit0 = ref_byte & 0x1;
  uint8_t result =
      (ref_byte >> 1) | static_cast<uint8_t>(registers_.carry << 7);
  memory_.write_byte(registers_.hl, result);
  registers_.set_zero_flag_from_byte_result(ref_byte);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  registers_.pc += 2;
  total_cycles_ += 2;
}
void Cpu::rr_a() { rr(registers_.a); }

void Cpu::sla_b() { sla(registers_.b); }
void Cpu::sla_c() { sla(registers_.c); }
void Cpu::sla_d() { sla(registers_.d); }
void Cpu::sla_e() { sla(registers_.e); }
void Cpu::sla_h() { sla(registers_.h); }
void Cpu::sla_l() { sla(registers_.l); }
void Cpu::sla_hl_ref() {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t bit7 = (ref_byte & 0x8) >> 7;
  uint8_t result = static_cast<uint8_t>(ref_byte << 1);
  memory_.write_byte(registers_.hl, result);
  registers_.set_zero_flag_from_byte_result(result);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit7;
  registers_.pc += 2;
  total_cycles_ += 2;
}
void Cpu::sla_a() { sla(registers_.a); }

void Cpu::sra_b() { sra(registers_.b); }
void Cpu::sra_c() { sra(registers_.c); }
void Cpu::sra_d() { sra(registers_.d); }
void Cpu::sra_e() { sra(registers_.e); }
void Cpu::sra_h() { sra(registers_.h); }
void Cpu::sra_l() { sra(registers_.l); }
void Cpu::sra_hl_ref() {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t bit0 = ref_byte & 0x1;
  uint8_t bit7 = ref_byte & 0x80;
  uint8_t result = (ref_byte >> 1) | bit7;
  memory_.write_byte(registers_.hl, result);
  registers_.set_zero_flag_from_byte_result(result);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  registers_.pc += 2;
  total_cycles_ += 2;
}
void Cpu::sra_a() { sra(registers_.a); }

void Cpu::swap_b() { swap(registers_.b); }
void Cpu::swap_c() { swap(registers_.c); }
void Cpu::swap_d() { swap(registers_.d); }
void Cpu::swap_e() { swap(registers_.e); }
void Cpu::swap_h() { swap(registers_.h); }
void Cpu::swap_l() { swap(registers_.l); }
void Cpu::swap_hl_ref() {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t lower_bits = static_cast<uint8_t>((ref_byte & 0xF) << 4);
  uint8_t upper_bits = (ref_byte & 0xF0) >> 4;
  uint8_t result = lower_bits | upper_bits;
  memory_.write_byte(registers_.hl, result);
  registers_.set_zero_flag_from_byte_result(result);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = 0;
  registers_.pc += 2;
  total_cycles_ += 2;
}
void Cpu::swap_a() { swap(registers_.a); }

void Cpu::srl_b() { srl(registers_.b); }
void Cpu::srl_c() { srl(registers_.c); }
void Cpu::srl_d() { srl(registers_.d); }
void Cpu::srl_e() { srl(registers_.e); }
void Cpu::srl_h() { srl(registers_.h); }
void Cpu::srl_l() { srl(registers_.l); }
void Cpu::srl_hl_ref() {
  uint8_t ref_byte = memory_.read_byte(registers_.hl);
  uint8_t bit0 = ref_byte & 0x1;
  uint8_t result = static_cast<uint8_t>(ref_byte >> 1);
  memory_.write_byte(registers_.hl, result);
  registers_.set_zero_flag_from_byte_result(result);
  registers_.subtract = 0;
  registers_.half_carry = 0;
  registers_.carry = bit0;
  registers_.pc += 2;
  total_cycles_ += 2;
}
void Cpu::srl_a() { srl(registers_.a); }

void Cpu::bit_0_b() { bit(registers_.b, 0); }
void Cpu::bit_0_c() { bit(registers_.c, 0); }
void Cpu::bit_0_d() { bit(registers_.d, 0); }
void Cpu::bit_0_e() { bit(registers_.e, 0); }
void Cpu::bit_0_h() { bit(registers_.h, 0); }
void Cpu::bit_0_l() { bit(registers_.l, 0); }
void Cpu::bit_0_hl_ref() { bit_hl_ref(0); }
void Cpu::bit_0_a() { bit(registers_.a, 0); }

void Cpu::bit_1_b() { bit(registers_.b, 1); }
void Cpu::bit_1_c() { bit(registers_.c, 1); }
void Cpu::bit_1_d() { bit(registers_.d, 1); }
void Cpu::bit_1_e() { bit(registers_.e, 1); }
void Cpu::bit_1_h() { bit(registers_.h, 1); }
void Cpu::bit_1_l() { bit(registers_.l, 1); }
void Cpu::bit_1_hl_ref() { bit_hl_ref(1); }
void Cpu::bit_1_a() { bit(registers_.a, 1); }

void Cpu::bit_2_b() { bit(registers_.b, 2); }
void Cpu::bit_2_c() { bit(registers_.c, 2); }
void Cpu::bit_2_d() { bit(registers_.d, 2); }
void Cpu::bit_2_e() { bit(registers_.e, 2); }
void Cpu::bit_2_h() { bit(registers_.h, 2); }
void Cpu::bit_2_l() { bit(registers_.l, 2); }
void Cpu::bit_2_hl_ref() { bit_hl_ref(2); }
void Cpu::bit_2_a() { bit(registers_.a, 2); }

void Cpu::bit_3_b() { bit(registers_.b, 3); }
void Cpu::bit_3_c() { bit(registers_.c, 3); }
void Cpu::bit_3_d() { bit(registers_.d, 3); }
void Cpu::bit_3_e() { bit(registers_.e, 3); }
void Cpu::bit_3_h() { bit(registers_.h, 3); }
void Cpu::bit_3_l() { bit(registers_.l, 3); }
void Cpu::bit_3_hl_ref() { bit_hl_ref(3); }
void Cpu::bit_3_a() { bit(registers_.a, 3); }

void Cpu::bit_4_b() { bit(registers_.b, 4); }
void Cpu::bit_4_c() { bit(registers_.c, 4); }
void Cpu::bit_4_d() { bit(registers_.d, 4); }
void Cpu::bit_4_e() { bit(registers_.e, 4); }
void Cpu::bit_4_h() { bit(registers_.h, 4); }
void Cpu::bit_4_l() { bit(registers_.l, 4); }
void Cpu::bit_4_hl_ref() { bit_hl_ref(4); }
void Cpu::bit_4_a() { bit(registers_.a, 4); }

void Cpu::bit_5_b() { bit(registers_.b, 5); }
void Cpu::bit_5_c() { bit(registers_.c, 5); }
void Cpu::bit_5_d() { bit(registers_.d, 5); }
void Cpu::bit_5_e() { bit(registers_.e, 5); }
void Cpu::bit_5_h() { bit(registers_.h, 5); }
void Cpu::bit_5_l() { bit(registers_.l, 5); }
void Cpu::bit_5_hl_ref() { bit_hl_ref(5); }
void Cpu::bit_5_a() { bit(registers_.a, 5); }

void Cpu::bit_6_b() { bit(registers_.b, 6); }
void Cpu::bit_6_c() { bit(registers_.c, 6); }
void Cpu::bit_6_d() { bit(registers_.d, 6); }
void Cpu::bit_6_e() { bit(registers_.e, 6); }
void Cpu::bit_6_h() { bit(registers_.h, 6); }
void Cpu::bit_6_l() { bit(registers_.l, 6); }
void Cpu::bit_6_hl_ref() { bit_hl_ref(6); }
void Cpu::bit_6_a() { bit(registers_.a, 6); }

void Cpu::bit_7_b() { bit(registers_.b, 7); }
void Cpu::bit_7_c() { bit(registers_.c, 7); }
void Cpu::bit_7_d() { bit(registers_.d, 7); }
void Cpu::bit_7_e() { bit(registers_.e, 7); }
void Cpu::bit_7_h() { bit(registers_.h, 7); }
void Cpu::bit_7_l() { bit(registers_.l, 7); }
void Cpu::bit_7_hl_ref() { bit_hl_ref(7); }
void Cpu::bit_7_a() { bit(registers_.a, 7); }

void Cpu::res_0_b() { res(registers_.b, 0); }
void Cpu::res_0_c() { res(registers_.c, 0); }
void Cpu::res_0_d() { res(registers_.d, 0); }
void Cpu::res_0_e() { res(registers_.e, 0); }
void Cpu::res_0_h() { res(registers_.h, 0); }
void Cpu::res_0_l() { res(registers_.l, 0); }
void Cpu::res_0_hl_ref() { res_hl_ref(0); }
void Cpu::res_0_a() { res(registers_.a, 0); }

void Cpu::res_1_b() { res(registers_.b, 1); }
void Cpu::res_1_c() { res(registers_.c, 1); }
void Cpu::res_1_d() { res(registers_.d, 1); }
void Cpu::res_1_e() { res(registers_.e, 1); }
void Cpu::res_1_h() { res(registers_.h, 1); }
void Cpu::res_1_l() { res(registers_.l, 1); }
void Cpu::res_1_hl_ref() { res_hl_ref(1); }
void Cpu::res_1_a() { res(registers_.a, 1); }

void Cpu::res_2_b() { res(registers_.b, 2); }
void Cpu::res_2_c() { res(registers_.c, 2); }
void Cpu::res_2_d() { res(registers_.d, 2); }
void Cpu::res_2_e() { res(registers_.e, 2); }
void Cpu::res_2_h() { res(registers_.h, 2); }
void Cpu::res_2_l() { res(registers_.l, 2); }
void Cpu::res_2_hl_ref() { res_hl_ref(2); }
void Cpu::res_2_a() { res(registers_.a, 2); }

void Cpu::res_3_b() { res(registers_.b, 3); }
void Cpu::res_3_c() { res(registers_.c, 3); }
void Cpu::res_3_d() { res(registers_.d, 3); }
void Cpu::res_3_e() { res(registers_.e, 3); }
void Cpu::res_3_h() { res(registers_.h, 3); }
void Cpu::res_3_l() { res(registers_.l, 3); }
void Cpu::res_3_hl_ref() { res_hl_ref(3); }
void Cpu::res_3_a() { res(registers_.a, 3); }

void Cpu::res_4_b() { res(registers_.b, 4); }
void Cpu::res_4_c() { res(registers_.c, 4); }
void Cpu::res_4_d() { res(registers_.d, 4); }
void Cpu::res_4_e() { res(registers_.e, 4); }
void Cpu::res_4_h() { res(registers_.h, 4); }
void Cpu::res_4_l() { res(registers_.l, 4); }
void Cpu::res_4_hl_ref() { res_hl_ref(4); }
void Cpu::res_4_a() { res(registers_.a, 4); }

void Cpu::res_5_b() { res(registers_.b, 5); }
void Cpu::res_5_c() { res(registers_.c, 5); }
void Cpu::res_5_d() { res(registers_.d, 5); }
void Cpu::res_5_e() { res(registers_.e, 5); }
void Cpu::res_5_h() { res(registers_.h, 5); }
void Cpu::res_5_l() { res(registers_.l, 5); }
void Cpu::res_5_hl_ref() { res_hl_ref(5); }
void Cpu::res_5_a() { res(registers_.a, 5); }

void Cpu::res_6_b() { res(registers_.b, 6); }
void Cpu::res_6_c() { res(registers_.c, 6); }
void Cpu::res_6_d() { res(registers_.d, 6); }
void Cpu::res_6_e() { res(registers_.e, 6); }
void Cpu::res_6_h() { res(registers_.h, 6); }
void Cpu::res_6_l() { res(registers_.l, 6); }
void Cpu::res_6_hl_ref() { res_hl_ref(6); }
void Cpu::res_6_a() { res(registers_.a, 6); }

void Cpu::res_7_b() { res(registers_.b, 7); }
void Cpu::res_7_c() { res(registers_.c, 7); }
void Cpu::res_7_d() { res(registers_.d, 7); }
void Cpu::res_7_e() { res(registers_.e, 7); }
void Cpu::res_7_h() { res(registers_.h, 7); }
void Cpu::res_7_l() { res(registers_.l, 7); }
void Cpu::res_7_hl_ref() { res_hl_ref(7); }
void Cpu::res_7_a() { res(registers_.a, 7); }

void Cpu::set_0_b() { set(registers_.b, 0); }
void Cpu::set_0_c() { set(registers_.c, 0); }
void Cpu::set_0_d() { set(registers_.d, 0); }
void Cpu::set_0_e() { set(registers_.e, 0); }
void Cpu::set_0_h() { set(registers_.h, 0); }
void Cpu::set_0_l() { set(registers_.l, 0); }
void Cpu::set_0_hl_ref() { set_hl_ref(0); }
void Cpu::set_0_a() { set(registers_.a, 0); }

void Cpu::set_1_b() { set(registers_.b, 1); }
void Cpu::set_1_c() { set(registers_.c, 1); }
void Cpu::set_1_d() { set(registers_.d, 1); }
void Cpu::set_1_e() { set(registers_.e, 1); }
void Cpu::set_1_h() { set(registers_.h, 1); }
void Cpu::set_1_l() { set(registers_.l, 1); }
void Cpu::set_1_hl_ref() { set_hl_ref(1); }
void Cpu::set_1_a() { set(registers_.a, 1); }

void Cpu::set_2_b() { set(registers_.b, 2); }
void Cpu::set_2_c() { set(registers_.c, 2); }
void Cpu::set_2_d() { set(registers_.d, 2); }
void Cpu::set_2_e() { set(registers_.e, 2); }
void Cpu::set_2_h() { set(registers_.h, 2); }
void Cpu::set_2_l() { set(registers_.l, 2); }
void Cpu::set_2_hl_ref() { set_hl_ref(2); }
void Cpu::set_2_a() { set(registers_.a, 2); }

void Cpu::set_3_b() { set(registers_.b, 3); }
void Cpu::set_3_c() { set(registers_.c, 3); }
void Cpu::set_3_d() { set(registers_.d, 3); }
void Cpu::set_3_e() { set(registers_.e, 3); }
void Cpu::set_3_h() { set(registers_.h, 3); }
void Cpu::set_3_l() { set(registers_.l, 3); }
void Cpu::set_3_hl_ref() { set_hl_ref(3); }
void Cpu::set_3_a() { set(registers_.a, 3); }

void Cpu::set_4_b() { set(registers_.b, 4); }
void Cpu::set_4_c() { set(registers_.c, 4); }
void Cpu::set_4_d() { set(registers_.d, 4); }
void Cpu::set_4_e() { set(registers_.e, 4); }
void Cpu::set_4_h() { set(registers_.h, 4); }
void Cpu::set_4_l() { set(registers_.l, 4); }
void Cpu::set_4_hl_ref() { set_hl_ref(4); }
void Cpu::set_4_a() { set(registers_.a, 4); }

void Cpu::set_5_b() { set(registers_.b, 5); }
void Cpu::set_5_c() { set(registers_.c, 5); }
void Cpu::set_5_d() { set(registers_.d, 5); }
void Cpu::set_5_e() { set(registers_.e, 5); }
void Cpu::set_5_h() { set(registers_.h, 5); }
void Cpu::set_5_l() { set(registers_.l, 5); }
void Cpu::set_5_hl_ref() { set_hl_ref(5); }
void Cpu::set_5_a() { set(registers_.a, 5); }

void Cpu::set_6_b() { set(registers_.b, 6); }
void Cpu::set_6_c() { set(registers_.c, 6); }
void Cpu::set_6_d() { set(registers_.d, 6); }
void Cpu::set_6_e() { set(registers_.e, 6); }
void Cpu::set_6_h() { set(registers_.h, 6); }
void Cpu::set_6_l() { set(registers_.l, 6); }
void Cpu::set_6_hl_ref() { set_hl_ref(6); }
void Cpu::set_6_a() { set(registers_.a, 6); }

void Cpu::set_7_b() { set(registers_.b, 7); }
void Cpu::set_7_c() { set(registers_.c, 7); }
void Cpu::set_7_d() { set(registers_.d, 7); }
void Cpu::set_7_e() { set(registers_.e, 7); }
void Cpu::set_7_h() { set(registers_.h, 7); }
void Cpu::set_7_l() { set(registers_.l, 7); }
void Cpu::set_7_hl_ref() { set_hl_ref(7); }
void Cpu::set_7_a() { set(registers_.a, 7); }

} // namespace Core
} // namespace GameBoyEmu
