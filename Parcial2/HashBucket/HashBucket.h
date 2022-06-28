#pragma once

#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<class T>
struct DefaultFunc
{
	size_t operator()(const T& data)
	{
		return (size_t)data;
	}
};

struct StringFunc
{
	size_t operator()(const string& str)
	{
		size_t sum = 0;
		for (size_t i = 0; i < str.size(); ++i)
		{
			sum += str[i];
		}
		return sum;
	}
};

template<class K, class V>
struct HashBucketNode
{
	K _key;
	V _value;
	HashBucketNode<K, V>* _next;
	HashBucketNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _next(NULL)
	{}
};

template<class K, class V, class FuncModle = DefaultFunc<K>>
class HashBucket
{
	typedef HashBucketNode<K, V> Node;
public:
	HashBucket();
	//~HashBucket();
	HashBucket(const HashBucket<K, V, FuncModle>& h);
	HashBucket<K, V, FuncModle>& operator=(HashBucket<K, V, FuncModle> h);
	bool Insert(const K& key, const V& value);
	Node* Find(const K& key);
	bool Remove(const K& key);
	//bool Alter(const K& key);//Implementado con Buscar
	void Print();
protected:
	void _CheckExpand();
	size_t _GetNextPrime(size_t size);
	size_t _HashFunc(const K& key, size_t mod);
protected:
	vector<Node*> _table;
	size_t _size;
};