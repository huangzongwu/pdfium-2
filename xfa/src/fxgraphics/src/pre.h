// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "../../foxitlib.h"
#ifndef FXSYS_Mul
#define		FXSYS_Mul(a, b) ((a) * (b))
#define		FXSYS_Div(a, b) ((a) / (b))
#define		FXSYS_MulDiv(a, b, c) ((a) * (b) / (c))
#define		FXSYS_sqrt2(a, b) (FX_FLOAT)FXSYS_sqrt((a)*(a) + (b)*(b))
#endif
enum {
    FX_CONTEXT_None		= 0,
    FX_CONTEXT_Device,
};
enum {
    FX_COLOR_None		= 0,
    FX_COLOR_Solid,
    FX_COLOR_Pattern,
    FX_COLOR_Shading
};
enum {
    FX_PATTERN_None		= 0,
    FX_PATTERN_Bitmap,
    FX_PATTERN_Hatch
};
enum {
    FX_SHADING_None		= 0,
    FX_SHADING_Axial,
    FX_SHADING_Radial
};
#define	FX_HATCHSTYLE_Total	53
struct FX_HATCHDATA {
    int32_t	width;
    int32_t	height;
    uint8_t		maskBits[64];
};
typedef FX_HATCHDATA const * FX_LPCHATCHDATA;
static const FX_HATCHDATA hatchBitmapData[FX_HATCHSTYLE_Total] = {
    {16, 16, {0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,}},
    {16, 16, {0x80, 0x80, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,}},
    {16, 16, {0x01, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,}},
    {16, 16, {0xff, 0xff, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,}},
    {16, 16, {0x81, 0x81, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00,}},
    {16, 16, {0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x88, 0x88, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00,}},
    {16, 16, {0xaa, 0xaa, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00,}},
    {16, 16, {0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x51, 0x51, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x15, 0x15, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x51, 0x51, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x15, 0x15, 0x00, 0x00,}},
    {16, 16, {0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00,}},
    {16, 16, {0xee, 0xee, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xbb, 0xbb, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xee, 0xee, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xbb, 0xbb, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xee, 0xee, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xbb, 0xbb, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xee, 0xee, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xbb, 0xbb, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00,}},
    {16, 16, {0x77, 0x77, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00,}},
    {16, 16, {0x77, 0x77, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xdd, 0xdd, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,}},
    {16, 16, {0xef, 0xef, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xef, 0xef, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xef, 0xef, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xef, 0xef, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,}},
    {16, 16, {0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xf7, 0xf7, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x7f, 0x7f, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xf7, 0xf7, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x7f, 0x7f, 0x00, 0x00,}},
    {16, 16, {0x88, 0x88, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00,}},
    {16, 16, {0x11, 0x11, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00,}},
    {16, 16, {0xcc, 0xcc, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00,}},
    {16, 16, {0x33, 0x33, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00,}},
    {16, 16, {0xc1, 0xc1, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x0e, 0x0e, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x83, 0x83, 0x00, 0x00, 0xc1, 0xc1, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x0e, 0x0e, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x83, 0x83, 0x00, 0x00,}},
    {16, 16, {0x83, 0x83, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x0e, 0x0e, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0xc1, 0xc1, 0x00, 0x00, 0x83, 0x83, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x0e, 0x0e, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0xc1, 0xc1, 0x00, 0x00,}},
    {16, 16, {0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00,}},
    {16, 16, {0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00,}},
    {16, 16, {0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00, 0xcc, 0xcc, 0x00, 0x00,}},
    {16, 16, {0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00,}},
    {16, 16, {0x80, 0x80, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00,}},
    {16, 16, {0xb1, 0xb1, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x1b, 0x1b, 0x00, 0x00, 0xd8, 0xd8, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x8d, 0x8d, 0x00, 0x00, 0xb1, 0xb1, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x1b, 0x1b, 0x00, 0x00, 0xd8, 0xd8, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x8d, 0x8d, 0x00, 0x00,}},
    {16, 16, {0x81, 0x81, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00,}},
    {16, 16, {0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x25, 0x25, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x25, 0x25, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x25, 0x25, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x25, 0x25, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00,}},
    {16, 16, {0x01, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00,}},
    {16, 16, {0xff, 0xff, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00,}},
    {16, 16, {0x88, 0x88, 0x00, 0x00, 0x54, 0x54, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x45, 0x45, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x14, 0x14, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x51, 0x51, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x54, 0x54, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x45, 0x45, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x14, 0x14, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x51, 0x51, 0x00, 0x00,}},
    {16, 16, {0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00,}},
    {16, 16, {0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,}},
    {16, 16, {0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
    {16, 16, {0x03, 0x03, 0x00, 0x00, 0x84, 0x84, 0x00, 0x00, 0x48, 0x48, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x84, 0x84, 0x00, 0x00, 0x48, 0x48, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,}},
    {16, 16, {0xff, 0xff, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00,}},
    {16, 16, {0x77, 0x77, 0x00, 0x00, 0x89, 0x89, 0x00, 0x00, 0x8f, 0x8f, 0x00, 0x00, 0x8f, 0x8f, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x98, 0x98, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x89, 0x89, 0x00, 0x00, 0x8f, 0x8f, 0x00, 0x00, 0x8f, 0x8f, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x98, 0x98, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00,}},
    {16, 16, {0xff, 0xff, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00, 0x88, 0x88, 0x00, 0x00,}},
    {16, 16, {0x99, 0x99, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00,}},
    {16, 16, {0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00,}},
    {16, 16, {0x82, 0x82, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x28, 0x28, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x28, 0x28, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x82, 0x82, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x82, 0x82, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x28, 0x28, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x28, 0x28, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00, 0x82, 0x82, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,}},
    {16, 16, {0x10, 0x10, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x7c, 0x7c, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0x7c, 0x7c, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x7c, 0x7c, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0x7c, 0x7c, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}},
};
#if defined (__WIN32__) || defined (_WIN32)
#define FX_START_TIMER	SYSTEMTIME start, stop; \
    ::GetLocalTime(&start);
#define FX_STOP_TIMER	::GetLocalTime(&stop); \
    WORD wSecond = stop.wSecond - start.wSecond; \
    WORD wMilliseconds = stop.wMilliseconds - start.wMilliseconds; \
    char buf[256]; \
    memset(buf, 0, sizeof(buf)); \
    snprintf(buf, sizeof(buf) - 1, "duration is %d millisecond\n", wSecond * 1000 + wMilliseconds); \
    ::OutputDebugString(buf);
#elif defined (__linux) || defined (linux)
#define FX_START_TIMER
#define FX_STOP_TIMER
#elif defined (__APPLE__) || defined (__MACOSX__)
#define FX_START_TIMER	NSTimeInterval start, stop; \
    start = [NSDate timeIntervalSinceReferenceDate];
#define FX_STOP_TIMER	stop = [NSDate timeIntervalSinceReferenceDate]; \
    NSTimeInterval duration = stop - start; \
    printf("duration is %f millisecond\n", duration * 1000);
#else
#endif
