#define _CRT_SECURE_NO_WARNINGS 1

#include"HashBucket.h"
#include<assert.h>

template<class K, class V, class FuncModle>
HashBucket<K, V, FuncModle>::HashBucket()
	:_size(0)
{}
template<class K, class V, class FuncModle>
HashBucket<K, V, FuncModle>::HashBucket(const HashBucket<K, V, FuncModle>& h)
{
	_table.resize(h._table.size());
	_size = h._size;
	for (size_t i = 0; i < h._table.size(); ++i)
	{
		if (h._table[i])
		{
			Node* cur = h._table[i];
			Node* newcur = new Node(cur->_key, cur->_value);
			_table[i] = newcur;
			cur = cur->_next;
			while (cur)
			{
				Node* node = new Node(cur->_key, cur->_value);
				newcur->_next = node;
				newcur = newcur->_next;
				cur = cur->_next;
			}
		}
	}
}
template<class K, class V, class FuncModle>
HashBucket<K, V, FuncModle>& HashBucket<K, V, FuncModle>::
operator=(HashBucket<K, V, FuncModle> h)
{
	swap(_table, h._table);
	swap(_size, h._size);
}
template<class K, class V, class FuncModle>
size_t  HashBucket<K, V, FuncModle>::_HashFunc(const K& key, size_t mod)
{
	return FuncModle()(key) % mod;
}

template<class K, class V, class FuncModle>
size_t  HashBucket<K, V, FuncModle>::_GetNextPrime(size_t size)
{
	const int _PrimeSize = 28;
	//Tabla de números primos, algoritmo hash módulo números primos son los mejores
	static const unsigned long _PrimeList[_PrimeSize] =
	{
		53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};
	for (int i = 0; i < _PrimeSize; ++i)
	{
		if (_PrimeList[i] > size)
			return _PrimeList[i];
	}
	assert(false);
	return 4294967291ul;
}
template<class K, class V, class FuncModle>
void HashBucket<K, V, FuncModle>::_CheckExpand()
{
	if (_size == _table.size())
	{
		size_t newsize = _GetNextPrime(_size);//Tome el siguiente número primo de la tabla de números primos
		if (newsize == _size)
			return;
		vector<Node*> newtable;
		newtable.resize(newsize);
		for (size_t i = 0; i < _size; ++i)
		{
			size_t index = _HashFunc(_table[i]->_key, newsize);
			if (_table[i])
			{
				Node* head = _table[i];//guardar el nodo principal
				newtable[index] = head;//Retire el primer puntero del vector como el nodo principal de la nueva tabla
				_table[i] = _table[i]->_next;
				while (_table[i])//Elije nodos a su vez
				{
					Node* tmp = _table[i];
					_table[i] = _table[i]->_next;
					head->_next = tmp;
					head = head->_next;
				}
			}
			else
				newtable[index] = NULL;
			_table[i] = NULL;
		}
		swap(_table, newtable);
	}
}
template<class K, class V, class FuncModle>
bool HashBucket<K, V, FuncModle>::Insert(const K& key, const V& value)
{
	_CheckExpand();
	size_t index = _HashFunc(key, _table.size());
	Node* tmp = new Node(key, value);//Debe usar nuevo fuera del nodo
	if (_table[index] == NULL)
	{
		_table[index] = tmp;
	}
	else
	{
		//Si no es NULL, use el método de inserción de encabezado para insertar un nuevo nodo
		tmp->_next = _table[index];
		_table[index] = tmp;
	}
	_size++;
	return true;
}


template<class K, class V, class FuncModle>
HashBucketNode<K, V>* HashBucket<K, V, FuncModle>::Find(const K& key)
{
	size_t index = _HashFunc(key, _table.size());
	while (_table[index])
	{
		if (_table[index]->_key == key)
		{
			return _table[index];
		}
		_table[index] = _table[index]->_next;
	}
	return NULL;
}
template<class K, class V, class FuncModle>
bool HashBucket<K, V, FuncModle>::Remove(const K& key)
{
	//No se puede encontrar con buscar y luego eliminar.
	size_t index = _HashFunc(key, _table.size());
	if (_table[index] == NULL)
		return false;
	Node* cur = _table[index];
	if (cur->_key == key)
	{
		Node* del = cur;
		_table[index] = cur->_next;
		delete del;
		_size--;
		return true;
	}
	else
	{
		Node* prev = NULL;
		while (cur)
		{
			if (cur->_key == key)
			{
				prev->_next = cur->_next;
				delete cur;
				_size--;
				return true;
			}
			prev = cur;
			cur = cur->_next;
		}
		return false;
	}
}
template<class K, class V, class FuncModle>
void HashBucket<K, V, FuncModle>::Print()
{
	for (size_t i = 0; i < _table.size(); i++)
	{
		if (_table[i])
		{
			printf("Table[%d]:", i);
			Node* cur = _table[i];
			while (cur)
			{
				cout << cur->_key << "-" << cur->_value << "->";
				cur = cur->_next;
			}

		}
		else
		{
			printf("Table[%d]:", i);
		}
		cout << "NULL" << endl;
	}
}