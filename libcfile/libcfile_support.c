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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_ERRNO_H )
#include <errno.h>
#endif

#include "libcfile_definitions.h"
#include "libcfile_libcerror.h"
#include "libcfile_libclocale.h"
#include "libcfile_libuna.h"
#include "libcfile_support.h"
#include "libcfile_winapi.h"

file_exists_ptr custom_io_file_exists_ptr = NULL;
file_exists_wide_ptr custom_io_file_exists_wide_ptr = NULL;
file_create_handle_ptr custom_io_file_create_handle_ptr = NULL;
file_create_handle_wide_ptr custom_io_file_create_handle_wide_ptr = NULL;
file_close_handle_ptr custom_io_file_close_handle_ptr = NULL;
file_read_ptr custom_io_file_read_ptr = NULL;

#if !defined( HAVE_LOCAL_LIBCFILE )

/* Returns the library version as a string
 */
const char *libcfile_get_version(
             void )
{
	return( (const char *) LIBCFILE_VERSION_STRING );
}

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
int libcfile_get_codepage(
     int *codepage,
     libcerror_error_t **error )
{
	static char *function = "libcfile_get_codepage";

	if( libclocale_codepage_get(
	     codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve codepage.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
int libcfile_set_codepage(
     int codepage,
     libcerror_error_t **error )
{
	static char *function = "libcfile_set_codepage";

	if( libclocale_codepage_set(
	     codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set codepage.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#endif /* !defined( HAVE_LOCAL_LIBCFILE ) */

int libcfile_set_io_backend(
  file_exists_ptr file_exists,
  file_exists_wide_ptr file_exists_wide,
  file_create_handle_ptr file_create_handle,
  file_create_handle_wide_ptr file_create_handle_wide,
  file_close_handle_ptr file_close_handle,
  file_read_ptr file_read )
{
  custom_io_file_exists_ptr = file_exists;
  custom_io_file_exists_wide_ptr = file_exists_wide;
  custom_io_file_create_handle_ptr = file_create_handle;
  custom_io_file_create_handle_wide_ptr = file_create_handle_wide;
  custom_io_file_close_handle_ptr = file_close_handle;
  custom_io_file_read_ptr = file_read;
  return 1;
}

/* Determines if a file exists
 * This function uses the WINAPI function for Windows XP (0x0501) or later,
 * or tries to dynamically call the function for Windows 2000 (0x0500) or earlier
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libcfile_file_exists(
     const char *filename,
     libcerror_error_t **error )
{
	static char *function  = "libcfile_file_exists";

	if( custom_io_file_exists_ptr == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: file exists callback is not set.",
		 function );

		return( -1 );
	}

    return custom_io_file_exists_ptr(filename);
}

/* Determines if a file exists using get file attibutes
 * This function uses the WINAPI function for Windows XP (0x0501) or later,
 * or tries to dynamically call the function for Windows 2000 (0x0500) or earlier
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libcfile_file_exists_wide(
     const wchar_t *filename,
     libcerror_error_t **error )
{
	static char *function  = "libcfile_file_exists_wide";

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: file exists callback is not set.",
		 function );

		return( -1 );
	}

    return custom_io_file_exists_wide_ptr(filename);
}
