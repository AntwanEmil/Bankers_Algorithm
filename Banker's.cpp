#include <iostream>
#include <string>
using namespace std;
int out[100];
string safe_processes = "<";
bool safety(int n, int m, int Available[], int Allocation[100][100], int Need[100][100]){
	safe_processes = "<";
	bool *Finish;
	Finish = new bool[n];
	int sum1 = 0, sum2 = 0;
	int flag = 0, count = 0;
	int *Work;
	Work = new int[m];
	for (int i = 0; i < n; i++)
		Finish[i] = false;
	for (int i = 0; i < n; i++)
		Work[i] = Available[i];


	int i = 0,index=0;
	while (i<n){
		//finding false element
		if (Finish[i] == false){
			flag = 0;
			for (int j = 0; j < m; j++){
				if (Need[i][j] > Work[j]){
					flag = 1;
					break;
				}
			}

			if (flag == 0){
				for (int j = 0; j < m; j++){
					Work[j] += Allocation[i][j];
				}
				Finish[i] = true;
				out[index] = i;
				index++;
				safe_processes += "P" + to_string(i);
				if (index != n)safe_processes += ",";
			}

		}
		if (count == n) break;

		if (i == n - 1){ i = 0; count++; continue; };
		i++;
	}


	for (int i = 0; i < n; i++)
	{
		if (Finish[i] == false)
			return false;
	}
	//safe_processes[safe_processes.length() - 1] = '\0';
	safe_processes += ">";
	return true;
}

int main(){
	int n, m;
	int * Available;
	int Max[100][100];
	int Allocation[100][100];
	int Need[100][100];
	string op;
	bool safe;
	cout << "Enter n & m values separated by space: ";
	cin >> n >> m;
	Available = new int[m];
	cout << "Enter the Available matrix elements separated by space: ";
	for (int i = 0; i < m; i++)
		cin >> Available[i];
	cout << "Enter Max matrix elements: \n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cin >> Max[i][j];
		}
	}
	cout << "Enter Allocation matrix elements: \n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cin >> Allocation[i][j];
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}
	cout << "Need Matrix:\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << Need[i][j] << " ";
			if (j == m - 1)cout << "\n";
		}
	}

	while (1){
		cout << "Press s for safe state enquiry i for immediate request enquiry ,and q for quit:  ";
		cin >> op;


		if (op == "s"){
			safe = safety(n, m, Available, Allocation, Need);
			if (safe == true){
				cout << "Yes, Safe state " + safe_processes << endl;
			}
			else cout << "No";
		}

		if (op == "i"){
		}

		if (op == "q") break;
	}

	system("pause");
	return 0;
}
