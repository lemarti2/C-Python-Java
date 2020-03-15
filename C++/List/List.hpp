/*
  Filename   : List.hpp
  Author     : Leandro Martinez
  Course     : CSCI 362-01
  Assignment : N/A
  Description: List class, our implementation of a list ADT 
                 using a circular, doubly-linked list.
*/   
/************************************************************/
// Macro guard

#ifndef LIST_HPP
#define LIST_HPP

/************************************************************/
// System includes

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <initializer_list>

/************************************************************/
// Local includes

/************************************************************/
// Using declarations

using std::ostream;
using std::ostream_iterator;
using std::initializer_list;

/************************************************************/
template <typename T>
struct ListNode 
{
  ListNode ()
    : data ()
  {
    // Make a circular node, with next and prev
    //   pointing to this node
    // TODO
    next = this;
    prev = this;
  }

  // TODO
  ListNode (const T& d, ListNode* n = nullptr,
	    ListNode* p = nullptr)
    : data(d),
      next(n),
      prev(p)
    // Initialize the three data members appropriately
  {
  }

  T          data;
  ListNode*  next;
  ListNode*  prev;
};


/************************************************************/

template<typename T>
struct ListIterator
{
  typedef ListIterator<T>                  Self;
  typedef ListNode<T>                      Node;

  typedef ptrdiff_t                        difference_type;
  typedef std::bidirectional_iterator_tag  iterator_category;

  typedef T                                value_type;
  typedef T*                               pointer;
  typedef T&                               reference;

  ListIterator ()
    : m_nodePtr ()
  { }

  explicit
  ListIterator (Node* n)
    : m_nodePtr (n) 
  { }
  
  reference
  operator* () const
  { 
    return m_nodePtr->data;
  }
  
  // Return address of node's data member
  pointer
  operator-> () const
  { 
    return &m_nodePtr->data;
  }
  
  // Pre-increment: TODO
  Self&
  operator++ ()
  {
    // Make the iterator point to the next node
    //   and return the updated iterator
    m_nodePtr = m_nodePtr -> next;
    return *this;

  }
  
  // Post-increment
  Self
  operator++ (int)
  {
    Self temp (*this);
    m_nodePtr = m_nodePtr->next;
    return temp;
  }

  // Pre-decrement: TODO
  Self&
  operator-- ()
  {
    // Make the iterator point to the prev node
    //   and return the updated iterator
    m_nodePtr = m_nodePtr -> prev;
    return *this;
  }
  
  // Post-decrement
  Self
  operator-- (int)
  {
    Self temp (*this);
    m_nodePtr = m_nodePtr->prev;
    return temp;
  }
  
  bool
  operator== (const Self& i) const
  {
    return m_nodePtr == i.m_nodePtr;
  }
  
  bool
  operator!= (const Self& i) const
  {
    return m_nodePtr != i.m_nodePtr;
  }
  
  /************************************************************/

  Node* m_nodePtr;

};

/************************************************************/

template<typename T>
struct ListConstIterator
{
  typedef ListConstIterator<T>     Self;
  typedef const ListNode<T>        Node;
  typedef ListIterator<T>          iterator;
  
  typedef ptrdiff_t                        difference_type;
  typedef std::bidirectional_iterator_tag  iterator_category;

  typedef       T                   value_type;
  typedef const T*                  pointer;
  typedef const T&                  reference;
  
  ListConstIterator ()
    : m_nodePtr ()
  { }
  
  explicit
  ListConstIterator (Node* n)
    : m_nodePtr (n)
  { }
  
  ListConstIterator (const iterator& i)
    : m_nodePtr (i.m_nodePtr)
  { 
  }
  
  reference
  operator* () const
  { 
    return m_nodePtr->data;
  }
  
  pointer
  operator-> () const
  { 
    return &m_nodePtr->data;
  }

  Self&
  operator++ ()
  {
    m_nodePtr = m_nodePtr->next;
    return *this;
  }
  
  // Post-increment: TODO
  Self
  operator++ (int)
  {
    Self temp (*this);
    m_nodePtr = m_nodePtr ->next;
    return temp;
  }
  
  Self&
  operator-- ()
  {
    m_nodePtr = m_nodePtr->prev;
    return *this;
  }
  
  // Post-decrement: TODO
  Self
  operator-- (int)
  {
    Self temp (*this);
    m_nodePtr = m_nodePtr ->prev;
    return temp;
  }
  
  bool
  operator== (const Self& i) const
  { 
    return m_nodePtr == i.m_nodePtr;
  }
  
  bool
  operator!= (const Self& i) const
  { 
    return m_nodePtr != i.m_nodePtr;
  }
  
  /************************************************************/

  Node* m_nodePtr;

};

template<typename T>
inline bool
operator== (const ListIterator<T>& i1,
	    const ListConstIterator<T>& i2)
{ 
  // Return whether the two iterators refer to the same node
  // TODO
  return i1 == i2;
}

