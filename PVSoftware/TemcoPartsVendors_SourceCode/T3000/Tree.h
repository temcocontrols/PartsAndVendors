/////////////////////////////////
//
// Tree.h
//
// This class implements a tree data structure ..
// note that the user passes the data type for which he wishes to 
// create a tree. The tree node itself is NOT that data type. 
//
////////////////////////////////////


#ifndef __TREE_H__
#define __TREE_H__



template <typename T>
class Tree
{
	// ---- local node class ------
public:
	class Node
	{
		typedef std::vector <Node*>	Children;
		Children	_children;
		Node*		_parent;
		T			_data;

	public:

		Node ()						: _parent (NULL)						{}
		explicit Node (T t)			: _data (t), _parent (NULL)				{}
		Node (T t, Node* parent)	: _data (t), _parent (parent)			{}

		T& data()							{	return ( _data);					}	

		int num_children() const			{	return ( _children.size() );		}
		Node* child (int i)					{	return ( _children [ i ] );		}
		Node* parent()						{	return ( _parent);				}
		void set_parent (Node* parent)		{	_parent = parent;				}
		bool has_children() const			{	return ( num_children() > 0 );	}
		
		void add_child (Node* child) {
			child -> set_parent ( this ); 
			_children.push_back ( child ); }

		~Node() {
			for (int i = 0; i < num_children(); i++)
				delete ( _children [ i ] ); }
	};	// --- end local node class ---


	// --- tree class methods ---
	
private:
	Node* _root;		// the root node of the tree



public:
	// define a DFS iterator (in-order) ..
	// I will define other iterators later perhaps
	// but an in order DFS one is perhaps the most commonly used one
	class iterator_dfs
	{
		// dfs iterator needs a stack
		// note: the ietaror needs to keep track of the 'current' node in the tree
		// so we maintain a pointer to the current node
		// we use a stack or que for appropriate traversal type
		typedef std::stack <Node*> Stack;
		Stack _stack;

		Node* _current;

		Tree* _tree;		// reference to the tree this iterator is part of

	public:
		iterator_dfs (Tree& tree, Node* start_node) : _tree (&tree), _current (start_node) { }

		iterator_dfs& operator ++ () 
		{
			// put the current' nodes children on the stack, and 
			// then move onto the next one by popping it
			// off the stack and making it the current one 
			if (_current) 		
				for ( int i = _current -> num_children() - 1; i >= 0 ; i-- )
					_stack.push ( _current -> child (i) );
	

			if (! _stack.empty() ) {
				_current = _stack.top();
				_stack.pop(); }
			else 
				*this = _tree -> end(); 

			return (*this); 
		}

		// operator bool is a conversion functions
		// (conversion functions are defined that way)
		// This allows the iterator to take part in 
		// if else style constructs
		operator bool ()			{ return ( _current != NULL);		}

		const iterator_dfs& operator = (const iterator_dfs& iter)
		{
			_tree = iter._tree;
			_current = iter._current;
			while (! _stack.empty() )
				_stack.pop();

			
			// and now we need to copy the stacks as well.
			typedef std::vector <Node*> NodesVec;
			NodesVec v ( iter._stack.size() );

			iterator_dfs& it = const_cast <iterator_dfs&> (iter);	// remove const-ness
			while (! it._stack.empty() ) {
				v.push_back ( it._stack.top() );
				it._stack.pop(); }

			// now fill both stacks from the vector (traverse from back)
			for (int i = v.size() - 1; i >= 0; i-- ) {
				it._stack.push ( v [i] ); 
				_stack.push ( v [i] ); }
		
			
			return (*this);
		}
	
		
		// copy CTOR	- do via operator =
		iterator_dfs (const iterator_dfs& iter)		{		(*this) = iter ;	 }			
		
		bool operator == (const iterator_dfs& iter) const
		{
			// i am not going to do stack check because checking the stack is costly
			// so just check if tree, and current and stack sizes are the same
			if (_current == iter._current  &&  _tree == iter._tree  && _stack.size() == iter._stack.size() )
				return (true);
			else
				return (false);
		}


		bool operator != (const iterator_dfs& iter) const		{	return (! operator == (iter) ); 	}

		

		//Node* operator -> ()	{	return (_current);										}
		//Node& operator * ()	{	assert (_current);	return (* _current);				}
		// NO . .iteraotr dereferenes should return the T type, not the (internal) Node type.
		T* operator -> ()		{	return ( current ? & _current -> data() : current  );	}
		T& operator * ()		{	assert (_current);	return (_current -> data() );		}


		Node* current_node()	{	return (_current);										}
		// jsut incase we need to work with the internal Node class directly
		// But be sure that any node operations may potentially make the
		// iterator invalid .. and once node is given all bests are off ... since
		// the user can now add children to the nodes thus making the iterator invalid, etc.
	};


	// --- tree methods --- 
	explicit Tree (Node* root) : _root (root)	{}
	Tree() : _root (NULL)						{} 

	void set_root (Node* root) {
		if (_root)	delete (_root);
		_root = root; }
	



	
	iterator_dfs begin ()		{	return ( iterator_dfs ( *this, _root) );		}
	iterator_dfs end ()			{	return ( iterator_dfs ( *this, NULL ) );		}

};	// --- end tree class methods ---

#endif
