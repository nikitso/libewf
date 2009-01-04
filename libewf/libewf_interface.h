/*
 * libewf interface (API) functions
 *
 * Copyright (c) 2006-2008, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the creator, related organisations, nor the names of
 *   its contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER, COMPANY AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined( _LIBEWF_INTERFACE_H )
#define _LIBEWF_INTERFACE_H

#include <common.h>
#include <character_string.h>
#include <system_string.h>

/* If libtool DLL support is enabled set LIBEWF_DLL_EXPORT
 * before including libewf/extern.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBEWF_DLL_EXPORT
#endif

#include <libewf/extern.h>
#include <libewf/handle.h>
#include <libewf/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

LIBEWF_EXTERN uint8_t libewf_get_flags_read(
                       void );

LIBEWF_EXTERN uint8_t libewf_get_flags_read_write(
                       void );

LIBEWF_EXTERN uint8_t libewf_get_flags_write(
                       void );

LIBEWF_EXTERN int libewf_get_sectors_per_chunk(
                   libewf_handle_t *handle,
                   uint32_t *sectors_per_chunk );

LIBEWF_EXTERN int libewf_get_bytes_per_sector(
                   libewf_handle_t *handle,
                   uint32_t *bytes_per_sector );

LIBEWF_EXTERN int libewf_get_amount_of_sectors(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_sectors );

LIBEWF_EXTERN int libewf_get_chunk_size(
                   libewf_handle_t *handle,
                   size32_t *chunk_size );

LIBEWF_EXTERN int libewf_get_error_granularity(
                   libewf_handle_t *handle,
                   uint32_t *error_granularity );

LIBEWF_EXTERN int libewf_get_compression_values(
                   libewf_handle_t *handle,
                   int8_t *compression_level,
                   uint8_t *compress_empty_block );

LIBEWF_EXTERN int libewf_get_media_size(
                   libewf_handle_t *handle,
                   size64_t *media_size );

LIBEWF_EXTERN int libewf_get_media_type(
                   libewf_handle_t *handle,
                   uint8_t *media_type );

LIBEWF_EXTERN int libewf_get_media_flags(
                   libewf_handle_t *handle,
                   uint8_t *media_flags );

LIBEWF_EXTERN int libewf_get_volume_type(
                   libewf_handle_t *handle,
                   uint8_t *volume_type );

LIBEWF_EXTERN int libewf_get_format(
                   libewf_handle_t *handle,
                   uint8_t *format );

LIBEWF_EXTERN int libewf_get_guid(
                   libewf_handle_t *handle,
                   uint8_t *guid,
                   size_t size );

LIBEWF_EXTERN int libewf_get_md5_hash(
                   libewf_handle_t *handle,
                   uint8_t *md5_hash,
                   size_t size );

LIBEWF_EXTERN int libewf_get_segment_filename(
                   libewf_handle_t *handle,
                   system_character_t *filename,
                   size_t length );

LIBEWF_EXTERN int libewf_get_delta_segment_filename(
                   libewf_handle_t *handle,
                   system_character_t *filename,
                   size_t length );

LIBEWF_EXTERN int libewf_get_amount_of_acquiry_errors(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_errors );

LIBEWF_EXTERN int libewf_get_acquiry_error(
                   libewf_handle_t *handle,
                   uint32_t index,
                   off64_t *first_sector,
                   uint32_t *amount_of_sectors  );

LIBEWF_EXTERN int libewf_get_amount_of_crc_errors(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_errors );

LIBEWF_EXTERN int libewf_get_crc_error(
                   libewf_handle_t *handle,
                   uint32_t index,
                   off64_t *first_sector,
                   uint32_t *amount_of_sectors );

LIBEWF_EXTERN int libewf_get_amount_of_sessions(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_sessions );

LIBEWF_EXTERN int libewf_get_session(
                   libewf_handle_t *handle,
                   uint32_t index,
                   off64_t *first_sector,
                   uint32_t *amount_of_sectors );

LIBEWF_EXTERN int libewf_get_write_amount_of_chunks(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_chunks );

LIBEWF_EXTERN int libewf_get_amount_of_header_values(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_values );

LIBEWF_EXTERN int libewf_get_header_value_identifier(
                   libewf_handle_t *handle,
                   uint32_t index,
                   character_t *value,
                   size_t length );

LIBEWF_EXTERN int libewf_get_header_value(
                   libewf_handle_t *handle,
                   character_t *identifier,
                   character_t *value,
                   size_t length );

LIBEWF_EXTERN int libewf_get_amount_of_hash_values(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_values );

LIBEWF_EXTERN int libewf_get_hash_value_identifier(
                   libewf_handle_t *handle,
                   uint32_t index,
                   character_t *value,
                   size_t length );

LIBEWF_EXTERN int libewf_get_hash_value(
                   libewf_handle_t *handle,
                   character_t *identifier,
                   character_t *value,
                   size_t length );

LIBEWF_EXTERN int libewf_set_sectors_per_chunk(
                   libewf_handle_t *handle,
                   uint32_t sectors_per_chunk );

LIBEWF_EXTERN int libewf_set_bytes_per_sector(
                   libewf_handle_t *handle,
                   uint32_t bytes_per_sector );

LIBEWF_EXTERN int libewf_set_error_granularity(
                   libewf_handle_t *handle,
                   uint32_t error_granularity );

LIBEWF_EXTERN int libewf_set_compression_values(
                   libewf_handle_t *handle,
                   int8_t compression_level,
                   uint8_t compress_empty_block );

LIBEWF_EXTERN int libewf_set_media_size(
                   libewf_handle_t *handle,
                   size64_t media_size );

LIBEWF_EXTERN int libewf_set_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t segment_file_size );

LIBEWF_EXTERN int libewf_set_delta_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t delta_segment_file_size );

LIBEWF_EXTERN int libewf_set_media_type(
                   libewf_handle_t *handle,
                   uint8_t media_type );

LIBEWF_EXTERN int libewf_set_volume_type(
                   libewf_handle_t *handle,
                   uint8_t volume_type );

LIBEWF_EXTERN int libewf_set_format(
                   libewf_handle_t *handle,
                   uint8_t format );

LIBEWF_EXTERN int libewf_set_guid(
                   libewf_handle_t *handle,
                   uint8_t *guid,
                   size_t size );

LIBEWF_EXTERN int libewf_set_md5_hash(
                   libewf_handle_t *handle,
                   uint8_t *md5_hash,
                   size_t size );

LIBEWF_EXTERN int libewf_set_segment_filename(
                   libewf_handle_t *handle,
                   system_character_t *filename,
                   size_t length );

LIBEWF_EXTERN int libewf_set_delta_segment_filename(
                   libewf_handle_t *handle,
                   system_character_t *filename,
                   size_t length );

LIBEWF_EXTERN int libewf_set_read_wipe_chunk_on_error(
                   libewf_handle_t *handle,
                   uint8_t wipe_on_error );

LIBEWF_EXTERN int libewf_set_header_value(
                   libewf_handle_t *handle,
                   character_t *identifier,
                   character_t *value,
                   size_t length );

LIBEWF_EXTERN int libewf_set_hash_value(
                   libewf_handle_t *handle,
                   character_t *identifier,
                   character_t *value,
                   size_t length );

LIBEWF_EXTERN int libewf_parse_header_values(
                   libewf_handle_t *handle,
                   uint8_t date_format );

LIBEWF_EXTERN int libewf_parse_hash_values(
                   libewf_handle_t *handle );

LIBEWF_EXTERN int libewf_add_acquiry_error(
                   libewf_handle_t *handle,
                   off64_t first_sector,
                   uint32_t amount_of_sectors );

LIBEWF_EXTERN int libewf_add_crc_error(
                   libewf_handle_t *handle,
                   off64_t first_sector,
                   uint32_t amount_of_sectors );

LIBEWF_EXTERN int libewf_add_session(
                   libewf_handle_t *handle,
                   off64_t first_sector,
                   uint32_t amount_of_sectors );

LIBEWF_EXTERN int libewf_copy_header_values(
                   libewf_handle_t *destination_handle,
                   libewf_handle_t *source_handle );

LIBEWF_EXTERN int libewf_copy_media_values(
                   libewf_handle_t *destination_handle,
                   libewf_handle_t *source_handle );

#if defined( __cplusplus )
}
#endif

#endif
