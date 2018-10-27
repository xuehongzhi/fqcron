// cronModule.cpp : implementation file
//

#include "stdafx.h"
#include "messagemanager.h"
#include "cronModule.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "..\include\FQEventSinkImp.h"


LOGFONT g_fontSend, g_fontRecv;
COLORREF g_clrSend = RGB(0, 0, 0), g_clrRecv = RGB(0, 0, 0);
BOOL g_bcron = FALSE;
int g_BeforeMsgMode = 2;
BOOL g_bSendMsgEnter = FALSE;
BOOL g_bSaveWndSize = TRUE;
int g_nWndWidth = 0, g_nWndHeight = 0;
int g_nShowNameMode = 1;
BOOL g_nUserChangeTip = TRUE;


IMPLEMENT_DYNCREATE(CcronModule, CCmdTarget)
DELEGATE_DUAL_INTERFACE(CcronModule, FQModule)
DELEGATE_DUAL_INTERFACE(CcronModule, MenuSink)

VOID CALLBACK CcronModule::CheckMessage(HWND hwnd,        // handle to window for timer messages 
										UINT message,     // WM_TIMER message 
										UINT idTimer,     // timer identifier 
										DWORD dwTime)
{
	TRACE0("Timer\n");

    MessageManager* pMessageManger = MessageManager::GetInstance();
	pMessageManger->Load("d:\\message.txt");
	pMessageManger->SendMessages();

    
}

CcronModule::CcronModule()
{

	m_ptrMenu = NULL;
	m_ptrModuleSite = NULL;
	m_ptrRoot = NULL;


	memset(&g_fontSend,0,sizeof(LOGFONT));
	memset(&g_fontRecv,0,sizeof(LOGFONT));

	g_fontSend.lfHeight = -16;
	g_fontSend.lfWidth = 0;
	g_fontSend.lfEscapement = 0;
	g_fontSend.lfOrientation = 0;
	g_fontSend.lfWeight = FW_MEDIUM;
	g_fontSend.lfItalic = FALSE;
	g_fontSend.lfUnderline = FALSE;
	g_fontSend.lfStrikeOut = FALSE;
	g_fontSend.lfCharSet = GB2312_CHARSET;
	g_fontSend.lfOutPrecision = OUT_DEFAULT_PRECIS;
	g_fontSend.lfClipPrecision = CLIP_LH_ANGLES;
	g_fontSend.lfQuality = DEFAULT_QUALITY;
	g_fontSend.lfPitchAndFamily =  FF_SWISS;
	strncpy_s(g_fontSend.lfFaceName, "宋体",sizeof("宋体"));
	g_fontRecv = g_fontSend;

	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
	

}

CcronModule::~CcronModule()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	AfxOleUnlockApp();
}


void CcronModule::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CcronModule, CCmdTarget)
	//{{AFX_MSG_MAP(CcronModule)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CcronModule, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CcronModule)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IcronModule to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

static const IID IID_IcronModule =
{ 0xfd4c7e5c, 0x2c5, 0x49ae, { 0x90, 0x49, 0x7c, 0x14, 0xe2, 0x54, 0x9c, 0xc } };

BEGIN_INTERFACE_MAP(CcronModule, CCmdTarget)
	INTERFACE_PART(CcronModule, IID_IcronModule, Dispatch)
	INTERFACE_PART(CcronModule, IID_IFQModule, FQModule)
	INTERFACE_PART(CcronModule, IID_IFQUICommand, MenuSink)
END_INTERFACE_MAP()


IMPLEMENT_OLECREATE(CcronModule, "FeiQ.cronModule", 0x3a2e9929, 0x2633, 0x42e7, 0x84, 0x89, 0xe3, 0x90, 0x50, 0x82, 0x36, 0x67)

STDMETHODIMP CcronModule::XFQModule::raw_OnModuleEvent(BSTR eventType, BSTR Name,BSTR sParam, BSTR* pVal)
{
	METHOD_PROLOGUE(CcronModule, FQModule)

	return pThis->OnModuleEvent(eventType, Name, sParam, pVal);
}

