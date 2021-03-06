/* vi: set sw=4 ts=4: */
/*
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

#include "libbb.h"
#include "bb_archive.h"

archive_handle_t* FAST_FUNC init_handle(void)
{
	archive_handle_t *archive_handle;

	/* Initialize default values */
	archive_handle = xzalloc(sizeof(archive_handle_t));
	archive_handle->file_header = xzalloc(sizeof(file_header_t));
	archive_handle->action_header = header_skip;
	archive_handle->action_data = data_skip;
	archive_handle->filter = filter_accept_all;
#if !ENABLE_PLATFORM_MINGW32
	archive_handle->seek = seek_by_jump;
#else
	/* can't reliably detect pipes on WIN32: default to seek_by_read */
	archive_handle->seek = seek_by_read;
#endif

	return archive_handle;
}
