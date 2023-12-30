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
  int immc = 25, immb = 47; // be used to calculate lw's address  
  int sw_data = 222; // 1) be used to calculate sw's address
  int mem_res;
  // 2) be used as sw's wdata

  __asm__ volatile("addi t2, x0, %1\n"
                    // t2 = sw_data
                    "addi t3, x0, %2\n"
                    // t3 = immb
                    "sw t2, %3(t3)\n"
                    // mem[immb + immc] = sw_data
                    "addi %0, x0, 0\n"
                    // rd2 is mem_res
                    "lw_sw x%3, %2(t1)\n"
                    // rf[prev_rd_num] = mem[immb + immc];
                    :"=r"(mem_res)
                    :"i"(sw_data), "i"(immb), "i"(immc));
  
  if(mem_res == sw_data){
    puts("Test Pass!\n Stored Value is : ");
    puthex(mem_res);
  }
  else{
    puts("Test Failed!\n Stored Value is : ");
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