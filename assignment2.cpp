#include <iostream>

using namespace std;

class Node
{
public:
    Node();
    Node(int data, Node *next, Node *previous);
    ~Node();
    int getData();
    Node *getNext();
    Node *getPrevious();
    void setNext(Node *next);
    void setPrevious(Node *previous);

private:
    int data;
    Node *next;
    Node *previous;
};

// constructors
Node::Node(int data, Node *next, Node *previous) : data(data), next(next), previous(previous)
{
}
Node::Node()
{
}

// destructor
Node::~Node(){
    //cout << "destructor got called \n";
};

// getters
int Node::getData() { return data; }
Node *Node::getNext() { return next; }
Node *Node::getPrevious() { return previous; }

// setters
void Node::setNext(Node *next)
{
    this->next = (next);
}
void Node::setPrevious(Node *previous)
{
    this->previous = previous;
}

class DLLStructure
{
public:
    // constructors
    DLLStructure();
    DLLStructure(int array[], int size);
    // copy constructor
    DLLStructure(DLLStructure &dlls);
    // destructor
    ~DLLStructure();
    // methods
    void printDLL();
    void InsertAfter(int valueToInsertAfter, int valueToBeInserted);
    void InsertBefore(int valueToInsertBefore, int valueToBeInserted);
    void Delete(int value);
    void Sort();
    bool IsEmpty();
    int GetHead();
    int GetTail();
    int GetSize();
    int GetMax();
    int GetMin();

private:
    Node *first;
    Node *last;
    int size;
    int max;
    int min;
};

// constructors
DLLStructure::DLLStructure() : first(NULL), last(NULL), size(0), max(0), min(0)
{
}
DLLStructure::DLLStructure(int array[], int size)
{
    // assign first node to the first element of the input array
    Node *temp = new Node(array[0], NULL, NULL);
    first = temp;
    first->setPrevious(NULL);
    this->max = temp->getData();
    this->min = temp->getData();

    // add corresponding nodes to array elements
    for (int i = 1; i < size; i++)
    {
        temp->setNext(new Node(array[i], NULL, temp));
        temp = temp->getNext();

        // keep track of max & min values
        if (temp->getData() > this->max)
        {
            this->max = temp->getData();
        }
        if (temp->getData() < this->min)
        {
            this->min = temp->getData();
        }
    }

    // assign last node's next to NULL
    temp->setNext(NULL);
    last = temp;

    // keep track of list size
    this->size = size;
}

// copy constructor
DLLStructure::DLLStructure(DLLStructure &dlls)
{
    // check if input list is empty
    if (dlls.IsEmpty() == true)
    {
        first = NULL;
        last = NULL;
    }
    else
    {
        // assign int values to values of input lsit
        size = dlls.size;
        max = dlls.max;
        min = dlls.min;
        // copy nodes using the info of node to copy (not the actual node)
        first = new Node(dlls.first->getData(), NULL, NULL);
        Node *temp = first;
        Node *temp2 = dlls.first->getNext();
        while (temp2 != NULL)
        {
            temp->setNext(new Node(temp2->getData(), NULL, temp));
            temp = temp->getNext();
            temp2 = temp2->getNext();
        }
        last = temp;
    }
}

// destructor
DLLStructure::~DLLStructure()
{
    // go through the list of nodes and delete them one by one
    while (this->first != this->last)
    {
        Node *temp = this->first;
        this->first = first->getNext();
        delete temp;
    }
    delete this->last;
}

// printer method
void DLLStructure::printDLL()
{
    // loop through nodes of the list and print each node's data
    Node *temp = first;
    while (temp != this->last)
    {
        cout << temp->getData() << " ";
        temp = temp->getNext();
    }
    cout << temp->getData() << " \n";
}

// insertion method for after input data value is found
void DLLStructure::InsertAfter(int valueToInsertAfter, int valueToBeInserted)
{
    // loop through nodes looking for input value
    Node *temp = first;
    bool inserted = false;
    while (temp != this->last)
    {
        // insert new node after input value found
        if (temp->getData() == valueToInsertAfter)
        {
            Node *move = temp->getNext();
            temp->setNext(new Node(valueToBeInserted, move, temp));
            move->setPrevious(temp->getNext());
            inserted = true;
            // break out of loop once inserted
            break;
        }
        // continue looping if value not found in node
        temp = temp->getNext();
    }
    // insert at the end if new node hasn't been inserted yet
    if (inserted == false)
    {
        temp->setNext(new Node(valueToBeInserted, NULL, temp));
        this->last = temp->getNext();
    }
    // keep track of list size
    this->size++;

    // keep track of max & min values
    if (valueToBeInserted > this->max)
    {
        this->max = valueToBeInserted;
    }
    if (valueToBeInserted < this->min)
    {
        this->min = valueToBeInserted;
    }
}

