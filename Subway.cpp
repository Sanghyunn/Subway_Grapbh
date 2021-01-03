#include "station_list.h"

int main(){
    int ps = 0;
    Graph subway;

	subway.Init();

	while(1){
		cout << "(1) 최단시간 (2) 최소환승 (3) 프린트 (4) 종료 : "; cin >> ps;
		string a, b;
        switch(ps){
			case 1 :
				cout << "출발할 지점 : "; cin >> a;
           		cout << "도착할 지점 : "; cin >> b;
           		cout << a << "에서 " << b << "까지 \n" << subway.Shortcut(a, b) << " 만큼 걸립니다." << endl;
				subway.cost_Init();
				subway.visit_Init();
				break;
            

			case 2:
				break;

			case 3 :
				subway.Print();
				break;}


        if(ps == 4) break;
    }

    cout << "프로그램 종료" << endl;
}

