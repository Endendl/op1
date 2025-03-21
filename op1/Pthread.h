#pragma once
#include "init_tool.h"
#include <thread>
#include <mutex>
const int m = 4;//线程数

bool PthreadStart = true;
std::counting_semaphore<m> sem_thread(0); // 用于阻塞子线程
std::counting_semaphore<m> sem_main(0);   // 用于阻塞主线程
std::atomic<int> Pends = 0;
class fp//进度指针，记录总体进度
{
public:
	fp(GameObject& _obj) {
		obj = &_obj;
		homeobj = &_obj;
	};
	~fp() {};
	void fpnext() {
		if (obj == linknode)
		{
			fpenter();
			return;
		}
		obj = obj->nextOBJCT;
	}
	void fpenter() {//回归队列开头 1切换绘制
		obj = homeobj;
		mode = !mode;
	}
	bool mode = 1; //1切换update, 0绘制
	GameObject* getobj() {
		std::unique_lock<std::mutex> lock(mtx); // 加锁
		GameObject* temp = obj;
		fpnext();
		return temp;
	}
private:
	GameObject* obj = nullptr;
	GameObject* homeobj = nullptr;
	std::mutex mtx;// 互斥锁
};
fp* objp;//
class Pthread
{
public:
	Pthread(int _Species) {//创建，输入队列头部
		
		Species = _Species;
		t = new std::thread(&Pthread::run, this, 1, Species);
	}

	// 禁止复制和移动
	Pthread(const Pthread&) = delete;
	Pthread& operator=(const Pthread&) = delete;
	Pthread(Pthread&&) = delete;
	Pthread& operator=(Pthread&&) = delete;

	~Pthread() {
		if (t->joinable()) {
			t->join();
		}
	}
	GameObject* obj;


	void run(int is, int Species) {
		while (true)
		{
			while (objp->mode) {
				obj = objp->getobj();
				obj->Pupdate();
			}
			// 通知主线程可以运行 runupdate()释放一个信号量
			Pends++;//叠加
			sem_main.release();
			//std::cout << "Thread " << Species << ": sem_main.release()" << std::endl;
			// 等待主线程完成 runupdate() 抓取一个信号量
			sem_thread.acquire();
			//std::cout << "Thread " << Species << ": sem_thread.acquire()" << std::endl;

		}
		return;
	}
	int Species;
	std::thread* t;
	bool Pend = false; // 线程退出标志
	//std::atomic<bool> Pend; // 线程退出标志
	std::mutex mtx; // 互斥锁
	std::condition_variable cv; // 条件变量

};

int ptsum;
std::vector<std::unique_ptr<Pthread>> pt;

void sem_main_acquire() {
	if (PthreadStart) {
		for (int i = 0; i < m; i++) {
			sem_main.acquire();
		}
	}
}

void sem_thread_release() {
	if (PthreadStart) {
		for (int i = 0; i < m; ++i) {
			sem_thread.release();
		}
	}
	
}