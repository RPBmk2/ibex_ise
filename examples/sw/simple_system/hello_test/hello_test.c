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
  int lw_data = 50; //be used to calculate sw's address
  int rs_data = 870, immb = 6; // be used to calculate lw's address  
  int immc =5, sw_data = 222; // 1) be used to calculate sw's address
  int mem_res;
  // 2) be used as sw's wdata

  __asm__ volatile("addi t2, x0, %1\n"
                    // t2 = rs_data
                    "addi t5, x0, %2\n"
                    // t5 = lw_data
                    "sw t5, %4(t2)\n"
                    // mem[t2 + immb] = lw_data
                    "addi t4, x0, %3\n"
                    // t4 = sw_data
                    "sw t4, %5(t5)\n"
                    // mem[lw_data + immc] = sw_data
                    "lw_sw x%5, %4(t2)\n"
                    // temp = mem[t2 + immb];
                    // rf[prev_rd_num] = mem[temp + immc];
                    "addi %0, t4, 0\n"
                    // mem_res = t4
                    :"=r"(mem_res)
                    : "i"(rs_data), "i"(lw_data),"i"(sw_data),
                    "i"(immb), "i"(immc));
  
  if(mem_res == sw_data){
    puts("Test Pass!\n Stored Value is : ");
    puthex(mem_res);
  }
  // else{
  //   puts("Test Failed!\n Stored Value is : ");
  //   puthex(mem_res);
  // }
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
