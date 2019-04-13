#ifndef _SINGLETON_THREAD__
#define _SINGLETON_THREAD__

#include <iostream>
#include <mutex>

using std::cout;
using std::endl; 
using std::mutex;

template <typename T>
class Singleton_thread
{
public:
	const T& getValue() { return value; }
	void setValue(const T& v) { value = v; }
	~Singleton_thread() { cout << "destruction." << endl; }
	static Singleton_thread <T>* getInstance();
private:
	T value;
	static Singleton_thread<T>* instance;
	static mutex mtx;
	Singleton_thread() { cout << "contruction." << endl; }
};

template <typename T>
Singleton_thread<T>* Singleton_thread<T>::instance = nullptr;

template <typename T>
mutex Singleton_thread<T>::mtx;

template <typename T>
Singleton_thread<T>* Singleton_thread <T>::getInstance()
{
	if (!instance)
	{
		mtx.lock();
		if (!instance)
		{
			instance = new Singleton_thread<T>;
		}
		mtx.unlock();
	}

	return instance;
}

#endif