#include "parse.h"

#include <arpa/inet.h>
#include <glib.h>

#include "cmd.h"
#include "log.h"

gint wshd_get_message_size(GIOChannel* std_output, GError* err) {
	wshd_message_size_t out;
	gsize read;

	g_io_channel_read_chars(std_output, out.buf, 4, &read, &err);
	out.size = ntohl(out.size);

	return out.size;
}

