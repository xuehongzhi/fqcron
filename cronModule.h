#pragma once

// cronModule.h : header file
//


#include "..\include\FQEventSinkInc.h"
/////////////////////////////////////////////////////////////////////////////
// CcronModule command target
class MessageManager;
class CcronModule : public CCmdTarget
{
	DECLARE_DYNCREATE(CcronModule)
	DECLARE_EVENT_RECEIVER(CcronModule)

	CcronModule();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CcronModule)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CcronModule();

	// Generated message map functions
	//{{AFX_MSG(CcronModule)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	BEGIN_DUAL_INTERFACE_PART(FQModule, IFQModule)
	STDMETHOD(raw_OnModuleEvent)(/*[in]*/ BSTR eventType, /*[in]*/ BSTR Name, /*[in]*/ BSTR sParam, /*[out, retval]*/ BSTR* pVal);
	STDMETHOD(raw_OnLoad)(/*[in]*/ IDispatch* FQModuleSite);
	STDMETHOD(raw_OnUnload)();
	STDMETHOD(raw_OnConfig)();
	STDMETHOD(get_Identifier)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Author)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ModuleSite)(/*[out, retval]*/ IDispatch* *pVal)
	{
		METHOD_PROLOGUE(CcronModule, FQModule)
		
		FQ_CHECK_INVALIDARG_NULL(pVal);
		
		*pVal = pThis->m_ptrModuleSite;

		if (*pVal != NULL)
		{
			(*pVal)->AddRef();
		}

		return *pVal != NULL ? S_OK : E_FAIL;
	}
	END_DUAL_INTERFACE_PART(FQModule)	

	BEGIN_DUAL_INTERFACE_PART(MenuSink, IFQUICommand)
    STDMETHOD(raw_OnInvoke)( enum FQ_UI_TYPE Type, long Id, VARIANT Parameter );
    STDMETHOD(raw_OnQueryState) (enum FQ_UI_TYPE Type, long Id, VARIANT Parameter,
                                 BSTR * bstrText,
                                 enum FQ_UI_ITEM_STATE * State );
	END_DUAL_INTERFACE_PART(MenuSink)

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CcronModule)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CcronModule)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:

    static VOID CALLBACK CheckMessage(HWND, UINT, UINT_PTR, DWORD);
	UINT_PTR m_hTimer;
	IFQModuleSitePtr m_ptrModuleSite;

	CFQEventSinkRoot m_RootEventSink;

    IFQRootPtr m_ptrRoot;
    MessageManager* m_pMessageManger;

	IFQMenuPtr m_ptrMenu;
	int m_AddMenuID;

public:
	HRESULT OnModuleEvent(BSTR eventType, BSTR Name, BSTR sParam, BSTR* pVal);
	HRESULT OnLoad(IDispatch* FQModuleSite);
	HRESULT OnUnload();
	HRESULT OnConfig();
	HRESULT get_Identifier(BSTR* pVal);
	HRESULT get_Name(BSTR* pVal);
	HRESULT get_Description(BSTR* pVal);
	HRESULT get_Author(BSTR* pVal);


	HRESULT MenuOnInvoke(enum FQ_UI_TYPE Type, long Id, VARIANT Parameter );

	HRESULT OnUserEnter(LPCTSTR userMemoName, LPCTSTR userNickName, LPCTSTR userHostName, LPCTSTR userLoginName, LPCTSTR userMemoGroupName, LPCTSTR userGroupName, LPCTSTR userIP, LPCTSTR userMAC);
	HRESULT OnUserExit(LPCTSTR userMemoName, LPCTSTR userNickName, LPCTSTR userHostName, LPCTSTR userLoginName, LPCTSTR userMemoGroupName, LPCTSTR userGroupName, LPCTSTR userIP, LPCTSTR userMAC);
	HRESULT OnSkinChange(COLORREF clrFrame, COLORREF clrFont, COLORREF clrLeftTop, COLORREF clrRightBtm);
	HRESULT OnBeforeRecvMsg(LPCTSTR MemoName, LPCTSTR Host, LPCTSTR Group, LPCTSTR IP, LPCTSTR MAC, LPCTSTR sendMsg, LPCTSTR font, enum FQ_BEFORERECVMSG_RESULT *pResult);
	HRESULT OnFolderBarChange(LONG nBeforeBarIndex, LONG nNowBarIndex);
	HRESULT OnRootEvent(LPCTSTR eventType, LPCTSTR Name, LPCTSTR sParam, IFQData* pData);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

