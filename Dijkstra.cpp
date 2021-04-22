#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include  <sstream>
#include  <fstream>
#include <string>
#include "heap.h"
#include "util.h"
#include "graph1.h"


using namespace std;


int main(int argc, char** argv)
{
	string str1, tempstr;
	char c;
	int SIZE, EDGE, Dir = -1;
	string s, d, f;
	int E, U, V = -1;
	float W = 0.0;
	int source, dest = 0;
	ifstream file;

	file.open(argv[1]);				// read file name to "file"

	if (!file)
	{
		cout << "Error: cannot open file for reading" << endl;		// report if doesn't find the txt file
		return 1;
	}

	if (strcmp(argv[2], "directed") == 0)
	{
		Dir = 1;
	}

	else if (strcmp(argv[2], "undirected") == 0)
	{
		Dir = 0;
	}


	file >> SIZE >> EDGE;					// store number of node into "SIZE", and number of edge to "EDGE"			

	graph1 G(SIZE, Dir);			// set direction and size

	while (file >> E >> U >> V >> W)			// read each line of the file
	{
		G.initAdj(U, V, W);


	}


	file.close();


	while (1)
	{
		c = nextCommand(&s, &d, &f);
		switch (c)
		{

		case '0':
			cout << "Query: stop" << endl;
			delete G.V;
			delete G.Adj;
			deleteHeap(G.heap);
			exit(0);


		case '1':
			//int dest;
			int flag;

			cout << "Query: find" << " " << s << " " << d << " " << f << endl;

			if (s.find(".") == 0 || d.find(".") == 0 || f.find(".") == 0)
			{
				cout << "Error: invalid find query" << endl;
				break;
			}
			try
			{
				source = stoi(s);
				dest = stoi(d);
				flag = stoi(f);
			}
			catch (exception& e)
			{
				cout << "Error: invalid find query" << endl;
				break;
			}

			if (source < 1 || source > SIZE || source == dest || (flag != 0 && flag != 1))
			{
				cout << "Error: invalid find query" << endl;
				break;
			}

			if (flag == 1)
			{
				G.flag = 1;
				G.valid = G.Dijkstra(source, dest);		// search all elements and tell information
			}
			else if (flag == 0)
			{
				G.flag = 0;
				G.valid = G.Dijkstra(source, dest);		// search all elements without telling information
			}

			G.findSource = source;
			break;



		case '2':
			cout << "Query: write path " << s << " " << d << endl;

			if (G.valid == -1)
			{
				printf("Error: no path computation done\n");
				break;
			}

			if (s.find(".") == 0 || d.find(".") == 0)
			{
				cout << "Error: invalid source destination pair" << endl;
				break;
			}

			try
			{
				source = stoi(s);
				dest = stoi(d);
			}
			catch (exception& e)
			{
				cout << "Error: invalid source destination pair" << endl;
				break;
			}

			if (G.findSource != source || dest > SIZE)
			{
				cout << "Error: invalid source destination pair" << endl;
				break;
			}


			if (G.V[dest].color == 3)					// (a) posibility
			{
				string text = d;
				int predecessorName = G.V[dest].pi;

				while (predecessorName != source)
				{
					text = to_string(predecessorName) + ", " + text;
					predecessorName = G.V[predecessorName].pi;
				}

				text = to_string(predecessorName) + ", " + text;
				cout << "Shortest path: <" << text << ">" << endl;		// shortest path


				printf("The path weight is:%13.4f\n", G.V[dest].d);	// shortest path weight
			}


			else if (G.V[dest].color == 2)				// (b) posibility
			{
				string text = d;
				int predecessorName = G.V[dest].pi;

				while (predecessorName != source)
				{
					text = to_string(predecessorName) + ", " + text;
					predecessorName = G.V[predecessorName].pi;
				}

				text = to_string(predecessorName) + ", " + text;
				cout << "Path not known to be shortest: <" << text << ">" << endl;	// shortest path


				printf("The path weight is:%13.4f\n", G.V[dest].d);	// shortest path weight
			}


			else if (G.V[dest].color == 1)				
			{
				if (G.valid == 0)
					cout << "No " << source << "-" << dest <<  " path has been computed." << endl;	// (c) posibility

				else if (G.valid == 1)
					cout << "No " << source << "-" << dest << " path exists." << endl;				// (d) posibility
			}


			else
				break;

			

		default: break;
		}
	}

	exit(0);
};