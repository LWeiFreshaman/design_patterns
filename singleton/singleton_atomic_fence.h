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
	Singleton_atomic_fence<T>* tmp = instance.load(std::memory_order_relaxed);		//第一次读取
	std::atomic_thread_fence(std::memory_order_acquire);

	if (nullptr == tmp)
	{
		std::unique_lock<mutex> uniLoc(mtx);
		tmp = instance.load(std::memory_order_relaxed);			
		if (nullptr == tmp)
		{
			//这个地方，new可能被cpu重排操作变成分配内存-赋值-构造，所以此处需要一个原子操作
			tmp = new Singleton_atomic_fence<T>;	//只有这里需要保证原子操作
			std::atomic_thread_fence(std::memory_order_release);
			instance.store(tmp, std::memory_order_relaxed);		//这里不需要保证内存顺序
		}
	}

	return tmp;
}

#endif