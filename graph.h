#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <map>

using namespace std;

class Node{
 private :
	string data;
	bool visit; // 해당 노드의 방문여부.
	int cost; // 해당 노드까지의 최소비용. default는 9999(infinite)
	vector<char> line_num; // 해당 노드를 지나가는 호선
	map<Node *, int> adj_list; // 해당 노드의 인접리스트 (인접노드의 주소, 노드 간 거리)

 public :
	Node(){
		visit = false;
		cost = 9999;}
	Node(string a){
		data = a;	
		visit = false;
		cost = 9999;}

	friend class Graph;
};


class Graph{
 public : 
	vector<Node> Node_list;
	void Add_Node(string); // 노드 추가
	void Add_Edge(string, string, int, int); // 인접노드추가 (연결할 노드1, 연결할 노드2, 호선, 노드 간 거리)
	void DFS_S(string); // DFS stack을 이용한
	void DFS_R(string); // DFS 재귀를 이용한
	void BFS(string); // BFS
	void Init(); // 초기 지하철 데이터값 입력
	void Print();
	void cost_Init();
	void visit_Init(); // DFS BFS 순환 후 모든 노드 visit 값 false로 변경
	int Shortcut(string, string); // 두 노드 간 최소비용 탐색
	bool Node_Search(string); // string에 해당되는 노드의 존재여부 반환
	bool Adj_Search(string, string); // string과 string이 인접하는 지 여부 반환
	

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

int Graph::Shortcut(string a, string b){
	Node *terminal;
	for(int i = 0; i < Node_list.size(); i++){
		if(Node_list[i].data == b) {terminal = &Node_list[i];}
		}  // b(종점)의 노드 주소값 저장

	if(Adj_Search(a, b)){
		Node *ps;
		for(int i = 0; i < Node_list.size(); i++){
			if(Node_list[i].data == a) ps = &Node_list[i];}
		terminal -> cost = terminal -> adj_list[ps];
		visit_Init();}
		

	else{
		map<Node *, int>::iterator it;
		if(!terminal -> visit){
			for(it = terminal -> adj_list.begin(); it != terminal -> adj_list.end(); it++){
					terminal -> visit = true;
					if(!it -> first -> visit){
						int *temp = new int;
						*temp = Shortcut(a, it -> first -> data) + it -> second;
						if(terminal -> cost > *temp) terminal -> cost = *temp;
						delete temp;}
					}

				}	
		}
	return terminal -> cost;
}

void Graph::cost_Init(){
	for(int i = 0; i < Node_list.size(); i++){
		Node_list[i].cost = 9999;}
}
	


void Graph::Print(){
	for(int i = 0; i < Node_list.size(); i++){
			cout << Node_list[i].data << '\t';}

	cout << '\n';
}
