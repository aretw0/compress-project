#include<iostream>
#include<fstream>
#include<string>
#include<iomanip> //for width()
#include<cctype> //for sprintf()

#define HELP_ERROR 99
#define width_unit 5

using namespace std;

// (Templated d-heap) (on dynamic array of pointers)
// priority queue
// min (root=min) ((balanced) d-tree on dynamic array) d-heap
template<class T>
class QueueHuff
{
    public:

        QueueHuff(int d=2); //constructor 
        ~QueueHuff(void); //destructor
        void enq(T*); //enqueue (to push)
        T* deq(void); //dequeue (to pop)
        T* front(void); //the front element
        bool empty(void) const; //is empty?
        bool full(void) const; //is full?

    private:

        int back; //the last element in the queue
        T* *arr; //dynamic array
        int size; //current size of the queue array
        static const int SIZE=10; //size increment step size  
        int D; //max number of children for a parent>=2 
        //copy constructor and assignment are hidden to protect 
        QueueHuff(const QueueHuff &);
        const QueueHuff & operator=(const QueueHuff &);

        //utility functions to fix the heap
        //when an element added or removed 
        void reheapup(int, int); //fix heap upward
        void reheapdown(int, int); //fix heap downward
        void swap(T* &, T* &); //swap f. needed by reheapup/down functions

}; //end class

// Huffman Tree
class Huff
{
    private:
        class Node
        {
            public:
                unsigned int freq;
                unsigned char ch;
                Node *left, *right;
                //constructor
                Node(void)
                    :freq(0), ch('\0'), left(NULL), right(NULL) {}
        };

        Node *root;
        //copy cons. and assign. op. overload prototypes are private to
        //prevent them to be used
        Huff(const Huff &); //copy constructor
        const Huff & operator=(const Huff &); //assignment oper. overload
        void chop(Node * N); //destroys the tree
        void print(ostream &, Node *, int) const; //prints the tree
        void print(Node *, int) const; //prints the tree

        void huf_write(unsigned char i, ofstream & outfile);
        unsigned char huf_read(ifstream & infile);

        void encode(ifstream & infile, ofstream & outfile,bool verbose);
	    void decode(ifstream & infile, ofstream & outfile,bool verbose);

    public:
         Huff(void); //constructor
        ~Huff(void); //destructor
        friend ostream & operator<<(ostream &, const Huff &);
        //utility functions to get or set class members
        unsigned int get_freq(void) const;
        unsigned char get_char(void) const;
        void set_freq(unsigned int);
        void set_char(unsigned char);
        Node* get_left(void) const;
        Node* get_right(void) const;
        void set_left(Node *);
        void set_right(Node *);
        Node* get_root(void) const;
        //comparison operator overloads to compare
        //2 objects of the class
        bool operator==(const Huff &) const;
        bool operator!=(const Huff &) const;
        bool operator<(const Huff &) const;
        bool operator>(const Huff &) const;
        bool operator<=(const Huff &) const;
        bool operator>=(const Huff &) const;

        //to get H. string of a given char
        void huf(Node *, unsigned char, string, string &) const; 
        //outputs the H. char-string pairs list
        void huf_list(Node *, string) const; 
        //to get char equivalent of a H. string (if exists)
        bool get_huf_char(string, unsigned char &) const;
        string print_char(Node *) const; //prints chars 
       

        void Start(string ifile); 
};