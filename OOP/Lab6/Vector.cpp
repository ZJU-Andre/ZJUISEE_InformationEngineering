#include "Vector.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory.h>
using namespace std;

int main()
{
	Vector <int> v;
	srand(time(NULL));
	v.inflate(10);
	try{	
		for (int i = 0; i != v.size(); ++i)
			v[i] = rand() % 10000;
		Vector<int> vc = v;
		cout<<"Vec 1\tVec 2"<<endl;
		for (int i = 0; i != 11; ++i) {
			cout<<v[i]<<'\t'<<vc[i]<<endl;
		}
	} catch (IndexOutofBounds &e){
		cout<<endl;
		cout<<e.what()<<endl;
	}
	return 0;
}

template <class T>
Vector<T>::Vector()
{
	m_nSize = 0;
	m_pElements = NULL;
}

template <class T>
Vector<T>::Vector(int size)
{
	m_nSize = size;
	m_pElements = new T[m_nSize];
}

template <class T>
Vector<T>::Vector(const Vector &r)
{
	m_nSize = r.m_nSize;
	m_pElements = new T[m_nSize];

	memcpy(m_pElements, r.m_pElements, sizeof(T) * m_nSize);
}

template <class T>
Vector<T>::~Vector()
{
	delete [] m_pElements;
	m_nSize = 0;
}

template <class T>
int Vector<T>::size()
{
	return m_nSize;
}

template <class T>
int Vector<T>::inflate(int addSize)
{
	T* temp = m_pElements;
	m_pElements = new T[m_nSize + addSize];
	memcpy(m_pElements, temp, sizeof(T) * m_nSize);
	delete [] temp;
	m_nSize += addSize;
}

template <class T>
T& Vector<T> :: operator[] (int index) throw(IndexOutofBounds)
{
	if (index < 0 || index >= m_nSize)
		throw IndexOutofBounds("Vector[] out of range");
	return m_pElements[index];
}

