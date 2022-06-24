uint8x8_t val_vuyx_cur_line0_u8x8 = vld1_u8(pa_input_line0);
uint8x8_t val_vuyx_cur_line1_u8x8 = vld1_u8(pa_input_line0);
uint8x8_t val_vuyx_cur_line2_u8x8 = vld1_u8(pa_input_line0);
uint8x8_t val_vuyx_cur_line3_u8x8 = vld1_u8(pa_input_line0);
uint8x8_t val_vuyx_cur_line4_u8x8 = vld1_u8(pa_input_line0);
uint8x8_t val_vuyx_cur_line5_u8x8 = vld1_u8(pa_input_line0);
uint8x8_t val_vuyx_cur_line6_u8x8 = vld1_u8(pa_input_line0);
uint8x8_t val_vuyx_cur_line7_u8x8 = vld1_u8(pa_input_line0);

uint8x8_t val_vuyx_nxt_line0_u8x8 = vld1_u8(pa_input_line1);
uint8x8_t val_vuyx_nxt_line1_u8x8 = vld1_u8(pa_input_line1);
uint8x8_t val_vuyx_nxt_line2_u8x8 = vld1_u8(pa_input_line1);
uint8x8_t val_vuyx_nxt_line3_u8x8 = vld1_u8(pa_input_line1);
uint8x8_t val_vuyx_nxt_line4_u8x8 = vld1_u8(pa_input_line1);
uint8x8_t val_vuyx_nxt_line5_u8x8 = vld1_u8(pa_input_line1);
uint8x8_t val_vuyx_nxt_line6_u8x8 = vld1_u8(pa_input_line1);
uint8x8_t val_vuyx_nxt_line7_u8x8 = vld1_u8(pa_input_line1);
/*
    v0  u0  y0  x0  v1  u1  y1  x1(v16)
    v2  u2  y2  x2  v3  u3  y3  x3(u16)
    v4  u4  y4  x4  v5  u5  y5  x5(y16)
    v6  u6  y6  x6  v7  u7  y7  x7(x16)
    v8  u8  y8  x8  v9  u9  y9  x9(v17)
    v10 u10 y10 x10 v11 u11 y11 x11(u17)
    v12 u12 y12 x12 v13 u13 y13 x13(y17)
    v14 u14 y14 x14 v15 u15 y15 x15(x17)

    nv0  nu0  ny0  nx0  nv1  nu1  ny1  nx1
    nv2  nu2  ny2  nx2  nv3  nu3  ny3  nx3
    nv4  nu4  ny4  nx4  nv5  nu5  ny5  nx5
    nv6  nu6  ny6  nx6  nv7  nu7  ny7  nx7
    nv8  nu8  ny8  nx8  nv9  nu9  ny9  nx9
    nv10 nu10 ny10 nx10 nv11 nu11 ny11 nx11
    nv12 nu12 ny12 nx12 nv13 nu13 ny13 nx13
    nv14 nu14 ny14 nx14 nv15 nu15 ny15 nx15
*/

