#pragma once

#include <list>
#include <string>
class FQMessage;
class MessageManager
{
public:
	static MessageManager* GetInstance();
	MessageManager(void);
	~MessageManager(void);

	void Save(char* pszFileName);
    void Load(char* pFileName, bool exclusive=true);
	void AddMessage(const char* pReceiver, const char* pTime, const char* pMessage);
	void SetRootPtr(IFQRootPtr);
	void SendMessages();
private:
	static MessageManager* m_pManager;
	std::list<FQMessage*> m_vecMessages;
	IFQRootPtr m_pRoot;
protected:
	bool getBuddy(IFQBuddyCollectionPtr pBuddys, const char* szBuddyName, std::string& szIP);

};