STDMETHODIMP CcronModule::XFQModule::raw_OnLoad(IDispatch* FQModuleSite)
{
	METHOD_PROLOGUE(CcronModule, FQModule)


	return pThis->OnLoad(FQModuleSite);
}

STDMETHODIMP CcronModule::XFQModule::raw_OnUnload()
{
	METHOD_PROLOGUE(CcronModule, FQModule)


	return pThis->OnUnload();
}

STDMETHODIMP CcronModule::XFQModule::raw_OnConfig()
{
	METHOD_PROLOGUE(CcronModule, FQModule)

	return pThis->OnConfig();
}

STDMETHODIMP CcronModule::XFQModule::get_Identifier(BSTR* pVal)
{
	METHOD_PROLOGUE(CcronModule, FQModule)

	return pThis->get_Identifier(pVal);
}


STDMETHODIMP CcronModule::XFQModule::get_Name(BSTR* pVal)
{
	METHOD_PROLOGUE(CcronModule, FQModule)

	return pThis->get_Name(pVal);
}

STDMETHODIMP CcronModule::XFQModule::get_Description(BSTR* pVal)
{
	METHOD_PROLOGUE(CcronModule, FQModule)

	return pThis->get_Description(pVal);
}

STDMETHODIMP CcronModule::XFQModule::get_Author(BSTR* pVal)
{
	METHOD_PROLOGUE(CcronModule, FQModule)

	return pThis->get_Author(pVal);
}

HRESULT CcronModule::get_Identifier(BSTR* pVal)
{
	if (NULL == pVal)
	{
		ASSERT(FALSE);
		return E_INVALIDARG;
	}

	*pVal = CString(FQ_MODULE_IDENTIFIER_PLUGINFEEDBACK).AllocSysString();

	return S_OK;
}

HRESULT CcronModule::get_Name(BSTR* pVal)
{
	if (NULL == pVal)
	{
		ASSERT(FALSE);
		return E_INVALIDARG;
	}

	*pVal = CString(FQ_MODULE_NAME_PLUGINFEEDBACK).AllocSysString();

	return S_OK;
}

HRESULT CcronModule::get_Description(BSTR* pVal)
{
	if (NULL == pVal)
	{
		ASSERT(FALSE);
		return E_INVALIDARG;
	}

	*pVal = CString(FQ_MODULE_DESCRIPTION_PLUGINFEEDBACK).AllocSysString();

	return S_OK;
}


HRESULT CcronModule::get_Author(BSTR* pVal)
{
	if (NULL == pVal)
	{
		ASSERT(FALSE);
		return E_INVALIDARG;
	}

	*pVal = CString(FQ_MODULE_AUTHOR_PLUGINFEEDBACK).AllocSysString();

	return S_OK;
}

HRESULT CcronModule::OnModuleEvent(BSTR eventType, BSTR Name, BSTR sParam, BSTR* pVal)
{
	if(CString(eventType) == "appbox.click")
	{


	}
	*pVal = CString("").AllocSysString();
	return S_OK;
}

