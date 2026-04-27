//UMBC - CSEE - CMSC 341 - Fall 2025 - Proj2
#include "booktree.h"
BookTree::BookTree() {
    m_root = nullptr;
}

BookTree::~BookTree() {
    deleteTree(m_root);
}

void BookTree::deleteTree(BNode* node) {//deletes splay tree called by decostructor
    if (node == nullptr) {
        return;
    }
    deleteTree(node->m_left);
    deleteTree(node->m_right);

    delete node;
}

void BookTree::loadData(Book data[], int arrayLength) {//loads data
    for (int i = 0; i < arrayLength; i++) {
        insert(data[i].m_title, data[i].m_author, data[i].m_text);
    }
}

bool BookTree::insert(string title, string author, string text) {//inserts book into splay tree
    BNode* node = findTitle(m_root, title);//check if book already exists

    if (node != nullptr) {//book exist already
        return false;
    }

    node = new BNode(title, author, text);
    BNode* pNode = findParentTitle(m_root, title);
    if (pNode == nullptr) {//check to see if node is the root probably could have just went if(m_root == nullptr) but we are here already
        m_root = node;
    }
    else if (pNode->m_title > title) {//check to see if it less than
        pNode->m_left = node;
    }
    else {//check for more than
        pNode->m_right = node;
    }
    m_root = splay(m_root, node->m_title);//splay the new node
    return true;
} 

int BookTree::findFrequency(string title, string word) {//find the frequency of a word
    if (m_root == nullptr) {
        return 0;
    }

    BNode* node = findTitle(m_root, title);

    if (node == nullptr) {//find parent node if node doesn't exist and splay it
        node = findParentTitle(m_root, title);
        if (node != nullptr) {
            m_root = splay(m_root, node->m_title);
        }
        return 0;
    }
    m_root = splay(m_root, node->m_title);//splay node
    return node->findFrequency(word);
}

int BookTree::searchCount(string title, string word) {//count amount of words in a book
    BNode* node = findTitle(m_root, title);

    if (node == nullptr) {//finds parent title if title doesn't exist and splays it
        node = findParentTitle(m_root, title);
        if (node != nullptr) {
           m_root = splay(m_root, node->m_title);
        }
        return 0;
    }
    m_root = splay(m_root, node->m_title);
    return node->searchCount(word);//calls function in BNode
}

int BookTree::getTextTreeHeight(string title) {//gets tree height
    BNode* node = findTitle(m_root, title);

    if (node == nullptr) {
        return -1;
    }

    m_root = splay(m_root, node->m_title);
    return node->getTextTreeHeight();
} 

string BookTree::getRootKey() {
    // implementation is provided
    // do not modify this function
    return m_root->m_title;
}

bool BookTree::removeWord(string title, string word) {//removes word
    BNode* node = findTitle(m_root, title);

    if (node == nullptr) {
        return false;
    }
    return node->m_tree.remove(word);//calls BNodes AVL remove function
}


BNode* BookTree::findTitle(BNode* node, string title) {//finds a title from root of splay tree
    if (node == nullptr) {
        return nullptr;
    }

    if (node->m_title == title) {//found title
        return node;
    }

    else if (title < node->m_title) {//recursive function call left subtree
        return findTitle(node->m_left, title);
    }
    else {//recursive function call right subtree
        return findTitle(node->m_right, title);
    }
}

BNode* BookTree::findParentTitle(BNode* node, string title) {//find parent node of a title
    if (node == nullptr) {
        return nullptr;
    }

    if ((title < node->m_title && node->m_left == nullptr) ||
        (title > node->m_title && node->m_right == nullptr)) //if parent node return
        return node;

    if (title < node->m_title) {//left subtree recusive call
        return findParentTitle(node->m_left, title);
    }
    else if (title > node->m_title) {//right subtree recusive call
        return findParentTitle(node->m_right, title);
    }
    else {//I don't think anything can/should meet this condition as == call should return parrent
        return nullptr;
    }
}

BNode* BookTree::splay(BNode* node, string title) {//spaly tree
    if (node == nullptr || node->m_title == title) {
        return node;
    }

    // Left subtree
    if (title < node->m_title) {
        if (node->m_left == nullptr)
            return node;

        // Zig-Zig (Left Left)
        if (title < node->m_left->m_title) {
            node->m_left->m_left = splay(node->m_left->m_left, title);
            node = rightRotate(node);
        }
        // Zig-Zag (Left Right)
        else if (title > node->m_left->m_title) {
            node->m_left->m_right = splay(node->m_left->m_right, title);

            if (node->m_left->m_right != nullptr) {
                node->m_left = leftRotate(node->m_left);
            }
        }

        if (node->m_left == nullptr) {
            return node;
        }
        else {
            return rightRotate(node);
        }
    }

    // Right subtree
    else {
        if (node->m_right == nullptr)
            return node;

        // Zig-Zig (Right Right)
        if (title > node->m_right->m_title) {
            node->m_right->m_right = splay(node->m_right->m_right, title);
            node = leftRotate(node);
        }
        // Zig-Zag (Right Left)
        else if (title < node->m_right->m_title) {
            node->m_right->m_left = splay(node->m_right->m_left, title);

            if (node->m_right->m_left != nullptr) {
                node->m_right = rightRotate(node->m_right);
            }
        }

        if (node->m_right == nullptr) {
            return node;
        }
        else {
            return leftRotate(node);
        }
    }
}

