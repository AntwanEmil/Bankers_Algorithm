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


	int i = 0, index = 0;
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
L1:int n, m, process_no;
	int * Available;
	int Max[100][100];
	int Allocation[100][100];
	int Need[100][100];
	int Request[100];
	string op, PID, request;
	bool safe;
	cout << "Enter n & m values respectively separated by space: ";
	cin >> n >> m;
	if (n <= 0 || m <= 0){
		cout << "Error: Both n&m should be bigger than 0." << endl;
		goto L1;
	}
	Available = new int[m];
	cout << "Enter the Available matrix elements separated by space: "<<endl;
	char z = 'A';
	for (int w = 0; w < m; w++){
		cout << z;
		if (z == 'Z') z = 'A';
		else z++;
		cout << "   ";
	}
	cout << "\n";
	for (int i = 0; i < m; i++){
		cin >> Available[i];
		if (Available[i] < 0){
			cout << "Error: one or more elements in the Available matrix is negative\n";
			goto L1;
		}
	}


	cout << "Enter Max matrix elements: \n";
	if (n < 10)
		cout << "\t";
	else
		cout << "       ";
	z = 'A';
	for (int w = 0; w < m; w++){
		cout << z;
		if (z == 'Z') z = 'A';
		else z++;
		cout << "   ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (j == 0){
				if (i<10)cout << "P" + to_string(i) + "      ";
				else cout << "P" + to_string(i) + "     ";
			}
			cin >> Max[i][j];
			if (Max[i][j] < 0){
				cout << "Error: one or more elements in the Max matrix is negative\n";
				goto L1;
			}
		}
	}
	cout << "Enter Allocation matrix elements: \n";
	if (n < 10)
		cout << "\t";
	else
		cout << "       ";
	z = 'A';
	for (int w = 0; w < m; w++){
		cout << z;
		if (z == 'Z') z = 'A';
		else z++;
		cout << "   ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (j == 0){
				if (i<10)cout << "P" + to_string(i) + "      ";
				else cout << "P" + to_string(i) + "     ";
			}
			cin >> Allocation[i][j];
			Need[i][j] = Max[i][j] - Allocation[i][j];
			if (Allocation[i][j] < 0){
				cout << "Error: one or more elements in the Allocation matrix is negative\n";
				goto L1;
			}
		}
	}
	int negative_flag = 0;
	cout << "Need Matrix:\n";
	if (n < 10)
		cout << "\t";
	else
		cout << "       ";
	z = 'A';
	for (int w = 0; w < m; w++){
		cout << z;
		if (z == 'Z') z = 'A';
		else z++;
		cout << "   ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (j == 0){ 
					if(i<10)cout << "P" + to_string(i) + "      "; 
					else cout << "P" + to_string(i) + "     ";
			}
			if (Need[i][j]>=0 && Need[i][j] <10)
				cout << Need[i][j] << "   ";
			else
				cout << Need[i][j] << "  ";
			if (j == m - 1)cout << "\n";
			if (Need[i][j] < 0) negative_flag = 1;
		}
	}
	if (negative_flag == 1){
		cout << "Error: one or more elements in the Need matrix is negative" << endl;
		goto L1;
	}
	while (1){
		cout << "Press s for safe state enquiry i for immediate request enquiry ,N for new operation ,and q for quit:  ";
		cin >> op;


		if (op == "s"){
			safe = safety(n, m, Available, Allocation, Need);
			if (safe == true){
				cout << "Yes, Safe state " + safe_processes << endl;
			}
			else cout << "No, State is not safe" << endl;
		}

		else if (op == "i"){
			cout << "		Enter PID [ex. P0]: ";
			cin >> PID;
			size_t last_index = PID.find_last_not_of("0123456789");
			string result = PID.substr(last_index + 1);
			process_no = stoi(result);
			if (process_no > n - 1){
				cout << "Error: P" + to_string(process_no) + " doesn't exist" << endl;
				continue;
			}
			cout << "		Enter request [ex. (1,2,3)]: ";
			cin >> request;
			int ptr1 = 0, ptr2 = 0, i = 0, count = 0;
			while (count != request.length()){
				if (request[count] == '('){

					count++;
				}
				else if (request[count] == ')'){
					Request[i] = stoi(request.substr(ptr1 + 1, ptr2));
					i++;
					break;
				}
				else{//, aw rakm

					if (request[count] == ','){
						Request[i] = stoi(request.substr(ptr1 + 1, ptr2));
						i++;
						ptr2 = count;
						ptr1 = ptr2;
					}
					else{
						ptr2 = count;
					}

					count++;
				}
			}
			int no_grant = 0;
			for (int i = 0; i < m; i++)
			{
				if (Request[i] > Need[process_no][i] || Request[i] > Available[i]){
					no_grant = 1;
					break;
				}
			}
			//decrementing and eincrementing matrices then calling the safet fn..
			if (no_grant == 0){
				for (int i = 0; i < m; i++)
				{
					Allocation[process_no][i] += Request[i];
					Need[process_no][i] -= Request[i];
					Available[i] -= Request[i];
				}
				safe = safety(n, m, Available, Allocation, Need);
				if (safe && no_grant == 0){
					cout << "Yes ,request can be granted with safe state , ";
					int l = 0;
					while (1){
						if (l == 0) cout << "<P" + to_string(process_no) + "req,";
						else cout << safe_processes[l];
						l++;
						if (l == safe_processes.length()) break;
					}
					cout << "\n";
				}
				else
					cout << "No ,Request couldn't be granted" << endl;

				//returning things to the original state
				for (int i = 0; i < m; i++)
				{
					Allocation[process_no][i] -= Request[i];
					Need[process_no][i] += Request[i];
					Available[i] += Request[i];
				}

			}
			else
				cout << "No ,Request couldn't be granted" << endl;


		}
		else if (op == "N"){
			cout << "\n================================================================\n";
			goto L1;
		}
		else if (op == "q") break;
	}

	return 0;
}
