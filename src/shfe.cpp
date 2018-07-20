#include "shfe.h"
#include "common.h"

// constructor (creates a new Queue)
template<class T>
QueueShfe<T>::QueueShfe(int d)
{
    if(d<2) d=2; //min a 2-heap is supported
    D=d;
    back=0;
    size=SIZE;
    arr=new T*[size];
}

// is QueueShfe empty?
template<class T>
bool QueueShfe<T>::empty(void) const
{
    return (back<=0);
}

// is QueueShfe full?
template<class T>
bool QueueShfe<T>::full(void) const
{
    return (back>=size);
}

// the front element of the QueueShfe 
template<class T>
T* QueueShfe<T>::deq(void)
{
    if(empty())
    {
        cerr<<"deq error! exiting..."<<endl;
        exit(1);
    }

    T* rval=arr[0];
    arr[0]=arr[back-1]; //the element in the back moved to front
    --back;
    reheapdown(0, back-1); //reheapdown called to fix the order back 
    return rval;
}

// a copy of the front element is returned but the QueueShfe is not changed
template<class T>
T* QueueShfe<T>::front(void)
{
    if(empty())
    {
        cerr<<"deq error! exiting..."<<endl;
        exit(1);
    }

    return arr[0];
}

// a new element to put in the QueueShfe
template<class T>
void QueueShfe<T>::enq(T* foo)
{
    if(full()) //if the array is full then make it larger
    {
        int nsize=size+SIZE; //the size of the new array
        T* *narr=new T*[nsize]; //new array
        for(int i=0;i<size;++i) //copy old array to the new one
            narr[i]=arr[i];
        delete[] arr; //delete reserved old array mem
        arr=narr; //pointer update
        size=nsize; //size update
    }

    //the new element added to the back of the QueueShfe
    //and the reheapup called to fix the order back
    arr[back++]=foo; //arr[back]=foo;++back;
    reheapup(0, back-1); 
}

// this is a recursive function to fix back the order in the QueueShfe
// upwards after a new element added back (bottom) of the QueueShfe 
template<class T>
void QueueShfe<T>::reheapup(int root, int bottom)
{
    int parent; //parent node (in the virtual tree) of the bottom element

    if(bottom > root)
    {
        parent=(bottom-1)/D;

        //compare the two node and if the order is wrong then swap them
        //and make a recursive call to continue upward in the virtual tree
        //until the whole tree heap order is restored   
        if(*arr[parent] > *arr[bottom])
        {
            swap(arr[parent], arr[bottom]);
            reheapup(root, parent);
        }
    }
}

// this is a recursive function to fix back the order in the QueueShfe
// downwards after a new element added front (root) of the QueueShfe 
template<class T>
void QueueShfe<T>::reheapdown(int root, int bottom)
{
    int minchild, firstchild, child;

    firstchild=root*D+1; //the position of the first child of the root

    if(firstchild <= bottom) //if the child is in the QueueShfe
    {
        minchild=firstchild; //first child is the min child (temporarily)

        for(int i=2;i <= D;++i)
        {
            child=root*D+i; //position of the next child
            if(child <= bottom) //if the child is in the QueueShfe
            {
                //if the child is less than the current min child
                //then it will be the new min child
                if(*arr[child] < *arr[minchild])
                {
                    minchild=child;
                }
            }
        }

        //if the min child found is less then the root(parent node)
        //then swap them and call reheapdown() recursively and
        //continue to fix the order in the virtual tree downwards
        if(*arr[root] > *arr[minchild])
        {
            swap(arr[root], arr[minchild]);
            reheapdown(minchild, bottom);
        }
    } 
}

// the values of 2 variables will be swapped
template<class T>
void QueueShfe<T>::swap(T* &a, T* &b)
{
    T* c;
    c=a;
    a=b;
    b=c;
}

// destructor (because default dest. does not erase the array)
template<class T>
QueueShfe<T>::~QueueShfe(void)
{
    delete[] arr;
}

//constructor
Shfe::Shfe(void)
{
    Node* N=new Node;
    root=N;
}

//recursive func to delete the whole tree
void Shfe::chop(Node *N)
{
    if(N)
    {
        chop(N->left);
        chop(N->right);
        delete N;
    }
}

//destructor for tree objects
Shfe::~Shfe(void)
{
    chop(root);
}

unsigned int Shfe::get_freq(void) const
{
    return root->freq;
}

unsigned char Shfe::get_char(void) const
{
    return root->ch;
}

void Shfe::set_freq(unsigned int f)
{
    root->freq=f;
}

void Shfe::set_char(unsigned char c)
{
    root->ch=c;
}

Shfe::Node* Shfe::get_left(void) const
{
    return root->left;
}

