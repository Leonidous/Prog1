#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int globalArgc; //for global argc variable
int GlobalErr=0; // for checking errors GlobalErr=0 is ALL PHRASES EQUAL, GlobalErr=-1 all other errors, GlobalErr=1 no errors
void Nchecker(string arg){

    string temp=arg;

    int z=atoi(temp.c_str());

    if(z==0||z<0){
        cout << "INVALID PHRASE LENGTH" << endl;
        GlobalErr=1;
    }
}

void ModeChecker(string arg){

    string temp=arg;

    if(globalArgc==2){
        if(temp!="top"&&temp!="all"){
            cout << "INVALID MODE" << endl;
            GlobalErr=-1; //change text to "NO MODE" if no mode runcase added.
        }
    }else if(temp!="top"&&temp!="all"){
            cout << "INVALID MODE" << endl;
            GlobalErr=-1;
    }
}

string PhraseMaker(vector<string> vec, int startPos, int N){

    string Phrase = vec[startPos];

    if((startPos+N)>vec.size()){
        return "Error";
    }else{
    for(int i=startPos+1; i!=startPos+N; i++){
        Phrase=Phrase + " " + vec[i];
    }

    return Phrase;
    }
}

int main(int argc, char *argv[]){

    globalArgc=argc-1;

    int N;
    string mode;

    if(argc-1==0){
        cout << "NO PHRASE LENGTH" << endl;
        GlobalErr=1;
    }else{

        for(int x=1; x<argc; x++){

        string s = argv[x];
            if(x==1){
                Nchecker(s);
                N=atoi(s.c_str());
            }
            if(x==2){
                ModeChecker(s);
                mode=s;
            }
            if(argc-1<=2 && ((mode=="all"||mode=="top") && (N!=0||N<0))){
                cout << "NO FILES GIVEN" << endl;
                GlobalErr=-1;
            }
            ifstream file;
            if(x>2){
                file.open(argv[x]);
                if( file.is_open()!=true ) {
                    cerr << "BAD FILE " << argv[x] << endl;
                    return -1;
                }else{
                    string name;
                    map<string, int> mymap;

                    vector<string> words;
                    while (file >> name){
                        transform(name.begin(), name.end(), name.begin(), ::tolower);
                        words.push_back(name);
                    }

                    for(int t=0; t<words.size(); t++){
                        string phrase=PhraseMaker(words, t, N);
                        if(phrase=="Error "){
                            break;
                        }
                        mymap[phrase]++;
                        GlobalErr=1;
                    }

                    string Phrase;
                    set<int>frequencies;

                    map<string,int>::iterator it;
                    if(mode=="all"){

                        for( it = mymap.begin(); it != mymap.end(); it++ ){
                            frequencies.insert(it->second);
                        }
                        if(frequencies.size()==1&&mymap.size()!=1){
                            cout << "ALL PHRASES EQUALLY FREQUENT" << endl;
                        }else{
                            for( it = mymap.begin(); it != mymap.end(); it++ ){
                                cout << it->first << " " << it->second << endl;
                            }
                        }

                        }else if(mode=="top"){
                        int v;
                        map<int, vector<string> > bycount;

                        map<string, int>::iterator it;
                        for(it = mymap.begin(); it != mymap.end(); it++){
                            bycount[it->second].push_back(it->first);
                        }

                        map<int,vector<string> >::iterator sit;
                        for(sit = bycount.begin(); sit != bycount.end(); sit++){
                            v = sit->first;
                            if(v>sit->first){
                                v = (sit->first);
                            }
                        }

                        for( it = mymap.begin(); it != mymap.end(); it++ ){
                            frequencies.insert(it->second);
                        }
                        if(frequencies.size()==1&&mymap.size()!=1){
                            cout << "ALL PHRASES EQUALLY FREQUENT" << endl;
                        }else{
                        for(int z=0; z<bycount[v].size(); z++){
                            cout << bycount[v][z] << " " << v << endl;
                        }
                        }
                    }
                    file.close();
                }
            }
        } if(GlobalErr==0){cout << "NO PHRASES\n";}
    }
}
