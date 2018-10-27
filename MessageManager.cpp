#include "stdafx.h"
#include <algorithm>
#include "fqmessage.h"
#include "messagemanager.h"

MessageManager* MessageManager::m_pManager = NULL;
MessageManager::MessageManager(void)
{
}

MessageManager::~MessageManager(void)
{
	m_vecMessages.clear();
}

MessageManager* MessageManager::GetInstance()
{
	if(m_pManager==NULL)
	{
		m_pManager = new MessageManager();
	}
	return m_pManager;
}


void MessageManager::AddMessage(const char* pReceiver, const char* pTime, const  char* pMessage)
{
	if(pReceiver==NULL || strlen(pReceiver) == 0)
	{
		return;
	}

	if(pTime==NULL || strlen(pTime) == 0 )
	{
		return;
	}

	if(pMessage==NULL || strlen(pMessage) == 0 )
	{
		return;
	}

	m_vecMessages.push_back(new FQMessage(pReceiver, pTime, pMessage));
}

void MessageManager::SetRootPtr(IFQRootPtr rtptr)
{
	m_pRoot = rtptr;
}

void MessageManager::Load(char* pFileName, bool exclusive)
{
	if(pFileName==NULL || strlen(pFileName) == 0)
	{
		return;
	}

	try
	{
		int of = CFile::modeReadWrite | CFile::typeText;
		if(exclusive)
		{
			of |= CFile::shareExclusive;
		}

		CStdioFile f3( pFileName, of );
		//message format: receiver,time, message 
		CString szLine;
		while(f3.ReadString(szLine))
		{
			int nStart = 0;
			CString szReceiver, szTime, szMessage;
			szReceiver = szLine.Tokenize(",",  nStart);
			szTime = szLine.Tokenize(",",  nStart);
			szMessage = szLine.Tokenize(",",  nStart);
			TRACE(_T("mesage item loaded = %s,%s,%s\n"), (LPCSTR)szReceiver, (LPCSTR)szTime, (LPCSTR)szMessage);
			AddMessage((LPCSTR)szReceiver, (LPCSTR)szTime, (LPCSTR)szMessage);
		}
		f3.SetLength(0);
		f3.Close();
	}
	catch(CFileException* pe)
	{
		TRACE(_T("File could not be opened, cause = %d\n"),
			pe->m_cause);
		pe->Delete();
	}
	catch(CInvalidArgException* pe)
	{
		TRACE(_T("file args invalid"));
		pe->Delete();
	}
}


void MessageManager::SendMessages()
{
	IFQRootPtr pFQManager = m_pRoot;
	//refresh  feiq
	if(!pFQManager)
	{
		return;
	}

	pFQManager->RefreshBuddys();
	IFQBuddyCollectionPtr pBuddys = pFQManager->GetOnlineBuddys();
	if(!pBuddys)
	{
		return;

	}
	std::list<FQMessage*>::iterator it = m_vecMessages.begin();
	std::list<FQMessage*> vecSucMsg;
	
	for (; it!=m_vecMessages.end(); ++it)
	{
		std::string szIP;
		bool r = getBuddy(pBuddys,(*it)->m_sReceiver.c_str(), szIP);
		if(r && (*it)->Send(pFQManager, szIP.c_str())){
			vecSucMsg.push_back((*it));
		}
	}
    
	for(it=vecSucMsg.begin(); it!=vecSucMsg.end(); ++it)
	{
		m_vecMessages.remove((*it));
	}

}

bool MessageManager::getBuddy(IFQBuddyCollectionPtr pBuddys, const char* pszBuddyName, std::string& szIP)
{

	for(int i=0; i<pBuddys->GetCount(); ++i)
	{
		IFQBuddyPtr pBuddy = pBuddys->GetItem(i);
		
		CString szLoginName = (char*)(pBuddy->GetName());
		szLoginName.MakeLower();
	
	    if (szLoginName.Find(strlwr(const_cast<char *>(pszBuddyName))) >= 0){
			szIP = (char *)pBuddy->GetIPValue();
			return true;
		}

	}
	return false;
}


void MessageManager::Save(char* pszFileName)
{
	if (pszFileName == NULL || strlen(pszFileName) == 0)
	{
		return;
	}

	try
	{
		int of = CFile::modeCreate | CFile::modeWrite | CFile::typeText;
		CStdioFile f3(pszFileName, of);
		//message format: receiver,time, message 
		std::list<FQMessage*>::iterator it = m_vecMessages.begin();
		for (; it != m_vecMessages.end(); ++it)
		{
			f3.WriteString((*it)->GetFormated().c_str());
		}
		f3.Close();
	}
	catch (CFileException* pe)
	{
		TRACE(_T("File could not be opened, cause = %d\n"),
			pe->m_cause);
		pe->Delete();
	}
	catch (CInvalidArgException* pe)
	{
		TRACE(_T("file args invalid"));
		pe->Delete();
	}

}