Shfe::Node* Shfe::get_right(void) const
{
    return root->right;
}

void Shfe::set_left(Node* N)
{
    root->left=N;
}

void Shfe::set_right(Node* N)
{
    root->right=N;
}

Shfe::Node* Shfe::get_root(void) const
{
    return root;
}

//the recursive tree output (w/ respect to its graph) fn.
void Shfe::print(ostream & ost, Node * curr, int level) const
{
    if(curr) //if the current node is not null then
    {
        print(ost,curr->right,level+1); //try to go to right node
        //output the node data w/ respect to its level
        ost<<setw(level*width_unit)<<print_char(curr)<<":"
           <<curr->freq<<endl;
        print(ost,curr->left,level+1); //try to go to left node
    }
}

//the recursive tree print (w/ respect to its graph) fn.
void Shfe::print(Node * curr, int level) const
{
    if(curr) //if the current node is not null then
    {
        print(curr->right,level+1); //try to go to right node
        //print the node data w/ respect to its level
        cout<<setw(level*width_unit)<<print_char(curr)<<":"
            <<curr->freq<<endl;
        print(curr->left,level+1); //try to go to left node
    }
}

//utility fn to output a tree
ostream & operator<<(ostream &ost, const Shfe &t)
{
    t.print(ost, t.root, 1);
    return ost;
}

//the comparison operator overloads to compare 2 Huffman trees

bool Shfe::operator==(const Shfe & T) const
{
    return (root->freq == T.root->freq);    
}

bool Shfe::operator!=(const Shfe & T) const
{
    return (root->freq != T.root->freq);    
}

bool Shfe::operator<(const Shfe & T) const
{
    return (root->freq < T.root->freq);    
}

bool Shfe::operator>(const Shfe & T) const
{
    return (root->freq > T.root->freq);    
}

bool Shfe::operator<=(const Shfe & T) const
{
    return (root->freq <= T.root->freq);    
}

bool Shfe::operator>=(const Shfe & T) const
{
    return (root->freq >= T.root->freq);    
}

//Huffman string finder (recursive func.)
//input : a tree node to start the search, a char to find its
//        Huffman string equivalent, current Huffman string according to
//        position on the Huffman tree, and a string (by reference) to
//        copy the resulted full Huffman string end of the search
//return: none (except Huffman string by reference)
void Shfe::shf(Node* N, unsigned char c, string str, string & s) const
{
    if(N) //if the node is not null
    {
        //compare char of the leaf node and the given char
        if(!N->left && !N->right && N->ch == c)
        {
            s=str; //if the char is found then copy the H. string
        }
        else
        {
            //continue to search if the same char still not found
            shf(N->left, c, str+"0",s);
            shf(N->right, c, str+"1",s);
        }
    }
}

//Huffman char-string lister (recursive func.)
//input : a tree node to start the search, current Huffman string according to
//        position on the Huffman tree
//output: whole list of char-H. string code list of the H. tree
void Shfe::shf_list(Node* N, string str) const
{
    if(N) //if the node is not null
    {
        if(!N->left && !N->right) //if it is a leaf node
            cout<<print_char(N)<<" "<<str<<endl;
        else
        {
            //continue to search
            shf_list(N->left, str+"0");
            shf_list(N->right, str+"1");
        }
    }
}

//char finder with given Huffman string
//input : a Huffman string to traverse on the H. tree and
//        a u. char by ref. to copy the char found
//return: true if a char is found else false
bool Shfe::get_shf_char(string s, unsigned char & c) const
{
    Node * curr=root;
    for(unsigned int i=0;i<s.size();++i)
    {
        if(s[i]=='0') //go to left in the H. tree
            curr=curr->left;
        if(s[i]=='1') //go to right in the H. tree
            curr=curr->right;
    }

    bool found=false;

    if(!curr->left && !curr->right) //if it is a leaf node
    {
        found=true;
        c=curr->ch;
    }

    return found;
}

//input : a H. tree node
//return: the same char as string or if the char is not printable
//        then its octal representation in the ASCII char set
string Shfe::print_char(Node * N) const
{
    string s="";

    if(!N->left && !N->right) //if it is a leaf node
    {
        unsigned char c=N->ch;

        //if the char is not printable then output its octal ASCII code
        if(iscntrl(c) || c==32) //32:blank char
        {
            //calculate the octal code of the char (3 digits)
            char* cp=new char;
            for(int i=0;i<3;++i)
            {
                sprintf(cp,"%i",c%8);
                c-=c%8;
                c/=8;
                s=(*cp)+s;
            }
            s='/'+s; // adds \ in front of the octal code
        }
        else
            s=c;
    }
    return s;
}

