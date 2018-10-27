#pragma once
#include <string>
class FQMessage
{
	friend class MessageManager;
public:
	FQMessage(const char* pReceiver, const char* pTime, const char* pMessage);
	~FQMessage(void);

	bool KeepedForXhours(int nHours);
	bool Send(IFQRootPtr pRoot, const char* szIP);
	std::string GetFormated();

	bool operator == (const FQMessage anthor);
private:
	std::string m_sReceiver;
	std::string m_sTime;
	std::string m_sMessage;
};
