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
  int rs1_value = 25; // sw's address and lui imm
  int immb = 213; // low 5bit is just used as immb, high 7bit is also used as immc's high bit 
  int sw_data = 222; 
  int mem_res;

  __asm__ volatile("sw %1, %2(%3)\n"
                    // mem[rs1_value + immb] = sw_data
                    "lw_addi %0, %3, %2\n"
                    // rf[rs1] = mem[rs1_value + immb] + immb;
                    :"=r"(mem_res)
                    :"r"(sw_data), "i"(immb), "r"(rs1_value));
  
  if(mem_res == sw_data + immb){
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