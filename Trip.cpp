#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<string>
#include<vector>
#include<Windows.h>
#include<stdlib.h>
#include<Rtutils.h>
#include<list>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int flag;

void mainmenu();
void nerd();
void main2();
void peek();
void gotoxy(int x, int y);
void dataset();
void addedge(int u, int v, int x);
void pathfinder(int source, int destination, int budget, int days);
void printpaths(int u, int d, bool visited[], int path[], int& path_index, int budget, int days);


class city
{
public:
	int index;
	string name;
	int budget;
	string type;
	int days;

	city()
	{
		index = -1;
		name = "NULL";
		budget = 0;
		type = "NULL";
		days = 0;
	}

	void input(int index, string name, int budget, string type, int days)
	{
		this->index = index;
		this->name = name;
		this->budget = budget;
		this->type = type;
		this->days = days;
	}

	void display()
	{
		cout << "\n";
		cout << "\n\tThe name : ";
		SetConsoleTextAttribute(hConsole, 4);
		cout << name;
		SetConsoleTextAttribute(hConsole, 15);
		cout << "\n\tContribution in terms of money: ";
		SetConsoleTextAttribute(hConsole, 2);
		cout << budget;
		SetConsoleTextAttribute(hConsole, 15);
		cout << "\n\tThe type of attraction : " << type << "\n";
	}
}c[25];

list < pair<int, int>> graph[25];

void addedge(int u, int v, int x)
{
	graph[u].push_back(make_pair(v, x));
	graph[v].push_back(make_pair(u, x));
}

void dataset()
{
	c[0].input(0, "Delhi", 22000, "Historical/Metropolitan", 3);
	c[1].input(1, "Agra", 8000, "Historical", 2);
	c[2].input(2, "Kasol", 12000, "Scenic/Hilly", 3);
	c[3].input(3, "Jaipur", 10000, "Historical/Scenic", 2);
	c[4].input(4, "Amritsar", 8000, "Historical/Religious", 2);
	c[5].input(5, "Chandigarh", 10000, "Standard", 2);
	c[6].input(6, "Srinagar", 8000, "Scenic/Hilly", 4);
	c[7].input(7, "Leh/Ladakh", 15000, "Scenic/Religious", 4);
	c[8].input(8, "Mussourie/Dhanolti", 14000, "Hill Stations", 2);
	c[9].input(9, "Haridwar/Rishikesh", 12000, "Religious/Adventurous", 3);
	c[10].input(10, "Bhopal", 6000, "Standard", 2);
	c[11].input(11, "Nagpur", 6000, "Standard", 1);
	c[12].input(12, "Pune", 10000, "Metropolitan", 1);
	c[13].input(13, "Mumbai", 25000, "Metropolitan", 3);
	c[14].input(14, "The State of Goa", 40000, "Coastal/Aesthetic", 6);
	c[15].input(15, "Hyderabad", 9000, "Historical", 1);
	c[16].input(16, "Chennai", 13000, "Coastal/Cultural", 2);
	c[17].input(17, "Bangalore", 15000, "Metropolitan", 2);
	c[18].input(18, "The State of Kerala", 35000, "Scenic/Coastal", 6);
	c[19].input(19, "Kanniyakumari", 4000, "Religious", 1);
	c[20].input(20, "Ooty", 7000, "Hill Station", 2);
	c[21].input(21, "Ahmedabad", 6000, "Cultural", 2);
	c[22].input(22, "Varanasi", 6000, "Religious", 2);
	c[23].input(23, "Kolkata", 10000, "Costal/Cultural", 3);
	c[24].input(24, "Darjeeling", 12000, "Plantations/Hilly", 2);
	addedge(0, 1, 233);
	addedge(0, 3, 281);
	addedge(0, 5, 243);
	addedge(0, 9, 218);
	addedge(0, 22, 820);
	addedge(1, 10, 524);
	addedge(1, 22, 590);
	addedge(2, 5, 281);
	addedge(2, 9, 483);
	addedge(3, 21, 677);
	addedge(4, 5, 225);
	addedge(5, 6, 560);
	addedge(6, 7, 421);
	addedge(8, 9, 79);
	addedge(10, 11, 351);
	addedge(10, 15, 850);
	addedge(11, 12, 706);
	addedge(12, 13, 147);
	addedge(12, 14, 440);
	addedge(13, 14, 583);
	addedge(13, 21, 524);
	addedge(14, 18, 680);
	addedge(15, 16, 625);
	addedge(15, 17, 575);
	addedge(16, 19, 705);
	addedge(16, 23, 1668);
	addedge(17, 20, 271);
	addedge(18, 19, 510);
	addedge(22, 23, 678);
	addedge(23, 24, 615);

}

