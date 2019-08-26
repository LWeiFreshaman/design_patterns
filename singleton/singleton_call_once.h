#ifndef _SINGLETON_CALL_ONCE__
#define _SINGLETON_CALL_ONCE__

#include <iostream>
#include <mutex>
#include <atomic>

using std::cout;
using std::endl; 
using std::mutex;
using std::atomic;

template <typename T>
class Singleton_call_once
{
public:
	const T& getValue() { return value; }
	void setValue(const T& v) { value = v; }
	~Singleton_call_once() { cout << "destruction." << endl; }
	static Singleton_call_once<T>* getInstance();
private:
	T value;
	static Singleton_call_once<T>* instance;
	static std::once_flag oc;
	Singleton_call_once() { cout << "contruction." << endl; }
};

template <typename T>
std::once_flag Singleton_call_once<T>::oc;

template <typename T>
Singleton_call_once<T>* Singleton_call_once<T>::instance = nullptr;

template <typename T>
Singleton_call_once<T>* Singleton_call_once <T>::getInstance()
{
	std::call_once(oc, [&](){ instance = new Singleton_call_once<T>;  });

	return instance;
}

#endif