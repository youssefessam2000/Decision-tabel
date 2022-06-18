#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;
class Decision_Table {

	int number_conditions;
	int condition_numb_values;
	char condition_value;
	string condition_name;

	map<string, vector<char>>conditions_value;

	//////////////////////////////////////////

	int number_actions;
	int action_numb_values;
	char action_value;
	string actions_name;
	map<string, vector<char>>actions_value;
	///////////////////////////////////////

	vector<vector<char>>scenario;
	vector<vector<char>>old_table;
	vector<vector<char>>new_table;
	char senario_action_value;
	int number_rules;

public:

	void get_input()
	{
		read_conditions();
		read_actions();
		read_scenario();
	}

	int cal_Num_rules() {

		int number_rules = 1;
		map<string, vector<char>>::iterator i;
		for (i = conditions_value.begin(); i != conditions_value.end(); ++i) {
			number_rules *= i->second.size();
		}
		return number_rules;
	}
	void read_conditions() {

		cout << "enter number of conditions \n";
		cin >> number_conditions;

		for (int i = 0; i < number_conditions; ++i) {

			cout << "please enter condition name \n";
			cin >> condition_name;


			cout << "please enter number of condition values \n";
			cin >> condition_numb_values;


			for (int j = 0; j < condition_numb_values; ++j) {

				cout << "please enter condition values \n";
				cin >> condition_value;
				conditions_value[condition_name].push_back(condition_value);
			}

		}

	}
	void read_actions() {
		cout << "please enter number of actions \n";
		cin >> number_actions;

		for (int i = 0; i < number_actions; ++i) {

			cout << "please enter action name \n";
			cin >> actions_name;

			cout << "please enter number of action values \n";
			cin >> action_numb_values;


			for (int j = 0; j < action_numb_values; ++j) {

				cout << "please enter action values \n";
				cin >> action_value;
				actions_value[condition_name].push_back(action_value);
			}

		}

	}

	void read_scenario() {
		vector<char>Senario_action_values;
		number_rules = cal_Num_rules();

		for (int i = 0; i < number_rules; ++i) {
			cout << "please enter Action scenarios for rule number" << i + 1 << "\n";
			for (int j = 0; j < number_actions + number_conditions; ++j) {
				cin >> senario_action_value;
				Senario_action_values.push_back(senario_action_value);

			}
			scenario.push_back(Senario_action_values);
			Senario_action_values.clear();

		}

		cout << "\n";
	}


	//build old table using repeating factor without output/actions
	void Repeating_Factor() {

		int remaining_repeating_factor = number_rules;
		int count_reach_RF = 0;
		int index_condition_value = 0;
		int row_numb = 0;
		map<string, vector<char>>::iterator numb_condition_value_it;
		vector<char>DT_record;


		for (numb_condition_value_it = conditions_value.begin(); numb_condition_value_it != conditions_value.end(); ++numb_condition_value_it) {

			remaining_repeating_factor /= numb_condition_value_it->second.size();
			for (int i = 0; i < number_rules; ++i) {

				count_reach_RF++;
				DT_record.push_back(numb_condition_value_it->second[index_condition_value]);


				if (count_reach_RF == remaining_repeating_factor)
				{
					count_reach_RF = 0;
					// used when the case of t f t f t f ... , index_condition_value will be out of range of the vector
					if (index_condition_value < numb_condition_value_it->second.size() - 1)
						index_condition_value++;
					else
						index_condition_value = 0;

				}

			}
			old_table.push_back(DT_record);

			DT_record.clear();
			index_condition_value = 0;
		}
		add_actions_to_old_table();
	}

	void output() {

		for (int i = 0; i < old_table.size(); i++) {
			for (int j = 0; j < old_table[i].size(); j++)
				cout << old_table[i][j] << "     ";
			cout << endl << endl;
		}
	}

