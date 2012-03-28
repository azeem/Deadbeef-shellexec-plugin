#ifndef __SHELLEXEC_H
#define __SHELLEXEC_H

#include <deadbeef/deadbeef.h>

//Probably it's reasonable to move these flags to parent struct
enum {
    SHX_ACTION_LOCAL_ONLY       = 1 << 0,
    SHX_ACTION_REMOTE_ONLY      = 1 << 1
};

typedef struct Shx_action_s
{
    DB_plugin_action_t parent;

    const char *shcommand;
    uint32_t shx_flags;
} Shx_action_t;

typedef struct Shx_plugin_s
{
	DB_misc_t misc;
	Shx_action_t *
	(*shx_get_actions)(DB_plugin_action_callback_t callback, int omit_disabled);
	void
	(*shx_save_actions)(Shx_action_t *action_list);
} Shx_plugin_t;

#endif