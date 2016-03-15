#pragma once

/**
 * The background module is for managing the background and control plane thread.
 * This includes tasks such as logging, as well as admin port operations.
 */

#include <cc_define.h>
#include <cc_metric.h>
#include <cc_option.h>

#include <stdbool.h>

#define ADMIN_HOST      NULL
#define ADMIN_PORT      "9999"
#define ADMIN_TIMEOUT   100     /* in ms */
#define ADMIN_NEVENT    1024
#define ADMIN_TW_TICK   10      /* in ms */
#define ADMIN_TW_CAP    1000    /* 1000 ticks in timing wheel */
#define ADMIN_TW_NTICK  100     /* 1 second's worth of timeout events */

/*          name            type                default         description */
#define ADMIN_OPTION(ACTION)                                                                    \
    ACTION( admin_host,     OPTION_TYPE_STR,    ADMIN_HOST,     "admin interfaces listening on")\
    ACTION( admin_port,     OPTION_TYPE_STR,    ADMIN_PORT,     "admin port"                   )\
    ACTION( admin_timeout,  OPTION_TYPE_UINT,   ADMIN_TIMEOUT,  "evwait timeout"               )\
    ACTION( admin_nevent,   OPTION_TYPE_UINT,   ADMIN_NEVENT,   "evwait max nevent returned"   )\
    ACTION( admin_tw_tick,  OPTION_TYPE_UINT,   ADMIN_TW_TICK,  "timing wheel tick size (ms)"  )\
    ACTION( admin_tw_cap,   OPTION_TYPE_UINT,   ADMIN_TW_CAP,   "# ticks in timing wheel"      )\
    ACTION( admin_tw_ntick, OPTION_TYPE_UINT,   ADMIN_TW_NTICK, "max # ticks processed at once")

typedef struct {
    ADMIN_OPTION(OPTION_DECLARE)
} admin_options_st;

struct timing_wheel;
struct timeout_event;

extern bool admin_running;

void core_admin_setup(admin_options_st *options);
void core_admin_teardown(void);

/* timeout events must be added while admin evloop is not running */
rstatus_i core_admin_add_tev(struct timeout_event *tev);

void *core_admin_evloop(void *arg);
