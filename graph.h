#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <map>

using namespace std;

class Node{
 private :
	string data;
	bool visit;
	vector<char> line_num;
	map<Node *, int> adj_list;

 public :
	Node(){
		visit = false;}
	Node(string a){
		data = a;	
		visit = false;}

	friend class Graph;
};


class Graph{
 public : 
	vector<Node> Node_list;
	void Add_Node(string);
	void Add_Edge(string, string, int, int);
	void DFS_S(string);
	void DFS_R(string);
	void BFS(string);
	void Init();
	void visit_Init();
	bool Node_Search(string);
	bool Adj_Search(string, string);
	

};	
	

void Graph::Add_Node(string a){
	Node Temp(a);
	Node_list.push_back(Temp);

	for(int i = 0; i < Node_list.size(); i++){
		for(int j = 0; j < Node_list.size(); j++){
			map<Node *, int>::iterator it;
			for(it = Node_list[j].adj_list.begin(); it != Node_list[j].adj_list.end(); it++){
				if(Node_list[i].data == it -> first -> data) Node_list[j].adj_list[&Node_list[i]] = it -> second;}
							}
					}

}
	

void Graph::Add_Edge(string a, string b, int line_num, int distance){
	Node *Temp1; Node *Temp2;
	for(int i = 0 ; i < Node_list.size(); i++){
		if(Node_list[i].data == a) Temp1 = &Node_list[i];
		if(Node_list[i].data == b) Temp2 = &Node_list[i];}


	Temp1 -> adj_list[Temp2] = distance;
	Temp2 -> adj_list[Temp1] = distance;

	Temp1 -> line_num.push_back(line_num);
	Temp2 -> line_num.push_back(line_num);
}


void Graph::DFS_S(string a){
	Node *ps;
	for(int i = 0; i < Node_list.size(); i++){ // a값에 해당되는 Node 위치 찾기
		if(Node_list[i].data == a) ps = &Node_list[i];}

	stack<Node *> DFS_stack;

	ps -> visit = true;
	DFS_stack.push(ps);

	while(!DFS_stack.empty()){
		ps = DFS_stack.top();
		cout << ps -> data << '\t';
		DFS_stack.pop();
		

		map<Node *, int>::iterator it;

		for(it = ps -> adj_list.begin(); it != ps -> adj_list.end(); it++){	
			if(!it -> first -> visit) {
				it -> first  -> visit = true;
				DFS_stack.push(it -> first);}
					
			}
	}
}



void Graph::DFS_R(string a){
	Node * Head;
	for(int i = 0; i < Node_list.size(); i++){
		if(Node_list[i].data == a) Head = &Node_list[i];}

	
	Node *ps = Head;

	if(!ps -> visit){
		ps -> visit = true;
		cout << ps -> data << '\t';

		map<Node *, int>::iterator it;
		for(it = ps -> adj_list.begin(); it != ps -> adj_list.end(); it++){
			DFS_R(it -> first -> data);}
		}

}



void Graph::BFS(string a){
	Node *ps;
	for(int i = 0; i < Node_list.size(); i++){ // a값에 해당되는 Node 위치 찾기
		if(Node_list[i].data == a) ps = &Node_list[i];}

	queue<Node *> BFS_queue;

	ps -> visit = true;
	BFS_queue.push(ps);

	while(!BFS_queue.empty()){
		ps = BFS_queue.front();
		cout << ps -> data << '\t';
		BFS_queue.pop();
		

		map<Node *, int>::iterator it;
		for(it = ps -> adj_list.begin(); it != ps -> adj_list.end(); it++){
			if(it -> first -> visit) {
				it -> first  -> visit = true;
				BFS_queue.push(it -> first);}
			}
	}
}

void Graph::visit_Init(){
	for(int i = 0; i < Node_list.size(); i++){
		Node_list[i].visit = false;}
}



bool Graph::Node_Search(string b){
	for(int i = 0; i < Node_list.size(); i++){
		if(Node_list[i].data == b) return true;}


	return false;}


bool Graph::Adj_Search(string a, string b){

	Node * ps;
	for(int i = 0; i < Node_list.size(); i++){
		if(Node_list[i].data == a) ps = &Node_list[i];}

	map<Node *, int>::iterator it;
	for(it = ps -> adj_list.begin(); it != ps -> adj_list.end(); it++){
		if(it -> first -> data == b) return true;}


	return false;}

