#pragma once
#include "Channel.h"
#include <iostream>
#include "EventLoop.h"
#include "Dispatcher.h"
#include <sys/epoll.h>
#include <string>

using namespace std;
struct EventLoop;
class EpollDispatcher :public Dispatcher
{
public:
	EpollDispatcher(EventLoop* evLoop);
	~EpollDispatcher();
	//���
	int add() override;//C++11 ������������
	//ɾ��
	int remove()override;
	//�޸�
	int modify()override;
	//�¼���� ��û���¼�������
	int dispatcher(int timeout = 2)override;//��λ��s
private:
	int epollCtl(int op);
private:
	int m_epfd;//epoll���ĸ����
	epoll_event* m_events;
	const int m_maxNode = 520;
};