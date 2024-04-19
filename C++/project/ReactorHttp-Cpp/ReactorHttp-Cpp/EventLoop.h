#pragma once
#include "Dispatcher.h"
#include "Channel.h"
#include <thread>
#include <queue>
#include <map>
#include <mutex>
using namespace std;


//处理结点中channel的方式
enum class ElemType:char { ADD, DELETE, MODIFY };
//定义任务队列的结点
struct ChannelElement
{
	ElemType type;//如何处理结点中的channel
	Channel* channel;
};
class Dispatcher;

class EventLoop
{
public:
	EventLoop(); 
	EventLoop(const string threadName);
	~EventLoop();
	//启动反应堆模型 实际就是调用监听函数进行监听 epoll_wait
	int run();
	//处理被激活的文件fd     反应堆启动后，会检测到被激活的fd
	int eventActivate(int fd, int event);
	//添加任务到任务队列
	int addTask(Channel* channel, ElemType type);
	//处理任务队列中的任务
	int processTaskQ();
	//处理dispatcher中的结点
	int add(Channel* channel);
	int remove(Channel* channel);
	int modify(Channel* channel);
	//释放channel
	int freeChannel(Channel* channel);
	int readMessage();
	//返回线程id
	inline thread::id getThreadID() {
		return m_threadID;
	}
private:
	void taskWakeup();
private:
	bool m_isQuit;
	Dispatcher* m_dispatcher;//该指针指向子类的实例 epoll poll select
	//任务队列
	queue<ChannelElement*> m_taskQ;
	//map
	map<int, Channel*> m_channelMap;
	//线程id,name
	thread::id m_threadID;
	string m_threadName;
	mutex m_mutex;
	int m_socketPair[2];//存储本地通信的fd，用于主线程给子线程的eventloop发消息使其唤醒
	//然后处理任务队列，否则可能会由于epoll等阻塞而不处理任务队列(包括建立新连接任务)
};

