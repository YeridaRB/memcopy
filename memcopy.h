//===================== Copyright © 2017-2021, Jared Ryan Bills =====================//
//    This program is free software: you can redistribute it and/or modify	//
//    it under the terms of the GNU Lesser General Public License as published	//
//    by the Free Software Foundation, either version 3 of the License, or	//
//    (at your option) any later version.					//
//										//
//    This program is distributed in the hope that it will be useful,		//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of		//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the		//
//    GNU Lesser General Public License for more details.			//
//										//
//    You should have received a copy of the GNU Lesser General Public License	//
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.	//
//==============================================================================//
//										//
// Purpose: Contains a reimplementation of the ever-used memcpy (renamed	//
//	memcopy here). Includes memcopy derivatives for various bus sizes.	//
//										//
//==============================================================================//

#ifndef MEMCOPY_H
#define MEMCOPY_H

#include "datatypes.h"
#include <stddef.h>
#include <assert.h>

inline void * memcopy8(void *, void *, const size_t);
inline void * memcopy16(void *, void *, const size_t);
inline void * memcopy32(void *, void *, const size_t);
inline void * memcopy64(void *, void *, const size_t);

//Title:		memcopy
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			keeping bus size in mind.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Utilize in-built CPU features for faster memory vector and page operations.
//			Utilize memory alignment
inline void * memcopy(void * a_dest, void * a_src, const size_t a_byteLen) {
	if (!a_byteLen)
		return a_dest = NULL;
	size_t len = a_byteLen;
	size_t offset, totalOffset = 0;
	if (len > 111b && _BUS_SIZE >= sizeof(uint64)) {
		offset = len & ~(size_t)(111b);
		//Uncomment if you're reworking for higher bus sizes or vectors
		memcopy64( /* (void *)((size_t)( */ a_dest /* ) + totalOffset) */ , /* (void *)((size_t)( */a_src /* ) + totalOffset) */ , offset);
		totalOffset+=offset;
		len-=totalOffset;
	}
	if (len > 11b && _BUS_SIZE >= sizeof(uint32)) {
		offset = len & ~(size_t)(11b);
		memcopy32((void *)((size_t)(a_dest) + totalOffset), (void *)((size_t)(a_src) + totalOffset), offset);
		totalOffset += offset;
		len = a_byteLen - totalOffset;
	}
	if (len > 1b && _BUS_SIZE >= sizeof(uint16)) {
		offset = len & ~(size_t)(1b);
		memcopy16((void *)((size_t)(a_dest) + totalOffset), (void *)((size_t)(a_src) + totalOffset), offset);
		totalOffset += offset;
		len = a_byteLen - totalOffset;
	}
	//Doing a sanity check in case we're insane enough to run this on a 7-bit-based-byte architecture or something similar
	if (len && _BUS_SIZE >= sizeof(uint8)) {
		offset = len;
		memcopy8((void *)((size_t)(a_dest) + totalOffset), (void *)((size_t)(a_src) + totalOffset), offset);
		//Don't need these if unused.
		//totalOffset += offset;
		//len = a_byteLen - totalOffset;
	}
	return a_dest;
}
//Title:		memcopy8
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			one bytes at a time, but does not transfer tailing memory if less
//			than 8 bits wide.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Utilize in-built CPU features for faster memory vector and page operations.
//			Utilize memory alignment
inline void * memcopy8(void * a_dest, void * a_src, const size_t a_byteLen) {
	for (uintptr c = 0; c < a_byteLen; c += sizeof(uint8))
		*((uint8 *)(a_dest)+c) = *((uint8 *)(a_src)+c);
	return a_dest;
}
//Title:		memcopy16
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			two bytes at a time, but does not transfer tailing memory if less
//			than 16 bits wide.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Utilize in-built CPU features for faster memory vector and page operations.
//			Utilize memory alignment
inline void * memcopy16(void * a_dest, void * a_src, const size_t a_byteLen) {
	assert(!(a_byteLen & 0x1));
	for (uintptr c = 0; c < a_byteLen; c += sizeof(uint16))
		*((uint16 *)(a_dest)+c) = *((uint16 *)(a_src)+c);
	return a_dest;
}
//Title:		memcopy32
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			four bytes at a time, but does not transfer tailing memory if less
//			than 32 bits wide.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Utilize in-built CPU features for faster memory vector and page operations.
//			Utilize memory alignment
inline void * memcopy32(void * a_dest, void * a_src, const size_t a_byteLen) {
	assert(!(a_byteLen & 0x3));
	for (uintptr c = 0; c < a_byteLen; c += sizeof(uint32))
		*((uint32 *)(a_dest)+c) = *((uint32 *)(a_src)+c);
	return a_dest;
}
//Title:		memcopy64
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			eight bytes at a time, but does not transfer tailing memory if less
//			than 64 bits wide.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Utilize in-built CPU features for faster memory vector and page operations.
//			Utilize memory alignment
inline void * memcopy64(void * a_dest, void * a_src, const size_t a_byteLen) {
	assert(!(a_byteLen & 0x7));
	for (uintptr c = 0; c < a_byteLen; c += sizeof(uint64))
		*((uint64 *)(a_dest)+c) = *((uint64 *)(a_src)+c);
	return a_dest;
}

#endif
