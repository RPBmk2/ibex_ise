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
  int rs_immc = 25, immb = 47; // be used to calculate lw's address  
  int sw_data = 222; // 1) be used to calculate sw's address
  int mem_res;
  // 2) be used as sw's wdata

  __asm__ volatile("addi t3, %3, 3\n"
                    // t3 = immb*2^8 + rs_immc*2^3 + 3
                    "sw %1, %2(t3)\n"
                    // mem[t3 + immb] = sw_data
                    "lw_sw %0, %2(x%4)\n"
                    // rf[rd] = mem[immb + immb*2^8 + rs_immc*2^3 + 3];
                    :"=r"(mem_res)
                    :"r"(sw_data), "i"(immb), "r"(immb*256 + rs_immc*8), "i"(rs_immc));
  
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