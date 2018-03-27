#include <bits/stdc++.h>
#define MAX_TREE_HT 256
using namespace std;

// to map each character its huffman value
map<char, string> codes;

// to store the frequency of character of the input data
map<char, int> freq;


struct MinHeapNode
{
    char data;
    int freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// utility function for the priority queue
struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void storeCodes(struct MinHeapNode* root, string str)
{
    if (root==NULL)
        return;
    if (root->data != '$')
        codes[root->data]=str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect
// to their heap root node value
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size)
{
    struct MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++)
        minHeap.push(new MinHeapNode(v->first, v->second));
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void calcFreq(string str, int n)
{
    for (int i=0; i<str.size(); i++)
        freq[str[i]]++;
}

string decode_file(struct MinHeapNode* root, string s)
{
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '0')
           curr = curr->left;
        else
           curr = curr->right;

        // reached leaf node
        if (curr->left==NULL and curr->right==NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }

    return ans+'\0';
}

 int binaryToDecimal(int n)
{
    int num = n;
    int dec_value = 0;

    int base = 1;

    int temp = num;
    while(temp)
    {
        int last_digit = temp % 10;
        temp = temp/10;

        dec_value += last_digit*base;

        base = base*2;
    }

    return dec_value;
}

int encrypt(string g){

    int len=g.length();
    len=len-4;
    int public_key=0b1001;
    int private_key=0b1000;
//  cout<<private_key<<endl;
    int z=binaryToDecimal(stoi(g));
    int k=public_key<<len; //shifted first time
//  cout<<len<<endl;
//  cout<<k<<endl;

    for(int i=0;i<len+1;i++){
        z=z^k;
        k=k>>1;
    }
//  cout<<z<<endl;
    int mul=z*private_key;
//  cout<<mul<<endl;     // incrption complete
    return mul;
}

int main()
{
    string str = "geeksforgeeks";
    string encodedString, decodedString;
    calcFreq(str, str.length());
    HuffmanCodes(str.length());
    cout << "Character With there Frequencies:\n";
    for (auto v=codes.begin(); v!=codes.end(); v++)
        cout << v->first <<' ' << v->second << endl;

    for (auto i: str)
        encodedString+=codes[i];

    cout << "\nEncoded Huffman data:\n" << encodedString << endl;


    int encrypted_data=encrypt(encodedString);
    //int a = 20;
   // std::string s = to_string(encrypted_data);
    //cout<<s<<endl;

    //string decrypted_data=decrypt(encrypted_data);

    decodedString = decode_file(minHeap.top(), encodedString);
    cout << "\nDecoded Huffman Data:\n" << decodedString << endl;
    return 0;
}
