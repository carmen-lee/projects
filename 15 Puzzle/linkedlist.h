/*
* Carmen Lee, 2001586623, Doubly Linked List Header File
* Referenced from Dr. James Andro-Vasko, UNLV CS302
*/

#include <iostream>

/*
* class_identifier: This class defines a doubly linked list where elements of the list is of type struct node where each node 
*                   contains some data in its item field and contains a pointer next to the node to the right and a pointer prev 
*                   that points to the node to the left.
* constructors: 
*                   iterator();
*                   iterator(node*);
*                   LL();
*                   LL(const LL&);
*                   const LL& operator=(const LL&);
*                   ~LL();
* public functions:
*                   Type operator*();
*                   iterator operator++(int);
*                   iterator operator--(int);
*                   bool operator==(const iterator&) const;
*                   bool operator!=(const iterator&) const;
* static members: 
* (variables and function prototypes)
*                   Type item;
*                   node * next;
*                   node * prev;
*                   node * current;
*                   node * head;
*                   node * tail;
*/
template <class Type>
class LL
{
    struct node
    {
        Type item;
        node * next;
        node * prev;
    };
public:
    class iterator
    {
        public:
            friend class LL;
            iterator();
            iterator(node*);
            Type operator*();
            iterator operator++(int);
            iterator operator--(int);
            bool operator==(const iterator&) const;
            bool operator!=(const iterator&) const;
        private:
            node * current;
    };

    LL();
    LL(const LL&);
    const LL& operator=(const LL&);
    ~LL();
    iterator begin() const;
    iterator end() const;
    void headRemove();
    void tailRemove();
    void removeNode (const iterator&);
    bool isEmpty() const;
    void headInsert(const Type&);
    void tailInsert(const Type&);
    void update(const iterator&, const Type&);

private:
    node * head;
    node * tail;
};

/*
* function_identifier: default constructor that sets current to NULL
* parameters: 
* return value: 
*/
template <class Type>
LL<Type>::iterator::iterator()
{
    current = NULL;
}

/*
* function_identifier: constructor that assigns current with pointer
* parameters: pointer that should be assigned to current
* return value: 
*/
template <class Type>
LL<Type>::iterator::iterator(node * pointer)
{
    current = pointer;
}

/*
* function_identifier: returns the item field of the node that current points to
* parameters:
* return value: item field of current
*/
template <class Type>
Type LL<Type>::iterator::operator*()
{
    return current->item;
}

/*
* function_identifier: moves the iterator object over to the next node in the linked list, ie sets pointer over to the next node
* parameters:
* return value:
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator::operator++(int)
{
    current = current->next;
    return *this;
}

/*
* function_identifier: moves the iterator object over to the previous node in the linked list, ie sets pointer over to the previous node
* parameters:
* return value:
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator::operator--(int)
{
    current = current->prev;
    return *this;
}

/*
* function_identifier: compares *this iterator and the rhs object
* parameters: rhs object
* return value: true if *this points to the same node as the rhs object, otherwise false
*/
template <class Type>
bool LL<Type>::iterator::operator==(const iterator& rhs) const
{
    return current == rhs.current;
}

/*
* function_identifier: compares *this iterator and the rhs object
* parameters: rhs object
* return value: false if *this points to the same node as the rhs object, otherwise true
*/
template <class Type>
bool LL<Type>::iterator::operator!=(const iterator& rhs) const
{
    return current != rhs.current;
}

/*
* function_identifier: default constructor that assigns NULL to both head and tail
* parameters: 
* return value: 
*/
template <class Type>
LL<Type>::LL()
{
    head = tail = NULL;
}

/*
* function_identifier: copy constructor, performs a deep copy of the copy object to the *this object
* parameters:  LL<Type> object to be copied to
* return value: 
*/
template <class Type>
LL<Type>::LL(const LL& copy)
{
    head = tail = NULL;
    *this = copy;   // calls assignment operator
}