// insertion method for before input data value is found
void DLLStructure::InsertBefore(int valueToInsertBefore, int valueToBeInserted)
{
    // loop through nodes looking for input value
    Node *temp = this->first;
    int afterVal;
    bool inserted = false;
    while (temp != this->last)
    {
        if (temp->getData() == valueToInsertBefore)
        {
            // get value of node before input value node
            afterVal = temp->getPrevious()->getData();
            // call InsertAfter function on found value
            InsertAfter(afterVal, valueToBeInserted);
            inserted = true;
            // break out of loop once inserted
            break;
        }
        // continue looping if value not found in node
        temp = temp->getNext();
    }
    // insert at the end if new node hasn't been inserted yet
    if (inserted == false)
    {
        temp = this->first;
        this->first = new Node(valueToBeInserted, temp, NULL);
        temp->setPrevious(this->first);
        // keep track of list size
        this->size++;
        // keep track of max & min values
        if (temp->getData() > this->max)
        {
            this->max = temp->getData();
        }
        if (temp->getData() < this->min)
        {
            this->min = temp->getData();
        }
    }
}

void DLLStructure::Delete(int value)
{
    // loop through nodes looking for input value
    Node *temp = this->first;
    while (temp != NULL)
    {
        if (temp->getData() == value)
        {
            // once value is found, update previous & next node
            // change accordingly if node is first or last or only
            if (this->size == 1) {
                this->first = NULL;
                this->last = NULL;
                temp = NULL;
                this->size--;
                break;
            }
            if (temp != this->first)
            {
                temp->getPrevious()->setNext(temp->getNext());
            }
            else
            {
                first = temp->getNext();
            }
            if (temp != this->last)
            {
                temp->getNext()->setPrevious(temp->getPrevious());
            }
            else
            {
                last = temp->getPrevious();
            }
            temp = NULL;
            // keep track of list size
            this->size--;
            // break out of loop once deleted
            break;
        }
        // continue looping if value not found in node
        temp = temp->getNext();
    }

    // if the deleted value was the max or min, update them accordingly
    if (this->max == value)
    {
        Node *temp = this->first;
        this->max = temp->getData();
        while (temp != NULL)
        {
            if (temp->getData() > this->max)
            {
                this->max = temp->getData();
            }
            temp = temp->getNext();
        }
    }
    if (this->min == value)
    {
        Node *temp = this->first;
        this->min = temp->getData();
        while (temp != NULL)
        {
            if (temp->getData() < this->min)
            {
                this->min = temp->getData();
            }
            temp = temp->getNext();
        }
    }
}

void DLLStructure::Sort()
{
    bool sorted;
    do
    {
        Node *temp = first;
        Node *swap = first->getNext();
        sorted = true;
        // loop through nodes
        while (temp != last)
        {
            // check if neighbour nodes are in ascending order
            if (temp->getData() > swap->getData())
            {
                sorted = false;

                // swap nodes into ascending order
                if (temp == this->first)
                {
                    swap->setPrevious(NULL);
                    this->first = swap;
                }
                else
                    swap->setPrevious(temp->getPrevious());
                if (swap == last)
                {
                    temp->setNext(NULL);
                    this->last = temp;
                }
                else
                    temp->setNext(swap->getNext());
                swap->setNext(temp);
                temp->setPrevious(swap);
                // update neighbouring nodes
                if (swap->getPrevious() != NULL)
                {
                    swap->getPrevious()->setNext(swap);
                }
                if (temp->getNext() != NULL)
                {
                    temp->getNext()->setPrevious(temp);
                }
            }
            temp = swap;
            swap = swap->getNext();
        }
    }
    // stop going through once nodes sorted into ascending order
    while (sorted == false);
}

bool DLLStructure::IsEmpty()
{
    if (this->first == NULL)
    {
        return true;
    }
    else
        return false;
}

