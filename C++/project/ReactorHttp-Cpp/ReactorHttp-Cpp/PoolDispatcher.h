#pragma once
#include "Channel.h"
#include <iostream>
#include "EventLoop.h"
#include "Dispatcher.h"
#include <poll.h>
#include <string>

using namespace std;
class PollDispatcher :public Dispatcher
{
public:
	PollDispatcher(EventLoop* evLoop);
	~PollDispatcher();
	//���
	int add() override;//C++11 ������������
	//ɾ��
	int remove()override;
	//�޸�
	int modify()override;
	//�¼���� ��û���¼�������
	int dispatcher(int timeout = 2)override;//��λ��s

private:
	int m_maxfd;
	struct pollfd* m_fds;
	const int m_maxNode = 1024;
};