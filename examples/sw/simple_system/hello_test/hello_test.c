// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "simple_system_common.h"

int main(int argc, char **argv) {
  // pcount_enable(0);
  // pcount_reset();
  // pcount_enable(1);

  // puts("Hello simple system\n");
  // puthex(0xDEADBEEF);
  // putchar('\n');
  // puthex(0xBAADF00D);
  // putchar('\n');

  // pcount_enable(0);

  // // Enable periodic timer interrupt
  // // (the actual timebase is a bit meaningless in simulation)
  // timer_enable(2000);

  // uint64_t last_elapsed_time = get_elapsed_time();
  int rs1_num = 25; // sw's address and lui imm
  int rs2_num = 18; // sw's data reg num and lui imm
  int immb = 0b010101010110; // low 5bit is just used as immb, high 7bit is also used as immc's high bit 
  int sw_data = 222; 
  int imm_I =(immb>>5) * 8192 + rs2_num*256 + rs1_num * 8;
  int mem_res;

  __asm__ volatile("addi t3, %3, 3\n"
                    // t3 = immb>>5 * 8192 + rs2_num*256 + rs1_num * 8 + immb + 3
                    // t3'data is the sw address
                    "addi x%4, %1, 0\n"
                    // rf[rs2] = sw_data
                    "lui_sw x%4, %2(x%5)\n"
                    // mem[immb>>5 * 8192 + rs2_num*256 + rs1_num * 8 + 3] = sw_data;
                    "lw %0, %2(t3)"
                    :"=r"(mem_res)
                    :"r"(sw_data), "i"(immb), "r"(imm_I), "i"(rs2_num), "i"(rs1_num));
  
  if(mem_res == sw_data){
    puts("Test Pass!\n Load Value is : ");
    puthex(mem_res);
  }
  else{
    puts("Test Failed!\n Load Value is : ");
    puthex(mem_res);
  }
  // while (last_elapsed_time <= 4) {
  //   uint64_t cur_time = get_elapsed_time();
  //   if (cur_time != last_elapsed_time) {
  //     last_elapsed_time = cur_time;

  //     if (last_elapsed_time & 1) {
  //       puts("Tick!\n");
  //     } else {
  //       puts("Tock!\n");
  //     }
  //   }
  //   asm volatile("wfi");
  // }

  return 0;
}