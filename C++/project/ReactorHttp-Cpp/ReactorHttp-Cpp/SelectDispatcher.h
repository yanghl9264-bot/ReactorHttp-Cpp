#pragma once
#include "Channel.h"
#include <iostream>
#include "EventLoop.h"
#include "Dispatcher.h"
#include <sys/epoll.h>
#include <string>

using namespace std;
struct EventLoop;
class SelectDispatcher :public Dispatcher
{
public:
	SelectDispatcher(EventLoop* evLoop);
	~SelectDispatcher();
	//���
	int add() override;//C++11 ������������
	//ɾ��
	int remove()override;
	//�޸�
	int modify()override;
	//�¼���� ��û���¼�������
	int dispatcher(int timeout = 2)override;//��λ��s
private:
	void setFdSet();
	void clearFdSet();
private:
	fd_set m_readSet;
	fd_set m_writeSet;
	const int m_maxSize = 1024;
};