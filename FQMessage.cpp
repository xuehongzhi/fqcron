#include "stdafx.h"
#include "FQMessage.h"

FQMessage::FQMessage(const char* pReceiver, const char* pTime, const char* pMessage)
{
	m_sReceiver = pReceiver;
	m_sTime = pTime;
	m_sMessage = pMessage;
}

FQMessage::~FQMessage(void)
{
}

std::string FQMessage::GetFormated()
{
	return m_sReceiver + "," + m_sTime + "," + m_sMessage;
}

bool FQMessage::operator == (const FQMessage anthor)
{
	return m_sMessage==anthor.m_sMessage && m_sReceiver == anthor.m_sReceiver && m_sTime == m_sTime;
}

bool FQMessage::KeepedForXhours(int nHours)
{
	COleDateTime now = COleDateTime::GetCurrentTime();
	COleDateTime dtMessage = COleDateTime();
	dtMessage.ParseDateTime(m_sTime.c_str());
	if (dtMessage.GetStatus() == COleDateTime::invalid){
		TRACE("%s's time format is valid:(%s)", m_sReceiver.c_str(), m_sTime.c_str());
		return true; //no valid 
	}
    COleDateTimeSpan dtSpan = now-dtMessage;
	return dtSpan.GetHours() > nHours;
}

bool FQMessage::Send(IFQRootPtr pRoot, const char* szIP) 
{
	//if really send the messgage or message is keeped for about 1 day then consider it to be send
	if (KeepedForXhours(1)){
		return true;
	}
	FQ_TRY
	{
		HRESULT hr = pRoot->SendBuddyMessage(_bstr_t(szIP), _bstr_t(m_sMessage.c_str()), _bstr_t(""));
		if (SUCCEEDED(hr)){
			return true;
		}
	}
	FQ_CATCH_ALL(return false);
}