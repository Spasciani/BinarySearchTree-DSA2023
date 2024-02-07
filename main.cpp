#include <iostream>
#include "BST.h"

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

//Main gets the lines from the document and calls actions in BST.h based on the line
int main(){
	BST* bstTree = new BST();
	string obtainLine;
	getline(cin, obtainLine); //gets the first line: number of commands
	int count = stoi(obtainLine);

	for(int i = 0; i < count; i++){ //Obtains the next commands based on the first line
		getline(cin, obtainLine);
		int emptySpaceCount = std::count(obtainLine.begin(), obtainLine.end(), ' '); //empty space determines if there is a first and last name
		istringstream in(obtainLine);
		string desired;
		in >> desired; //sets desired to the input

		if(desired == "insert"){

			bool fullname = false;
			bool successful = true;
			string name;
			string firstname;
			string lastname;
			string ufID;

			getline(in, firstname, '"');
			in >> firstname;
			if(emptySpaceCount > 2){
				getline(in, lastname, '"');
				name = firstname + lastname;
			}
			if(emptySpaceCount < 3){
				name = firstname;
				name.erase(remove(name.begin(), name.end(), '"')); //Removes the ""
			}
			for(char c : name){
				if(!isalpha(c) && c!= ' '){ //checks if there are values besides letters or spaces in the name
					cout <<"unsuccessful" <<endl;
					successful = false;
					break;
				}
			}
			if(successful){ //if passes all checks and successful do this:
				getline(in, ufID, ' ');
				in >> ufID;
				for(char c : ufID){
					if(!isdigit(c) || ufID.length() != 8){
						cout << "unsuccessful" <<endl;
						successful = false;
						break;
					}
				}
				if(successful){
					bstTree->insertPub(stoi(ufID), name);
				}
			}

		}else if(desired == "remove"){ //Removes ufID from the BST
			bool successful = true;
			string ufID;
			in >> ufID;
			for(char c : ufID){
				if(!isdigit(c) && ufID.length() != 8){
					cout << "unsuccessful" <<endl;
					successful = false;
					break;
				}
			}
			if(successful){
				bstTree->removeIDPub(stoi(ufID));
				cout<< "successful" <<endl;
			}

		}else if(desired == "search"){ //Both search by name and Search by ID are conducted through this main
			bool verify;
			string in1;
			string in2;
			string in3;
			getline(in, in1, ' ');
			in >> in2;
			if(emptySpaceCount > 1){
				in >> in3;
				in1 = in2 + ' ' + in3;
			}else{
				in1 = in2;
			}
			if(!isdigit(in1.at(2))){
				getline(in, in1, '"');
				in1.erase(remove(in1.begin(),in1.end(),'"'));
				in1.erase(remove(in1.begin(),in1.end(),'"'));

			}
			for(char c : in1){
				if (isdigit(c) && in1.length() == 8){
					verify = true;
				}else if (isalpha(c) && c != ' '){
					verify = false;
				}
			}
			if(verify == true){ //Search by ID
				bstTree->searchIDPub(stoi(in1));
			}
			if(verify == false){ //Search by name
				bstTree->searchNamePub(in1);
			}

		}else if(desired == "removeInorder"){
			string x;
			int n;
			bool verify = true;
			getline(in, x, ' ');
			in >> x;
			n = stoi(x);
			if(n < 0){
				cout<< "unsuccessful";
				verify = false;
			}
			if(verify){
				bstTree->removeInorderPub(stoi(x));
			}

		}else if(desired == "printLevelCount"){
			bstTree->printLevelCountPub();

		}else if (desired == "printInorder"){
			bstTree->printInorderPub();
			cout<< endl;

		}else if(desired == "printPreorder"){
			bstTree->printPreorderPub();
			cout<< endl;

		}else if(desired == "printPostorder"){
			bstTree->printPostorderPub();
			cout<< endl;

		}else{
			cout << "unsuccessful" <<endl;
		}
	}
	delete bstTree;


	return 0;
}

