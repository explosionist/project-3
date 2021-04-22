#include <stdio.h>
#include <iostream>
#include <string>
#include "util.h"
#include "heap.h"

using namespace std;


int nextCommand(string* s, string* d, string* f)
{

	cin.clear();

	int index = 0;



	string input;
	getline(cin, input);

	int size = 0;

	string words[5];
	int i = 1;

	while (input.find(" ") != string::npos)
	{
		if (i < 4)
		{
			words[i] = input.substr(0, input.find(" "));
			i++;
		}
		input = input.substr(input.find(" ") + 1, input.length());
		size++;
	}

	words[i] = input.substr(0, input.find(" "));
	size++;


	if (size != 1 && size != 4)
	{
		return -1;
	}


	if (size == 1 && words[1].compare("stop") == 0)
	{
		return '0';
	}


	if (words[1].compare("find") == 0)
	{
		*s = words[2];
		*d = words[3];
		*f = words[4];
		return '1';
	}


	if (words[1].compare("write") == 0 && words[2].compare("path") == 0)
	{
		*s = words[3];
		*d = words[4];
		return '2';
	}


	return -1;
}









/*
int nextCommand(int* s, int* d, int* f)
{
	cin.sync();
	string command;
	char c;
	while (1)
	{
		cin >> command;

		if (command == " ")
		{
			continue;
		}


		if (command == "stop")
		{
			c = '0';
			break;
		}


		if (command == "find")
		{
			c = '1';
			cin >> *s >> *d >> *f;

			break;
		}


		if (command.compare("write path"))
		{
			string g;
			c = '2';
			cin >> g >> *s >> *d;

			break;
		}


	}
	printf("this is c: %d", c);
	return c;
}
*/

