/*

use vld4_u8

cv0 cv1 cv2 cv3 cv4 cv5 cv6 cv7 | cv8 cv9 cv10 cv11 cv12 cv13 cv15 cv16
cu0 cu1 cu2 cu3 cu4 cu5 cu6 cu7 | cu8 cu9 cu10 cu11 cu12 cu13 cu14 cu15
cy0 cy1 cy2 cy3 cy4 cy5 cy6 cy7 | cy8 cy9 cy10 cy11 cy12 cy13 cy14 cy15
               
nv0 nv1 nv2 nv3 nv4 nv5 nv6 nv7 | nv8 nv9 nv10 nv11 nv12 nv13 nv15 nv16
nu0 nu1 nu2 nu3 nu4 nu5 nu6 nu7 | nu8 nu9 nu10 nu11 nu12 nu13 nu14 nu15
ny0 ny1 ny2 ny3 ny4 ny5 ny6 ny7 | ny8 ny9 ny10 ny11 ny12 ny13 ny14 ny15
*/

/*
vaddl *2
cnv0 cnv1 cnv2 cnv3 cnv4 cnv5 cnv6 cnv7 | cnv8 cnv9 cnv10 cnv11 cnv12 cnv13 cnv14 cnv15
vuzp1
cnv0 cnv2 cnv4 cnv6 cnv8 cnv10 cnv12 cnv14
vuzp2
cnv1 cnv3 cnv5 cnv7 cnv9 cnv11 cnv13 cnv15
vadd
V0 V1 V2 V3 V4 V5 V6 V7
vadd with -512
-> use 2vuzp +2vaddl+2vadd for V
-> use 2vuzp +2vaddl+2vadd for U
-> use 2vuzp +2vaddl+1vadd for Y

V0 V1 V2 V3 V4 V5 V6 V7
U0 U1 U2 U3 U4 U5 U6 U7
Y0 Y1 Y2 Y3 Y4 Y5 Y6 Y7
*/

