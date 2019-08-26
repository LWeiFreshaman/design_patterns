#ifndef _SINGLETON_ATOMIC_FENCE__
#define _SINGLETON_ATOMIC_FENCE__

#include <iostream>
#include <mutex>
#include <atomic>

using std::cout;
using std::endl; 
using std::mutex;
using std::atomic;

template <typename T>
class Singleton_atomic_fence
{
public:
	const T& getValue() { return value; }
	void setValue(const T& v) { value = v; }
	~Singleton_atomic_fence() { cout << "destruction." << endl; }
	static Singleton_atomic_fence <T>* getInstance();
private:
	T value;
	static atomic<Singleton_atomic_fence<T>*> instance;
	static mutex mtx;
	Singleton_atomic_fence() { cout << "contruction." << endl; }
};

template <typename T>
atomic<Singleton_atomic_fence<T>*> Singleton_atomic_fence<T>::instance = nullptr;

template <typename T>
mutex Singleton_atomic_fence<T>::mtx;

template <typename T>
Singleton_atomic_fence<T>* Singleton_atomic_fence <T>::getInstance()
{
	Singleton_atomic_fence<T>* tmp = instance.load(std::memory_order_relaxed);		//��һ�ζ�ȡ
	std::atomic_thread_fence(std::memory_order_acquire);

	if (nullptr == tmp)
	{
		std::unique_lock<mutex> uniLoc(mtx);
		tmp = instance.load(std::memory_order_relaxed);			
		if (nullptr == tmp)
		{
			//����ط���new���ܱ�cpu���Ų�����ɷ����ڴ�-��ֵ-���죬���Դ˴���Ҫһ��ԭ�Ӳ���
			tmp = new Singleton_atomic_fence<T>;	//ֻ��������Ҫ��֤ԭ�Ӳ���
			std::atomic_thread_fence(std::memory_order_release);
			instance.store(tmp, std::memory_order_relaxed);		//���ﲻ��Ҫ��֤�ڴ�˳��
		}
	}

	return tmp;
}

#endif