void gotoxy(int x, int y)
{
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}



void pathfinder(int source, int destination, int budget, int days)
{
	bool* visited = new bool[25]; 
	int* path = new int[25];
	int index = 0;  
	for (int i = 0; i < 25; i++)
	{
		visited[i] = false;
	} 
	printpaths(source, destination, visited, path, index, budget, days);
}

 
void printpaths(int u, int d, bool visited[],
	int path[] , int& index, int budget, int days)
{ 
	visited[u] = true;
	path[index] = u;
	index++;
	int totalb = 0, totald = 0;
	if (u == d)
	{
		totalb = 0, totald = 0;
		for (int i = 0; i < index; i++)
		{	
			list<pair<int, int>>::iterator it;
			for (it = graph[path[i]].begin(); it != graph[path[i]].end(); ++it)
			{
				if (it->first==path[i+1])
				{
					totalb += (it->second * 5) + (c[it->first].budget);
					totald += (c[it->first].days);
					break;
				}

			}
		}
		if (totalb <= budget && totald <= days)
		{
			::flag = 0;
			for (int i = 0; i < index; i++)
			{
				SetConsoleTextAttribute(hConsole, 2);
				cout << c[path[i]].name;
				if (!(i + 1 == index))
				{
					SetConsoleTextAttribute(hConsole, 15);
					cout << "->";
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 15);
					cout << "\n\t\tThe total budget required: ";
					SetConsoleTextAttribute(hConsole, 3);
					cout << totalb;
					SetConsoleTextAttribute(hConsole, 15);
					cout << " Rupees";
					SetConsoleTextAttribute(hConsole, 15);
					cout << "\n\t\tThe total duration: ";
					SetConsoleTextAttribute(hConsole, 3);
					cout << totald;
					SetConsoleTextAttribute(hConsole, 15);
					cout << " Days";
				}
				SetConsoleTextAttribute(hConsole, 15);
			}
			cout << "\n\n\t\t";
		}
	}
	else  
	{ 
		list<pair<int, int>>::iterator it;
		for (it = graph[u].begin(); it != graph[u].end(); ++it)
		{
			if (!visited[it->first])
			{
				printpaths(it->first, d, visited, path, index, budget, days);
			}
		}			
	} 
	index--;
	visited[u] = false;
}

void nerd()
{
	system("CLS");
	int input;
	gotoxy(100, 5);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "THE NERD'S ARENA";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "\n\n\n\t\t\tA graph is a set of connected nodes, wherein the nodes are connected in a random way, just like roads of a map.";
	cout << " The graph(of cities) is represented as a list of individual connections.\n";
	cout << "\t\t\tThe weight of the graph is the distance and duration corresponding to two cities, and the shortest path can be found using";
	SetConsoleTextAttribute(hConsole, 2);
	cout << " DIJKSTRA";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " Algorithm. But our problem requires not the shortest\n\t\t"; cout << " path, but a number of paths according to your criteria. Therefore we use";
	SetConsoleTextAttribute(hConsole, 2);
	cout << " DFS(Depth First Search)";
	SetConsoleTextAttribute(hConsole, 15);
	cout << ", to find all paths between a source and a destination, and then filter them according to your input.";
	cout << "\n\n\n\n\t\t\tThank you for showing interest! Tell us what you want to do next.";
	cout << "\n\n\t\t\t1 Go back to the previous menu\n\t\t\t2 Exit the program";
	cout << "\n\n\t\t\t\tENTER YOUR CHOICE : ";
	cin >> input;
	switch (input)
	{
	case 1: mainmenu();
		break;
	case 2: SetConsoleTextAttribute(hConsole, 2);
		cout << "\n\n\n\t\t\t\tTHANK YOU!";
		Sleep(3000);
		exit(0);
		break;
	default: cout << "\n\n\t\t\t\tPLEASE TRY AGAIN"; Sleep(3000);
		nerd();
	}
}

