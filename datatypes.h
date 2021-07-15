//===================== Copyright © 2017, Jared Ryan Bills =====================//
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
// Purpose: Contains various useful data type definitions to simplify working	//
//	with memory.								//
//										//
//==============================================================================//

#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdint.h>
#ifdef __cplusplus
#include <vector.h>
#endif

#define _BUS_SIZE					(sizeof(size_t))

typedef uintptr_t					uintptr;
typedef intptr_t					intptr;
typedef uint8_t						uint8;
typedef uint16_t					uint16;
typedef uint32_t					uint32;
typedef uint64_t					uint64;
typedef int8_t						int8;
typedef int16_t						int16;
typedef int32_t						int32;
typedef int64_t						int64;
typedef float						float32;
typedef double						float32_64;
typedef long double					float64;
#ifdef __cplusplus
typedef Vector<int64, 2>				Vector2D;
typedef Vector<int64, 3>				Vector3D;
typedef Vector<int64, 4>				Vector4D;
typedef Vector<float32, 2>				Vector2D_fl32;
typedef Vector<float32, 3>				Vector3D_fl32;
typedef Vector<float32, 4>				Vector4D_fl32;
typedef Vector<float64, 2>				Vector2D_fl64;
typedef Vector<float64, 3>				Vector3D_fl64;
typedef Vector<float64, 4>				Vector4D_fl64;
#else
typedef struct {int64 ix, iy;}				Vector2D;
typedef struct {int64 ix, iy, iz;}			Vector3D;
typedef struct {int64 ix, iy, iz, it;}			Vector4D;
typedef struct {float32 flx32, fly32;}			Vector2D_fl32;
typedef struct {float32 flx32, fly32, flz32;}		Vector3D_fl32;
typedef struct {float32 flx32, fly32, flz32, flt32;}	Vector4D_fl32;
typedef struct {float64 flx64, fly64;}			Vector2D_fl64;
typedef struct {float64 flx64, fly64, flz64;}		Vector3D_fl64;
typedef struct {float64 flx64, fly64, flz64, flt64;}	Vector4D_fl64;
#endif

//Title:	var64
//Purpose:	Generic 64-bit variable, with all appropriate primitive containers
//		suitable to be used (useful for loose type safety)
typedef union {
	uint64	var64;
	int64	int64;
	float64	float64;

	struct {
		uint32	a;
		uint32	b;
	} var32;
	struct {
		int32	a;
		int32	b;
	} int32;
	struct {
		float32	a;
		float32 b;
	} float32;
	struct {
		uint16	a;
		uint16	b;
		uint16	c;
		uint16	d;
	} var16;
	struct {
		int16	a;
		int16	b;
		int16	c;
		int16	d;
	} int16;
	struct {
		uint8	a;
		uint8	b;
		uint8	c;
		uint8	d;
		uint8	e;
		uint8	f;
		uint8	g;
		uint8	h;
	} var8;
	struct {
		int8	a;
		int8	b;
		int8	c;
		int8	d;
		int8	e;
		int8	f;
		int8	g;
		int8	h;
	} int8;

	char	char8[8];
} var64;

//Title:	var32
//Purpose:	Generic 32-bit variable, with all appropriate primitive containers
//		suitable to be used (useful for loose type safety)
typedef union {
	uint32	var32;
	int32	int32;
	float32	float32;

	struct {
		uint16	a;
		uint16	b;
	} var16;
	struct {
		int16	a;
		int16	b;
	} int16;
	struct {
		uint8	a;
		uint8	b;
		uint8	c;
		uint8	d;
	} var8;
	struct {
		int8	a;
		int8	b;
		int8	c;
		int8	d;
	} int8;

	char	char8[4];
} var32;

//Title:	var16
//Purpose:	Generic 16-bit variable, with all appropriate primitive containers
//		suitable to be used (useful for loose type safety)
typedef union {
	uint16	var16;
	int16	int16;

	struct {
		uint8	a;
		uint8	b;
	} var8;
	struct {
		int8	a;
		int8	b;
	} int8;

	char	char8[2];
} var16;

//Title:	var8
//Purpose:	Generic 8-bit variable, with all appropriate primitive containers
//		suitable to be used (useful for loose type safety)
typedef union {
	uint8	var8;
	int8	int8;
	char	char8;
} var8;

#endif

