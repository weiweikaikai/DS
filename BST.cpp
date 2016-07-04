/*************************************************************************
	> File Name: BST.cpp
	> Author: wk
	> Mail: 18402927708@163.com
	> Created Time: Mon 04 Jul 2016 09:55:18 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

template<class K,class V>
class BST_Node
{
public:
	BST_Node(const K&key=K(), const V&value=V()) :left(NULL), right(NULL), key(key), value(value)
	{}
	~BST_Node()
	{}
	BST_Node<K, V> *left;
	BST_Node<K, V> *right;

	K key; //保存的值
	V value; //插入的次序
	//int frque;//相等节点的数目
};

template<class K,class V>
class BST
{
	typedef BST_Node<K, V> BST_Node;
public:
	BST() :root(NULL)
	{}
	~BST()
	{}
public:
	bool insert_norecursion(const K&key, const V&value)
	{
		if (root == NULL)
		{
			root = new BST_Node(key, value);
		}
		BST_Node*cur = root;
		while (cur)
		{
			if (cur->key > key)
			{
				if (cur->left == NULL)
				{
					cur->left = new BST_Node(key, value);
				}
				else
				{
					cur = cur->left;
				}
			}
			else if (cur->key < key)
			{
				if (cur->right == NULL)
				{
					cur->right = new BST_Node(key, value);
				}
				else
				{
					cur = cur->right;
				}
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	void  insert_recursion(BST_Node *&node ,const K&key)
	{
		if (node == NULL)
		{
			node = new BST_Node(key);
			return true;
		}
		if (key> node->key)
		{
			insert_recursion(node->right, key);
		}
		else if (key < node->key)
		{
			insert_recursion(node->left, key);
		}
		else
		{
			return;
		}
	}
	BST_Node* Find_norecursion(const K&key)
	{
		if (root == NULL)
		{
			return false;
		}
		BST_Node *cur = root;
		while (cur)
		{
			if (key > cur->key)
			{
				cur = cur->right;
			}
			else if (key < cur->key)
			{
				cur = cur->left;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}
	BST_Node* Find_recursion(BST_Node *&node, const K&key)
	{
		if (node == NULL)
		{
			return NULL;
		}
		if (key > node->key)
		{
			return Find_recursion(node->right);
		}
		else if (key < node->key)
		{
			return Find_recursion(node->left);
		}
		else
		{
			return node;
		}
	}
	bool Remove_norecursion(const K&key)
	{
		if (root == NULL)//没有节点
		{
			return false;
		}
		else if (root->left == NULL && root->right == NULL) //一个根节点
		{
			if (root->key == key)
			{
				delete root;
				root = NULL;
				return true;
			}
			else
			{
				return false;
			}
		}
		else //两个或两个以上节点
		{
			BST_Node*cur = root;
			BST_Node*parent = NULL;
			while (cur)
			{
				if (key > cur->key)
				{
					parent = cur;
					cur = cur->right;
				}
				else if (key < cur->key)
				{
					parent = cur;
					cur = cur->left;
				}
				else //找到key
				{
					BST_Node*del = cur;
					if (cur->left == NULL) //左子树为空，右子树存在或者不存在
					{
						if (parent == NULL)//如果parent为NULL表示此时cur为要删除的根节点
						{
							root = cur->right;//将右子树链上之后删除根节点
						}
						else //父节点不为空时
						{
							if (parent->left == cur)
							{
								parent->left = cur->right;
							}
							else
							{
								parent->right = cur->right;
							}
						}
					}
					else if (cur->right == NULL)//右子树为空
					{
						if (parent == NULL)
						{
							root = cur->left;
						}
						else
						{
							if (parent->left == cur)
							{
								parent->left = cur->left;
							}
							else
							{
								parent->right = cur->left;
							}
						}
					}
					else //左右子树都不为空  此时用右子树中中最小的节点和当前节点交换，之后删除
					{
						parent = cur;
						BST_Node*firstleft = cur->right;

						while (firstleft != NULL && firstleft->left！ = NULL)
						{
							parent = firstleft;
							firstleft = firstleft->left;
						}
						del = firstleft;

						swap(firstleft->key, cur->key);

						if (parent->left == firstleft)
							parent->left = firstleft->right;
						else
							parent->right = firstleft->right;

					}
					delete del;
					del = NULL;
					return true;
				}
			}
			return false;
		}
	}
	void Remove_recursion(BST_Node *&node, const K&key)
	{
		if (node == NULL)
		{
			return;
		}
		if (key > node->key)
		{
			Remove_recursion(node->right, key);
		}
		else if (key < node->key)
		{
			Remove_recursion(node->left, key);
		}
		else//相等
		{
			if (node->left && node->right) //此节点右两个儿子
			{
				BST_Node*tmp = node->right; 
				while (tmp->left != NULL) //找到右子树中最小值得节点
					temp = tmp->left;
				
				node->data = temp->data;
				Remove_recursion(node->right, temp->data);//将right子树中最小的删除
			}
			else
			{
				BST_Node*tmp = node;
				if (node->left == NULL) //有右儿子或者没有儿子
					node = node->rson;//这里使用的是引用，node相当于当前父节点的左子节点指针或者右子节点指针
				else if (node->right == NULL)
					node = node->right;

				delete tmp;
			}
		}
	}
	bool Empty()
	{
		if (root == NULL)
		{
			return true;
		}
		return false;
	}
protected:
	BST_Node *root;

};

void test()
{
	BST<int, int> bst;
	bst.insert_norecursion(1, 1);
	bst.insert_norecursion(3, 2);
	bst.insert_norecursion(4, 3);
	bst.insert_norecursion(6, 4);
	bst.insert_norecursion(7, 5);
	bst.insert_norecursion(8, 6);
	bst.insert_norecursion(9, 7);
	bst.insert_norecursion(10, 8);

	cout<<bst.Empty()<<endl;
}

int main()
{

	test();
	system("pause");
	return 0;
}