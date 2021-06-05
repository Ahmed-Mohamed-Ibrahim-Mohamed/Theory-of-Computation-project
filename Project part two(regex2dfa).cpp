#include<iostream>
#include<stack>
#include<string>
#include <algorithm> 
#include<vector>
#include<regex>
#include<bits/stdc++.h>

using namespace std;

class node{
public:
	char input;
	int to;
	node *next;
};



int prec(char c){
	if(c=='*'){
		return 3;
	}else if(c=='.'){
		return 2;
	}else if(c=='|'){
		return 1;
	}else{
		return -1;
	}
}



string post(string s) 
{ 
    stack<char> st; 
    st.push('N'); 
    int l = s.length(); 
    string ns; 
    for(int i = 0; i < l; i++) 
    {
        if((s[i] >= 'a' && s[i] <= 'z')||(s[i] >= 'A' && s[i] <= 'Z')){
	        ns+=s[i]; 
        }

        else if(s[i] == '('){          
	        st.push('('); 
        }
        else if(s[i] == ')') 
        { 
            while(st.top() != 'N' && st.top() != '(') 
            { 
                char c = st.top(); 
                st.pop(); 
               ns += c; 
            } 
            if(st.top() == '(') 
            { 
                char c = st.top(); 
                st.pop(); 
            } 
          } 
        else{ 
            while(st.top() != 'N' && prec(s[i]) <= prec(st.top())) 
            { 
                char c = st.top(); 
                st.pop(); 
                ns += c; 
            } 
            st.push(s[i]); 
        } 

    } 
    while(st.top() != 'N') 
    { 
        char c = st.top(); 
        st.pop(); 
        ns += c; 
    } 
return ns;
}

void printnode(vector<node*> v){
	cout<<"___________________________________________"<<endl;
	cout<<"| from state\t| input\t| to states"<<endl;
	for(int i=0;i<v.size();i++){
		cout<<"| "<<i<<"          \t|";
		node* head = v[i];
 		cout<<head->input;
 		bool first = true;
		while(head!=NULL){
			if (first)
			{
				cout<<"     \t|";
				first = false;
			}else{
				cout<<"     \t";
			}
			cout<<head->to;
			head = head->next;
		}
		cout<<endl;
		// cout<<"\t\t\t\t\t\t|"<<endl;
	}
	cout<<"___________________________________________"<<endl;
}




node* makenode(char in){
	node* a = new node;
	a->input = in;
	a->to = -1;
	a->next = NULL;
	return a;
}

node* copynode(node* a){
	node* b = new node;
	b->input = -1;
	b->to = -1;
	b->next =NULL;
	return b;
}


void andd(vector<node*> &v,vector<vector<int> > &st){
	int x,y;
	int first,last1;
	y = st[st.size()-1][0];
	x = st[st.size()-2][1];
	first = st[st.size()-2][0];
	last1 = st[st.size()-1][1];

	st.pop_back();
	st.pop_back();

	vector<int> ptemp;
	ptemp.push_back(first);
	ptemp.push_back(last1);
	st.push_back(ptemp);

	node* last = v[y];
	node * lnode= v[x];
	node* temp = copynode(last);
	// temp->to = -1;
	while(lnode->next!=NULL){
		lnode = lnode->next;
	}
	lnode->next = temp;
	lnode->to = y;

}

void orr(vector<node*> &v,vector<vector<int> > &st){
	int x,y,x1,y1;
	x = st[st.size()-2][0];
	y = st[st.size()-1][0];
	x1 = st[st.size()-2][1];
	y1 = st[st.size()-1][1];
	node* start = makenode('e');
	node* end = makenode('e');
	v.push_back(start);
	int firstnode = v.size() -1;
	v.push_back(end);
	int endnode = v.size() -1;

	st.pop_back();
	st.pop_back();

	vector<int> ptemp;
	ptemp.push_back(firstnode);
	ptemp.push_back(endnode);
	st.push_back(ptemp);

	for(int i=0;i<v.size()-2;i++){
		node* h=v[i];
		while(h->next!=NULL){
			if(h->to==x || h->to == y){
				h->to = firstnode;
			}
			h = h->next;
		}
	}


	node* temp = copynode(v[x]);
	node* temp1 = copynode(v[y]);
	node* t = v[firstnode];
	while(t->next!=NULL){
		t = t->next;
	}
	t->to = x;
	t->next  = temp;
	t->next->to = y;
	t->next->next = temp1;

	node* adlink = v[x1];
	while(adlink->next!=NULL){
		adlink = adlink->next;
	}

	adlink->to= endnode;
	adlink->next = copynode(end);

	node* adlink1 = v[y1];
	while(adlink1->next!=NULL){
		adlink1 = adlink1->next;
	}
	adlink1->to = endnode;
	adlink1->next = copynode(end);

}


