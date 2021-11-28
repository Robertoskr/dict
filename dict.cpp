#include "dict.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//demostration of usage of this dictionary class;


struct person{
    string name;
    int age;
};


string text = "this is an example text for testing the dict class, the problem is to find the most frecuent word in this text, good luck and hope you understand";


int main(){
    //EXAMPLE 1;
    person roberto;
    roberto.name = "roberto";
    roberto.age = 17;
    dict<string, person*> *d = new dict<string, person*>(100);
    d->add("julian", &roberto);
    person *other = d->get("julian");
    cout << other->age;
    //EXAMPLE 2;
    //example solving the frecuency problem using the dict;
    vector<string> words;
    int start = 0;
    int end = 0;
    int index = 0;


    for(auto c : text){
        if(c == ' '){
            words.push_back(string(text.begin() + start, text.begin() + end));
            start = end;
        }
        end++;
    }
    dict<string, int> frequency(100);
    string mostrepeated;
    int best = 0;
    for(auto word : words){
        int actual;
        if(frequency.find(word)){
            actual = frequency.get(word)+1;
            frequency.set(word, actual);
        }else{
            actual = 1;
            frequency.add(word, 1);
        }
        if(actual > best || actual == 0){
            best = actual;
            mostrepeated = word;
        }
    }
    cout << "the most repeated word is: " << mostrepeated << " with " << best << endl;
}