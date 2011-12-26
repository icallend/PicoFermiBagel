//
// Pico Fermi Bagel!
// icallend (github)
// icallend@cs.brown.edu
// 05/06/2011
// main.cpp
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <vector>

using namespace std;


int * convertNumberToArray(unsigned int number)
{
    int length = (int)floor(log10((float)number)) + 1;
    int * arr = new int[length];
    int i = 0;
    do {
        arr[i] = number % 10;
        number /= 10;
        i++;
    } while (number != 0);
    
    for (int i=0;i<length/2;i++){
        arr[i]^=arr[length-i-1];
        arr[length-i-1]^=arr[i];
        arr[i]^=arr[length-i-1];
    }

    return arr;
}

int main()
{
	while(1){
		int input, randum[4],digSize=9;
		bool notfound = true;
		srand ( time(NULL) );
		int availDigs[9] = {1,2,3,4,5,6,7,8,9};
		vector<int> digits;
	
		for(int i=1;i<10;i++){
			digits.push_back(i);
		}
	
		for(int i=0;i<4;i++){
			int random = rand() % digSize;
			randum[i] = digits[random];
			digits.erase (digits.begin()+random);
			digSize--;
		}
		
		cout <<"\nI'm thinking of a number made up of four distinct digits 1 through 9..."<<endl;
		do{
			cout<<"Take a guess!"<<endl;
			while(1){
				cin>>input;
	
				if( ((int)floor(log10((float)input)) + 1) != 4 ){
					cout<<"Your guess must be four digits long! Guess again."<<endl;
					continue;
				}else{
					break;
				}
			}
	
			int * guess = new int[4];
			string message = "";
			guess = convertNumberToArray(input);
	
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){
					if( (randum[j] == guess[i]) && (i==j)){
						message += "fermi; ";
					}else if( (randum[j]  == guess[i]) && (i!=j) ){
						message += "pico; ";
					}
				}
			}
	
			if(message == ""){
				message += "bagel!";
			}
			if(message == "fermi; fermi; fermi; fermi; "){
				message += "\nCREAM CHEESE!\nCongratulations, you won!";
				notfound = false;
			}
			cout<<message<<endl;
		
		}while(notfound);


		cin.clear(); cin.ignore();
		cout << "\nPlay again? (y/n)" << endl;
		char c;
		cin>>c;
		cin.clear(); cin.ignore();
		switch(c){
			case 'y':
				continue;
				break;
			case 'n':
				break;
			default:
				cout<<"Huh? Let's just quit."<<endl;
				break;
		}
		break;
	}
	cout<<"Return to exit."<<endl;
	cin.get();
}

