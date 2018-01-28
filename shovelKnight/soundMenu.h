#pragma once
#include "menuBase.h"

#define selectRect	4

class soundMenu : public menuBase
{
public:


	image* _soundLetter2Box;				//글자 2개박스
	image* _soundLetter4Box;				//글자 3개박스
	image* _soundLetter5Box;				//글자 5개박스
	image* _soundLetter10Box;				//글자 10개박스
	image* _soundLetterBoxEm;				//비어있는 박스
	image* _soundLetterBoxEm2;				//비어있는 박스
	image* _soundLetterBoxEm3;				//비어있는 박스
	image* _soundLetterBoxEm4;				//비어있는 박스

	
	animation* _soundLetterBoxAni;			//레터박스 애니 2글자짜리
	animation* _soundLetterBoxAni2;			//레터박스 애니 3글자짜리
	animation* _soundLetterBoxAni3;			//레터박스 애니 5글자짜리
	animation* _soundLetterBoxAni4;			//레터박스 애니 10글자짜리



	RECT _rcSound[selectRect];				//뒤로, 게임, 조작, 사운드, 그래픽, 데이터 삭제를 선택하기 위한 렉트를 깐다.
	int _indexSoundRc;						//인덱스 RC

	
	RECT _rcEffectVolume;					//이펙트볼륨바 렉트
	RECT _rcEffectVolumeButton;				//이펙트볼륨바 버튼 렉트
	RECT _bmgVolume;						//배경음볼륨바 렉트
	RECT _bgmVolumeButton;					//배경음볼륨바 버튼 렉트
	image* _effectVolumeButton;				//이펙트볼륨바 버튼 이미지
	image* _bgmVolumeButtonimg;				//배경음볼륨바 버튼 이미지

	int _effectSoundRectButtonX;			//이펙트사운드버튼X좌표
	int _bgmSoundRectButtonX;				//볼륨사운드버튼X좌표

	float _effectVol;						//이펙트 볼륨
	float _bgmVol;							//배경음 볼륨

	float _eV;								//이펙트 볼륨 계산
	float _bV;								//배경음 볼륨 계산

	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);
	void draw(HDC hdc);
	void effectVolumeControl();					//이펙트볼륨컨트롤
	void bgmVolumeControl();					//배경음볼륨컨트롤


	soundMenu();
	~soundMenu();
};

