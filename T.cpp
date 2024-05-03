#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;
string str, opt, RT;
vector<string> value;
vector<string> opt_value;
CONSOLE_SCREEN_BUFFER_INFO csbi;
int columns, rows;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
int front_color = 0,back_color = 0;
#define black 0
#define blue 1
#define green 2
#define light_green 3
#define red 4
#define purple 5
#define yellow 6
#define white 7
#define gray 8
#define light_blue 9
#define pale_green 10
#define pale_light_green 11
#define pale_red 12
#define pale_purple 13
#define pale_yellow 14
#define light_white 15
#define elif else if
void COLOR_PRINT(const char* s, int color/*<=255*/)
{
    front_color = color & 0xF;
    back_color = (color >> 4) & 0xF;
 SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
 printf(s);
 SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}
void NULL_color(int color){
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
}
void NULL_color(int front_color,int back_color){
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | front_color | (back_color << 4));
}
void setfrontcolor(int color/*<=15*/){
    front_color = color&0xF;
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color | (back_color << 4));
}
void setbackcolor(int color/*<=15*/){
    back_color = (color) & 0xF;
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | (color << 4) | front_color);
}
void resetcolor(){
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | front_color | (back_color << 4));
    
}
void clean_color(){
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
    front_color = 0;
    back_color = 0;
}
void NULL_clean_color(){
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}
void lower(string &in){for(char &k : in){if((unsigned char)(k - 'A') <= 25)k |= 0X20;}}
bool isdigit(string s)
{
    bool d = false;
    for(int i = 0; i < s.size(); i ++)
    {
        if((s[i] < '0' or s[i] > '9')&& s[i] != '.') { return false; }
        if(s[i] == '.')
        {
            if(d) { return false; }
            d ++;
        }
    }
    return true;
}
bool isint(string s)
{
    for(int i = 0; i < s.size(); i ++)
    {
        if(s[i] < '0' || s[i] > '9') { return false; }
    }
    for(int i =0 ; i < 10 - s.size(); i++){
        s = "0" + s;
    }
    if(s > "2147483647") { return false; }
    return true;
}
void cls() { system("cls"); }
void print(char c, int n)
{
    if(n <= 0)
    return;
    while(n --)
    printf("%c", c);
}
int DEC_len(int n)
{
    int r = 0;
    while(n)
    {
        n /= 10;
        r ++;
    }
    return r;
}
void print()
{
    NULL_clean_color();
    NULL_color(yellow,gray);
    printf("\n==========DEBUG==========\n");
    NULL_clean_color();
    cout << "opt:" << opt << endl;
    if(opt_value.empty())
    {
        printf("no opt values\n");
    }
    else
    {
        int n = 1;
        for(vector<string>::iterator it = opt_value.begin(); it != opt_value.end(); it ++)
        {
            // printf("value -");
            NULL_color(n);
            printf("value -");
            print(' ', 5 - DEC_len(n));
            cout << n << "|||          " << it -> data() << endl;
            n ++;
        }
    }
    NULL_clean_color();
    printf("\n\n\n\n");
    if(value.empty())
    {
        printf("no values\n");
    }
    else
    {
        int n = 1;
        for(vector<string>::iterator it = value.begin(); it != value.end(); it ++)
        {
            // COLOR_PRINT("value -",n);
            NULL_color(n&0xF);
            printf("value -");
            print(' ', 5 - DEC_len(n));
            cout << n << "|||          " << it -> data() << endl;
            NULL_clean_color();
            n++;
        }
    }
    printf("========DEBUG_END========\n");
}
void push_back()
{
    value.insert(value.end(), opt_value.begin(), opt_value.end());
}
void push_front()
{
    value.insert(value.begin(), opt_value.begin(), opt_value.end());
}
void pop_v()
{
    if(value.empty())
    {
        return;
    }
    while(not value.empty())
    {
        if(count(opt_value.begin(), opt_value.end(), value.front())) { value.erase(value.begin()); }
        else break;
    }
    while(not value.empty())
    {
        if(count(opt_value.begin(), opt_value.end(), value.back())) { value.erase(value.end()); }
        else break;
    }
    /*vector<string>::iterator T = value.begin();
    for(vector<string>::iterator it=T;it!=value.end(); it ++ ){
        while(*(it+1) == opt_value[0]){
            if(value.size() == 1){
                value.clear();
                return;
            }
            value.erase(it+1);
        }
    }*/
    for(int i = 0; i < value.size(); i ++)
    {
        if(value.empty())
        {
            break;
        }
        if(count(opt_value.begin(), opt_value.end(), value[i]))
        {
            value.erase(value.begin() + i);
            i --;
        }
    }
}
void pop_back()
{
    if(value.empty()) { return; }
    if(opt_value.empty()) { value.erase(
        value.end() - 1); }
    else
    {
        if(isint(opt_value[0])) { 
            int n = stoi(opt_value[0]);
            value.erase(value.end() - min((int)value.size(),n),value.end()); }
        else
        {
            printf("WRONG!\n");
            return;
        }
    }
}
void pop_front()
{
    if(value.empty()) { return; }
    if(opt_value.empty()) { value.erase(
        value.begin()); }
    else
    {
        if(isint(opt_value[0])) { 
            int n = stoi(opt_value[0]);
            value.erase(value.begin(),value.begin() + min((int)value.size(),n)); }
        else
        {
            printf("WRONG!\n");
            return;
        }
    }
}
void help()
{
    printf("vector = {a,b,c}\n");
    printf("push xxx ->  {a,b,c,xxx}\n");       // ok
    printf("push_back xxx ->  {a,b,c,xxx}\n");  // ok
    printf("push_front xxx ->  {xxx,a,b,c}\n"); // ok
    printf("pop_v c -> {a,b}\n");               // ok
    printf("pop_back -> {a,b}\n");              // ok
    printf("pop_front -> {b,c}\n");
    printf("pop_back 1 -> {a,b}\n");
    printf("pop_front 1 -> {b,c}\n");
    printf("\"color\" (front or back) color");
    system("pause");
    cls();
}
int main(/*int argc, char const *argv[]*/)
{
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    while(opt != "exit")
    {
        // code for cin
        {
            NULL_clean_color();
            cls();
            print();
            str.clear();
            opt.clear();
            RT.clear();
            opt_value.clear();
            resetcolor();
            printf("AZZR>>>");
            getline(cin, str);
            for(int i = 0; i < str.length(); i ++)
            {
                if(str[i] == ' ')
                {
                    if(RT.empty())
                    continue;
                    if(opt.empty())
                    {
                        opt = RT;
                    }
                    else
                    {
                        opt_value.push_back(RT);
                    }
                    RT.clear();
                }
                else
                {
                    RT.push_back(str[i]);
                }
            }
            if(not RT.empty())
            {
                if(opt.empty())
                {
                    opt = RT;
                }
                else
                {
                    opt_value.push_back(RT);
                }
            }
        }
        // cls();
        lower(opt);
        if(opt == "push" or opt == "push_back"){push_back();}
        if(opt == "push_front"){push_front();}
        if(opt == "pop_v"){pop_v();}
        if(opt == "pop_back"){pop_back();}
        if(opt == "pop_front"){pop_front();}
        if(opt == "test")
        {
            if(not opt_value.empty()){
                if(isint(opt_value[0])){
                    srand(time(0));
                    for(int i = 0 ; i < stoi(opt_value[0]) ; i++){
                        value.push_back(to_string(rand()));
                    }
                }
            }
            else{
                for(int i = 1; i <= 10; i ++)
                {
                    value.push_back(to_string(i));
                }
            }
        }
        if(opt == "color"){
            if(opt_value[0] == "front"){
                if(opt_value[1] == "black"){setfrontcolor( 0 );}
                if(opt_value[1] == "blue"){setfrontcolor( 1 );}
                if(opt_value[1] == "green"){setfrontcolor( 2 );}
                if(opt_value[1] == "light_green"){setfrontcolor( 3 );}
                if(opt_value[1] == "red"){setfrontcolor( 4 );}
                if(opt_value[1] == "purple"){setfrontcolor( 5 );}
                if(opt_value[1] == "yellow"){setfrontcolor( 6 );}
                if(opt_value[1] == "white"){setfrontcolor( 7 );}
                if(opt_value[1] == "gray"){setfrontcolor( 8 );}
                if(opt_value[1] == "light_blue"){setfrontcolor( 9 );}
                if(opt_value[1] == "pale_green"){setfrontcolor( 10 );}
                if(opt_value[1] == "pale_light_green"){setfrontcolor( 11 );}
                if(opt_value[1] == "pale_red"){setfrontcolor( 12 );}
                if(opt_value[1] == "pale_purple"){setfrontcolor( 13 );}
                if(opt_value[1] == "pale_yellow"){setfrontcolor( 14 );}
                if(opt_value[1] == "light_white"){setfrontcolor( 15 );}
            }
            if(opt_value[0] == "back"){
                if(opt_value[1] == "black"){setbackcolor( 0 );}
                if(opt_value[1] == "blue"){setbackcolor( 1 );}
                if(opt_value[1] == "green"){setbackcolor( 2 );}
                if(opt_value[1] == "light_green"){setbackcolor( 3 );}
                if(opt_value[1] == "red"){setbackcolor( 4 );}
                if(opt_value[1] == "purple"){setbackcolor( 5 );}
                if(opt_value[1] == "yellow"){setbackcolor( 6 );}
                if(opt_value[1] == "white"){setbackcolor( 7 );}
                if(opt_value[1] == "gray"){setbackcolor( 8 );}
                if(opt_value[1] == "light_blue"){setbackcolor( 9 );}
                if(opt_value[1] == "pale_green"){setbackcolor( 10 );}
                if(opt_value[1] == "pale_light_green"){setbackcolor( 11 );}
                if(opt_value[1] == "pale_red"){setbackcolor( 12 );}
                if(opt_value[1] == "pale_purple"){setbackcolor( 13 );}
                if(opt_value[1] == "pale_yellow"){setbackcolor( 14 );}
                if(opt_value[1] == "light_white"){setbackcolor( 15 );}
            }
        }
        if(opt == "help")
        {
            help();
        }
    }
    return 0;
}