HRESULT CcronModule::OnLoad(IDispatch* FQModuleSite)
{

	if (NULL == FQModuleSite)
	{
		ASSERT(FALSE);
		return E_INVALIDARG;
	}

	FQ_TRY
	{
		
		m_ptrModuleSite = FQModuleSite;
		m_ptrModuleSite->get_FQRoot(&m_ptrRoot);
		MessageManager::GetInstance()->SetRootPtr(m_ptrRoot);

		CComBSTR identeriferMenu("FeiQ.Menu");
		m_ptrMenu =  m_ptrRoot->Module[(_bstr_t)identeriferMenu];
		IFQUICommand* pUICmd = dynamic_cast<IFQUICommand* >(&m_xMenuSink);

		//m_AddMenuID = m_ptrMenu->AddItem(FQ_UI_TYPE_TRAY_MENU, "软件帮助", pUICmd, "办公模式对话框||", 101);

		/*
		菜单Text说明:
		形式如 ||测试Group||||测试 其中 || 和  可选。|| 表示分隔符。在名称前加 || 表示在添加的菜单项上面添加分隔符. 
		在名称前后 || 表示在添加的菜单项下面添加分隔符.  是上下级菜单的关系。例子中测试菜单的父菜单是测试Group。当测试Group不存在时，程序会自动创建这组菜单
		*/
		

		m_RootEventSink.HookEvent(evt_OnUserEnter, this, &CcronModule::OnUserEnter);
		m_RootEventSink.HookEvent(evt_OnUserExit, this, &CcronModule::OnUserExit);
		m_RootEventSink.HookEvent(evt_OnBeforeRecvMsg, this, &CcronModule::OnBeforeRecvMsg);
		m_RootEventSink.HookEvent(evt_OnRootEvent, this, &CcronModule::OnRootEvent);
	
		if (!m_RootEventSink.Advise(m_ptrRoot))
		{
			throw FQ_UNSPECIFIC_ERROR;
		}
		
		IFQDataPtr cfgPtr;
		m_ptrRoot->get_UserCustomConfig(&cfgPtr);
		if(cfgPtr)
		{
			int ncron = cfgPtr->GetLong(L"cron");
			if(ncron == 1)
			{
				g_bcron = TRUE;
			}
			else
			{
				g_bcron = FALSE;
			}
			int nBufferLen = cfgPtr->GetBufferLength(L"BGCHAT_SENDFONT");
			if(nBufferLen == sizeof(LOGFONT))
			{
				cfgPtr->GetBuffer(L"BGCHAT_SENDFONT", (unsigned char *)&g_fontSend, sizeof(LOGFONT));
			}
			nBufferLen = cfgPtr->GetBufferLength(L"BGCHAT_RECVFONT");
			if(nBufferLen == sizeof(LOGFONT))
			{
				cfgPtr->GetBuffer(L"BGCHAT_RECVFONT", (unsigned char *)&g_fontRecv, sizeof(LOGFONT));
			}
			long clrSend = 0, clrRecv = 0;
			if(cfgPtr->raw_GetLong(L"BGCHAT_SENDCLR", &clrSend) == S_OK)
			{
				g_clrSend = (COLORREF)clrSend;
			}
			if(cfgPtr->raw_GetLong(L"BGCHAT_RECVCLR", &clrRecv) == S_OK)
			{
				g_clrRecv = (COLORREF)clrRecv;
			}
			long nMsgMode = 2;
			if(cfgPtr->raw_GetLong(L"BGCHAT_MSGMODE", &nMsgMode) == S_OK)
			{
				g_BeforeMsgMode = nMsgMode;
			}
			long nSendMsgEnter = 0;
			if(cfgPtr->raw_GetLong(L"BGCHAT_SENDMODE", &nSendMsgEnter) == S_OK)
			{
				g_bSendMsgEnter = nSendMsgEnter;
			}
			long nSaveWndSize = 0;
			if(cfgPtr->raw_GetLong(L"BGCHAT_SAVEWNDSIZE", &nSaveWndSize) == S_OK)
			{
				g_bSaveWndSize = nSaveWndSize;
			}
			long nWndWidth = 0;
			if(cfgPtr->raw_GetLong(L"BGCHAT_WNDWIDTH", &nWndWidth) == S_OK)
			{
				g_nWndWidth = nWndWidth;
			}
			long nWndHeight = 0;
			if(cfgPtr->raw_GetLong(L"BGCHAT_WNDHEGHT", &nWndHeight) == S_OK)
			{
				g_nWndHeight = nWndHeight;
			}
			long nShowNameMode = 1;
			if(cfgPtr->raw_GetLong(L"BGCHAT_SHOWNAMEMODE", &nShowNameMode) == S_OK)
			{
				g_nShowNameMode = nShowNameMode;
				if(g_nShowNameMode == 0) g_nShowNameMode = 1;
			}
			long nUserChangeTip = 1;
			if(cfgPtr->raw_GetLong(L"BGCHAT_USERCHANGETIP", &nUserChangeTip) == S_OK)
			{
				g_nUserChangeTip = nUserChangeTip;
			}
			cfgPtr->SetLong(L"cron", g_bcron);//保存进配置
			cfgPtr->SetBuffer(L"BGCHAT_SENDFONT", (unsigned char *)&g_fontSend, sizeof(LOGFONT));
			cfgPtr->SetBuffer(L"BGCHAT_RECVFONT", (unsigned char *)&g_fontRecv, sizeof(LOGFONT));
			cfgPtr->SetLong(L"BGCHAT_SENDCLR", g_clrSend);
			cfgPtr->SetLong(L"BGCHAT_RECVCLR", g_clrRecv);
			cfgPtr->SetLong(L"BGCHAT_MSGMODE", g_BeforeMsgMode);
			cfgPtr->SetLong(L"BGCHAT_SENDMODE", g_bSendMsgEnter);
			cfgPtr->SetLong(L"BGCHAT_SAVEWNDSIZE", g_bSaveWndSize);
			cfgPtr->SetLong(L"BGCHAT_WNDWIDTH", g_nWndWidth);
			cfgPtr->SetLong(L"BGCHAT_WNDHEGHT", g_nWndHeight);
			cfgPtr->SetLong(L"BGCHAT_SHOWNAMEMODE", g_nShowNameMode);
			cfgPtr->SetLong(L"BGCHAT_USERCHANGETIP", g_nUserChangeTip);
		}

		m_hTimer = ::SetTimer((HWND)m_ptrRoot->GetMainWndHandle(), 1023, 30000, &CcronModule::CheckMessage);
		
		return S_OK;

	}
	FQ_CATCH_ALL(return E_FAIL)
}

