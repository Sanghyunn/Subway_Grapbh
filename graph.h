#include <vector>
#include <iostream>
#include <stack>
#include <queue> 
#include <map>
#include "line_color.h"

using namespace std;

class Node{
 private :
	string data;
	bool visit; // 해당 노드의 방문여부.
	int cost; // 해당 노드까지의 최소비용. default는 9999(infinite)
	int trans_count; // 환승횟수
	int now_line; // 현재 호선
	vector<Node *> route_list; // 해당 노드까지의 최소거리의 경로
	vector<Node *> temp_route;
	vector<char> line_num; // 해당 노드를 지나가는 호선
	map<Node *, int> adj_list; // 해당 노드의 인접리스트 (인접노드의 주소, 노드 간 거리)

 public :
	Node(){
		visit = false;
		cost = 9999;
		trans_count = 9999;}

	Node(string a){
		data = a;	
		visit = false;
		cost = 9999;
		trans_count = 9999;}

	friend class Graph;
};


class Graph{
 public : 
	vector<Node> Node_list;
	void Add_Node(string); // 노드 추가
	void Add_Edge(string, string, int, int); // 인접노드추가 (연결할 노드1, 연결할 노드2, 호선, 노드 간 거리)
	void Init(); // 초기 지하철 데이터값 입력
	void cost_Init();
	void visit_Init(); 
	bool Node_Search(string); // string에 해당되는 노드의 존재여부 반환
	bool Adj_Search(string, string); // string과 string이 인접하는 지 여부 반환
	int Line_Search(Node *, Node *);
	pair<int, int> Minimum_Trans(string, string); // 두 노드 간 최소환승 탐색
	pair<int, int> Shortcut(string, string); // 두 노드 간 최소비용 탐색
	void route_Print(string);
	

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

void Graph::visit_Init(){
	for(int i = 0; i < Node_list.size(); i++){
		Node_list[i].visit = false;}
}

void Graph::cost_Init(){
	for(int i = 0; i < Node_list.size(); i++){
		Node_list[i].cost = 9999;
		Node_list[i].trans_count = 9999;}
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



pair<int, int> Graph::Shortcut(string a, string b){
	Node *terminal;
	for(int i = 0; i < Node_list.size(); i++){
		if(Node_list[i].data == b) terminal = &Node_list[i];
		}  // b(종점)의 노드 주소값 저장

	if(Adj_Search(a, b)){
		Node *ps;
		for(int i = 0; i < Node_list.size(); i++){
			if(Node_list[i].data == a) ps = &Node_list[i];}

		if(terminal -> cost > terminal -> adj_list[ps]){ // a,b간 노드거리가 최단거리일때만 대입

			if(terminal -> trans_count > 0) terminal -> trans_count = 0;

			terminal -> now_line = Line_Search(ps, terminal);
			terminal -> cost = terminal -> adj_list[ps];
			terminal -> route_list.clear();
			terminal -> route_list.push_back(terminal);
			terminal -> route_list.push_back(ps);
				}
		}

	else{
		map<Node *, int>::iterator it;
		for(it = terminal -> adj_list.begin(); it != terminal -> adj_list.end(); it++){
				terminal -> visit = true; // terminal 지점 방문 체크
				if(!it -> first -> visit){
					pair<int, int> temp;
					int *temp_time = new int;
					int *temp_trans = new int;
					int *temp_line = new int;

					temp = Shortcut(a, it -> first -> data);

					*temp_time = temp.first + it -> second;
					*temp_trans = temp.second;
					*temp_line = Line_Search(it -> first, terminal);
					if(*temp_line != it -> first -> now_line){
						*temp_time += 3;//환승 시 소요시간 3분 추가
						(*temp_trans)++;//환승 횟수++
							}

					if(terminal -> cost > *temp_time){
						terminal -> now_line = *temp_line;
						terminal -> trans_count = *temp_trans;
						terminal -> cost = *temp_time;
						terminal -> route_list.clear();
						terminal -> route_list.push_back(terminal);
						copy(it -> first -> route_list.begin(), it -> first -> route_list.end(), back_inserter(terminal -> route_list));
							}

					delete temp_time;
					delete temp_trans;
					delete temp_line;
					}

				if(!terminal -> temp_route.empty()) terminal -> temp_route.pop_back();
				terminal -> visit = false; // terminal 지점 방문 체크 해제 (visit 초기화)
				}
		}
	return make_pair(terminal -> cost, terminal -> trans_count);
}




void Graph::route_Print(string b){
	Node *ps;
	for(int i = 0; i < Node_list.size(); i++){
		if(Node_list[i].data == b) ps = &Node_list[i];}

	vector<Node *>::iterator it = ps -> route_list.end() - 1;
	Color_Change(Line_Search(*it, *(it - 1)));
	for(; it != ps -> route_list.begin(); it--){
		Color_Change(Line_Search(*it, *(it - 1)));
		cout << (*it) -> data << " -> ";
		ps -> route_list.pop_back();}


	
	cout << (*it) -> data << endl;

	printf("%c[%d;%d;%dm",27,0,30,0); // 색상 초기화
}
	
	
int Graph::Line_Search(Node *a, Node *b){
	for(int i = 0; i < a -> line_num.size(); i++){
		for(int j = 0; j < b -> line_num.size(); j++){
			if(a -> line_num[i] == b -> line_num[j]) return (a -> line_num[i]);
								}
					}

	return 0;
}


