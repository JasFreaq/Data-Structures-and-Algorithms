#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
	int x, y, rank;
	point* parent = nullptr;

	point(int X, int Y, int Rank = 0, point* Parent = nullptr) :
		x(X), y(Y), rank(Rank), parent(Parent) { }
};

struct edge
{
	point* p1;
	point* p2;

	edge(point* a, point* b) : p1(a), p2(b) { }

	double Distance()
	{
		int x_sqrd = pow(p1->x - p2->x, 2);
		int y_sqrd = pow(p1->y - p2->y, 2);
		return sqrt(x_sqrd + y_sqrd);
	}
};

int CompareEdge(const void* a, const void* b)
{
	edge* e1 = (edge*)a;
	edge* e2 = (edge*)b;

	return e1->Distance() > e2->Distance();
}

point* Find(point* p)
{
	point* itr = p;
	while (itr->parent != nullptr)
	{
		itr = itr->parent;
	}

	return itr;
}

void Union(point* u, point* v, vector<point>& points)
{
	point* r1 = Find(u);
	point* r2 = Find(v);

	if (r1 != r2)
	{
		if (r1->rank > r2->rank)
		{
			r2->parent = r1;
		}
		else
		{
			r1->parent = r2;
			if (r1->rank == r2->rank)
			{
				r2->rank++;
			}
		}
	}
}

double clustering(vector<point>& points, int k)
{
	double result = 0.;
	vector<edge> edges;
	for (size_t i = 0, n = points.size(); i < n - 1; i++)
	{
		for (size_t j = i + 1; j < n; j++)
		{
			edges.push_back(edge(&points[i], &points[j]));
		}
	}
	qsort(&edges[0], edges.size(), sizeof(edge), CompareEdge);

	int num_unions = 0;
	for (size_t i = 0, n = edges.size(), m = points.size(); i < n; i++)
	{
		point* u = edges[i].p1;
		point* v = edges[i].p2;

		if (Find(u) != Find(v))
		{
			num_unions++;
			Union(u, v, points);
		}

		if (num_unions > m - k)
			return edges[i].Distance();
	}

	return -1.;
}

int main()
{
	size_t n;
	cin >> n;

	int x, y;
	vector<point> points;
	for (size_t i = 0; i < n; i++)
	{
		cin >> x >> y;
		points.push_back(point(x, y));
	}

	int k;
	cin >> k;
	cout << setprecision(10) << clustering(points, k) << endl;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.