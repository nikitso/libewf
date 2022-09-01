/*
 * Support functions
 *
 * Copyright (C) 2008-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBCFILE_SUPPORT_H )
#define _LIBCFILE_SUPPORT_H

#include <common.h>
#include <types.h>

#include "libcfile_extern.h"
#include "libcfile_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBCFILE )

LIBCFILE_EXTERN \
const char *libcfile_get_version(
             void );

LIBCFILE_EXTERN \
int libcfile_get_codepage(
     int *codepage,
     libcerror_error_t **error );

LIBCFILE_EXTERN \
int libcfile_set_codepage(
     int codepage,
     libcerror_error_t **error );

#endif /* !defined( HAVE_LOCAL_LIBCFILE ) */

typedef int (*file_exists_ptr)( const char *);
typedef int (*file_exists_wide_ptr)( const wchar_t *);
typedef int (*file_create_handle_ptr)(const char*, uint32_t, uint32_t, uint32_t, void**);
typedef int (*file_create_handle_wide_ptr)(const wchar_t*, uint32_t, uint32_t, uint32_t, void**);
typedef int (*file_close_handle_ptr)(void*);
typedef int (*file_read_ptr)(void*, int64_t, uint8_t*, int32_t, int32_t*);
typedef int (*file_seek_ptr)(void*, int64_t, uint32_t);
typedef int (*file_write_ptr)(void*, const uint8_t*, int32_t, int32_t*);
typedef int (*file_get_size_ptr)(void*, int64_t*);

LIBCFILE_EXTERN_VARIABLE file_exists_ptr custom_io_file_exists_ptr;
LIBCFILE_EXTERN_VARIABLE file_exists_wide_ptr custom_io_file_exists_wide_ptr;
LIBCFILE_EXTERN_VARIABLE file_create_handle_ptr custom_io_file_create_handle_ptr;
LIBCFILE_EXTERN_VARIABLE file_create_handle_wide_ptr custom_io_file_create_handle_wide_ptr;
LIBCFILE_EXTERN_VARIABLE file_close_handle_ptr custom_io_file_close_handle_ptr;
LIBCFILE_EXTERN_VARIABLE file_read_ptr custom_io_file_read_ptr;
LIBCFILE_EXTERN_VARIABLE file_seek_ptr custom_io_file_seek_ptr;
LIBCFILE_EXTERN_VARIABLE file_write_ptr custom_io_file_write_ptr;
LIBCFILE_EXTERN_VARIABLE file_get_size_ptr custom_io_file_get_size_ptr;

LIBCFILE_EXTERN \
int libcfile_set_io_backend(
  file_exists_ptr file_exists,
  file_exists_wide_ptr file_exists_wide,
  file_create_handle_ptr file_create_handle,
  file_create_handle_wide_ptr file_create_handle_wide,
  file_close_handle_ptr file_close_handle,
  file_read_ptr file_read,
  file_seek_ptr file_seek,
  file_write_ptr file_write,
  file_get_size_ptr file_get_size );

LIBCFILE_EXTERN \
int libcfile_file_exists(
     const char *filename,
     libcerror_error_t **error );

LIBCFILE_EXTERN \
int libcfile_file_exists_wide(
     const wchar_t *filename,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBCFILE_SUPPORT_H ) */

