#ifndef _SINGLETON_ATOMIC__
#define _SINGLETON_ATOMIC__

#include <iostream>
#include <mutex>
#include <atomic>

using std::cout;
using std::endl; 
using std::mutex;
using std::atomic;

template <typename T>
class Singleton_atomic
{
public:
	const T& getValue() { return value; }
	void setValue(const T& v) { value = v; }
	~Singleton_atomic() { cout << "destruction." << endl; }
	static Singleton_atomic<T>* getInstance();
private:
	T value;
	static atomic<Singleton_atomic<T>*> instance;
	static mutex mtx;
	Singleton_atomic() { cout << "contruction." << endl; }
};

template <typename T>
atomic<Singleton_atomic<T>*> Singleton_atomic<T>::instance = nullptr;

template <typename T>
mutex Singleton_atomic<T>::mtx;

template <typename T>
Singleton_atomic<T>* Singleton_atomic <T>::getInstance()
{
	//���ǰ�atomic_thread_fence�����Ƶ�ԭ�ӱ�������
	Singleton_atomic<T>* tmp = instance.load(std::memory_order_acquire);		//��һ�ζ�ȡ
	//std::atomic_thread_fence(std::memory_order_acquire);

	if (nullptr == tmp)
	{
		//tmp = instance.load(std::memory_order_acquire);
		std::unique_lock<mutex> uniLoc(mtx);
		tmp = instance.load(std::memory_order_relaxed);		//����ط���������Ƶ������棬
		if (nullptr == tmp)
		{
			//����ط���new���ܱ�cpu���Ų�����ɷ����ڴ�-��ֵ-���죬���Դ˴���Ҫһ��ԭ�Ӳ���
			tmp = new Singleton_atomic<T>;	//ֻ��������Ҫ��֤ԭ�Ӳ���
			//std::atomic_thread_fence(std::memory_order_release);
			instance.store(tmp, std::memory_order_release);		//���ﲻ��Ҫ��֤�ڴ�˳��
		}
	}

	return tmp;
}

#endif