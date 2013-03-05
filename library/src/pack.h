#ifndef __WSH_PACK_H
#define __WSH_PACK_H

#include <glib.h>

#include "cmd.h"

void wsh_pack_request(guint8** buf, gsize* buf_len, const wsh_cmd_req_t* req);
void wsh_unpack_request(wsh_cmd_req_t* req, const guint8* buf, gsize buf_len);
void wsh_free_unpacked_request(wsh_cmd_req_t* req);

#endif