void closure(vector<node*> &v, vector<vector<int> > &st){
	int x,x1;
	x = st[st.size()-1][0];
	x1 = st[st.size()-1][1];
	node* s = makenode('e');
	// node* e = makenode('e');
	v.push_back(s);
	int firstnode = v.size() -1;
	// v.push_back(e);
	// int endnode = v.size() -1;
	st.pop_back();
	vector<int> ptemp;
	ptemp.push_back(x);
	ptemp.push_back(firstnode);
	st.push_back(ptemp);

	for(int i=0;i<v.size()-2;i++){
		node* h=v[i];
		while(h->next!=NULL){
			if(h->to==x){
				h->to = firstnode;
			}
			h = h->next;
		}
	}



	node* t = v[x1];
	while(t->next!=NULL){
		t = t->next;
	}
	t->to = x;
	t->next = copynode(t);
	t->next->to = firstnode;
	t->next->next = copynode(s);
}

void print(vector<vector<vector<int> > > table){
	cout<<"  STATE/INPUT  |";
	char a='a';
	for(int i=0;i<table[0].size()-1;i++){
		cout<<"   "<<a++<<"   |";
	}
	cout<<"   ^   "<<endl<<endl;
	for(int i=0;i<table.size();i++){
		cout<<"       "<<i<<"      ";
		for(int j=0;j<table[i].size();j++){
			cout<<" | ";
			for(int k=0;k<table[i][j].size();k++){ 
				cout<<table[i][j][k]<<" ";
				
			}
		}
		cout<<endl;
	}
}

void printdfa(vector<vector<int> > states, vector<vector<vector<int> > > dfa){
	cout<<"  STATE/INPUT  ";
	char a='a';
	for(int i=0;i<dfa[0].size();i++){
		cout<<"|   "<<a++<<"   ";
	}
	cout<<endl;
	for(int i=0;i<states.size();i++){
		cout<<"{ ";
		for(int h=0;h<states[i].size();h++)
			cout<<states[i][h]<<" ";
		if(states[i].empty()){
			cout<<"^ ";
		}
		cout<<"} ";
		for(int j=0;j<dfa[i].size();j++){
			cout<<" | ";
			for(int k=0;k<dfa[i][j].size();k++){
				cout<<dfa[i][j][k]<<" ";
				
			}
			if(dfa[i][j].empty()){
				cout<<"^ ";
			}
		}
		cout<<endl;
	}
}
vector<int> closure(int s,vector<vector<vector<int> > > v){
	vector<int> t;
	queue<int> q;
	t.push_back(s);
	int a=v[s][v[s].size()-1].size();
	for(int i=0;i<a;i++){
		t.push_back(v[s][v[s].size()-1][i]);
		//cout<<"t[i]"<<t[i]<<endl;
		q.push(t[i]);
	}
	while(!q.empty()){
		int f=q.front();
		q.pop();
		if(!v[f][v[f].size()-1].empty()){
			int u=v[f][v[f].size()-1].size();
			for(int i=0;i<u;i++){
				int y=v[f][v[f].size()-1][i];
				if(find(t.begin(),t.end(),y)==t.end()){
					//cout<<"y"<<y<<endl;
					t.push_back(y);
					q.push(y);
				}
			}
		}
	}
	return t;
}

