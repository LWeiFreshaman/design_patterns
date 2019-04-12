#ifndef _SINGLETON_POINTER_H__
#define _SINGLETON_POINTER_H__

#include <iostream>
#include <memory>

using std::shared_ptr;
using std::make_shared;

/******************************************************

ģ��+ָ��
�ڴ����δʵ�֣�gc���ṹ��

******************************************************/

template <class T>
class Singleton_pointer;

template <typename T>
class Gc
{
public:
	Gc() { std::cout << "gc construction." << std::endl; }
	~Gc() 
	{ 
		std::cout << "gc destruction." << std::endl;

		if (Singleton_pointer<T>::instance)
		{
			delete Singleton_pointer<T>::instance;
		}
	}
};

template <class T>
class Singleton_pointer
{
public:
	static Singleton_pointer<T>* getInstance() 
	{ 
		if (!instance)
			instance = new Singleton_pointer<T>;

		return instance;
	}
	~Singleton_pointer() { std::cout << "destruction." << std::endl; }
	void setValue(const T& v) { value = v; }
	const T& getValue() { return value; }

private:
	T value;
	static Singleton_pointer<T> *instance;
	static Gc<T> gc;
	Singleton_pointer() { std::cout << "construction." << std::endl; }
};

template <class T>
Singleton_pointer<T>* Singleton_pointer<T>::instance = nullptr;

template <class T>
Gc<T> Singleton_pointer<T>::gc;


/******************************************************

ָ��ʵ��

******************************************************/

class Singleton_pointer
{
public:
	static Singleton_pointer* getInstance() 
	{ 
		if (!instance)
			instance = new Singleton_pointer;

		return instance;
	}
	~Singleton_pointer() { std::cout << "destruction." << std::endl; }
	void setValue(const int& v) { value = v; }
	const int& getValue() { return value; }

	struct Gc
	{
		Gc() { std::cout << "gc construction." << std::endl; }
		~Gc() 
		{ 
			std::cout << "gc destruction." << std::endl;

			if (Singleton_pointer::instance)
			{
				delete Singleton_pointer::instance;
			}
		}
	};

private:
	int value;
	static Singleton_pointer *instance;
	static Gc gc;
	Singleton_pointer() { std::cout << "construction." << std::endl; };	
};

Singleton_pointer* Singleton_pointer::instance = nullptr;

typename Singleton_pointer::Gc Singleton_pointer::gc;

/******************************************************

ģ��+����ָ��
���Ի����ڴ�

******************************************************/

template <typename T>
class Singleton_sp
{
public:
	~Singleton_sp() { std::cout << "destruction." << std::endl; }
	void setValue(const T& v) { value = v; }
	const T& getValue() { return value; }
	static shared_ptr<Singleton_sp<T>> getInstance() 
	{
		return singleton; 
	}
private:
	T value;
	static shared_ptr<Singleton_sp<T>> singleton;
	Singleton_sp(const Singleton_sp<T>& rhs) {  }
	Singleton_sp() { std::cout << "construction." << std::endl; }
};

template <typename T>
shared_ptr<Singleton_sp<T>> Singleton_sp<T>::singleton(new Singleton_sp<T>);

#endif