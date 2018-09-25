/*
Markovian Tweet Generator
Authors: Steven Soranno, Mike Meehan
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>
#include <time.h>

using namespace std;

struct MarkovianList{
    string word;
    vector<string> nextWords;
};

int dictContains(vector<MarkovianList> Dict, string s, int length);
vector<MarkovianList> makeDictionary(string tweet[],int length);
int dictContains(vector<MarkovianList> Dict, string s, int length);
string createTweet(vector<MarkovianList> Dict, string startWord);
void printTweet(string tweet);

vector<MarkovianList> makeDictionary(string tweet[],int length){
    vector<MarkovianList> Dict;
    for(int i = 0; i<length-1; i++){
        int index = dictContains(Dict,tweet[i],length);
	if(index != -1){
        //cout<< "nextword"<< tweet[i+1]<< endl;
            
	    Dict[index].nextWords.push_back(tweet[i+1]);
            
	} else{
            MarkovianList newList;
            newList.word = tweet[i];
            newList.nextWords.push_back(tweet[i+1]);
            Dict.push_back(newList);
	}
    }
    //Print Dict
    /*for(int i = 0; i<Dict.size(); i++){
        cout<< "word:"<< Dict[i].word;
        cout<<" wordlist: ";
        for(int j = 0; j<Dict[i].nextWords.size(); j++){
            cout<< Dict[i].nextWords[j]<< ", ";
        }
        cout<< endl;
    }*/
    return Dict;
}

int dictContains(vector<MarkovianList> Dict, string s, int length){
    vector<MarkovianList>::iterator it;    
    for(int i = 0; i<Dict.size(); i++){
        string w1 = Dict[i].word;
        string w2 = s;
        transform(w1.begin(), w1.end(), w1.begin(), ::tolower);
        transform(w2.begin(), w2.end(), w2.begin(), ::tolower);  
	if(w1 == w2){
	    return i;
	}
    }
    return -1;
}

string createTweet(vector<MarkovianList> Dict, string startWord){
    int numCharacters = 0;
    string currentWord = startWord;
    string newTweet = startWord;
    srand(time(0));
    while(numCharacters < 280){
        int indexCurrentWord = dictContains(Dict, currentWord, Dict.size());
        int sizeOfNextWord = Dict[indexCurrentWord].nextWords.size();
        int randIndex = rand()%sizeOfNextWord;

        // Testing print statements
        //cout<< "Current Word:"<<currentWord << endl;
        //cout<< "randIndex:"<<randIndex << endl;
        string nextWord = Dict[indexCurrentWord].nextWords[randIndex];
        //cout<< "nextWord" << nextWord << endl;
        if(nextWord != "." && nextWord != "?" && nextWord != "!" && nextWord != "," && nextWord != ";"){
            //cout<< "added space" << endl;
            newTweet = newTweet+ " " + nextWord;
            //cout<< "newTweet+space:" << newTweet << endl;
            numCharacters = numCharacters + nextWord.length()+1;
        } else{
            newTweet = newTweet+nextWord;
            numCharacters = numCharacters + nextWord.length();
	}
        //cout<< "newTweet:" << newTweet << endl;
        //cout<< "newTweet len:" << newTweet.length() << endl;
        //cout<< "numChar:"<< numCharacters << endl;
        currentWord = "";
        currentWord = currentWord+nextWord;
    }
    return newTweet;
}

void printTweet(string tweet){
    cout<< "New Tweet:" << endl;
    int indexOfSpace1 = 0;
    for(int i = 70; i<80; i++){
        if(tweet[i] ==' '){
            indexOfSpace1 = i;
        }
    }
    string line1 = tweet.substr(0,indexOfSpace1);
    cout<< line1 << endl;
    int indexOfSpace2 = 0;
    for(int i = indexOfSpace1+70; i<indexOfSpace1+80; i++){
        if(tweet[i] == ' '){
            indexOfSpace2 = i;
        }
    }
    string line2 = tweet.substr(indexOfSpace1+1,indexOfSpace2-(indexOfSpace1+1));
    cout<< line2 << endl;
    int indexOfSpace3 = 0;
    for(int i = indexOfSpace2+70; i<indexOfSpace2+80; i++){
        if(tweet[i] == ' '){
            indexOfSpace3 = i;
        }
    }
    string line3 = tweet.substr(indexOfSpace2+1,indexOfSpace3-(indexOfSpace2+1));
    cout<< line3 << endl;
    string line4 = tweet.substr(indexOfSpace3+1,tweet.length()-indexOfSpace3);
    cout<< line4 << endl;
    //cout<< line1 << endl << line2 << endl << line3 << endl << line4 << endl;
}

int main(){
    ifstream file;
    file.open("tweet.txt");
    string word;
    vector<string> tweet;
    int i = 0;
    if(!file.is_open()){
        cout<< "Could not open file" << endl;
        return 0;
    } else{
        while(file >> word){
            string newWords[10];
            string temp = word;
            int k = 0;
            for(int j = 0; j<temp.length();j++){
	        //cout<<"word: " << word;
                word.erase(remove( word.begin(), word.end(), '\"' ),word.end());
                if(word.find(".") != std::string::npos){
                    newWords[k] = word[word.find(".")];
                    word.erase(word.find("."),1);
                    k++;
                }
		if(word.find(",") != std::string::npos){
		    newWords[k] = word[word.find(",")];
                    word.erase(word.find(","),1);
                    k++;
		}
		if(word.find("?") != std::string::npos){
                    newWords[k] = word[word.find("?")];
                    word.erase(word.find("?"),1);
                    k++;
                }
		if(word.find("!") != std::string::npos){
                    newWords[k] = word[word.find("!")];
                    word.erase(word.find("!"),1);
                    k++;
                }
                if(word.find(";") != std::string::npos){
                    newWords[k] = word[word.find(";")];
                    word.erase(word.find(";"),1);
                    k++;
                }

                /*if(word.find("\"") != std::string::npos){
                    cout<< " gotHere ";
	            word.erase(word.find("\""),1);
                    k++;
                }*/
                //cout<< "  word2: "<< word << endl;
            }
            tweet.push_back(word);
	    i++;
            for(int j = 0; j<10; j++){
                if(newWords[j] != ""){
		    tweet.push_back(newWords[j]);
		    i++;
		}
            }
        }
    }
    string newArr[i];
    for(int q = 0; q<i; q++){
        newArr[q] = tweet[q];
        //cout<<tweet[q]<<endl;
    }
    vector<MarkovianList> Dict = makeDictionary(newArr, i);
    string newTweet = createTweet(Dict,"The");
    printTweet(newTweet);
    file.close();
    return 0;
}
