/*
 * Table section functions
 *
 * Copyright (C) 2006-2020, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBEWF_TABLE_SECTION_H )
#define _LIBEWF_TABLE_SECTION_H

#include <common.h>
#include <types.h>

#include "libewf_io_handle.h"
#include "libewf_libbfio.h"
#include "libewf_libcerror.h"
#include "libewf_section_descriptor.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libewf_table_section libewf_table_section_t;

struct libewf_table_section
{
	/* The section data
	 */
	uint8_t *section_data;

	/* The section data size
	 */
	size_t section_data_size;
};

int libewf_table_section_initialize(
     libewf_table_section_t **table_section,
     libcerror_error_t **error );

int libewf_table_section_free(
     libewf_table_section_t **table_section,
     libcerror_error_t **error );

ssize_t libewf_table_section_read_file_io_pool(
         libewf_table_section_t *table_section,
         libewf_section_descriptor_t *section_descriptor,
         libewf_io_handle_t *io_handle,
         libbfio_pool_t *file_io_pool,
         int file_io_pool_entry,
         uint8_t format_version,
         uint8_t segment_file_type,
         uint8_t **section_data,
         size_t *section_data_size,
         uint64_t *first_chunk_index,
         uint64_t *base_offset,
         uint8_t **table_entries_data,
         size_t *table_entries_data_size,
         uint32_t *number_of_entries,
         uint8_t *entries_corrupted,
         libcerror_error_t **error );

ssize_t libewf_table_section_write_file_io_pool(
         libewf_section_descriptor_t *section_descriptor,
         libewf_io_handle_t *io_handle,
         libbfio_pool_t *file_io_pool,
         int file_io_pool_entry,
         uint8_t format_version,
         uint8_t segment_file_type,
         uint8_t *type_string,
         size_t type_string_length,
         off64_t section_offset,
         uint8_t *section_data,
         size_t section_data_size,
         uint64_t first_chunk_index,
         uint64_t base_offset,
         uint8_t *table_entries_data,
         size_t table_entries_data_size,
         uint32_t number_of_entries,
         size64_t chunks_data_size,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBEWF_TABLE_SECTION_H ) */

