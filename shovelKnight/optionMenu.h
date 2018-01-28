#pragma once
#include "menuBase.h"
#include "soundMenu.h"

enum LETTERBOX
{
	LETTERBACK,					//뒤로
	LETTERGAME,					//게임
	LETTERCONTROL,				//조작
	LETTERSOUND,				//사운드
	LETTERGRAPHIC,				//그래픽
	LETTERDATADELETE,			//데이터삭제
	LETTEREND
};

#define selectRect	6


class optionMenu : public menuBase
{
public:

	image* _letter2Box;				//글자 2개박스
	image* _letter3Box;				//글자 3개박스
	image* _letter5Box;				//글자 5개박스
	image* _letterBox;				//비어있는 박스
	image* _letterBoxEm;			//비어있는 박스
	image* _letterBoxEm2;			//비어있는 박스

	LETTERBOX _letterBoxEnum;			//셀렉트 레터박스 이넘제어변수
	animation* _letterBoxAni;			//레터박스 애니 2글자짜리
	animation* _letterBoxAni2;			//레터박스 애니 3글자짜리
	animation* _letterBoxAni3;			//레터박스 애니 5글자짜리


	soundMenu* _sm;

	RECT _rcOption[selectRect];			//뒤로, 게임, 조작, 사운드, 그래픽, 데이터 삭제를 선택하기 위한 렉트를 깐다.
	int _indexRc;						//인덱스 RC

	bool _isSoundMenu;					//사운드메뉴 그리기용


	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);
	void draw(HDC hdc);

	void showLetterBox();
	
	
	inline bool getIsSoundMenu() { return _isSoundMenu; }

	optionMenu();
	~optionMenu();
};