	void add_actions_to_old_table() {
		vector<char>add_action_record_to_old_table;
		int total_tabel_size = number_conditions * number_rules;

		int k=0;
		int m=0;
		int l = 0;
		bool isequal = true;
		for (int i = 0; i < number_rules; ++i){


			for (int j = 0;j < number_conditions; ++j)
			{
				if (scenario[i][k] != old_table[j][m])
				{

					++k;
					isequal = true;
				}
				else
				{
					isequal = false;
					break;
				}

			}
			if (isequal){

				add_action_record_to_old_table.push_back(scenario[i].back());

			}
			k = 0;
			m++;



		}

		old_table.push_back(add_action_record_to_old_table);

		
 







/*
		vector<char>add_record_action_to_old_table;
		int i = 0;
		int j = 0;
		bool isequal = true;

		for (; i < number_rules; i++) {


			for (; j < number_conditions; j++) {

				if (isequal == true) {
					if (old_table[j][i] == scenario[i][j])
						isequal = true;
					else
					{
						isequal = false;
						break;
					}
				}
			}
			if (isequal == true)
				add_record_action_to_old_table.push_back(scenario[i][number_conditions]);
			j = 0;
			isequal = true;

		}
		old_table.push_back(add_record_action_to_old_table);
	*/
	}

void reduce_redundancey(){

	vector<char>temp;
	vector<vector<char>>transpozed_table;
	int will_redundant = 0;
	int counter_for_escape_rules=0;
	//fill transpozed table
	for (int i = 0; i < number_rules; ++i) {

		for (int j = 0; j < number_conditions+1; ++j) {
			temp.push_back(old_table[j][i]);
		}
		transpozed_table.push_back(temp);
		temp.clear();
	}

	for (int i = 0; i < number_rules; ++i) {

		for (int j = 0; j < number_conditions+1; ++j) {

			if(i+1>=number_rules)
				break;
			if (transpozed_table[i][j] == transpozed_table[i + 1][j])
			{
				will_redundant++;
			}
		}
		if (i + 1 >=number_rules)
			break;
		
		if (will_redundant == number_conditions )
		{
			transpozed_table[i].clear();
			counter_for_escape_rules++;
		}
		will_redundant = 0;
	}
	/////////////////////// convert transpozed to original table shape
	for (int i =0 ; i < number_conditions + 1; ++i) {

		for (int j = counter_for_escape_rules; j <number_rules; ++j) {
			temp.push_back(transpozed_table[j][i]);
		}
		new_table.push_back(temp);
		temp.clear();
	}
	for (int i = 0; i < new_table.size(); i++) {
		for (int j = 0; j < new_table[i].size(); j++)
			cout << new_table[i][j] << "     ";
		cout << endl << endl;
	}




	//int will_redundant=0;
	//vector<char>temp;
	//vector<vector <char>>temp_table;

	//for (int i = 0; i < number_rules; ++i) {

	//	for (int j = number_conditions; j > 0; --j) {
	//		//condition for out index
	//		if (i + 1 >= number_rules)
	//			break;
	//		if (old_table[j][i] == old_table[j][i + 1])
	//			will_redundant++;
	//		
	//	}
	//	//condition for out index
	//	if (i + 1 >= number_rules)
	//		break;
	//	int x = i;
	//	if(will_redundant == number_actions - 1)
	//	{
	//		//we add 1 one number_condition to also add action "E" with condition values
	//		for (int k = 0; k< number_conditions+1; ++k) {
	//			temp.push_back(old_table[k][x]);
	//			cout << *(temp.end()-1);
	//		}

	//		temp_table.push_back(temp);
	//		temp.clear();

	//	}
	//	will_redundant = 0;
	//}
	//
}

};
int main()
{
	Decision_Table DT;
	DT.get_input();
	DT.Repeating_Factor();
	cout << "tabel before reduction \n \n";
	DT.output();
	cout << "tabel after reduction \n \n";
	DT.reduce_redundancey();




}