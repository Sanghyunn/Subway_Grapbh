#include "graph.h" 

void Graph::Init(){
	// 2호선
	Add_Node("상왕십리"); Add_Node("왕십리"); Add_Node("한양대"); Add_Node("뚝섬"); Add_Node("성수"); Add_Node("건대입구"); Add_Node("구의"); Add_Node("강변"); 
	Add_Node("잠실나루"); Add_Node("잠실"); Add_Node("잠실새내"); Add_Node("종합운동장"); Add_Node("삼성"); Add_Node("선릉");
	
	// 5호선
	Add_Node("신금호"); Add_Node("행당"); Add_Node("마장"); Add_Node("답십리"); Add_Node("장한평"); Add_Node("군자"); Add_Node("아차산"); Add_Node("광나루"); 
	Add_Node("천호"); Add_Node("강동");

	// 7호선
	Add_Node("반포"); Add_Node("논현"); Add_Node("학동"); Add_Node("강남구청"); Add_Node("청담"); Add_Node("뚝섬유원지"); Add_Node("어린이대공원"); Add_Node("중곡"); 
	Add_Node("용마산"); 

	// 8호선
	Add_Node("몽촌토성"); Add_Node("강동구청"); Add_Node("암사");

	// 9호선
	Add_Node("선정릉");

	// 분당선(10호선)
	Add_Node("압구정로데오"); Add_Node("서울숲");
	
	

	// ----------------------------------------------------------------- 노 선 추 가 ------------------------------------------------------------------------------------



	// 2호선
	Add_Edge("상왕십리", "왕십리", 2, 1); Add_Edge("왕십리", "한양대", 2, 2); Add_Edge("한양대", "뚝섬", 2, 2); Add_Edge("뚝섬", "성수", 2, 1);
	Add_Edge("성수", "건대입구", 2, 2); Add_Edge("건대입구", "구의", 2, 2); Add_Edge("구의", "강변", 2, 1); Add_Edge("강변", "잠실나루", 2, 4); 
	Add_Edge("잠실나루", "잠실", 2, 2); Add_Edge("잠실", "잠실새내", 2, 1); Add_Edge("잠실새내", "종합운동장", 2, 1); Add_Edge("종합운동장", "삼성", 2, 1);
	Add_Edge("삼성", "선릉", 2, 1);

	// 5호선
	Add_Edge("왕십리", "마장", 5, 1); Add_Edge("마장", "답십리", 5, 2); Add_Edge("답십리", "장한평", 5, 2); Add_Edge("장한평", "군자", 5, 1);
	Add_Edge("군자", "아차산", 5, 1); Add_Edge("아차산", "광나루", 5, 2); Add_Edge("광나루", "천호", 5, 2);

	// 7호선
	Add_Edge("강남구청", "청담", 7, 1); Add_Edge("청담", "뚝섬유원지", 7, 2); Add_Edge("뚝섬유원지", "건대입구", 7, 2); Add_Edge("건대입구", "어린이대공원", 7, 1);
	Add_Edge("어린이대공원", "군자", 7, 1);

	// 8호선
	Add_Edge("잠실", "몽촌토성", 8, 1); Add_Edge("몽촌토성", "강동구청", 8, 2); Add_Edge("강동구청", "천호", 8, 1); 

	// 분당선(10호선)
	Add_Edge("선릉", "선정릉", 10 ,2); Add_Edge("선정릉", "강남구청", 10, 1); Add_Edge("강남구청", "압구정로데오", 10, 2); Add_Edge("압구정로데오", "서울숲", 10, 2); 
	Add_Edge("서울숲", "왕십리", 10, 3);
}
