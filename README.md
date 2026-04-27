------------* Natural Language Processing *------------

Description:
	This project Allows for the storage of book and there words.
	The books are stored in a binary search tree.
	While the words are stored in a splay tree allowing for easy access of common words.
	There are also functions that allowing for searching these tree for information such as word count and height of tree.

Technical Description:
	structure:
		Book tree (BST) holds BNodes which they themselves hold the books information as well a splay tree.
		They splay tree holds nodes which contain the word from the book
		
		BST(Book Tree)
		 |
		BNode
		/   \
	  Book  SplayTree(Words of the Book)
			    |
		      Node(individual nodes)
	
