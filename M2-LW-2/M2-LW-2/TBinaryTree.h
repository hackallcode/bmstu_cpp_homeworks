#ifndef __TBINARY_TREE_INCLUDED__
#define __TBINARY_TREE_INCLUDED__

#include <exception>
#include <iostream>

struct TExistElementException
	: public std::exception
{
	TExistElementException(char const* const message) throw()
		: std::exception(message)
	{
	}
};


struct TNotFoundException
	: public std::exception
{
	TNotFoundException(char const* const message) throw()
		: std::exception(message)
	{ }
};

class TBinaryTree
{
public:
	using value_type = int;

	struct TNode
	{
		value_type Data;
		TNode * Right;
		TNode * Left;

	private:
		TNode(const value_type& data, TNode * next = nullptr, TNode * prev = nullptr)
			: Data(data)
			, Right(next)
			, Left(prev)
		{ }
		TNode()
			: Data(value_type())
			, Right(nullptr)
			, Left(nullptr)
		{ }

		~TNode()
		{
			delete Left;
			delete Right;
		}

		friend class TBinaryTree;
	};

private:
	TNode * Root = nullptr;

	static void Print(std::ostream & out, TBinaryTree::TNode * node)
	{
		if (node)
		{
			Print(out, node->Left);
			out << std::endl << node->Data;
			Print(out, node->Right);
		}
	}

	void FindCycle(TNode*& curNode, TNode*& prevNode, const value_type & value) {
		curNode = Root;
		prevNode = curNode;
		while (curNode) {
			prevNode = curNode;
			if (curNode->Data == value)
				return;
			if (curNode->Data < value)
				curNode = curNode->Right;
			else
				curNode = curNode->Left;
		}
	}

public:
	TBinaryTree()
	{ }

	~TBinaryTree()
	{
		delete Root;
	}

	void Insert(const value_type& data)
	{
		if (!TryInsert(data))
			throw TExistElementException("element already exist");
	}

	bool TryInsert(const value_type& data)
	{
		if (Root == nullptr)
		{
			Root = new TNode(data);
			return true;
		}

		TNode * curNode;
		TNode * prevNode;
		FindCycle(curNode, prevNode, data);

		if (curNode == nullptr) {
			TNode * newNode = new TNode(data);
			(prevNode->Data < data) ? prevNode->Right = newNode : prevNode->Left = newNode;
			return true;
		}
		else {
			return false;
		}
	}

	TNode * Find(const value_type & value)
	{
		if (Root == nullptr) {
			throw TNotFoundException("element not found");
		}

		TNode * curNode;
		TNode * prevNode;
		FindCycle(curNode, prevNode, value);

		if (curNode != nullptr)
			return curNode;
		else
			throw TNotFoundException("element not found");
	}

	friend std::ostream& operator << (std::ostream & out, const TBinaryTree& tree);
};

std::ostream& operator << (std::ostream & out, const TBinaryTree& tree)
{
	TBinaryTree::Print(out, tree.Root);
	return out;
}

#endif // __TBINARY_TREE_INCLUDED__