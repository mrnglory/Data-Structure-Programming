#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <queue>
using namespace std;

template <class T>

struct Node
{
	Node(T d, Node<T> *left = 0, Node<T> *right = 0)
		: data(d), leftChild(left), rightChild(right) {}

	Node<T> *leftChild;
	T data;
	Node<T> *rightChild;
};

template <class T>

class Tree
{
public:
	Tree() {root = 0; } // empty tree

	void Insert(T &value) 
	{
		Insert(root, value); 
	}

	void Preorder()
	{
		Preorder(root);
	}

	void Inorder()
	{
		Inorder(root); 
	}

	void Postorder()
	{
		Postorder(root);
	}

	void Levelorder();

private:
	void Visit(Node<T> *);
	void Insert(Node<T> *&, T &);
	void Preorder(Node<T> *);
	void Inorder(Node<T> *);
	void Postorder(Node<T> *);

	Node<T> *root;
};

template <class T>
void Tree<T>::Visit(Node<T> *ptr)
{
	cout << ptr -> data << " ";
}

template <class T>
void Tree<T>::Insert(Node<T>* &ptr, T &value)
{
	// Insert 의 helper 함수
	if (ptr == 0)
		ptr = new Node<T>(value);

	else if (value < ptr -> data)
		Insert(ptr -> leftChild, value);

	else if (value > ptr -> data)
		Insert(ptr -> rightChild, value);

	else
		cout << endl << "Duplicate value" << value << "ignored\n";
}

// Preorder, Inorder, Postorder, Levelorder 함수를 구현하시오.
// Levelorder(교재 p266 참조하되 STL 큐를 이용) 를 구현하시오.

template <class T>
void Tree<T>::Preorder(Node<T> *currentNode)
{
	// Workhorse traverses the subtree rooted at currentNode.
	// The workhorse is declared
	// as a private member function of Tree.

	if(currentNode)
	{
		Visit(currentNode);
		Preorder(currentNode -> leftChild);
		Preorder(currentNode -> rightChild);
	}
}

/*template <class T>
void Tree<T>::Postorder(Node<T> *currentNode)
{
	// 이진 트리의 Postorder Traversal
	Postorder(root);
}*/

template <class T>
void Tree<T>::Postorder(Node<T> *currentNode)
{
	// Workhorse traverses the subtree rooted at currentNode.
	// The workhorse is declared
	// as a private member function of Tree.

	if(currentNode)
	{
		Postorder(currentNode -> leftChild);
		Postorder(currentNode -> rightChild);
		Visit(currentNode);
	}
}

template <class T>
void Tree<T>::Inorder(Node<T> *currentNode)
{
	// 일정한 공간만 추가로 사용하면서 이진 트리를 중위 순회.

	if(!root)
		return;

	Node<T> *top = 0, *lastRight = 0, *p, *q, *r, *r1;
	p = q = root;

	while(1)
	{
		while(1)
		{
			if((!p -> leftChild) && (!p -> rightChild))
			{
				// 리프 노드

				Visit(p);

				break;
			}

			if(!p -> leftChild)
			{
				// p를 방문하고 p -> rightChild 로 이동

				Visit(p);

				r = p -> rightChild;
				p -> rightChild = q;

				q = p;
				p = r;

				break;
			}

			else
			{
				// p -> leftChild 로 이동

				r = p -> leftChild;
				p -> leftChild = q;

				q = p;
				p = r;

				break;
			}
		}

		break;
		// 안쪽 while 의 끝
	}
	// p 는 리프 노드, 오른쪽 서브트리를 아직 검사하지 않은
	// 노드를 위해 위쪽으로 이동

	Node<T> *av = p;

	while(1)
	{
		if (p == root)
			return;

		if (!q -> leftChild)
		{
			// q 는 rightChild 를 통해 연결

			r = q -> rightChild;
			q -> rightChild = p;

			p = q;
			q = r;
		}

		else if (!q -> rightChild)
		{
			// q 는 leftChild 를 통해 연결

			r = q -> leftChild;
			q -> leftChild = p;

			p = q;
			q = r;

			Visit(p);
		}

		else
		{
			// p 가 q 의 rightChild 인지 검사

			if (q == lastRight)
			{
				r = top;
				lastRight = r -> leftChild;
				top = r -> rightChild; // 스택에서 제거
				r -> leftChild = r -> rightChild = 0;
				r = q -> rightChild;
				q -> rightChild = p;
	
				p = q;
				q = r;
			}

			else
			{
				// p 가 q 의 leftChild 인지 검사

				Visit(q);
				av -> leftChild = lastRight;
				av -> rightChild = top;
				top = av;
				lastRight = q;
				r = q -> leftChild;
				q -> leftChild = p; // p 로 가는 링크를 복구
				r1 = q -> rightChild;
				q -> rightChild = r;
				p = r1;

				break;
			}
		}
		// 안쪽 while 루프의 끝
	}
	// 바깥쪽 while 루프의 끝
}

template <class T>
void Tree<T>::Levelorder()
{
	queue<Node<T>*> q;
	Node<T> * currentNode = root;

	while(currentNode)
	{
		Visit(currentNode);

		if(currentNode -> leftChild)
			q.push(currentNode -> leftChild);

		if(currentNode -> rightChild)
			q.push(currentNode -> rightChild);

		if(q.empty())
			return;

		currentNode = q.front(); // 큐에서 꺼내자.
		q.pop();
	}
}

#endif