template<typename T>
inline bool
operator!= (const ListIterator<T>& i1,
	    const ListConstIterator<T>& i2)
{ 
  // Return whether the two iterators refer to different nodes
  // TODO
  return i1 != i2;
}

/************************************************************/

template<typename T>
class List 
{
  typedef ListNode<T>            Node;

public:

  typedef ListIterator<T>        iterator;
  typedef ListConstIterator<T>   const_iterator;
  typedef T                      value_type;
  typedef T*                     pointer;
  typedef T&                     reference;
  typedef const T&               const_reference;

  // Initialize an empty list
  List ()
  // Initialize data members
    :m_header(),
     m_size()
  {
  }

  // Initialize a list with the elements in "values",
  //   in the same order
  List (initializer_list<T> values)
    : m_header (), m_size (0)
  {
     for( T element : values){
      push_back(element);
    }
    
  }  

  // Initialize a list of size "n", with each value set to "defValue"
  explicit List (size_t n, const T& defValue = T ())
    :m_header(),
     m_size(0)
  {
    // for(size_t i = 0; i < n; ++i)
    //{
    //std :: cout<< i << std :: endl;
    //push_back(defValue);
    //}
  }

  // Copy constructor
  //   Initialize this list to be a copy of "otherList"
  List (const List& otherList)
    :m_header(),
     m_size(0)
  {
    for( T element : otherList)
    {
      push_back(element);
    }
  }
    
    
  		    
  // Destructor
  ~List ()
  {
    // Deallocate all nodes
    // TODO
    while(!empty()) pop_back();
  }

  // Assign "rhs" to this object
  //   Watch for self-assignment
  List&
  operator= (const List& rhs)
  {
    if(&rhs != this)
    {
      erase(begin(), end());
      for( T element : rhs)
      {
	push_back(element);
      }
    }
  }
  // Return whether the list is empty
  bool    
  empty () const
  {
    return m_size == 0;
  }
  
  // Return the size
  size_t
  size ()  const
  {
    return m_size;
  }

  // Return the first element
  reference
  front ()
  {
    return m_header.next-> data;
  }

  const_reference
  front () const
  {
    return m_header.next-> data;
  }

  // Return the back element
  reference
  back ()
  {
    return m_header.prev-> data;
  }

  const_reference
  back () const
  {
    return m_header.prev-> data;
  }

  // Add "item" to the front of the list
  void 
  push_front (const_reference item)
  {
    insert(begin(), item);
  }

  // Remove the first element
  void
  pop_front  ()
  {
    erase(begin());
  }

  // Add "item" to the back of the list
  void 
  push_back  (const_reference item)
  {
    insert(end(), item);
  }

  // Remove the last element
  void 
  pop_back   ()
  {
    erase(--end());
  }

  // Return an iterator referencing the first element
  iterator       
  begin ()
  {
    return iterator( m_header.next);
  }

  const_iterator 
  begin () const
  {
    return const_iterator( m_header.next);
  }

  // Return an iterator referencing one past the last element
  iterator       
  end  ()
  {
    return iterator(&m_header);
  }

  const_iterator 
  end   () const
  {
    return const_iterator( &m_header);
  }  

  // Insert "item" at position "i"
  // Return an iterator referencing the inserted element
  iterator 
  insert (iterator i, const T& item)
  {
    Node* succ = i.m_nodePtr;
    Node* pred = i.m_nodePtr->prev;
    Node* n = new Node(item, succ, pred);
    pred->next = n;
    succ->prev = n;
    ++m_size;
    return iterator(n);
  }

  // Erase element at position "i"
  // Return an iterator referencing the element beyond the one erased
  iterator 
  erase  (iterator i)
  {
    Node* curr = i.m_nodePtr;
    Node* prevNode = curr -> prev;
    Node* succNode = curr -> next;
    delete curr;
    prevNode -> next = succNode;
    succNode -> prev = prevNode;
    --m_size;
    return iterator(succNode);
  } 

  // Erase elements in the range [i1, i2)
  // Return iterator "i2"
  iterator 
  erase  (iterator i1, iterator i2)
  {
    while( i1 != i2){
      iterator temp = i1;
      erase(temp);
      ++i1;
    }
    return i2;
  }
  
private:
  // Dummy header
  Node   m_header;
  size_t m_size;

};

/************************************************************/

// Output operator
// Output "list" in the format [ e1 e2 e3 ... en ]
template<typename T>
ostream&
operator<< (ostream& out, const List<T>& list)
{
  out << "[ ";
  auto it = list.begin();
  for( size_t i = 0; i < list.size(); ++i)
  {
    out<< *it << " ";
    ++it;
  }
  out << ']';
  return out;
}

/************************************************************/

#endif

/************************************************************/