BNode* BookTree::rightRotate(BNode* node) {//right rotation
    BNode* hold = node->m_left;
    node->m_left = hold->m_right;
    hold->m_right = node;
    return hold;
}

BNode* BookTree::leftRotate(BNode* node) {//left rotation
    BNode* hold = node->m_right;
    node->m_right = hold->m_left;
    hold->m_left = node;
    return hold;
}



void BookTree::dump(bool verbose) const {
    //cout << "m_root is " << m_root->m_title << endl;
    dumpHelper(m_root, verbose);
    cout << endl;
}

void BookTree::dumpHelper(BNode* root, bool verbose) const {
    if (root != nullptr) {
        if (verbose) {
            cout << "(";
            dumpHelper(root->m_left, verbose);
            cout << root->m_title << ":" << root->m_author;
            root->m_tree.dump();
            dumpHelper(root->m_right, verbose);
            cout << ")";
        }
        else {
            cout << "(";
            dumpHelper(root->m_left, verbose);
            cout << root->m_title;
            dumpHelper(root->m_right, verbose);
            cout << ")";
        }
    }
}
///////////////////////////////////////////////////////////////////
WordTree::~WordTree() {
    deleteTree(m_root);//call recursive deletetion of avl tree
}

void WordTree::deleteTree(Node* node) {//recursive deletetion of avl tree
    if (node == nullptr) {
        return;
    }
    deleteTree(node->m_left);
    deleteTree(node->m_right);

    delete node;
}

Node* WordTree::find(const string& word) {//call recursive function
    return findNode(m_root, word);
}

bool WordTree::remove(const string& word) {//call recursive function than
    if (findNode(m_root, word) == nullptr) {//if word doesn't exist
        return false;
    }
    m_root = removeNode(m_root, word);//delete word and update root
    return true;
}

void WordTree::insert(const string& word) {//insert word
    Node* node = find(word);//find word
    if (node != nullptr) {//if found update the count and return
        node->m_count++;
        return;
    }
    node = new Node(word);//word doesn't exist so make one
    node->m_count = 1;

    if (m_root == nullptr) {//if no root
        m_root = node;
    }
    else {
       m_root = insertion(m_root, node);
    }
}

int WordTree::searchCount(string word) {//recusive call to a private function
    int start = 0;
    return searchNode(m_root, word, start);
}

int WordTree::getTreeHeight() {
    // implementation is provided
    // do not modify this function
    return m_root->m_height;
}

Node* WordTree::findNode(Node* node, const string& word) {//find node through recusrsion
    if (node == nullptr) {
        return nullptr;
    }
    //left
    else if (node->m_word > word) {//less than
        return findNode(node->m_left, word);
    }
    //right
    else if (node->m_word < word) {
        return findNode(node->m_right, word);
    }
    else {//found
        return node;
    }
}

Node* WordTree::removeNode(Node* node, const string& word) {//removes node through recusion
    if (word < node->getValue()) {
        node->m_left = removeNode(node->m_left, word);
    }

    else if (word > node->getValue()) {
        node->m_right = removeNode(node->m_right, word);
    }
    else {// Node found
        if (node->m_left == nullptr || node->m_right == nullptr) {
            Node* temp = node->m_left ? node->m_left : node->m_right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }
            delete temp;
        }
        else { // Two children find inorder successor
            Node* temp = node->m_right;
            while (temp->m_left != nullptr)
                temp = temp->m_left;
            node->m_word = temp->m_word;
            node->m_count = temp->m_count;
            node->m_right = removeNode(node->m_right, temp->m_word);
        }
    }

    if (node == nullptr) {
        return node;
    }
   
    
    node->m_height = max(getHeightNode(node->m_left), getHeightNode(node->m_right)) + 1;//get height value for current node

    int balance = isBalance(node);//balance

    if (balance > 1 && isBalance(node->m_left) >= 0) {//left left
        return rightRotate(node);
    }

    if (balance > 1 && isBalance(node->m_left) < 0) {//left right
        node->m_left = leftRotate(node->m_left);
        return rightRotate(node);
    }

    if (balance < -1 && isBalance(node->m_right) <= 0) {//right right
        return leftRotate(node);
    }
    
    if (balance < -1 && isBalance(node->m_right) > 0) {//right left
        node->m_right = rightRotate(node->m_right);
        return leftRotate(node);
    }

    return node;
}

