#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>

using namespace std;

struct JobData
{
	long long end_time;
	int thread_num;

	JobData(long long end_time, int thread_num)
		: end_time(end_time), thread_num(thread_num)
	{}
};

struct CompareTime
{
	bool operator()(JobData const& j1, JobData const& j2)
	{
		if (j1.end_time == j2.end_time)
		{
			return j1.thread_num > j2.thread_num;
		}

		return j1.end_time > j2.end_time;
	}
};

class JobQueue
{
private:
	int num_workers_;
	vector<int> jobs_;

	vector<int> assigned_workers_;
	vector<long long> start_times_;
	priority_queue<JobData, vector<JobData>, CompareTime> end_times_;

	void WriteResponse() const
	{
		for (int i = 0; i < jobs_.size(); i++)
		{
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData()
	{
		int m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; i++)
			cin >> jobs_[i];
	}

	void AssignJobs()
	{
		int assignedJobCounter = 0;
		long long currentTime = 0;
		queue<int> threads;

		while (assignedJobCounter < jobs_.size())
		{
			if (!end_times_.empty())
			{
				JobData data = end_times_.top();
				end_times_.pop();

				currentTime = data.end_time;
				threads.push(data.thread_num);

				while (!end_times_.empty() && currentTime == end_times_.top().end_time && threads.size() <= num_workers_)
				{
					data = end_times_.top();
					end_times_.pop();

					threads.push(data.thread_num);
				}
			}
			else
			{
				for (int i = 0; i < num_workers_; i++)
				{
					threads.push(i);
				}
			}

			for (int i = 0, n = num_workers_ - end_times_.size(); i < n; i++)
			{
				int thread = threads.front();
				threads.pop();

				JobData data(currentTime + jobs_[assignedJobCounter], thread);
				end_times_.push(data);

				start_times_.push_back(currentTime);
				assigned_workers_.push_back(thread);

				assignedJobCounter++;
			}
		}
	}

public:
	void Solve()
	{
		ReadData();
		AssignJobs();
		WriteResponse();
	}
};

int main()
{
	ios_base::sync_with_stdio(false);

	JobQueue job_queue;
	job_queue.Solve();
	return 0;
}

//Code written by Jasfiq Rahman as a part of the Data Structures and Algorithms Specialization offered by
//the University of California, San Diego and the Higher School of Economics, Moscow on Coursera.