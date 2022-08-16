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
#include <FileStreamInterface.h>

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#if defined( HAVE_ERRNO_H )
#include <errno.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "libcfile_definitions.h"
#include "libcfile_libcerror.h"
#include "libcfile_libclocale.h"
#include "libcfile_libuna.h"
#include "libcfile_support.h"

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

#if defined( WINAPI )

/* Determines if a file exists
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libcfile_file_exists(
     const char *filename,
     libcerror_error_t **error )
{
	static char *function  = "libcfile_file_exists";
	DWORD error_code       = 0;
	FileStreamHandle handle = NULL;
	int result             = 1;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
  
  handle = OpenFileHandle(filename);
	if( handle == NULL )
	{
		error_code = (uint32_t) GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				result = 1;

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				result = 0;

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 error_code,
				 "%s: unable to open file: %s.",
				 function,
				 filename );

				return( -1 );
		}
	}
	else
	{
    result = CloseFileHandle(handle);
		if( result == 0 )
		{
			error_code = GetLastError();

			libcerror_system_set_error(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 error_code,
			 "%s: unable to close file.",
			 function );

			return( -1 );
		}
		result = 1;
	}

	return( result );
}

#elif defined( HAVE_STAT )

/* Determines if a file exists
 * This function uses the POSIX stat function or equivalent
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libcfile_file_exists(
     const char *filename,
     libcerror_error_t **error )
{
	struct stat file_statistics;

	static char *function = "libcfile_file_exists";
	int result            = 0;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     &file_statistics,
	     0,
	     sizeof( struct stat ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file statistics.",
		 function );

		return( -1 );
	}
	result = stat(
	          filename,
	          &file_statistics );

	if( result != 0 )
	{
		switch( errno )
		{
			case EACCES:
				result = 1;

				break;

			case ENOENT:
				result = 0;

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_GENERIC,
				 errno,
				 "%s: unable to stat file: %" PRIs_SYSTEM ".",
				 function,
				 filename );

				return( -1 );
		}
	}
	else
	{
		result = 1;
	}
	return( result );
}

#else
#error Missing file exists function
#endif

#if defined( HAVE_WIDE_CHARACTER_TYPE )

#if defined( HAVE_STAT )

/* Determines if a file exists
 * This function uses the POSIX stat function or equivalent
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libcfile_file_exists_wide(
     const wchar_t *filename,
     libcerror_error_t **error )
{
	struct stat file_statistics;

	char *narrow_filename       = NULL;
	static char *function       = "libcfile_file_exists_wide";
	size_t narrow_filename_size = 0;
	size_t filename_size        = 0;
	int result                  = 0;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	filename_size = 1 + wide_string_length(
	                     filename );

	/* Convert the filename to a narrow string
	 * if the platform has no wide character open function
	 */
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) filename,
		          filename_size,
		          &narrow_filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) filename,
		          filename_size,
		          &narrow_filename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) filename,
		          filename_size,
		          libclocale_codepage,
		          &narrow_filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) filename,
		          filename_size,
		          libclocale_codepage,
		          &narrow_filename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow character filename size.",
		 function );

		return( -1 );
	}
	narrow_filename = narrow_string_allocate(
	                   narrow_filename_size );

	if( narrow_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow character filename.",
		 function );

		return( -1 );
	}
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_filename,
		          narrow_filename_size,
		          (libuna_utf32_character_t *) filename,
		          filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_filename,
		          narrow_filename_size,
		          (libuna_utf16_character_t *) filename,
		          filename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_filename,
		          narrow_filename_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) filename,
		          filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_filename,
		          narrow_filename_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) filename,
		          filename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow character filename.",
		 function );

		memory_free(
		 narrow_filename );

		return( -1 );
	}
	result = stat(
	          narrow_filename,
	          &file_statistics );

	memory_free(
	 narrow_filename );

	if( result != 0 )
	{
		switch( errno )
		{
			case EACCES:
				result = 1;

				break;

			case ENOENT:
				result = 0;

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_GENERIC,
				 errno,
				 "%s: unable to stat file: %" PRIs_SYSTEM ".",
				 function,
				 filename );

				return( -1 );
		}
	}
	else
	{
		result = 1;
	}
	return( result );
}

#endif

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */