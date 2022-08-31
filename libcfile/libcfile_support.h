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

typedef int (*file_exists_ptr)( const char *, libcerror_error_t **);
typedef int (*file_exists_wide_ptr)( const wchar_t *, libcerror_error_t **);

LIBCFILE_EXTERN_VARIABLE file_exists_ptr custom_io_file_exists_ptr;
LIBCFILE_EXTERN_VARIABLE file_exists_wide_ptr custom_io_file_exists_wide_ptr;

LIBCFILE_EXTERN \
int libcfile_set_io_backend(
  file_exists_ptr file_exists,
  file_exists_wide_ptr file_exists_wide
  );

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

