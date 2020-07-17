#include <iostream>  
#include "TourGuide.h"

using namespace std;
 


int main()
{
	TourGuide Guide1;
	char choose_index;
	
	while(1){
		cout << "|  Enter the number to select the corresponding service below:                  |" << endl;
		cout << "|  1. Show map connection matrix;                                               |" << endl;
		cout << "|  2. Places information query;                                                 |" << endl;
		cout << "|  3. Get the best access path from X to Y through N points;                    |" << endl;
		cout << "|  4. Ask for ways from anywhere to other places.                               |" << endl;
		cout << "|  5. Quit the campus navigation system.                                        |" << endl;
		cout << "|-------------------------------------------------------------------------------|" << endl;
		cout << "|                                                                               |" << endl;
    	cout << "|  Now enter the number corresponding to the service you need:                  |" << endl;
		cout << "|";
		cin >> choose_index;
		if(choose_index == '1'){
			cout << "|----------------------------Show map connection matrix-------------------------|" << endl;
			Guide1.printGraph();
			cout << "|-------------------------------------------------------------------------------|" << endl;
		}
		else if(choose_index == '2'){
			cout << "|----------------------------Places information query---------------------------|" << endl;
			string data1;
			cout << "|  please insert name of place you want to konw:                                |" << endl;
			cout << "|";
			cin >> data1;
			Guide1.searchPlace(data1);
			// Guide1.searchPlace("A栋");
			cout << "|-------------------------------------------------------------------------------|" << endl;
		}
		else if(choose_index == '3'){
			cout << "|-------------Get the best access path from X to Y through N points-------------|" << endl;
			string data2, data3;
			int num;
			cout << "|  please insert name of place where to start:                                  |" << endl;
			cout << "|";
			cin >> data2;
			cout << "|  please insert name of place where to go:                                     |" << endl;
			cout << "|";
			cin >> data3;
			cout << "|  please insert number of places passed:                                       |" << endl;
			cout << "|";
			cin >> num;
			Guide1.AskRoad_fromXtoYviaN(data2, data3, num);
			// Guide1.AskRoad_fromXtoYviaN("A栋", "T6栋", 8);
			cout << "|-------------------------------------------------------------------------------|" << endl;
		}
		else if(choose_index == '4'){
			cout << "|----------------Ask for ways from anywhere to other places---------------------|" << endl;
			string data4;
			cout << "|  please insert name of place where you want to konw the shortest road to      |" << endl;
			cout << "|others places:                                                                 |" << endl;
			cin >> data4;
			Guide1.AskRoad_fromX(data4);
			// Guide1.AskRoad_fromX("B栋");
			// Guide1.printGraph();
		}
		else if(choose_index == '5'){
			break;
		}
		else{
			cout << "|  Sorry, the number you entered is incorrect, please re-enter                  |" << endl;
		}
		
	}

	return 0;
}
