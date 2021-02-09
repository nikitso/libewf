/*
 * Handle class of libewf .net managed wrapper
 *
 * Copyright (C) 2006-2021, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _EWF_NET_HANDLE_H )
#define _EWF_NET_HANDLE_H

#include "ewf.net_file_entry.h"
#include "ewf.net_sector_range.h"

#using <mscorlib.dll>

using namespace System;
using namespace System::IO;

namespace EWF {

/* The access flags definitions
 * bit 1							set to 1 for read access
 * bit 2							set to 1 for write access
 * bit 3-4							not used
 * bit 5        set to 1 to resume write
 * bit 6-8							not used
 */
[System::Flags]
public enum class LIBEWF_ACCESS_FLAGS
{
	LIBEWF_ACCESS_FLAG_READ					= 0x01,
	LIBEWF_ACCESS_FLAG_WRITE				= 0x02,

	LIBEWF_ACCESS_FLAG_RESUME				= 0x10
};

/* The compression level definitions
 */
public enum class LIBEWF_COMPRESSION_LEVELS : int
{
	LIBEWF_COMPRESSION_LEVEL_DEFAULT			= -1,
	LIBEWF_COMPRESSION_LEVEL_NONE				= 0,
	LIBEWF_COMPRESSION_LEVEL_FAST				= 1,
	LIBEWF_COMPRESSION_LEVEL_BEST				= 2,
};

/* The compression flags
 * bit 1							set to 1 for empty block compression
 *              detects empty blocks and stored them compressed, the compression
 *              is only done once
 * bit 2							set to 1 for pattern fill compression
 *              this implies empty block compression using the pattern fill method
 *              used internally only
 * bit 3-8							not used
 */
[System::Flags]
public enum class LIBEWF_COMPRESSION_FLAGS
{
  LIBEWF_COMPRESS_FLAG_NONE                         = (uint8_t) 0x00,
	LIBEWF_COMPRESS_FLAG_USE_EMPTY_BLOCK_COMPRESSION	= (uint8_t) 0x01,
	LIBEWF_COMPRESS_FLAG_USE_PATTERN_FILL_COMPRESSION	= (uint8_t) 0x10,
};

/* The media type definitions
 */
public enum class LIBEWF_MEDIA_TYPES
{
	LIBEWF_MEDIA_TYPE_REMOVABLE			= 0x00,
	LIBEWF_MEDIA_TYPE_FIXED					= 0x01,
	LIBEWF_MEDIA_TYPE_OPTICAL				= 0x03,
	LIBEWF_MEDIA_TYPE_SINGLE_FILES	= 0x0e,
	LIBEWF_MEDIA_TYPE_MEMORY				= 0x10
};

/* The media flags definitions
 */
[System::Flags]
public enum class LIBEWF_MEDIA_FLAGS
{
	LIBEWF_MEDIA_FLAG_PHYSICAL			= 0x02,
	LIBEWF_MEDIA_FLAG_FASTBLOC			= 0x04,
	LIBEWF_MEDIA_FLAG_TABLEAU				= 0x08
};

public ref class Handle sealed
{
	private:
		System::IntPtr ewf_handle;

	private:
		Handle( System::IntPtr ewf_handle );

	public:
		Handle( void );
		~Handle( void );

		static int GetAccessFlagsRead( void );
		static int GetAccessFlagsReadWrite( void );
		static int GetAccessFlagsWrite( void );
		static int GetAccessFlagsWriteResume( void );

		static bool CheckFileSignature( System::String^ filename );

		static array<System::String^>^ Glob( System::String^ filename );

		Handle^ Clone( void );

		void Open( array<System::String^>^ filenames,
		           int access_flags );

		void Close( void );

		/* TODO add read write chunk functions ? */

		int ReadBuffer( array<System::Byte>^ buffer,
		                int size );

		int ReadBufferAtOffset( array<System::Byte>^ buffer,
		                        int size,
		                        System::Int64 offset );

		int WriteBuffer( array<System::Byte>^ buffer,
		                 int size );

		int WriteBufferAtOffset( array<System::Byte>^ buffer,
		                         int size,
		                         System::Int64 offset );

		System::Int64 SeekOffset( System::Int64 offset,
		                          System::IO::SeekOrigin origin );

		System::Int64 GetOffset( void );

		/* TODO add segment file functions ? */

		System::UInt32 GetSectorsPerChunk( void );

		void SetSectorsPerChunk( System::UInt32 sectors_per_chunk );

		System::UInt32 GetBytesPerSector( void );

		void SetBytesPerSector( System::UInt32 bytes_per_sector );

		System::UInt64 GetNumberOfSectors( void );

		System::UInt32 GetChunkSize( void );

		System::UInt32 GetErrorGranularity( void );

		void SetErrorGranularity( System::UInt32 error_granularity );

		/* TODO add compression values functions ? */

		System::UInt64 GetMediaSize( void );

		void SetMediaSize( System::UInt64 media_size );

		System::Byte GetMediaType( void );

		void SetMediaType( System::Byte media_type );

		System::Byte GetMediaFlags( void );

		void SetMediaFlags( System::Byte media_flags );

		System::Byte GetFormat( void );

		void SetFormat( System::Byte format );

  	void SetMaximumSegmentSize(System::UInt64 maximum_segment_size);

    void SetCompression(LIBEWF_COMPRESSION_LEVELS compression_level, LIBEWF_COMPRESSION_FLAGS compression_flags);

		/* TODO add GUID functions ? */

		/* TODO add MD5 hash functions ? why bother when Get/SetHashValue are available ? */

		/* TODO add SHA1 hash functions ? why bother when Get/SetHashValue are available ? */

		/* TODO add other functions ? */

		int GetNumberOfAcquiryErrors( void );

		SectorRange^ GetAcquiryError( int index );

		void AppendAcquiryError( SectorRange^ sector_range );

		int GetNumberOfChecksumErrors( void );

		SectorRange^ GetChecksumError( int index );

		void AppendChecksumError( SectorRange^ sector_range );

		int GetNumberOfSessions( void );

		SectorRange^ GetSession( int index );

		void AppendSession( SectorRange^ sector_range );

		int GetNumberOfTracks( void );

		SectorRange^ GetTrack( int index );

		void AppendTrack( SectorRange^ sector_range );

		/* TODO add header codepage functions ?

		int GetHeaderCodepage( void );

		void SetHeaderCodepage( int codepage );

		*/

		/* TODO add header date format functions ?

		int GetHeaderValuesDateFormat( void );

		void SetHeaderValuesDateFormat( int date_format );

		*/

#if _MSC_VER >= 1600

		int GetNumberOfHeaderValues( void );

		System::String^ GetHeaderValueIdentifier( int index );

		System::String^ GetHeaderValue( System::String^ identifier );

		void SetHeaderValue( System::String^ identifier,
		                     System::String^ header_value );

		int GetNumberOfHashValues( void );

		System::String^ GetHashValueIdentifier( int index );

		System::String^ GetHashValue( System::String^ identifier );

		void SetHashValue( System::String^ identifier,
		                   System::String^ hash_value );

#endif /* _MSC_VER >= 1600 */

		FileEntry^ GetRootFileEntry( void );
};

} // namespace EWF

#endif

