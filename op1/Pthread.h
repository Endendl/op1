#pragma once
#include "init_tool.h"
#include <thread>
#include <mutex>
const int m = 4;//�߳���

bool PthreadStart = true;
std::counting_semaphore<m> sem_thread(0); // �����������߳�
std::counting_semaphore<m> sem_main(0);   // �����������߳�
std::atomic<int> Pends = 0;
class fp//����ָ�룬��¼�������
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
	void fpenter() {//�ع���п�ͷ 1�л�����
		obj = homeobj;
		mode = !mode;
	}
	bool mode = 1; //1�л�update, 0����
	GameObject* getobj() {
		std::unique_lock<std::mutex> lock(mtx); // ����
		GameObject* temp = obj;
		fpnext();
		return temp;
	}
private:
	GameObject* obj = nullptr;
	GameObject* homeobj = nullptr;
	std::mutex mtx;// ������
};
fp* objp;//
class Pthread
{
public:
	Pthread(int _Species) {//�������������ͷ��
		
		Species = _Species;
		t = new std::thread(&Pthread::run, this, 1, Species);
	}

	// ��ֹ���ƺ��ƶ�
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
			// ֪ͨ���߳̿������� runupdate()�ͷ�һ���ź���
			Pends++;//����
			sem_main.release();
			//std::cout << "Thread " << Species << ": sem_main.release()" << std::endl;
			// �ȴ����߳���� runupdate() ץȡһ���ź���
			sem_thread.acquire();
			//std::cout << "Thread " << Species << ": sem_thread.acquire()" << std::endl;

		}
		return;
	}
	int Species;
	std::thread* t;
	bool Pend = false; // �߳��˳���־
	//std::atomic<bool> Pend; // �߳��˳���־
	std::mutex mtx; // ������
	std::condition_variable cv; // ��������

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