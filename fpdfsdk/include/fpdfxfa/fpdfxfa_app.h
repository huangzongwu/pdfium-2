// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef FPDFXFA_APP_H_
#define FPDFXFA_APP_H_

class IFXJS_Runtime;
class CJS_RuntimeFactory;

class CPDFXFA_App : public IXFA_AppProvider
{
public:
    static CPDFXFA_App* GetInstance();
    static void ReleaseInstance();

    CPDFXFA_App();
    ~CPDFXFA_App() override;

    FX_BOOL             Initialize();
    IXFA_App*           GetXFAApp() { return m_pXFAApp; }

    FX_BOOL             AddFormFillEnv(CPDFDoc_Environment* pEnv);
    FX_BOOL             RemoveFormFillEnv(CPDFDoc_Environment* pEnv);

    FXJSE_HRUNTIME      GetJSERuntime() { return m_hJSERuntime; }
    void                ReleaseRuntime();
    FX_BOOL             InitRuntime(FX_BOOL bReset=FALSE);

    CJS_RuntimeFactory* GetRuntimeFactory() { return m_pJSRuntimeFactory; }

    // IFXA_AppProvider:
    void GetAppType(CFX_WideString &wsAppType) override;
    void SetAppType(FX_WSTR wsAppType) override;

    void GetLanguage(CFX_WideString &wsLanguage) override;
    void GetPlatform(CFX_WideString &wsPlatform) override;
    void GetVariation(CFX_WideString &wsVariation) override;
    void GetVersion(CFX_WideString &wsVersion) override;
    void GetFoxitVersion(CFX_WideString &wsFoxitVersion) override {
        wsFoxitVersion = L"7.0";
    }

    void GetAppName(CFX_WideString& wsName) override;
    void GetFoxitAppName(CFX_WideString& wsFoxitName) override {
        wsFoxitName = L"Foxit";
    }

    void Beep(FX_DWORD dwType) override;
    int32_t MsgBox(FX_WSTR wsMessage, FX_WSTR wsTitle, FX_DWORD dwIconType, FX_DWORD dwButtonType) override;
    void Response(CFX_WideString &wsAnswer, FX_WSTR wsQuestion, FX_WSTR wsTitle,
                  FX_WSTR wsDefaultAnswer, FX_BOOL bMark) override;

    int32_t GetDocumentCountInBatch() override;
    int32_t GetCurDocumentInBatch() override;

    IFX_FileRead* DownloadURL(FX_WSTR wsURL) override;
    FX_BOOL PostRequestURL(FX_WSTR wsURL, FX_WSTR wsData, FX_WSTR wsContentType,
                           FX_WSTR wsEncode, FX_WSTR wsHeader, CFX_WideString &wsResponse) override;
    FX_BOOL PutRequestURL(FX_WSTR wsURL, FX_WSTR wsData, FX_WSTR wsEncode) override;

    void LoadString(int32_t iStringID, CFX_WideString &wsString) override;
    FX_BOOL ShowFileDialog(FX_WSTR wsTitle, FX_WSTR wsFilter, CFX_WideStringArray &wsPathArr, FX_BOOL bOpen) override;
    IFWL_AdapterTimerMgr* GetTimerMgr() override;

    CFX_ArrayTemplate<CPDFDoc_Environment*> m_pEnvList;

protected:
    static CPDFXFA_App* g_pApp;

    FX_BOOL m_bInitRuntime;
    IXFA_App* m_pXFAApp;
    IXFA_FontMgr* m_pFontMgr;
    FXJSE_HRUNTIME m_hJSERuntime;
    IFXJS_Runtime* m_pJSRuntime;
    CJS_RuntimeFactory* m_pJSRuntimeFactory;
    CFX_WideString m_csAppType;
};

#endif  // FPDFXFA_APP_H_