HRESULT CcronModule::OnUnload()
{
	//DeleteTimerQueueTimer(NULL, m_hTimer, INVALID_HANDLE_VALUE );
	::KillTimer((HWND)m_ptrRoot->GetMainWndHandle(), m_hTimer);
	m_hTimer = NULL;
	IFQUICommand* pUICmd = dynamic_cast<IFQUICommand* >(&m_xMenuSink);
	if(m_ptrMenu)
	{
		//m_ptrMenu->DelItem(FQ_UI_TYPE_TRAY_MENU, m_AddMenuID, pUICmd);
	}

    
	m_RootEventSink.Unadvise();
	m_RootEventSink.UnhookEvent(evt_OnUserEnter, this, &CcronModule::OnUserEnter);
	m_RootEventSink.UnhookEvent(evt_OnUserExit, this, &CcronModule::OnUserExit);
	m_RootEventSink.UnhookEvent(evt_OnBeforeRecvMsg, this, &CcronModule::OnBeforeRecvMsg);
	m_RootEventSink.UnhookEvent(evt_OnRootEvent, this, &CcronModule::OnRootEvent);
	return S_OK;
}

HRESULT CcronModule::OnConfig()
{
	
	return S_OK;
}



HRESULT CcronModule::XMenuSink::raw_OnInvoke(enum FQ_UI_TYPE Type, long Id, VARIANT Parameter)
{	
	METHOD_PROLOGUE(CcronModule, MenuSink)
	pThis->MenuOnInvoke(Type, Id, Parameter);
	return S_OK;	
}


HRESULT CcronModule::XMenuSink::raw_OnQueryState(enum FQ_UI_TYPE Type, long Id, VARIANT Parameter,
                                 BSTR * bstrText,
                                 enum FQ_UI_ITEM_STATE * State )
{
	METHOD_PROLOGUE(CcronModule, MenuSink)
	
