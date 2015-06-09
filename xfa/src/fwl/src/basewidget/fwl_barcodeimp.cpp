// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "../../../foxitlib.h"
#include "../core/include/fwl_targetimp.h"
#include "../core/include/fwl_noteimp.h"
#include "../core/include/fwl_widgetimp.h"
#include "include/fwl_editimp.h"
#include "include/fwl_barcodeimp.h"
IFWL_Barcode* IFWL_Barcode::Create()
{
    return new IFWL_Barcode;
}
IFWL_Barcode::IFWL_Barcode()
{
    m_pData = NULL;
}
IFWL_Barcode::~IFWL_Barcode()
{
    if (m_pData) {
        delete (CFWL_BarcodeImp*)m_pData;
        m_pData = NULL;
    }
}
FWL_ERR IFWL_Barcode::Initialize(IFWL_Widget *pOuter)
{
    m_pData = FX_NEW CFWL_BarcodeImp(pOuter);
    ((CFWL_BarcodeImp*)m_pData)->SetInterface(this);
    return ((CFWL_BarcodeImp*)m_pData)->Initialize();
}
FWL_ERR	IFWL_Barcode::Initialize(const CFWL_WidgetImpProperties &properties, IFWL_Widget *pOuter)
{
    m_pData = FX_NEW CFWL_BarcodeImp(properties, pOuter);
    ((CFWL_BarcodeImp*)m_pData)->SetInterface(this);
    return ((CFWL_BarcodeImp*)m_pData)->Initialize();
}
void	IFWL_Barcode::SetType(BC_TYPE type)
{
    ((CFWL_BarcodeImp*)m_pData)->SetType(type);
}
FX_BOOL	IFWL_Barcode::IsProtectedType()
{
    return ((CFWL_BarcodeImp*)m_pData)->IsProtectedType();
}
CFWL_BarcodeImp::CFWL_BarcodeImp(IFWL_Widget *pOuter )
    : CFWL_EditImp(pOuter)
    , m_pBarcodeEngine(NULL)
    , m_dwStatus(0)
    , m_type(BC_UNKNOWN)
{
}
CFWL_BarcodeImp::CFWL_BarcodeImp(const CFWL_WidgetImpProperties &properties, IFWL_Widget *pOuter )
    : CFWL_EditImp(properties, pOuter)
    , m_pBarcodeEngine(NULL)
    , m_dwStatus(0)
    , m_type(BC_UNKNOWN)
{
}
CFWL_BarcodeImp::~CFWL_BarcodeImp()
{
    ReleaseBarcodeEngine();
}
FWL_ERR CFWL_BarcodeImp::GetClassName(CFX_WideString &wsClass) const
{
    wsClass = FWL_CLASS_Barcode;
    return FWL_ERR_Succeeded;
}
FX_DWORD CFWL_BarcodeImp::GetClassID() const
{
    return FWL_CLASSHASH_Barcode;
}
FWL_ERR	CFWL_BarcodeImp::Initialize()
{
    if (!m_pDelegate) {
        m_pDelegate = (IFWL_WidgetDelegate*) FX_NEW CFWL_BarcodeImpDelegate(this);
    }
    _FWL_ERR_CHECK_RETURN_VALUE_IF_FAIL(CFWL_EditImp::Initialize(), FWL_ERR_Indefinite);
    return FWL_ERR_Succeeded;
}
FWL_ERR	CFWL_BarcodeImp::Finalize()
{
    if (m_pDelegate) {
        delete (CFWL_BarcodeImpDelegate*)m_pDelegate;
        m_pDelegate = NULL;
    }
    ReleaseBarcodeEngine();
    return CFWL_EditImp::Finalize();
}
FWL_ERR CFWL_BarcodeImp::Update()
{
    if (IsLocked()) {
        return FWL_ERR_Indefinite;
    }
    FWL_ERR ret = CFWL_EditImp::Update();
    GenerateBarcodeImageCache();
    return ret;
}
FWL_ERR CFWL_BarcodeImp::DrawWidget(CFX_Graphics *pGraphics, const CFX_Matrix *pMatrix )
{
    _FWL_RETURN_VALUE_IF_FAIL(pGraphics, FWL_ERR_Indefinite);
    _FWL_RETURN_VALUE_IF_FAIL(m_pProperties->m_pThemeProvider, FWL_ERR_Indefinite);
    if ((m_pProperties->m_dwStates & FWL_WGTSTATE_Focused) == 0) {
        GenerateBarcodeImageCache();
        if (!m_pBarcodeEngine || (m_dwStatus & XFA_BCS_EncodeSuccess) == 0) {
            return FWL_ERR_Succeeded;
        }
        CFX_Matrix mt;
        mt.e = m_rtClient.left;
        mt.f = m_rtClient.top;
        if (pMatrix) {
            mt.Concat(*pMatrix);
        }
        int32_t errorCode = 0;
        _FWL_RETURN_VALUE_IF_FAIL(m_pBarcodeEngine->RenderDevice(pGraphics->GetRenderDevice(), pMatrix, errorCode), FWL_ERR_Indefinite);
        return FWL_ERR_Succeeded;
    }
    return CFWL_EditImp::DrawWidget(pGraphics, pMatrix);
}
void CFWL_BarcodeImp::GenerateBarcodeImageCache()
{
    if ((m_dwStatus & XFA_BCS_NeedUpdate) == 0) {
        return;
    }
    m_dwStatus = 0;;
    CreateBarcodeEngine();
    IFWL_BarcodeDP *pData = (IFWL_BarcodeDP*)m_pProperties->m_pDataProvider;
    _FWL_RETURN_IF_FAIL(pData);
    _FWL_RETURN_IF_FAIL(m_pBarcodeEngine);
    CFX_WideString wsText;
    _FWL_RETURN_IF_FAIL(GetText(wsText) == FWL_ERR_Succeeded);
    CFWL_ThemePart part;
    part.m_pWidget = m_pInterface;
    IFWL_ThemeProvider *pTheme = GetAvailableTheme();
    IFX_Font* pFont = (IFX_Font*)pTheme->GetCapacity(&part, FWL_WGTCAPACITY_Font);
    CFX_Font* pCXFont = (CFX_Font*)(pFont ? pFont->GetDevFont() : NULL);
    if(pCXFont) {
        m_pBarcodeEngine->SetFont(pCXFont);
    }
    FX_FLOAT* pFontSize = (FX_FLOAT*)pTheme->GetCapacity(&part, FWL_WGTCAPACITY_FontSize);
    if(pFontSize) {
        m_pBarcodeEngine->SetFontSize(*pFontSize);
    }
    FX_ARGB* pFontColor = (FX_ARGB*)pTheme->GetCapacity(&part, FWL_WGTCAPACITY_TextColor);
    if(pFontColor) {
        m_pBarcodeEngine->SetFontColor(*pFontColor);
    }
    m_pBarcodeEngine->SetHeight(int32_t(m_rtClient.height));
    m_pBarcodeEngine->SetWidth(int32_t(m_rtClient.width));
    FX_DWORD dwAttributeMask = pData->GetBarcodeAttributeMask();
    if (dwAttributeMask & FWL_BCDATTRIBUTE_CHARENCODING)	{
        m_pBarcodeEngine->SetCharEncoding			(pData->GetCharEncoding());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_MODULEHEIGHT)	{
        m_pBarcodeEngine->SetModuleHeight			(pData->GetModuleHeight());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_MODULEWIDTH) {
        m_pBarcodeEngine->SetModuleWidth			(pData->GetModuleWidth());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_DATALENGTH) {
        m_pBarcodeEngine->SetDataLength				(pData->GetDataLength());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_CALCHECKSUM) {
        m_pBarcodeEngine->SetCalChecksum			(pData->GetCalChecksum());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_PRINTCHECKSUM)	{
        m_pBarcodeEngine->SetPrintChecksum			(pData->GetPrintChecksum());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_TEXTLOCATION)	{
        m_pBarcodeEngine->SetTextLocation			(pData->GetTextLocation());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_WIDENARROWRATIO)	{
        m_pBarcodeEngine->SetWideNarrowRatio		(pData->GetWideNarrowRatio());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_STARTCHAR) {
        m_pBarcodeEngine->SetStartChar				(pData->GetStartChar());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_ENDCHAR) {
        m_pBarcodeEngine->SetEndChar				(pData->GetEndChar());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_VERSION) {
        m_pBarcodeEngine->SetVersion				(pData->GetVersion());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_ECLEVEL) {
        m_pBarcodeEngine->SetErrorCorrectionLevel	(pData->GetErrorCorrectionLevel());
    }
    if (dwAttributeMask & FWL_BCDATTRIBUTE_TRUNCATED) {
        m_pBarcodeEngine->SetTruncated				(pData->GetTruncated());
    }
    int32_t errorCode = 0;
    m_dwStatus = m_pBarcodeEngine->Encode(wsText, TRUE, errorCode) ? XFA_BCS_EncodeSuccess : 0;
}
void CFWL_BarcodeImp::CreateBarcodeEngine()
{
    if ((m_pBarcodeEngine == NULL) && (m_type != BC_UNKNOWN)) {
        m_pBarcodeEngine = FX_Barcode_Create(m_type);
    }
}
void CFWL_BarcodeImp::ReleaseBarcodeEngine()
{
    if (m_pBarcodeEngine) {
        m_pBarcodeEngine->Release();
        m_pBarcodeEngine = NULL;
    }
}
void CFWL_BarcodeImp::SetType(BC_TYPE type)
{
    if (m_type == type) {
        return;
    }
    ReleaseBarcodeEngine();
    m_type = type;
    m_dwStatus = XFA_BCS_NeedUpdate;
}
FWL_ERR CFWL_BarcodeImp::SetText(const CFX_WideString &wsText)
{
    ReleaseBarcodeEngine();
    m_dwStatus = XFA_BCS_NeedUpdate;
    return CFWL_EditImp::SetText(wsText);
}
FX_BOOL CFWL_BarcodeImp::IsProtectedType()
{
    if (!m_pBarcodeEngine) {
        return TRUE;
    }
    BC_TYPE tEngineType = m_pBarcodeEngine->GetType();
    if (tEngineType == BC_QR_CODE || tEngineType == BC_PDF417 || tEngineType == BC_DATAMATRIX) {
        return TRUE;
    }
    return FALSE;
}
CFWL_BarcodeImpDelegate::CFWL_BarcodeImpDelegate(CFWL_BarcodeImp *pOwner)
    : CFWL_EditImpDelegate(pOwner)
{
}
FWL_ERR	CFWL_BarcodeImpDelegate::OnProcessEvent(CFWL_Event *pEvent)
{
    FX_DWORD dwFlag = pEvent->GetClassID();
    if (dwFlag == FWL_EVTHASH_EDT_TextChanged) {
        CFWL_BarcodeImp* pOwner = (CFWL_BarcodeImp*)m_pOwner;
        pOwner->ReleaseBarcodeEngine();
        pOwner->m_dwStatus = XFA_BCS_NeedUpdate;
    }
    return CFWL_EditImpDelegate::OnProcessEvent(pEvent);
}
