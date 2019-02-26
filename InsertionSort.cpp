
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;
//Node object that will hold the data of the list
struct Node
{
public:
	Node * next = NULL;
	Node * previous = NULL;
	int value;
};

struct List
{
public:
	Node *head;
	Node *tail;
	int size;
	//Constructor of the list
	List()
	{
		Node *node1 = new Node();
		head = node1;
		Node *node2 = new Node();
		tail = node2;
		size = 0;
	}
	//Pushes an object into the list
	void push(int x)
	{
		Node *temp = new Node();
		temp->value = x;
		if (size == 0)
		{
			temp->next = tail;
			tail->previous = temp;
		}
		
		if (size > 0)
		{
			head->next->previous = temp;
			temp->next = head->next;
		}
		temp->previous = head;
		head->next = temp;
		size++;
	}
	//prints out the list.  for testing purposes only. 
	void print()
	{
		Node *temp = head->next;
		for (int i = 0; i < size; i++)
		{
			cout << temp->value << " ";
			temp = temp->next;
		}
	}
	//sorts the list
	void sort()
	{
		Node *temp = head->next;
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{

			}
			else
			{
				temp = head->next;
				int j = 0;
				while (j < i)
				{
					j++;
					temp = temp->next;
				}
				while (temp->previous != head && temp->value < temp->previous->value)
				{
					Node * switcher;
					switcher = temp->previous;
					switcher->previous->next = temp;
					temp->next->previous = switcher;
					temp->previous = switcher->previous;
					switcher->next = temp->next;
					temp->next = switcher;
					switcher->previous = temp;
				}
			}
		}
	}
};
int main(int argc, char *argv[])
{
	//error that will occur if file names are not included
	if(argc != 3)
	{
		cout << "Please enter input/output file names";
		exit(1);
	}

	ifstream reader;
	reader.open(argv[1]);
	//error that occurs if the input file could not be opened
	if (!reader)
	{
		cerr << "Unable to open file for the input!";
		exit(2);
	}
	
	List list;
	int input;
	//reads from input file and pushes the ints into the list
	while(reader >> input)
	{
		list.push(input);
	}

	ofstream writer;
	writer.open(argv[2]);
	//Error that occurs if the file that is meant to be written to cannot be opened
	if(!writer)
	{
		cerr << "Unable to open file to writing!";
		exit(3);
	}
	//function call that sorts the list
	list.sort();
	
	Node *temp = list.head->next;
	//for loop used to write the output file
	for(int i = 0; i < list.size; i++)
	{
		writer << temp->value << "\n";
		temp = temp->next;
	}
	
	reader.close();
	writer.close();
	return 0;
}