void main2()
{
	system("CLS");
	gotoxy(100, 5);
	::flag = 1;
	int source, destination, budget, days;
	SetConsoleTextAttribute(hConsole, 3);
	cout << "PLANNING YOUR TRIP";
	cout << "\n\n";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "\n\t\t\t\t\tYou'll have to insert the index of the source city from one of the cities provided below, along with the destination(The one place you just can't miss).\n\n\n\t\t\t";
	for (int i = 0; i < 25; ++i)
	{
		if (i < 10)
		{
			SetConsoleTextAttribute(hConsole, 2);
			cout << i << "   " << c[i].name << "\n\t\t\t";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 2);
			cout << i << "  " << c[i].name << "\n\t\t\t";
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << "\n\t\t\t\tEnter your ";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "SOURCE";
	SetConsoleTextAttribute(hConsole, 15);
	cout<<": ";
	cin >> source;
	cout << "\n\t\t\t\tEnter your ";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "DESTINATION";
	SetConsoleTextAttribute(hConsole, 15);
	cout << ": ";
	cin >> destination;
	cout << "\n\t\t\t\tEnter your ";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "BUDGET(Maximum)";
	SetConsoleTextAttribute(hConsole, 15);
	cout << ": ";
	cin >> budget;
	cout << "\n\t\t\t\tEnter the number of ";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "DAYS(Maximum)";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " you have to travel : ";
	cin >> days;
	cout << "\n\n\n\tThe travelling path(s) most suitable for you are: \n\n\n\t\t";
	pathfinder(source, destination, budget, days);
	if (::flag)
	{
		cout << "\n\n\t\tNo suitable plans under these constraints";
	}
	cout << "\n\n\n\n\t\t\tThank you for showing interest! Tell us what you want to do next.";
	cout << "\n\n\t\t\t1 Go back to the previous menu\n\t\t\t2 Exit the program";
	cout << "\n\n\t\t\t\tENTER YOUR CHOICE : ";
	int input;
	cin >> input;
	switch (input)
	{
	case 1: mainmenu();
		break;
	case 2: SetConsoleTextAttribute(hConsole, 2);
		cout << "\n\n\n\t\t\t\tTHANK YOU!";
		Sleep(3000);
		exit(0);
		break;
	default: cout << "\n\n\t\t\t\tPLEASE TRY AGAIN"; Sleep(3000);
		nerd();
	}
}

void peek()
{
	system("CLS");
	int input;
	gotoxy(100, 5);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "OUR LIST OF CONTACTED CITIES: ";
	cout << "\n\n";
	SetConsoleTextAttribute(hConsole, 15);
	for (int i = 0; i < 25; ++i)
	{
		c[i].display();
	}
	cout << "\n\n\t\t\t1 Go back to the previous menu\n\t\t\t2 Exit the program";
	cout << "\n\n\t\t\t\tENTER YOUR CHOICE : ";
	cin >> input;
	switch (input)
	{
	case 1: mainmenu();
		break;
	case 2: SetConsoleTextAttribute(hConsole, 2);
		cout << "\n\n\n\t\t\t\tTHANK YOU!";
		Sleep(3000);
		exit(0);
		break;
	default: cout << "\n\n\t\t\t\tPLEASE TRY AGAIN"; Sleep(3000);
		peek();
	}
}


void mainmenu()
{
	system("CLS");
	gotoxy(100, 5);
	int input;
	SetConsoleTextAttribute(hConsole, 2);
	cout << "THE TRIP PLANNER";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "\n\n\n\t\t\t\t\t\tWe yearn for you to have the perfect vacation while exploring all you can, at the cheapest rates you can imagine.\n\n";
	cout << "\t\t1  Make your own trip plan\n";
	cout << "\t\t2  Take a peek at our contacted cities\n";
	cout << "\t\t3  Nerdy stuff about working algorithms(For cool nerds)\n";
	cout << "\t\t4  Exit this program\n";
	cout << "\n\n\t\t\t\tENTER YOUR INPUT(1-4) : ";
	cin >> input;
	switch (input)
	{
	case 1: main2();
		break;
	case 2: peek();
		break;
	case 3: nerd();
		break;
	case 4: SetConsoleTextAttribute(hConsole, 2);
		cout << "\n\n\n\t\t\t\tTHANK YOU!";
		Sleep(3000);
		exit(0);
		break;
	default: cout << "\n\n\n\n\t\t\t\t\tPLEASE TRY AGAIN"; Sleep(3000); mainmenu();
	}
}

int main()
{
	dataset();
	mainmenu();
}