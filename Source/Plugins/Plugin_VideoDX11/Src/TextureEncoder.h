// Copyright (C) 2003 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef _TEXTUREENCODER_H
#define _TEXTUREENCODER_H

#include "VideoCommon.h"

namespace DX11
{

// 4-bit format: 8x8 texels / cache line
// 8-bit format: 8x4 texels / cache line
// 16-bit format: 4x4 texels / cache line
// 32-bit format: 4x4 texels / 2 cache lines
// Compressed format: 8x8 texels / cache line

// Document EFB encoding formats here with examples of where they are used.

// Format: 0 - R4
// Used in The Legend of Zelda: The Wind Waker for character shadows (srcFormat 1,
// isIntensity 1, scaleByHalf 1).

// Format: 1 - R8
// FIXME: Unseen. May or may not be a duplicate of format 8.

// Format: 2 - A4 R4
// FIXME: Unseen.

// Format: 3 - A8 R8
// FIXME: Unseen.

// Format: 4 - R5 G6 B5
// Used in Wind Waker for most render-to-texture effects like heat shimmer and
// depth-of-field.

// Format: 5 - 1 R5 G5 B5 or 0 A3 R4 G4 B4
// Used in Twilight Princess for character shadows.

// Format: 6 - A8 R8 A8 R8 | G8 B8 G8 B8
// Used in Twilight Princess for bloom effect.

// Format: 7 - A8
// Used in Metroid Prime 2 for the scan visor.

// Format: 8 - R8
// Used in Twilight Princess for the map.

// Format: 9 - G8
// FIXME: Unseen.

// Format: A - B8
// Used in Metroid Prime 2 for the scan visor.

// Format: B - G8 R8
// Used in Wind Waker for depth-of-field. Usually used with srcFormat 3 to
// render depth textures. The bytes are swapped, so games have to correct it
// in RAM before using it as a texture.

// Format: C - B8 G8
// FIXME: Unseen.

const unsigned int BLOCK_WIDTHS[16] = {
	8, // R4
	8, // R8 (FIXME: duplicate of R8 below?)
	8, // A4 R4
	4, // A8 R8
	4, // R5 G6 B5
	4, // 1 R5 G5 B5 or 0 A3 R4 G4 B4
	4, // A8 R8 A8 R8 | G8 B8 G8 B8 (two cache lines)
	8, // A8
	8, // R8 (FIXME: duplicate of R8 above?)
	8, // G8
	8, // B8
	4, // G8 R8
	4, // B8 G8
	0, 0, 0 // Unknown formats
};

const unsigned int BLOCK_HEIGHTS[16] = {
	8, // R4
	4, // R8 (FIXME: duplicate of R8 below?)
	4, // A4 R4
	4, // A8 R8
	4, // R5 G6 B5
	4, // 1 R5 G5 B5 or 0 A3 R4 G4 B4
	4, // A8 R8 A8 R8 | G8 B8 G8 B8 (two cache lines)
	4, // A8
	4, // R8 (FIXME: duplicate of R8 above?)
	4, // G8
	4, // B8
	4, // G8 R8
	4, // B8 G8
	0, 0, 0 // Unknown formats
};

// Maximum number of bytes that can occur in a texture block-row generated by
// the encoder
static const UINT MAX_BYTES_PER_BLOCK_ROW = (EFB_WIDTH/4)*64;
// The maximum amount of data that the texture encoder can generate in one call
static const UINT MAX_BYTES_PER_ENCODE = MAX_BYTES_PER_BLOCK_ROW*(EFB_HEIGHT/4);

class TextureEncoder
{

public:

	virtual ~TextureEncoder() { }

	virtual void Init() = 0;
	virtual void Shutdown() = 0;
	// Returns size in bytes of encoded block of memory
	virtual size_t Encode(u8* dst, unsigned int dstFormat,
		unsigned int srcFormat, const EFBRectangle& srcRect, bool isIntensity,
		bool scaleByHalf) = 0;

};

}

#endif
