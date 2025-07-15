#include <bits/stdc++.h>
using namespace std;

int check_time(int h, int m, int s) {
    if((h>= 6 && h< 18) ||
        (h==18 && m==0 && s==0))
        return 0;
    if((h >= 0 && h <= 5)) return 1;
    return 2;
}

struct Xe{
    string time;  
    string num; 
    Xe() = default;
    Xe(const Xe & x){
        time= x.time;
        num= x.num;
    }
    Xe(const string &_time, const string &_num){
        time=_time;
        num=_num;
    }
};

struct Node{
    Xe x;
    Node * next;
    Node (const Xe &a){
        x= a;
        next= nullptr;
    }
};

struct LinkedList{
    Node * head;
    LinkedList() {
        head= nullptr;
    }
    void printList();
    bool insertNode(Xe);
    int findNode(string);
    bool eraseNode(string time_out, string num);
    int cnt_moto();
    int bill(string time_, string num);
};

void LinkedList::printList(){
    Node *tmp= head;
    while(tmp != nullptr){
        cout<<tmp->x.num<<"\n";
        tmp=tmp->next;
    }
}
int LinkedList:: findNode(string plate){
    Node *tmp= head;
    int cur=0;
    while(tmp != nullptr){
        if(tmp-> x.num ==plate) return cur;
        tmp= tmp->next;
        cur++;
    }
    return -1;
}
bool LinkedList:: insertNode(Xe x){
    if(findNode(x.num) != -1) return false;
    Node * newNode= new Node(x);
    if(head== nullptr) {
        head= newNode;
        return true;
    }
    Node *tmp= head;
    while(tmp-> next != nullptr){
        tmp= tmp->next;
    }
    tmp->next= newNode;
    return true;
}

bool LinkedList::eraseNode(string time_out, string num){
    Node *tmp1= head, *tmp2= nullptr;
    while(tmp1 != nullptr){
        if(tmp1->x.num== num){
            if(tmp2== nullptr){
                head= tmp1->next;
                free(tmp1);
            }
            else {
                tmp2->next = tmp1->next;
                free(tmp1);
            }
            return true;
        }
        tmp2= tmp1;
        tmp1=tmp1->next;
    }
    return false;
}

int LinkedList::cnt_moto() {
    int cnt=0;
    Node *tmp= head;
    while(tmp != nullptr) {
        if(tmp->x.num[0] !='x') cnt++;
        tmp= tmp->next;
    }
    return cnt;
}

int LinkedList::bill(string time_, string num) {
    if(findNode(num)==-1) {
        return -1;
    }
    Node *tmp= head;
    string time_in;
    while(tmp !=  nullptr) {
        if(tmp->x.num== num) {
            time_in= tmp->x.time;
            break;
        }
        tmp= tmp->next;
    }
    int hour_in, min_in, sec_in;
    hour_in= min_in=sec_in=0;
    int hour,min, sec; // thời điểm xét
    hour= min=sec=0;
    for(int i=0; i< 8; i++) {
        if(i==0 or i==1) {
            hour_in= hour_in*10+ (time_in[i]-'0');
            hour= hour*10+ (time_[i]-'0');
        }
        else if(i==3 or i==4) {
            min_in= min_in*10+ (time_in[i]-'0');
            min= min*10+ (time_[i]-'0');
        }
        else if(i==6 or i==7) {
            sec_in= sec_in*10+ (time_in[i]-'0');
            sec= sec*10+ (time_[i]-'0');
        }
    }  // chuyển string sang số
    if(!check_time(hour_in,min_in,sec_in)) {
        if(!check_time(hour,min,sec)) {
            if(num[0]=='x') {
                return 1;
            }
            return 3;
        }
        else {
            if(num[0]=='x') {
                return 3;
            }
            return 8;
        }
    }
    else if(check_time(hour_in,min_in,sec_in)==1){
        if(check_time(hour, min, sec)==1 ) {
            if(num[0]=='x') {
                return 2;
            }
            return 5;
        }
        else if(check_time(hour, min, sec)==2){
            if(num[0]=='x') {
                return 5;
            }
            return 13;
        }else{
            if(num[0]=='x') {
                return 3;
            }
            return 8;
        }
    }
    else{
        if(num[0]=='x') {
            return 2;
        }
        return 5;
    }
}
int main () {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    LinkedList bdx;
    string s;
    
    while(true) {
        getline(cin,s);
        if(s=="*") break;
        string time_in, num;
        for(int i=0; i < (int)s.size(); i++) {
            if(i < 8) time_in+= s[i];
            if(i >= 9) num+= s[i];
        }
        Xe x(time_in, num);
        bdx.insertNode(x);
    }
    while(true) {
        getline(cin,s);
        if(s=="***") break;
        if(s=="list") bdx.printList();
        else if(s[0]=='i') {
            string time_in= s.substr(3,8);
            string num= s.substr(12,11);
            Xe x(time_in, num);
            cout<<bdx.insertNode( x)<<"\n";
        }
        else if(s[0]=='o') {
            string time_out= s.substr(4,8);
            string num= s.substr(13,11);
            cout<<bdx.eraseNode(time_out, num)<<"\n";
        }
        else if(s[0]=='f') {
            string num= s.substr(5,11);
            cout<<bdx.findNode(num)<<"\n";
        }
        else if(s[0]=='c') {
            cout<<bdx.cnt_moto()<<"\n";
        }
        else {
            string time_= s.substr(5,8);
            string num= s.substr(14,11);
            cout<<bdx.bill(time_,num)<<"\n";
        }
    }
}