int WordTree::isBalance(Node* node) {// returns value of child nodes
    if(node == nullptr){
        return 0;
    }
    int h1 = getHeightNode(node->m_left);//get the height of node safe call
    int h2 = getHeightNode(node->m_right);
    return h1 - h2;
}

Node* WordTree::insertion(Node* node, Node* insert) {//recuvsive function for insert
    if (node == nullptr) {
        return insert;
    }

    if (insert->getValue() < node->getValue()) {//left
        node->m_left = insertion(node->m_left, insert);
    }

    else if (insert->getValue() > node->getValue()) {//right
        node->m_right = insertion(node->m_right, insert);
    }


    node->m_height = max(getHeightNode(node->m_left), getHeightNode(node->m_right)) + 1;//set node height


    return balance(node, insert);//call balance funtion to rebalance tree if need be
}

Node* WordTree::balance(Node* node, Node* insert) {//recursive balance function
    int balance = isBalance(node);//check if current node is balance


    if (balance > 1 && insert->getValue() < node->m_left->getValue()) {//right
        return rightRotate(node);
    }


    if (balance < -1 && insert->getValue() > node->m_right->getValue()) {//left
        return leftRotate(node);
    }

    if (balance > 1 && insert->getValue() > node->m_left->getValue()) {//left right
        node->m_left = leftRotate(node->m_left);
        return rightRotate(node);
    }

    if (balance < -1 && insert->getValue() < node->m_right->getValue()) {//right left
        node->m_right = rightRotate(node->m_right);
        return leftRotate(node);
    }

    return node;
}

Node* WordTree::leftRotate(Node* node) {//left rotation
    Node* right = node->m_right;//get right node
    Node* left = right->m_left;//left node

    right->m_left = node;//set right value to node
    node->m_right = left;//node value right is now left


    node->m_height = max(getHeightNode(node->m_left), getHeightNode(node->m_right)) + 1;//set height
    right->m_height = max(getHeightNode(right->m_left), getHeightNode(right->m_right)) + 1;//set height

    return right;//return new parent node
}

Node* WordTree::rightRotate(Node* node) {//right rotation 
    Node* left = node->m_left;//left node
    Node* right = left->m_right;//right node

    left->m_right = node;//left node right is now node
    node->m_left = right;//nodes left is now right

    

    node->m_height = max(getHeightNode(node->m_left), getHeightNode(node->m_right)) + 1;//set height
    left->m_height = max(getHeightNode(left->m_left), getHeightNode(left->m_right)) + 1;//set height

    return left;//return new parent node
}

int WordTree::searchNode(Node * node,const string& word, int start) {//recusive function for I think serachCount
    if (node == nullptr || node->getValue() == word) {//if found or not
        return start;
    }
    else if (node->getValue() > word) {// go left
        return searchNode(node->m_left, word, start+ 1);
    }
    else {//go right
        return searchNode(node->m_right, word, start+ 1);
    }
}

int WordTree::getHeightNode(Node* node) {//get height of a node
    if (node == nullptr) {
        return -1;
    }
    else {
        return node->getHeight();
    }
}

void WordTree::dump(std::ostream& ostr) {
    dump(m_root, ostr);
}

void WordTree::dump(Node* aNode, std::ostream& ostr) {
    if (aNode != nullptr) {
        ostr << "[";
        dump(aNode->m_left, ostr);//first visit the left child
        ostr << aNode->m_word << ":" << aNode->m_count << ":" << aNode->m_height;//second visit the node itself
        dump(aNode->m_right, ostr);//third visit the right child
        ostr << "]";
    }
}
////////////////////////////////////////////////////////////
BNode::BNode() {
    m_title = "";
    m_author = "";
    m_left = nullptr;
    m_right = nullptr;
}

BNode::BNode(string title, string author, string text) {
    m_title = title;
    m_author = author;
    m_left = nullptr;
    m_right = nullptr;

    string word = "";

    for (size_t i = 0; i <= text.size(); i++) {
        char c = (i < text.size()) ? text[i] : ' ';  //add space at end for delemnation

        //convert uppercase to lowercase
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }

        //if its a letter or digit add it
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            word += c;
        }
        else {
            //word boundary for space or punction
            if (!word.empty()) {
                m_tree.insert(word);
                word = "";
            }
        }
    }
}

BNode::~BNode() {
    m_left = nullptr;
    m_right = nullptr;
}

int BNode::findFrequency(string word) {
    Node* node = m_tree.find(word);
    if (node == nullptr) {
        return 0;
    }
    return node->getFrequency();
}

int BNode::searchCount(string word) {//call tree class function
    return m_tree.searchCount(word);
}

int BNode::getTextTreeHeight() {//call tree class function
    return m_tree.getTreeHeight();
}
