#ifndef _SINGLETON_H__
#define _SINGLETON_H__

#include <iostream>

template <typename T>
class Singleton
{
public:
	static Singleton<T>& getInstance() { return singleton; };
	void setValue(const T& v) { value = v; }
	const T& getValue() { return value; }
	~Singleton() { std::cout << value <<  "singleton destruct" << std::endl; }
	
private:
	T value;
	Singleton() { std::cout << "singleton construct" << std::endl; }
	static Singleton<T> singleton;
};

template<typename T> 
Singleton<T> Singleton<T>::singleton;

#endif