int search(string re)
{
	string input;
	regex integer_expr(re);
	//As long as the input is correct ask for another number
	while (true)
	{
		cout << "Enter the input: ";
		cin >> input;
		if (!cin) break;
		//Exit when the user inputs q
		if (input == "q")
			break;
		if (regex_match(input, integer_expr))
			cout << "Accepted " << endl;
		else
		{
			cout << "Not Accepted " << endl;
		}
	}
	return 0;
}
int main(){
	string in;
	cout<<"Enter a regular expression : \n";
	cin>>in;
	string o;
	vector<node*> v;
	o = post(in);
	cout<<"\npostfix expression is : "<< o<<endl;
	vector<vector<int>> st;
	int firstnode = 0;
	for(int l =0 ;l<o.length();l++){
		if(o[l] !='|' && o[l]!='*' && o[l]!='.'){
			node* temp = makenode(o[l]);
			v.push_back(temp);
			vector<int> ptemp;
			ptemp.push_back(v.size()-1);
			ptemp.push_back(v.size()-1);
			st.push_back(ptemp);
		}
		else if(o[l]=='.'){
			andd(v,st);
		}
		else if(o[l]=='|'){
			orr(v,st);
		}
		else if(o[l]=='*'){
			closure(v,st);
		}


	}
	cout<<"\ntrainsition table for given regular expression is :  \n";
	printnode(v);
	cout<<endl;
	cout<<"start node is : ";
	cout<<"{"<<st[st.size()-1][0]<<"}"<<endl;
	cout<<"end node is : ";
	cout<<"{"<<st[st.size()-1][1]<<"}"<<endl;
		int n,alpha;
	cout<<"************************* NFA to DFA *************************"<<endl<<endl;
	cout<<"Enter total number of states in NFA : ";
	cin>>n;
	cout<<"Enter number of elements in alphabet : ";
	cin>>alpha;
	vector<vector<vector<int> > > table;
	for(int i=0;i<n;i++){
		cout<<"For state "<<i<<endl;
		vector< vector< int > > v;
		char a='a';
		int y,yn;
		for(int j=0;j<alpha;j++){
			vector<int> t;
			cout<<"Enter no. of output states for input "<<a++<<" : ";
			cin>>yn;
			cout<<"Enter output states :"<<endl;
			for(int k=0;k<yn;k++){
				cin>>y;
				t.push_back(y);
			}
			v.push_back(t);
		}
		vector<int> t;
		cout<<"Enter no. of output states for input ^ : ";
		cin>>yn;
		cout<<"Enter output states :"<<endl;
		for(int k=0;k<yn;k++){
			cin>>y;
			t.push_back(y);
		}
		v.push_back(t);
		table.push_back(v);
	}
	cout<<"<<<<<<<<< TRANSITION TABLE OF NFA >>>>>>>>>>"<<endl;
	print(table);
	cout<<endl<<"<<<<<<<<<< TRANSITION TABLE OF DFA >>>>>>>>>>"<<endl;
	vector<vector<vector<int> > > dfa;
	vector<vector<int> > states;
	states.push_back(closure(0,table));
	queue<vector<int> > q;
	q.push(states[0]);
	while(!q.empty()){
		vector<int> f=q.front();
		q.pop();
		vector<vector<int> > v;
		for(int i=0;i<alpha;i++){
			vector<int> t;
			set<int> s;
			for(int j=0;j<f.size();j++){
				
				for(int k=0;k<table[f[j]][i].size();k++){
					vector<int> cl= closure(table[f[j]][i][k],table);
					for(int h=0;h<cl.size();h++){
						if(s.find(cl[h])==s.end())
						s.insert(cl[h]);
					}
				}
			}
			for(set<int >::iterator u=s.begin(); u!=s.end();u++)
				t.push_back(*u);
			v.push_back(t);
			if(find(states.begin(),states.end(),t)==states.end())
			{	
				states.push_back(t);
				q.push(t);
			}
		}
		dfa.push_back(v);
	}
	printdfa(states,dfa);

	string s;
	cout<<"if you want check some strings acceptance enter y "<<endl;
	cin>>s;
	if(s=="y"){
	search(in);
	}
	system("pause");
	return 0;
}