int DLLStructure::GetHead()
{
    // make sure list isn't empty before accessing data
    if (this->IsEmpty() == false)
    {
        return this->first->getData();
    }
    // if list is empty notify user and return 0
    else
    {
        cout << "head data inaccessible as list is empty";
    }
    return 0;
}

int DLLStructure::GetTail()
{
    // make sure list isn't empty before accessing data
    if (this->IsEmpty() == false)
    {
        return this->last->getData();
    }
    // if list is empty notify user and return 0
    else
    {
        cout << "tail data inaccessible as list is empty";
    }
    return 0;
}

int DLLStructure::GetSize()
{
    return this->size;
}

int DLLStructure::GetMax()
{
    return this->max;
}

int DLLStructure::GetMin()
{
    return this->min;
}

int main()
{
    // Q 1, 2, 3 should obviously be implemented successfully
// in order to run the following code
int array [ 5 ] = { 11 , 2 , 7 , 22 , 4 };
DLLStructure dll ( array , 5 ) ; // note that 5 is the size of the array
dll.printDLL(); // the output should be: 11, 2, 7, 22, 4
// Q 4
dll.InsertAfter( 7 , 13 ); // To insert 13 after the first occurence of 7
dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4
dll.InsertAfter( 25 , 7 ); // To insert 7 after the first occurence of 25
dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4, 7
// Q 5
dll.InsertBefore( 7 , 26 ); // To insert 26 before the first occurence of 7
dll.printDLL(); // the output should be: 11, 2, 26, 7, 13, 22, 4, 7
dll.InsertBefore( 19 , 12 ); // To insert 12 before the first occurence of 19
dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 22, 4, 7
// Q 6
dll.Delete( 22 );
dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 4, 7
// Q 7
dll.Sort();
dll.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
// Q 8
if (dll.IsEmpty()) {
cout << "The list is empty" << endl ;
}
// Q 9
cout << "Head element is: " << dll.GetHead() << endl ;
cout << "Tail element is: " << dll.GetTail() << endl ;
// Q 10
cout << "Number of elements in the list is: " << dll.GetSize() <<
endl ;
// Q 11
cout << "Max element is: " << dll.GetMax() << endl;
cout << "Min element is: " << dll.GetMin() << endl;
// Q 11 theory question
/* What would be the best implementation of GetMax and GetMin if these methods are
requested very often? In other terms, how can we avoid looping over the elements of the
list each time the GetMax or GetMin method gets called? Please provide your answer inside
a cout statement in the main() function to print it out to the screen when the TA runs your
program. */
cout << "To avoid looping over all the elements of the list every time GetMin or GetMax are called, the list";
cout << "requires a variable to keep track over its max and min values as it goes. This way, the value can be accessed";
cout << "immediately at any time that the methods are called. In order to do this, the max and min values need to";
cout << "be updated whenever they may have changed. In the case of my list, this would be when the following methods";
cout << "are called: the constructor (obviously), and the methods that add or delete a node from the list.";
cout << "This same logic and implementation applies to keeping track of the size of the list.\n";
// Q 12 theory question
/* What will happen if we rely on the default copy constructor that is provided by the compiler
to copy the elements of a list into a new one? Please provide your answer inside a cout
statement in the main() function to print it out to the screen when the TA runs your
program. */
cout << "The default copy constructor that is provided by the compiler will create a shallow (and therefore unreliable)";
cout << "copy rather than a deep copy. A shallow copy creates a new pointer variable for the copy list, however, its";
cout << "pointer nodes will all point to the same space in the computer's memory as the original list's nodes.";
cout << "This means that when one of the lists is changed in any way, the other list will be affected, in a way that a copy";
cout << "should not be. As well as this unexpected behvaiour, this way of copying could also lead to runtime errors.";
cout << "For example, if delete is called on nodes of the copied list, this would cause an error because the word";
cout << "new was never used to create them in the first place (it was only used for the original list).\n";
// Q 12
DLLStructure dll2 (dll) ;
dll2.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26


cout << "MINE\n";
int test [ 1 ] = { 1 };
DLLStructure tester ( test , 1 ) ;
tester.printDLL();
cout << tester.GetSize();
tester.Delete(1);
//cout << tester.GetSize();
//tester.printDLL();

return 0 ;
}