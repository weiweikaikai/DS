/*************************************************************************
	> File Name: HashTable.cpp
	> Author: wk
	> Mail: 18402927708@163.com
	> Created Time: Tue 05 Jul 2016 02:29:59 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;
 
template<class K,class V>
struct HashTableNode
{
   HashTableNode(const K&_key,const V&_value):key(_key),value(_value),next(NULL)
	{}
    HashTableNode()
	{}

	K key;
	V value;
	HashTableNode<K,V> *next;
};


struct  hash
{
	public:
	 size_t operator() (char *str)
	  {
	     unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
         unsigned int hash = 0;
 
            while (*str)
         {
           hash = hash * seed + (*str++);
         }
 
        return (hash & 0x7FFFFFFF);
	 }
	  size_t operator()(size_t num)
	  {
	    return num;
	  }
}hash;

template<class K,class V>
class HashTable
{
     typedef HashTableNode<K,V> Node;
	 public:
		 HashTable():capacity(0)
	    {
	        tables.resize(GetPrimeSize());
	    }

       bool insert(const K&key,const V&value)
	    {
	         CheckCapacity();
			 size_t index = HashFun(key,tables.size());
			 Node* cur = tables[index];

			 while(cur)
			{
			    if(cur->key == key)
				{
				   return false;
				}
				cur=cur->next;
			}
			Node* newNode = new Node(key,value);

			//头插
             newNode->next=tables[index];
			 tables[index]=newNode;
			 capacity++;
			 return true;
	    }
      Node* Find(const K& key)
	  {
		size_t index = HashFun(key, tables.size());
		Node* cur = tables[index];
		while(cur)
		{
			if(cur->key == key)
			{
				return cur;
			}
			cur = cur->next;
		}
		return NULL;
	 }
	 bool Remove(const K&key)
	 {
	      size_t index = HashFun(key,tables.size());
		  Node*cur = tables[index];
		  Node*prev = cur;

		  while(cur)
		 {
			  prev=cur;
		    if(cur->key == key)
			 {
			     if(cur == tables[index])
				 {
				   tables[index]=cur->next;
				 }
				 else
				 {
				   prev->next = cur->next;
				 }
				 delete cur;
				 cur == NULL;
				 --capacity;
				 return true;
			 }
			 cur=cur->next;
		  }
		  return false;
	 }
     protected:

		 void CheckCapacity()
	      {
		     if(tables.size() == capacity) //满了就直接   负载因子默认是1
			  {
			     size_t newsize = GetPrimeSize();
				 vector<Node*> newTables;
				 newTables.resize(newsize);
				 for(size_t i=0;i<tables.size();++i)
				  {
				    Node* cur = tables[i];
					while(cur)
					  {
					   Node* tmp = cur;
					   cur = cur->next;

					   size_t index = HashFun(tmp->key,newsize);

					   //头插元素
					   tmp->next = newTables[index];
					   newTables[index]=tmp;
					  }
                     tables[i]==NULL;
				   }
				   tables.swap(newTables);
			  }
		 }

		
		 unsigned int   GetPrimeSize()
	     {
	         /*学者研究的可以一定程度上避免哈希碰撞的数组*/
			 const unsigned int primeSize=28;
	    static const unsigned long _PrimeList[primeSize]=
		{
			53ul, 97ul, 193ul, 389ul, 769ul,1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
            49157ul, 98317ul, 196613ul, 393241ul, 786433ul,1572869ul, 3145739ul, 
			6291469ul, 12582917ul, 25165843ul,50331653ul, 100663319ul, 201326611ul,
			402653189ul, 805306457ul,1610612741ul, 3221225473ul, 4294967291ul
		};
			if(tables.size() == 0)
			 {
			   return primeSize;
			 }
			 size_t i=0;
			 for(i=0;i<tables.size();++i)
			 {
			   if(tables.size() < _PrimeList[i])
				 {
			       return _PrimeList[i];
			     }
			 }
			 //否则就返回最大
			 return _PrimeList[primeSize];
	     }

		  size_t HashFun(K key,size_t capacity)
	     {
		      return hash(key) %capacity;
		 }
     private:
		 vector<Node*> tables;
	     size_t capacity;
};




int main()
{

HashTable<char*,int> hash;
char *str=(char*)"abcd";
cout<<hash.HashFun(str,10)<<endl;

    return 0;
}