//the given bit will be written to the output file stream
//input : unsigned char i(:0 or 1 : bit to write ; 2:EOF) 
void Shfe::shf_write(unsigned char i, ofstream & outfile)
{
    static int bit_pos=0; //0 to 7 (left to right) on the byte block
    static unsigned char c='\0'; //byte block to write

    if(i<2) //if not EOF
    {
        if(i==1)
            c=c | (i<<(7-bit_pos)); //add a 1 to the byte
        else //i==0
            c=c & static_cast<unsigned char>(255-(1<<(7-bit_pos))); //add a 0
        ++bit_pos;
        bit_pos%=8;
        if(bit_pos==0)
        {
            outfile.put(c);
            c='\0';
        }
    }
    else
    {
        outfile.put(c);
    }
}


//input : a input file stream to read bits
//return: unsigned char (:0 or 1 as bit read or 2 as EOF) 
unsigned char Shfe::shf_read(ifstream & infile)
{
    static int bit_pos=0; //0 to 7 (left to right) on the byte block
    static unsigned char c=infile.get();

    unsigned char i;

    i=(c>>(7-bit_pos))%2; //get the bit from the byte
    ++bit_pos;
    bit_pos%=8;
    if(bit_pos==0)
        if(!infile.eof())
        {
            c=infile.get();
        }
        else
            i=2;

    return i;     
}


//Shannon Fano Encoder
void Shfe::encode(ifstream & infile, ofstream & outfile, bool verbose)
{

    //array to hold frequency table for all ASCII characters in the file
    unsigned int f[256];
    for(int i=0;i<256;++i)
        f[i]=0;

    //read the whole file and count the ASCII char table frequencies
    char c;
    unsigned char ch;
    while(infile.get(c))
    {
        ch=c;
        ++f[ch];
    }

    infile.clear(); //clear EOF flag
    infile.seekg(0); //reset get() pointer to beginning

    QueueShfe<Shfe> q(3); //use a 3-(priority)heap
    Shfe* tp;

    for(int i=0;i<256;++i)
    {
        //output char freq table to the output file
        //divide 32 bit u. int values into 4 bytes
        outfile.put(static_cast<unsigned char>(f[i]>>24));
        outfile.put(static_cast<unsigned char>((f[i]>>16)%256));
        outfile.put(static_cast<unsigned char>((f[i]>>8)%256));
        outfile.put(static_cast<unsigned char>(f[i]%256));
 
        if(f[i]>0)
        {
            //send freq-char pairs to the priority heap as Shannon Fano trees
            tp=new Shfe;
            (*tp).set_freq(f[i]);
            (*tp).set_char(static_cast<unsigned char>(i));
            q.enq(tp);
        }
    }

    //construct the main Shannon Fano Tree
    Shfe* tp2;
    Shfe* tp3;

    do
    {
        tp=q.deq();
        if(!q.empty())
        {
            //get the 2 lowest freq. trees and combine them into one
            //and put back into the priority heap
            tp2=q.deq();
            tp3=new Shfe;
            (*tp3).set_freq((*tp).get_freq()+(*tp2).get_freq());
            (*tp3).set_left((*tp).get_root());
            (*tp3).set_right((*tp2).get_root());
            q.enq(tp3);
        }
    }
    while(!q.empty()); //until all sub-trees combined into one

    //find strings of all chars in the H. tree and put into a string table
    string S_table[256];
    unsigned char uc;
    for(unsigned short us=0;us<256;++us)
    {
        S_table[us]="";
        uc=static_cast<unsigned char>(us);
        (*tp).shf((*tp).get_root(), uc, "", S_table[us]);
    } 

    if(verbose)
    {
        cout<<*tp<<endl; //output the Shannon Fano tree
        //output the char-H. string list 
        (*tp).shf_list((*tp).get_root(), "");
        cout<<"frequency table is "<<sizeof(unsigned int)*256<<" bytes"<<endl;
    }

    unsigned int total_chars=(*tp).get_freq();
    // cout<<"total chars to encode:"<<total_chars<<endl;

    //output Shannon Fano coded chars into the output file
    unsigned char ch2;
    while(infile.get(c))
    {
        ch=c;
        //send the Shannon Fano string to output file bit by bit
        for(unsigned int i=0;i<S_table[ch].size();++i)
        {
            if(S_table[ch].at(i)=='0')
                ch2=0;
            if(S_table[ch].at(i)=='1')
                ch2=1;
            shf_write(ch2, outfile);
        }
    }
    ch2=2; // send EOF
    shf_write(ch2, outfile);

    infile.close();
    outfile.close();

} //end of Shannon Fano encoder


