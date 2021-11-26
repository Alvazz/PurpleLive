#pragma once
/*
	������ Ŭ����
	�ñ׳� ������ ���
*/

#include "../../CLCWebsocketClient/inc/CLCWebsocketClient.h"

#include <string>
#include "TransactionId.hpp"
#include "StructureDefines.h"
#include "json/json.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib, "Winmm.lib")

#define DEFAULT_SIGNAL_KEEPALIVE_INTERVAL 30000

using namespace std;

const string kSignalClientErrorDomain = "SignalClient";

enum MediaStatus {
	Inactive,
	SendReceive,
	SendOnly,
	ReceiveOnly,
};

class MediaRoom;
struct IceServerInfo;

class SignalClient : public CLCWebsocketClient
{
public:
	SignalClient(MediaRoom* pOwner);
	~SignalClient();

	bool	JoinRoom(const string& signalServerURL, const string& authKey);
	void	LeaveRoom(const string& authKey);
	void	SdpExchange(const string authKey, const string peerID, const string type, const string sdp);
	void	IceCandidate(const string peerID, const string candidate, const int sdpMLineIndex, const string& sdpMid);
	void	SendIceConnectionState(const string& peerID, int state);
	void	Close();

	bool	_Connect(const string& url, const string& authKey); // ���� �ʱ�ȭ �� Signal ������ ����
protected:
	void	SendMsg(const string& msg);

	virtual void	OnClose(const string& reason, int errorCode) override;
	virtual int		OnMessage(const string& strMsg) override;
	int		_OnMessage_InstructionEvent(const Json::Value& jMsg);
	int		_OnMessage_InfoEvent(const Json::Value& jMsg);

	void			SendKeepAlive();
	static void CALLBACK KeepAliveProc(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

	void	StartKeepAliveTimer();
	void	StopKeepAliveTimer();

	string	m_signalServerURL;
	string	m_authKey;

	CTransactionId		m_TransactionIDGenerator;	// transactionID�� �����ϴ� �����߻���

	short				m_nKeepAliveIntervalms;
	UINT				m_nTimerID;

	PeerInfo			m_stPeerInfo;
	MediaRoom*			m_pOwner;	// �������� ������ MediaRoom ��ü ������
};
