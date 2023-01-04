#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

fstream rawData;
vector<float> y;
float threshold = 0.0f, maxAptitude = 0.0f, minAptitude = 10.0f, val = 0.0f;
float Rwave = 0.0f;

int numOfBeats = 0;

void storeData()
{
	while (rawData.good())
	{
		string line;
		getline(rawData, line, '\n');
		y.push_back(stof(line));
	}
	cout << "Data sets present in the raw ECG data are " << y.size() << endl;
}

void getThreshold()
{
	for (auto val = y.begin(); val != y.end(); val++)
	{
		if (*val > maxAptitude)
			maxAptitude = *val;
		else if (*val < minAptitude && *val >= 0)
			minAptitude = *val;
	}

	threshold = (((minAptitude + maxAptitude) / 2) + maxAptitude) / 2;

	cout << "Maximum Aptitude is " << maxAptitude << endl << "Minimum Aptitude is " << minAptitude << endl << "Threshold is " << threshold << endl;
}

float  getPeak(float Rwave, float val)
{
	if (val >= Rwave)
	{
		return val;
	}
	else if (val < Rwave)
	{
		//cout << "Peak val is " << Rwave << endl;
		numOfBeats++;
		return 0;
	}
}

int main()
{
	int timeLimit;
	cout << "Enter the range for calculating the number of heart beats in that range" << endl;
	cin >> timeLimit;
	
	rawData.open("Dataset/ecg-1.csv");

	storeData();

	getThreshold();

	int flag = 1, heartBeat = 0;
	for (auto val = y.begin(); val != y.end(); val++)
	{
		flag++;
		if (flag == timeLimit)
		{
			heartBeat = numOfBeats - heartBeat;
			cout << "Number of beats in " <<timeLimit << "ECG raw signal values are " << heartBeat << endl;
			heartBeat = numOfBeats;
			flag = 1;
		}
		if (*val > threshold || Rwave > threshold)
		{
			Rwave = getPeak(Rwave, *val);
		}
	}

	cout << "Number of beats are " << numOfBeats;

	return 0;
}
