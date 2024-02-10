#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;


// testing parseStringToWords
// int main(){
//     std::string rawWords = "we'll";
//     std::set<std::string> exampleSet = parseStringToWords(rawWords);
//     for(set<string>::iterator it=exampleSet.begin(); it != exampleSet.end(); ++it) {
//         cout << "Word: " << *it << endl;
//     }
// }

// //testing setIntersection and setUnion
// int main() {
//     set<string> s1;
//     s1.insert("Seth");
//     s1.insert("Jonah");
//     s1.insert("Michael");

//     cout << "Initial s1: " << endl;
//     for(set<string>::iterator it=s1.begin(); it != s1.end(); ++it){
//         cout << "Word: " << *it << endl;
//     }   

//     set<string> s2;
//     s2.insert("Kristen");
//     s2.insert("Rose");
//     s2.insert("Seth");

//     cout << "Initial s2: " << endl;
//     for(set<string>::iterator it=s2.begin(); it != s2.end(); ++it){
//         cout << "Word: " << *it << endl;
//     }   

//     cout << "Set Intersection" << endl;
//     std::set<string> intSet = setIntersection(s1, s2);
//     for(set<string>::iterator it=intSet.begin(); it != intSet.end(); ++it){
//         cout << "Item: " << *it << endl;
//     }   
//     cout << "Set Union" << endl;
//     set<string> unionSet = setUnion(s1, s2);
//     for(set<string>::iterator it=unionSet.begin(); it != unionSet.end(); ++it){
//         cout << "Item: " << *it << endl;
//     }   

// }