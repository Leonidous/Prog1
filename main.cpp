#include <string>
#include <bits/stdc++.h>
using namespace std;

string argumentf(string arg)
{
    string temp=arg;

        if(temp[0]=='L'){
            temp.erase(0,1);

            for(int x=0; x<=temp.length(); x++){
                    char c;
                    c = temp[x];
                    temp[x]=tolower(c);
            }

        }else if(temp[0]=='U'){
            temp.erase(0,1);

            for(int x=0; x<=temp.length(); x++){
                    char c;
                    c = temp[x];
                    temp[x]=toupper(c);
            }

        }else if(temp[0]=='r'){
            temp.erase(0,1);
            reverse(temp.begin(), temp.end());

        }else if(temp[0]=='R'){
            temp.erase(0,1);
            reverse(temp.begin(), temp.end());

            for(int x=0; x<=temp.length(); x++){
                    char c;
                    c = temp[x];
                    temp[x]=toupper(c);
            }

        }else{

        temp="FAIL";

        }

        return temp;
}

int main(int argc, char *argv[])
{
    for(int x=1; x<argc; x++){
        string s = argv[x];

        if(s[0]!='S'){
        cout<<argumentf(argv[x])<<endl;
        }
    }
}
