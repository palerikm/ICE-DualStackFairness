#include <stdlib.h>
#include <stdio.h>



#include "priority.h"
#include <check.h>


#define PRIORITY_HOST_1     ( ( 126 << 24) | (65535 << 8) | ( 256 - 1))
#define PRIORITY_HOST_2     ( ( 126 << 24) | (65535 << 8) | ( 256 - 2))
#define PRIORITY_SRFLX_1    ( ( 100 << 24) | (65535 << 8) | ( 256 - 1))
#define PRIORITY_SRFLX_2    ( ( 100 << 24) | (65535 << 8) | ( 256 - 2))
#define PRIORITY_RELAY_1    ( (   0 << 24) | (65535 << 8) | ( 256 - 1))
#define PRIORITY_RELAY_2    ( (   0 << 24) | (65535 << 8) | ( 256 - 2))
#define PRIORITY_PRFLX_1    ( ( 110 << 24) | (65535 << 8) | ( 256 - 1))
#define PRIORITY_PRFLX_2    ( ( 110 << 24) | (65535 << 8) | ( 256 - 2))

START_TEST (calculate_priority)
{
    uint32_t priority1;
    uint32_t priority2;
    uint32_t priority3;
    uint32_t priority4;
    uint32_t priority5;
    uint32_t priority6;
    uint32_t priority7;
    uint32_t priority8;

    priority1 = ICELIB_calculatePriority( ICE_CAND_TYPE_HOST,  1, 0xffff);
    priority2 = ICELIB_calculatePriority( ICE_CAND_TYPE_HOST,  2, 0xffff);
    priority3 = ICELIB_calculatePriority( ICE_CAND_TYPE_SRFLX, 1, 0xffff);
    priority4 = ICELIB_calculatePriority( ICE_CAND_TYPE_SRFLX, 2, 0xffff);
    priority5 = ICELIB_calculatePriority( ICE_CAND_TYPE_RELAY, 1, 0xffff);
    priority6 = ICELIB_calculatePriority( ICE_CAND_TYPE_RELAY, 2, 0xffff);
    priority7 = ICELIB_calculatePriority( ICE_CAND_TYPE_PRFLX, 1, 0xffff);
    priority8 = ICELIB_calculatePriority( ICE_CAND_TYPE_PRFLX, 2, 0xffff);

    fail_unless( priority1 == PRIORITY_HOST_1);
    fail_unless( priority2 == PRIORITY_HOST_2);
    fail_unless( priority3 == PRIORITY_SRFLX_1);
    fail_unless( priority4 == PRIORITY_SRFLX_2);
    fail_unless( priority5 == PRIORITY_RELAY_1);
    fail_unless( priority6 == PRIORITY_RELAY_2);
    fail_unless( priority7 == PRIORITY_PRFLX_1);
    fail_unless( priority8 == PRIORITY_PRFLX_2);


}
END_TEST




Suite * priority_suite (void)
{
  Suite *s = suite_create ("Priority");

  {/* Core test case */
      TCase *tc_core = tcase_create ("Core");
        tcase_add_test (tc_core, calculate_priority);
        suite_add_tcase (s, tc_core);
  }
  
  return s;
}
