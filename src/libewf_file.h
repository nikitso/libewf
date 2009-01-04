/*
 * libewf file handling
 *
 * Copyright (c) 2006, Joachim Metz <forensics@hoffmannbv.nl>,
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
 * - All advertising materials mentioning features or use of this software
 *   must acknowledge the contribution by people stated in the acknowledgements.
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

#ifndef _LIBEWF_FILE_H
#define _LIBEWF_FILE_H

#include "ewf_section.h"
#include "handle.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LIBEWF_OPEN_READ	1
#define LIBEWF_OPEN_WRITE	2

uint8_t libewf_check_file_signature( const char *filename );
LIBEWF_HANDLE *libewf_open( const char **filenames, uint32_t file_amount, uint8_t flags );
LIBEWF_HANDLE *libewf_open_read( LIBEWF_HANDLE *handle, const char *filename );
LIBEWF_HANDLE *libewf_open_write( LIBEWF_HANDLE *handle, const char *filename );
LIBEWF_HANDLE *libewf_build_index( LIBEWF_HANDLE *handle );
void libewf_close( LIBEWF_HANDLE *handle );
uint64_t libewf_data_size( LIBEWF_HANDLE *handle );
char *libewf_data_md5hash( LIBEWF_HANDLE *handle );
char *libewf_calculate_md5hash( LIBEWF_HANDLE *handle );

#ifdef __cplusplus
}
#endif

#endif

