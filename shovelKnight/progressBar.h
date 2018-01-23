#pragma once
#include "gameNode.h"

//12.12일 까먹지 않고
//** ##const 반장## **, 동윤, 호형, 재선, 경훈, 설륜, 지성에게 과제 내줄껏
//까먹지 않고 12.14일 프레임웤 과제도 내줄 것.
//지금 호명된 사람들은 각자 자기의 방식대로 코딩을 해서
//왁자지껄에 올린다음 반 친구들에게 나눔나눔 ^^*을 합니다
//받아본 반 친구들은 누구것이 좋다며 리플을 달아주길 바랍니다

//일단 과제 -> 
//적들이 18마리씩 3세트가 총 출현하는데
//1세트는 좌우로 움직인다
//2세트는 위아래로 움직인다
//3세트는 (여러분 패턴주고싶은대로) 움직인다

//모든 미니언들은 체력바가 달려있다
//모든 미니언들이 다 죽으면 화면 위에서 거대한 보스가 내려온다

//지금 현재 로직상태로는 체력바가 맨 처음 셋팅한 수치로 크기가 고정이 된다
//헵타팀의 북두칠성들은 현재 프로그레스바 클래스를 수정하여
//크기 셋팅이 자유자재로 되게끔 한다

//참고로 내일도 북두칠성들만의 과제가 있다 *^^* 빨리하고 쉴 것.
class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	progressBar();
	~progressBar();

	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
};