//Shannon Fano Decoder
void Shfe::decode(ifstream & infile, ofstream & outfile,bool verbose)
{

    //read frequency table from the input file
    unsigned int f[256];
    char c;
    unsigned char ch;
    unsigned int j=1;
    for(int i=0;i<256;++i)
    {
        //read 4 bytes and combine them into one 32 bit u. int value
        f[i]=0;
        for(int k=3;k>=0;--k)
        {
            infile.get(c);
            ch=c;
            f[i]+=ch*(j<<(8*k));
        }
    }

    //re-construct the Shannon Fano Huff
    QueueShfe<Shfe> q(3); //use a 3-(priority)heap (again)
    Shfe* tp;

    for(int i=0;i<256;++i)
    {
        if(f[i]>0)
        {
            //send freq-char pairs to the priority heap as Shannon Fano trees
            tp=new Shfe;
            (*tp).set_freq(f[i]);
            (*tp).set_char(static_cast<unsigned char>(i));
            q.enq(tp);
        }
    }

    //construct the main Shannon Fano Tree (as in Encoder func.)
    Shfe* tp2;
    Shfe* tp3;

    do
    {
        tp=q.deq();
        if(!q.empty())
        {
            //get the 2 lowest freq. S. trees and combine them into one
            //and put back into the priority heap
            tp2=q.deq();
            tp3=new Shfe;
            (*tp3).set_freq((*tp).get_freq()+(*tp2).get_freq());
            (*tp3).set_left((*tp).get_root());
            (*tp3).set_right((*tp2).get_root());
            q.enq(tp3);
        }
    }
    while(!q.empty()); //until all sub-trees combined into one

    if(verbose)
    {
        cout<<*tp<<endl; //output the Shannon Fano tree
        //output the char-S. string list 
        (*tp).shf_list((*tp).get_root(), "");
        cout<<"frequency table is "<<sizeof(unsigned int)*256<<" bytes"<<endl;
    }

    //read Shannon Fano strings from the input file
    //find out the chars and write into the output file
    string st;
    unsigned char ch2;
    unsigned int total_chars=(*tp).get_freq();
    // cout<<"total chars to decode:"<<total_chars<<endl;
    while(total_chars>0) //continue until no char left to decode 
    {
        st=""; //current Shannon Fano string
        do
        {
            //read H. strings bit by bit
            ch=shf_read(infile);
            if(ch==0)
                st=st+'0';
            if(ch==1)
                st=st+'1';
        } //search the H. tree
        while(!(*tp).get_shf_char(st, ch2)); //continue until a char is found

        //output the char to the output file
        outfile.put(static_cast<char>(ch2));
        --total_chars;
    }

    infile.close();
    outfile.close();

} //end of Shannon Fano decoder



void Shfe::Start(string ifile) {
    
    ifstream infile(ifile.c_str(), ios::in|ios::binary);

    if(!infile)
    {
        cerr <<ifile <<" nao pode ser aberto!" << endl;
        exit(EXIT_FAILURE);
    }

    Common tool;
    string ext = ".shfe";

    string hash1 = tool.hashfile(infile);

    int total = tool.sizefile(infile);

    string ofile = ifile.substr(ifile.rfind('/')+1,ifile.size()) + ext;

    if(ifstream(ofile.c_str()))
    {
        cerr<<ofile<<" ja existe!"<<endl;
        exit(EXIT_FAILURE);
    }

    //open the output file
    ofstream outfile(ofile.c_str(), ios::out|ios::binary);
    if(!outfile)
    {
        cerr<<ofile<<" nao pode ser aberto!"<<endl;
        exit(EXIT_FAILURE);
    }
    // tudo pronto para comprimir

    tool.Startcount();
    encode(infile,outfile,false);
    double finalTime = tool.Endcount();

    infile.close();
    outfile.close();

    infile.open(ofile, ios::in|ios::binary);

    int totalComp = tool.sizefile(infile);

    cout << "\n[Compressao Finalizada]\n";
    cout << "\tEm "<< finalTime << "s\n";
    cout << "\tCompressao de "<< tool.cmprssratio(total,totalComp) << "%\n";

    string decompFile = ofile.substr(0,ofile.size()-ext.size());

    outfile.open(decompFile,ios::out|ios::binary);

    decode(infile,outfile,false);

    infile.close();
    outfile.close();

    infile.open(decompFile, ios::in|ios::binary);
    string hash2 = tool.hashfile(infile);
    if (hash1 == tool.hashfile(infile)) {
        cout << "\tArquivos identicos\n";
    } else {
        cout << "\tArquivos diferentes\n";
    }
    cout << hash1 << endl;
    cout << hash2 << endl;
}