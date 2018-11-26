#include<iostream>
#include <vector>

struct Node {
	Node * left;
	Node * right;
	int value;
	Node(int value) :left(nullptr), right(nullptr), value(value) {
	};
};

void insert_recursivle(Node *& node, int value)
{
	if (node==nullptr)
	{
		node = new Node(value);
		return;
	}
	insert_recursivle(node->value > value ? node->left : node->right, value);
}
void insert(Node *& node, int value)
{
	//checking if node is empty
	if (node==nullptr)
	{
		node = new Node(value);
	}
	else
	{
		Node * current = node;
		Node * previous = nullptr;
		while (current != nullptr)
		{
			previous = current;
			if (current->value > value)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		current = new Node(value);
		if (previous->value > value)
		{
			previous->left = current;
		}
		else
		{
			previous->right = current;
		}

	}
	
	

}


bool find(Node * node, int value)
{
	while (node!=nullptr)
	{
		if (node->value>value)
		{
			node = node->left;
		}
		else if(node->value<value)
		{
			node = node->right;
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool find_recursivly(Node * node, int value)
{
	if (node==nullptr)
		return false;
	if (node->value==value)
		return true;
	find_recursivly(node->value < value ? node->right : node->left, value);
}

int find_min(Node * node)
{
	while (node->left)
	{
		node = node->left;
	}
	return node->value;
}
int extract_min(Node *& node)
{
	while (node->left)
	{
		node = node->left;
	}
	int value = node->value;
	node = nullptr;
	delete node;
	return value;
}


void erase(Node *& node,int value)
{
	if (node==nullptr)
	{
		return;
	}
	else if (value<node->value)
	{
		erase(node->left,value);
	}
	else if (value>node->value)
	{
		erase(node->right, value);
	}
	else
	{
		if (node->left==nullptr && node->right==nullptr)
		{
			node = nullptr;
		}
		else if (!node->left && node->right)
		{
			node->value = node->right->value;
			node->right = nullptr;
		
		}
		else if (node->left && !node->right)
		{
			node->value = node->left->value;
			node->left = nullptr;
		}
		else
		{
			node->value = extract_min(node->right);
			return;
		}
	}
}


int find_min_recursivle(Node * node)
{
	if (node->left==nullptr)
	{
	return node->value;
	}
	find_min_recursivle(node->left);
}
int find_max_recursivle(Node * node)
{
	if (node->right == nullptr)
	{
		return node->value;
	}
	find_max_recursivle(node->right);
}
int find_max(Node * node)
{
	while (node->right)
	{
		node = node->right;
	}
	return node->value;
}
void print_elements(Node * node)
{
	if (node==nullptr)
	{
		return;
	}
	print_elements(node->left);
	std::cout << node->value<< " " ;
	print_elements(node->right);

}
int main()
{
	Node * node=nullptr;
	insert_recursivle(*&node, 10);
	insert_recursivle(*&node, 5);
	insert_recursivle(*&node, 7);
	insert_recursivle(*&node, 4);
	insert_recursivle(*&node, 14);
	insert_recursivle(*&node, 11);
	insert_recursivle(*&node, 15);
	std::cout << find_max_recursivle(node)<<std::endl;
	erase(node, 5);
	print_elements(node);
	system("pause");



	
}