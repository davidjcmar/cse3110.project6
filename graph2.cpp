/*
David Cmar
CSE 3110.002
Program 6
4/31/15
*/
#include <iostream>
#include <ctime>
#include <queue>
#include <vector>
#define X 25

using namespace std;

class g_state
{
private:
	bool visit;
	int distance;
	int clicks;
public:
	vector<int> parent;
	g_state();
	bool get_visit();
	void set_visit();
	int get_dist();
	void set_dist(int);
	int get_clicks();
	void set_clicks(int);
};
g_state::g_state()
{
	visit=false;
	distance=0;
	clicks=0;
}
bool g_state::get_visit()
{
	return visit;
}
void g_state::set_visit()
{
	visit=true;
}
int g_state::get_dist()
{
	return distance;
}
void g_state::set_dist(int dist)
{
	distance=dist;
}
int g_state::get_clicks()
{
	return clicks;
}
void g_state::set_clicks(int clix)
{
	clicks=clix;
}
void dijkstra(int map[][X],g_state graph_state[],int current);
void print(g_state graph_state[]);
int main (void)
{
	int map[X][X];
	g_state graph_state[X];

	/* load map */
	for (int i=0;i<X;i++)
	{
		for (int j=0;j<X;j++)
		{
			int buffer;
			cin>>buffer;
			map[i][j]=buffer;
		}
	}
	dijkstra(map,graph_state,0);
	print(graph_state);
	//cout<<endl;
}

void dijkstra(int map[][X],g_state graph_state[],int current)
{
	queue<int> q;
	clock_t t;
	while (1)
	{
		t=clock(); // start clock
		graph_state[current].set_visit(); // set visit as true for vertex
		/* grab edges */
		for (int i=1;i<X;i++)
		{
			/* there is an edge */
			if (map[current][i]!=0)
			{
				/* either new distance is shorter than old distance or old distance equals zero */
				if ((graph_state[current].get_dist()+map[current][i]<graph_state[i].get_dist())||(graph_state[i].get_dist()==0))
				{
					/* set distance */
					graph_state[i].set_dist(graph_state[current].get_dist()+map[current][i]);
					/* clear path */
					graph_state[i].parent.clear();
					/* set new path */
					for (int p=0;p<graph_state[current].parent.size();p++)
						graph_state[i].parent.push_back(graph_state[current].parent[p]);
					graph_state[i].parent.push_back(current);
					/* push vertex on queue */
					q.push(i);
				}
				/* no edge */
				else
				{
					/* do not set distance */
				}
			}
		}
		graph_state[current].set_clicks(clock()-t); // stop clock
		current=q.front(); // set next vertex
		q.pop(); // remove next vertex from queue
		/* stop when queue is empty */
		if (q.empty())
			break;
	}
}

void print(g_state graph_state[])
{
	/* print all vertices */
	for (int i=0;i<X;i++)
	{
		cout<<graph_state[i].get_clicks()<<"c "; // clicks
		cout<<(float)graph_state[i].get_clicks()/CLOCKS_PER_SEC<<"s "; // clicks as time
		/* path to vertex */
		for (int p=0;p<graph_state[i].parent.size();p++)
			cout<<graph_state[i].parent[p]+1<<" ";
		cout<<endl;
	}
}