	return S_OK;
}

HRESULT CcronModule::MenuOnInvoke(enum FQ_UI_TYPE Type, long Id, VARIANT Parameter )
{



	
	return S_OK;
}

HRESULT CcronModule::OnUserEnter(LPCTSTR userMemoName, LPCTSTR userNickName, LPCTSTR userHostName, LPCTSTR userLoginName, LPCTSTR userMemoGroupName, LPCTSTR userGroupName, LPCTSTR userIP, LPCTSTR userMAC)
{

	return S_OK;
}
HRESULT CcronModule::OnUserExit(LPCTSTR userMemoName, LPCTSTR userNickName, LPCTSTR userHostName, LPCTSTR userLoginName, LPCTSTR userMemoGroupName, LPCTSTR userGroupName, LPCTSTR userIP, LPCTSTR userMAC)
{

	return S_OK;
}

HRESULT CcronModule::OnBeforeRecvMsg(LPCTSTR Memo, LPCTSTR Host, LPCTSTR Group, LPCTSTR IP, LPCTSTR MAC, LPCTSTR sendMsg, LPCTSTR font, enum FQ_BEFORERECVMSG_RESULT *pResult)
{
	if(!g_bcron)
	{
		*pResult = FQ_BEFORERECVMSG_RESULT_NORMAL;
		return S_OK;
	}
	if(sendMsg == "")
	{
		*pResult = FQ_BEFORERECVMSG_RESULT_NORMAL;
		return S_OK;
	}

	BOOL bInitSelUser = FALSE;

	CString strRecvMsg;
	COleDateTime dt = COleDateTime::GetCurrentTime();
	CString strUserName;
	if(g_nShowNameMode & 0x1)
	{
		strUserName = Memo;
	}
	if(g_nShowNameMode & 0x10)
	{
		if(strUserName != "")
		{
			strUserName += "(" + CString(Host) + ")";
		}
		else
		{
			strUserName += Host;
		}
	}
	if(g_nShowNameMode & 0x100)
	{
		if(strUserName != "")
		{
			strUserName += "(" + CString(Group) + ")";
		}
		else
		{
			strUserName += Group;
		}
	}
	if(g_nShowNameMode & 0x1000)
	{
		if(strUserName != "")
		{
			strUserName += "(" + CString(IP) + ")";
		}
		else
		{
			strUserName += IP;
		}
	}
	if(g_nShowNameMode & 0x10000)
	{
		if(strUserName != "")
		{
			strUserName += "(" + CString(MAC) + ")";
		}
		else
		{
			strUserName += MAC;
		}
	}
	strRecvMsg.Format("%s %s\r\n  %s\r\n", strUserName, dt.Format(_T("%H:%M:%S")), sendMsg);

	if(g_BeforeMsgMode == 0)
	{
		*pResult = FQ_BEFORERECVMSG_RESULT_NORMAL;
	}
	else if(g_BeforeMsgMode == 1)
	{
		*pResult = FQ_BEFORERECVMSG_RESULT_BLOCK_ALL;
	}
	else if(g_BeforeMsgMode == 2)
	{
		*pResult = FQ_BEFORERECVMSG_RESULT_BLOCK_SAVELOG;
	}
	else if(g_BeforeMsgMode == 3)
	{
		*pResult = FQ_BEFORERECVMSG_RESULT_BLOCK_SHOWTIP;
	}
	else if(g_BeforeMsgMode == 4)
	{
		*pResult = FQ_BEFORERECVMSG_RESULT_BLOCK_SAVELOG_SHOWTIP;
	}
	else
	{
		*pResult = FQ_BEFORERECVMSG_RESULT_NORMAL;
	}
	return S_OK;
}


HRESULT CcronModule::OnRootEvent(LPCTSTR eventType, LPCTSTR Name, LPCTSTR sParam, IFQData* pData)
{
//	IFQDataPtr pFQData(pData);

	return S_OK;
}


