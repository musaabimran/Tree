/*
musaab imran
20i-1794
section A
*/


// list of libraries
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

// node class
class node
{
public:
	string value;
	string URL;
	node* left;
	node* right;
};


// bst class
class tree
{
public:
	node* root;

	// constructor
	tree()
	{
		root = NULL;
	}


	// insertion function
	void insert(string url, string str)
	{
		node* temp, * tempsave;
		temp = new node;
		temp->left = temp->right = NULL;
		temp->value = str;

		temp->URL = "->";
		temp->URL += url;
		int count = 0;

		if (root == NULL)
		{
			root = temp;
		}

		else
		{
			tempsave = root;

			while (tempsave != NULL)
			{
				if (str < tempsave->value)
				{
					if (tempsave->left)
					{
						tempsave = tempsave->left;
					}

					else
					{
						tempsave->left = temp;
						break;
					}
				}

				else if (str > tempsave->value)
				{
					if (tempsave->right)
					{
						tempsave = tempsave->right;

					}

					else
					{
						tempsave->right = temp;
						break;
					}
				}


				// dealing with eqaulity cases
				// removing duplicates
				// adding up url in the strings

				else if (str == tempsave->value)
				{

					// checking the cases of same URL of same words
					if (tempsave->URL.find(temp->URL) != string::npos)
					{
						break;
					}

					else
					{

						tempsave->URL += " \n\t\t\t ";
						tempsave->URL += temp->URL;
						break;
					}

				}


			}
		}

	}


	// calling of insertion function and breaking of full sentences into tokens
	void insertcalling(string ul, string s2)
	{

		// making indexex spaces
		string token;
		ul[0] = ' ';
		ul[1] = ' ';


		istringstream tk(s2);
		while (tk)
		{
			tk >> token;

			insert(ul, token);
		}
	}

	// find function
	node* find(string str)
	{
		node* temp = root;

		while (temp)
		{
			// return the node when the value is found
			if (temp->value == str)
			{
				return temp;
			}


			// traversal cases
			else if (str < temp->value)
			{
				temp = temp->left;
			}

			else
			{
				temp = temp->right;
			}
		}

	}

	// bool find function to check
	// if the value is present or not
	bool check(string str)
	{
		node* temp = root;

		while (temp)
		{

			// return the node when the value is found
			if (temp->value == str)
			{
				return true;
			}


			// traversal cases
			else if (str < temp->value)
			{
				temp = temp->left;
			}

			else
			{
				temp = temp->right;
			}
		}

		// if not found
		return false;
	}


	// calling of delete function
	void delete_call(string str)
	{
		delete_node(root, str);
	}


	// delete node 
	void delete_node(node*& ptr, string s1)
	{
		if (ptr == NULL) // 
		{
			cout << " Word not found " << endl;
		}

		// find in left subtree
		else if (s1 < ptr->value)
		{
			delete_node(ptr->left, s1);
		}

		// find in right subtree
		else if (s1 > ptr->value)
		{
			delete_node(ptr->right, s1);
		}

		// actually deletes node from BST
		else
		{
			deletion(ptr);
		}
	}

	//passing the node and deleting 
	void deletion(node*& cur)
	{
		// Temperary pointer
		node* tempnode;

		//if right not exist than was left child
		if (cur->right == NULL)
		{
			tempnode = cur; //assigning

			// assiging to left child == = in this case null
			cur = cur->left;
			delete tempnode; //deleting leaf
		}

		//if was on right
		else if (cur->left == NULL)
		{

			tempnode = cur;
			cur = cur->right; //assign to right
			delete tempnode;
		}


		//if the both are there
		else
		{

			tempnode = cur->right;

			//finding the place in the left most side of right tree
			while (tempnode->left)
			{
				tempnode = tempnode->left;
			}

			//now assiging the child to left
			tempnode->left = cur->left;

			//now assigning the one to delete
			tempnode = cur;
			cur = cur->right;
			delete tempnode;
		}
	}

	// display call for key words
	void displayIn()
	{
		cout << " In-order : " << endl;
		displayRecursivelyIn(root);
		cout << endl;
	}

	void displayRecursivelyIn(node* start)
	{
		if (start)
		{
			displayRecursivelyIn(start->left);
			cout << start->value << "\t";
			displayRecursivelyIn(start->right);
		}
	}


	// display call for both url and keywords
	void displayInOrder()
	{
		cout << " In-order : " << endl;
		displayRecursivelyInorder(root);
		cout << endl;
	}

	void displayRecursivelyInorder(node* start)
	{
		if (start)
		{
			displayRecursivelyInorder(start->left);
			cout << start->value << " \t\t\t" << start->URL << endl;
			displayRecursivelyInorder(start->right);
		}
	}
};


// driver function
int main()
{
	// initialization
	tree t;
	fstream file;
	string read, save_url, save_text, findd, save, delval, file_name, search;
	int choice = 0;
	bool check = true;


menu1:
	cout << " Enter the name of the file: ";
	cin >> file_name;

	// file handling
	file.open(file_name, ios::in);

	// reading the file
	if (file.is_open())
	{
		cout << " File has been loaded!!! " << endl;
		cout << " Enter the word you want to search: ";
		cin >> search;


		while (file.good())
		{
			// reading the url line
			getline(file, read);
			save_url = read;
			//cout << save_url << endl;

			// reading the sentence
			getline(file, read);
			save_text = read;

			if (save_text.find(search) != string::npos)
			{
				cout << save_url << endl;
			}

			else
			{
				check = false;
			}
			//cout << save_text << endl;

			// reading the empty line
			getline(file, read);

			// senting url and sentence 
			// sentence will be converted to tokens

			t.insertcalling(save_url, save_text);
		}
	}

	// if file is not good
	// wrong file name
	else
	{
		cout << " Unable to open the File";
		goto menu1;
	}

	// closing the file
	file.close();




	// main menu
menu:
	cout << endl;
	cout << endl;
	cout << "\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
	cout << "\t\t\t\t | ::WELCOME TO SEARCH ENGINE::                  |" << endl;
	cout << "\t\t\t\t | 1. Enter 1 to View all the keyword and URLs:  |" << endl;
	cout << "\t\t\t\t | 2. Enter 2 to List of all the keywords:       |" << endl;
	cout << "\t\t\t\t | 3. Enter 3 to Find a keyword:                 |" << endl;
	cout << "\t\t\t\t | 4. Enter 4 to Delete a keyword:               |" << endl;
	cout << "\t\t\t\t | 5. Enter 5 to EXIT:                           |" << endl;
	cout << "\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;


	cout << "\t\t\t\t ENTER: ";
	cin >> choice;
	cout << endl;


	// to deal with diff cases
	switch (choice)
	{
		// displaying all the keywords and their urls
	case 1:
		t.displayInOrder();
		cout << endl;
		goto menu;

		// displaying only the list of keywords
	case 2:
		t.displayIn();
		cout << endl;
		goto menu;

		// finding the url based on keyword
	case 3:
		cout << " Enter the word you want to search: ";
		cin >> findd;

		if (t.check(findd))
		{
			save = t.find(findd)->URL;
			cout << "\t\t\t";
			cout << save << endl;
		}
		else
		{
			cout << " Word is not found! " << endl;
		}
		goto menu;

		// deleting the value (keyword)
	case 4:
		cout << " Enter the word you want to delete: ";
		cin >> delval;
		t.delete_call(delval);
		goto menu;

		// break case
	case 5:
		break;

		// default case
	default:
		break;

	}

	// end of driver function
	return 0;
}