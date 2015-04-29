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
//	void print_parent();
//	vector<int> get_parent();
//	void set_parent(int);
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
/*
void g_state::print_parent()
{
	for (int i=0;i<parent.size();i++)
		cout<<parent[i]<<" ";
	cout<<endl;
}
vector<int> g_state::get_parent()
{
	return parent;
}
void g_state::set_parent(int par)
{
	parent.push_back(par);
}
*/
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
	/* testing */
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
		t=clock();
		graph_state[current].set_visit();
		for (int i=1;i<X;i++)
		{
			if (map[current][i]!=0)
			{
				if ((graph_state[current].get_dist()+map[current][i]<graph_state[i].get_dist())||(graph_state[i].get_dist()==0))
				{
					/* set distance */
					graph_state[i].set_dist(graph_state[current].get_dist()+map[current][i]);
					graph_state[i].parent.clear();
					for (int p=0;p<graph_state[current].parent.size();p++)
						graph_state[i].parent.push_back(graph_state[current].parent[p]);
					graph_state[i].parent.push_back(current);
					q.push(i);
				}
				else
				{
					/* do not set distance */
				}
			}
		}
		graph_state[current].set_clicks(clock()-t);
		current=q.front();
		q.pop();
		if (q.empty())
			break;
	}
}

void print(g_state graph_state[])
{
	for (int i=0;i<X;i++)
	{
		cout<<graph_state[i].get_clicks()<<"c ";
		cout<<(float)graph_state[i].get_clicks()/CLOCKS_PER_SEC<<"s ";
		for (int p=0;p<graph_state[i].parent.size();p++)
			cout<<graph_state[i].parent[p]+1<<" ";
		cout<<endl;
	}
}