uint16x8_t val_addl_line0_u16x8 = vaddl_u8(val_vuyx_cur_line0_u8x8, val_vuyx_nxt_line0_u8x8);
uint16x8_t val_addl_line1_u16x8 = vaddl_u8(val_vuyx_cur_line1_u8x8, val_vuyx_nxt_line1_u8x8);
uint16x8_t val_addl_line2_u16x8 = vaddl_u8(val_vuyx_cur_line2_u8x8, val_vuyx_nxt_line2_u8x8);
uint16x8_t val_addl_line3_u16x8 = vaddl_u8(val_vuyx_cur_line3_u8x8, val_vuyx_nxt_line3_u8x8);
uint16x8_t val_addl_line4_u16x8 = vaddl_u8(val_vuyx_cur_line4_u8x8, val_vuyx_nxt_line4_u8x8);
uint16x8_t val_addl_line5_u16x8 = vaddl_u8(val_vuyx_cur_line5_u8x8, val_vuyx_nxt_line5_u8x8);
uint16x8_t val_addl_line6_u16x8 = vaddl_u8(val_vuyx_cur_line6_u8x8, val_vuyx_nxt_line6_u8x8);
uint16x8_t val_addl_line7_u16x8 = vaddl_u8(val_vuyx_cur_line7_u8x8, val_vuyx_nxt_line7_u8x8);
/*
    v0+nv0, u0+nu0, y0+ny0, x0+nx0, v1+nv1, u1+nu1, y1+ny1, x1+nx1
    v2+nv2, u2+nu2, y2+ny2, x2+nx2, v3+nv3, u3+nu3, y3+ny3, x3+nx3
    v4+nv4, u4+nu4, y4+ny4, x4+nx4, v5+nv5, u5+nu5, y5+ny5, x5+nx5
    v6+nv6, u6+nu6, y6+ny6, x6+nx6, v7+nv7, u7+nu7, y7+ny7, x7+nx7
    v8+nv8, u8+nu8, y8+ny8, x8+nx8, v9+nv9, u9+nu9, y9+ny9, x9+nx9
    v10+nv10, u10+nu10, y10+ny10, x10+nx10, v11+nv11, u11+nu11, y11+ny11, x11+nx11
    v12+nv12, u12+nu12, y12+ny12, x12+nx12, v13+nv13, u13+nu13, y13+ny13, x13+nx13
    v14+nv14, u14+nu14, y14+ny14, x14+nx14, v15+nv15, u15+nu15, y15+ny15, x15+nx15
*/
uint16x4_t val_low_addl_line0_u16x4 = vget_low_u16(val_addl_line0_u16x8);
uint16x4_t val_low_addl_line1_u16x4 = vget_low_u16(val_addl_line1_u16x8);
uint16x4_t val_low_addl_line2_u16x4 = vget_low_u16(val_addl_line2_u16x8);
uint16x4_t val_low_addl_line3_u16x4 = vget_low_u16(val_addl_line3_u16x8);
uint16x4_t val_low_addl_line4_u16x4 = vget_low_u16(val_addl_line4_u16x8);
uint16x4_t val_low_addl_line5_u16x4 = vget_low_u16(val_addl_line5_u16x8);
uint16x4_t val_low_addl_line6_u16x4 = vget_low_u16(val_addl_line6_u16x8);
uint16x4_t val_low_addl_line7_u16x4 = vget_low_u16(val_addl_line7_u16x8);

uint16x4_t val_high_addl_line0_u16x4 = vget_high_u16(val_addl_line0_u16x8);
uint16x4_t val_high_addl_line1_u16x4 = vget_high_u16(val_addl_line1_u16x8);
uint16x4_t val_high_addl_line2_u16x4 = vget_high_u16(val_addl_line2_u16x8);
uint16x4_t val_high_addl_line3_u16x4 = vget_high_u16(val_addl_line3_u16x8);
uint16x4_t val_high_addl_line4_u16x4 = vget_high_u16(val_addl_line4_u16x8);
uint16x4_t val_high_addl_line5_u16x4 = vget_high_u16(val_addl_line5_u16x8);
uint16x4_t val_high_addl_line6_u16x4 = vget_high_u16(val_addl_line6_u16x8);
uint16x4_t val_high_addl_line7_u16x4 = vget_high_u16(val_addl_line7_u16x8);

uint32x4_t val_addl_line0_u32x4 = vaddql_u16(val_low_addl_line0_u16x4, val_high_addl_line0_u16x4);
uint32x4_t val_addl_line1_u32x4 = vaddql_u16(val_low_addl_line1_u16x4, val_high_addl_line1_u16x4);
uint32x4_t val_addl_line2_u32x4 = vaddql_u16(val_low_addl_line2_u16x4, val_high_addl_line2_u16x4);
uint32x4_t val_addl_line3_u32x4 = vaddql_u16(val_low_addl_line3_u16x4, val_high_addl_line3_u16x4);
uint32x4_t val_addl_line4_u32x4 = vaddql_u16(val_low_addl_line4_u16x4, val_high_addl_line4_u16x4);
uint32x4_t val_addl_line5_u32x4 = vaddql_u16(val_low_addl_line5_u16x4, val_high_addl_line5_u16x4);
uint32x4_t val_addl_line6_u32x4 = vaddql_u16(val_low_addl_line6_u16x4, val_high_addl_line6_u16x4);
uint32x4_t val_addl_line7_u32x4 = vaddql_u16(val_low_addl_line7_u16x4, val_high_addl_line7_u16x4);

/*
    V0 U0 Y0 X0(*V8) -> line0
    V1 U1 Y1 X1(*U8) -> line1
    V2 U2 Y2 X2(*Y8) -> line2
    V3 U3 Y3 X3(*X8) -> line3

    V4 U4 Y4 X4(*V9) -> line4
    V5 U5 Y5 X5(*U9) -> line5
    V6 U6 Y6 X6(*Y9) -> line6
    V7 U7 Y7 X7(*X9) -> line7
*/

