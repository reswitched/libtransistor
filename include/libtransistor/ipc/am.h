#pragma once

#include<libtransistor/types.h>

// applet resource user id
typedef uint64_t aruid_t;

result_t am_init();
result_t am_isc_create_managed_display_layer(uint64_t *layer_id);
result_t am_isc_approve_to_display();
result_t am_iwc_get_applet_resource_user_id(aruid_t *aruid);
result_t am_iwc_acquire_foreground_rights();
void am_finalize();
