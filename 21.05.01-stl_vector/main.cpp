
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v_Number;
	
	v_Number.push_back(0); //배열의 맨 뒤에 자료를 삽입
	v_Number.push_back(1);
	v_Number.push_back(2);
	v_Number.push_back(3);

	//vector<int>::iterator iter;
	


	v_Number.erase(v_Number.begin() + 1);
	v_Number.erase(v_Number.end() - 1);

	vector<int> v_Value;

	
	while(v_Value.size() != 25){

		int i;
		cin >> i;
		v_Value.push_back(i);

		cout << v_Value.size() << endl;
	}


	return 0;
}
