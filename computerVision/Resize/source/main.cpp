#include <iostream>
#include "header/CVUtils.hpp"
#include <assert.h>

using INT32S=int;
using INT32U=unsigned int;
using INT16S=short;
using INT16U=unsigned short;
using INT08S=char;
using INT08U=unsigned char;
using FP32=float;
#define APP_CMR_SR_RSZ_SUB_PIXEL_BITS 3
#define INP_SIZE 8
#define OUT_SIZE 5

INT32S gen_bilinear_coeff(const INT32U inp_sz_inp_u32
                            , const INT32U inp_sz_out_u32
                            , const INT32U inp_mul_factor_u32
                            , INT16U* pa_out_pos_u16
                            , INT08S* pa_out_wgt_s8)
{
    const INT32U t_wgt_sum_u32 {(1U<<APP_CMR_SR_RSZ_SUB_PIXEL_BITS)};
    // 8
    const INT32U t_half_wgt_sum_u32{(1U<<(APP_CMR_SR_RSZ_SUB_PIXEL_BITS-1))};
    // 4
    const FP32 inp_sz_out_f32 = static_cast<FP32>(inp_sz_out_u32);
    
    INT32U pos_weighted_u32{0U};
    INT32U tmp_ref_pos_u32{0U};
    INT32U tmp_weight_u32{0U};
    FP32 wgt_pel_pos_f32{0.f};
    const INT32U t_max_pos_bound_u32 = {inp_sz_inp_u32 * inp_mul_factor_u32};
    assert(65535U > t_max_pos_bound_u32);

    for(INT32U idx_elmt_u32=0U; idx_elmt_u32<inp_sz_out_u32; idx_elmt_u32++)
    {
        wgt_pel_pos_f32 = static_cast<FP32>(((idx_elmt_u32*t_wgt_sum_u32)+t_half_wgt_sum_u32)
                                            *inp_sz_inp_u32);
        pos_weighted_u32 = static_cast<INT32U>(wgt_pel_pos_f32 / inp_sz_out_f32);
        
        tmp_ref_pos_u32 = 0U;
        tmp_weight_u32 = t_wgt_sum_u32; // 8;
        if( pos_weighted_u32 >= t_half_wgt_sum_u32)
        {
            tmp_ref_pos_u32 = ((pos_weighted_u32-t_half_wgt_sum_u32) >> APP_CMR_SR_RSZ_SUB_PIXEL_BITS);
            tmp_weight_u32 = t_wgt_sum_u32-((pos_weighted_u32-t_half_wgt_sum_u32)&(t_wgt_sum_u32-1U));           
        }
        if((inp_sz_inp_u32-1U)==tmp_ref_pos_u32)
        {
            tmp_ref_pos_u32 = (inp_sz_inp_u32-2U);
            tmp_weight_u32 = 0U;
        }
        *pa_out_pos_u16++ = static_cast<INT16U>(tmp_ref_pos_u32*inp_mul_factor_u32);
        *pa_out_wgt_s8++ = static_cast<INT08S>(tmp_weight_u32);
    }
    
}

int main()
{
    std::string target_path = PROJECT_ROOT"/../DB/lena.jpg";

    INT16U vert_pos_u16[OUT_SIZE];
    INT08S vert_wgt_s8[OUT_SIZE];

    gen_bilinear_coeff(INP_SIZE,OUT_SIZE,1,vert_pos_u16,vert_wgt_s8);

    /*
        자 위치정보는 먼가 느낌이 나누는 걸 기반으로 하는것 같다 이말이야...
        8/5 = 1.6
        즉 첫빠따는
        0
        1 -> (1.6)*1
        3 -> (1.6)*2 = 3.2
        4 -> (1.6)*3 = 4.8
        6 -> (1.6)*4 = 6.4
        6 ..?

        근데 먼가 미묘하게달라 뭐가 푕ㄴ트 일까?

    */
    return 0;
}