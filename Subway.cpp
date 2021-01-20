#include "station_list.h"

/* 환승 시 3분 추가 소요됩니다*/

int main(){
    int ps = 0;
    Graph subway;

	subway.Init();

	while(1){
		cout << "\t< 네이버 길찾기 >" << endl;
		cout << "(1) 길찾기 (2) 종료 : "; cin >> ps;
		string a, b;
		pair<int, int> result;
        switch(ps){
			case 1 :
				cout << "출발할 지점 : "; cin >> a;
           		cout << "도착할 지점 : "; cin >> b;

				result = subway.Shortcut(a, b);
				cout << "\n\t< 최 단 경 로 >" << endl;
           		cout << a << "에서 " << b << "까지 " << result.first << " 만큼 걸립니다. ( " << result.second << "번 환승)" << endl;
				subway.route_Print(b);
				subway.reset();




				cout << "\n\t< 최 소 환 승 >" << endl;
				result = subway.Minimum_Trans(a, b);
           		cout << a << "에서 " << b << "까지 " << result.first << " 만큼 걸립니다. ( " << result.second << "번 환승)" << endl;
				subway.route_Print(b);
				subway.reset();

				cout << '\n';
 
				break;

			case 2 :
				break;
			}
        
		if(ps == 2) break;
    }

    cout << "프로그램 종료" << endl;
}

