#ifndef BOOKTREE_H
#define BOOKTREE_H
#include <string>
#include <iostream>
using namespace std;
#define DELIMITER " "
class Tester;//test cases
class BookTree;
class BNode;
class Wordtree;
class Book {
public:
    Book(string author, string title, string text) {
        m_author = author; m_title = title; m_text = text;
    }
    string m_author;
    string m_title;
    string m_text;
};

class Node {
public:
    friend class Tester;
    friend class WordTree;
    friend class BookTree;
    Node(const string& v) {
        m_word = v;
        m_left = nullptr; m_right = nullptr; m_height = 0; m_count = 0;
    }
    void printWord() { cout << m_word << endl; }
    int getFrequency() { return m_count; }
    int getHeight() { return m_height; }
    string getValue() { return m_word; }
private:
    string  m_word;
    Node* m_left;
    Node* m_right;
    int     m_height;
    int     m_count;
};

class WordTree {
public:
    friend class Tester;
    friend class BookTree;
    WordTree() { m_root = nullptr; }
    ~WordTree();
    void insert(const string& word);
    Node* find(const string& word);
    bool remove(const string& word);
    void dump(std::ostream& ostr = std::cout);
    int searchCount(string word);
    int getTreeHeight();

private:
    Node* m_root;

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************

    void deleteTree(Node*);

    Node* findNode(Node*, const string&);

    Node* removeNode(Node*, const string&);

    int searchNode(Node*, const string&, int);

    Node* insertion(Node*, Node*);

    int isBalance(Node*);

    Node* balance(Node*, Node*);

    Node* leftRotate(Node*);

    Node* rightRotate(Node*);

    int getHeightNode(Node*);

    void dump(Node* aNode, std::ostream& ostr);
};

class BNode {
public:
    friend class Tester;
    friend class BookTree;
    BNode();
    BNode(string title, string author, string text);
    ~BNode();
    int findFrequency(string word);
    int searchCount(string word);
    int getTextTreeHeight();

private:
    string m_title;
    string m_author;
    WordTree m_tree;
    BNode* m_left;
    BNode* m_right;

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************

};

class BookTree {
public:
    friend class Tester;
    BookTree();
    ~BookTree();
    void dump(bool verbose = false) const;
    void loadData(Book data[], int arrayLength);
    bool insert(string title, string author, string text);
    int findFrequency(string title, string word);
    bool removeWord(string title, string word);
    int searchCount(string title, string word);
    int getTextTreeHeight(string title);
    string getRootKey();//returns the book title at root

private:
    BNode* m_root;

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************

    void deleteTree(BNode*);

    BNode* findTitle(BNode*, string);

    BNode* findParentTitle(BNode*, string);

    BNode* splay(BNode*, string);

    BNode* leftRotate(BNode*);

    BNode* rightRotate(BNode*);

    void dumpHelper(BNode* root, bool verbose = false) const;

};
#endif