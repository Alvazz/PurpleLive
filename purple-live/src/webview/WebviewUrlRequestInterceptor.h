#pragma once

#include "WebConfig.h"
#include <QApplication>
#include <QWebEngineProfile>
#include <QWebEngineView>
#include <QWebEngineUrlRequestInterceptor>
#include <QDebug>
#include "VideoChatApp.h"
class WebviewUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT
public:
	using QWebEngineUrlRequestInterceptor::QWebEngineUrlRequestInterceptor;
	
    void interceptRequest(QWebEngineUrlRequestInfo &info)
    {
/*
Accept-Language	������(���)	ko-KR, en-US, zh-TW, zh-CN, ja-JP
X-LauncherId	Lime-Device-Id ���� �뵵	
X-UserId		���� �α����� ������� NP UserId	
User-Agent		�������� User-Agent : PurpleLive/[version] (Windows)
*/
		info.setHttpHeader("Accept-Language", App()->GetLocalLanguage().toStdString().c_str());
		info.setHttpHeader("X-LauncherId", App()->GetDeviceId().c_str());
		info.setHttpHeader("X-UserId", "");
    }
};