/*
* function_identifier: assignment  operator, performs a deep copy of the rhs object into the *this object (aka the left hand side object)
* parameters:  LL<Type> object to be assigned to
* return value: 
*/
template <class Type>
const LL<Type>& LL<Type>::operator=(const LL& rhs)
{
    if (this != &rhs) {

        while (!isEmpty()) {
            headRemove();
        }

        if (!rhs.isEmpty()) {
            LL<int>::iterator theEnd(NULL);
            LL<Type>::iterator it;
            for(it = rhs.begin() ; it != theEnd ; it++) {
                tailInsert(*it);
            }
        }

    }
    return *this;
}

/*
* function_identifier: destructor, deallocates the linked list
* parameters:
* return value: 
*/
template <class Type>
LL<Type>::~LL()
{
    while (!isEmpty()) {
        headRemove();
    }
}

/*
* function_identifier: returns an iterator object whose current pointer is assigned with the address in the head pointer
* parameters:
* return value: iterator object that points to head
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::begin() const
{
    return LL<Type>::iterator(head);
}

/*
* function_identifier: returns an iterator object whose current pointer is assigned with the address in the tail pointer
* parameters:
* return value: iterator object that points to tail
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::end() const
{
    return LL<Type>::iterator(tail);
}

/*
* function_identifier: removes the node from the linked list that the iterator that is passed into the function is pointing to
* parameters: an iterator object that points to a node
* return value:
*/
template <class Type>
void LL<Type>::removeNode(const iterator& it)
{
    if (isEmpty() || it.current == NULL) {
        return;
    }

    if (it.current == head) {
        headRemove();
        return;
    }

    if (it.current == tail) {
        tailRemove();
        return;
    }

    node * prevNode = it.current->prev;
    it.current->next->prev = prevNode;
    prevNode->next = it.current->next;
    delete it.current;

    return;
}

/*
* function_identifier: removes the front node
* parameters:
* return value:
*/
template <class Type>
void LL<Type>::headRemove()
{
    if (!isEmpty()) {
        
        if (head == tail) {
            // only one node
            delete head;
            head = tail = NULL;
        } else {
            // More than one node
            node * del = head;
            head = head->next;
            delete del;
        }
    }

    return;
}

/*
* function_identifier: removes the end node
* parameters:
* return value:
*/
template <class Type>
void LL<Type>::tailRemove()
{
    if (!isEmpty()) {
        
        if (head == tail) {
            // one node
            headRemove();
        } else {
            // more than one node
            node * del = tail;
            tail = tail->prev;
            delete del;
        }
    }

    return;
}

/*
* function_identifier: checks if list is empty
* parameters:
* return value: true if the list is empty, otherwise false
*/
template <class Type>
bool LL<Type>::isEmpty() const
{
    // returns true if the list is empty
    // returns false if the list is not empty
    if (head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
* function_identifier: inserts a new node to the front of the linked list
* parameters: <Type> element, ie an integer
* return value: 
*/
template <class Type>
void LL<Type>::headInsert(const Type& element)
{
    node * insert = new node;
    insert->item = element;
    insert->prev = NULL;

    if (isEmpty()) {
            head = insert;
            head->next = NULL;
            tail = head;
    } else {
        insert->next = head;
        head->prev = insert;
        head = insert;
    }

    return;
}

/*
* function_identifier: inserts a new node to the end of the linked list
* parameters: <Type> element, ie an integer
* return value: 
*/
template <class Type>
void LL<Type>::tailInsert(const Type& element)
{
    node * insert = new node;
    insert->item = element;
    insert->prev = NULL;

    if (isEmpty()) {
        tail = insert;
        tail->next = NULL;
        head = tail;
    } else {
        insert->prev = tail;
        tail->next = insert;
        tail = insert;
    }

    return;

}

/*
* function_identifier: assigns the item field of the node that the iterator object points to with the element passed into the function
* parameters: an iterator object pointing to a node to be updated, a <Type> element (ie an int)
* return value: 
*/
template <class Type>
void LL<Type>::update(const LL<Type>::iterator& it, const Type& element)
{
    it.current->item = element;
    return;
}
