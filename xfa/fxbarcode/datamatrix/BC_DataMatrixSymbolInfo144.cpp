// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com
// Original code is licensed as follows:
/*
 * Copyright 2006 Jeremias Maerki
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "xfa/fxbarcode/datamatrix/BC_DataMatrixSymbolInfo144.h"
#include "xfa/fxbarcode/datamatrix/BC_Encoder.h"
#include "xfa/fxbarcode/datamatrix/BC_SymbolInfo.h"
#include "xfa/fxbarcode/datamatrix/BC_SymbolShapeHint.h"

CBC_DataMatrixSymbolInfo144::CBC_DataMatrixSymbolInfo144()
    : CBC_SymbolInfo(false, 1558, 620, 22, 22, 36) {
  m_rsBlockData = -1;
  m_rsBlockError = 62;
}
CBC_DataMatrixSymbolInfo144::~CBC_DataMatrixSymbolInfo144() {}
int32_t CBC_DataMatrixSymbolInfo144::getInterleavedBlockCount() {
  return 10;
}
int32_t CBC_DataMatrixSymbolInfo144getDataLengthForInterleavedBlock(
    int32_t index) {
  return (index <= 8) ? 156 : 155;
}
