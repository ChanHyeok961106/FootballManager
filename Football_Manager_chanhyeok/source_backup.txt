#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;
// 스트링 처리와 기본 입출력, 파일 입출력시 사용하는 라이브러리들 등등

// PLAYER 라는 선수 개인의 데이터를 간단하게 프로그램에서 돌리기 위한 변수 (포인터 변수로 선수단 구성)
typedef struct player {
	double stats[12]; // 스탯들 저장하는 곳 12가지 스탯이 저장됨
	char name[20]; // 선수이름
}PLAYER;
// 사용자의 ID와 PASSWORD를 위한 객체
class user { // 사용자
public:
	char ID[10]; // ID
	char PASS[10]; // PASSWORD
public:
	user() { strcpy(this->ID, "test_id"); strcpy(this->PASS, "test_pass"); } // 디폴트
	user(char *id, char *pass) { strcpy(this->ID, id); strcpy(this->PASS, pass); } // 아이디와 비밀번호 받아 저장하는 생성자
	void setID(char *id) { strcpy(this->ID, id); } // 아이디 설정 및 재설정용
	void setPASS(char *pass) { strcpy(this->PASS, pass); } // 비밀번호 설정 및 재설정용
	char *getID() { return this->ID; } // ID getter
	char *getPASS() { return this->PASS; } // PASSWORD getter
};
// user를 상속받는 user의 정보 객체
class user_info : public user { // user를 상속받는 user의 정보 객체
public:
	user DATA; // user ID PASSWORD 데이터 객체
	char PHONE[20]; // 전화번호
public:
	user_info() :DATA() { strcpy(this->PHONE, "test_phone"); } // 디폴트
	user_info(char *id, char *pass, char *phone) :user(id, pass) { strcpy(this->PHONE, phone); } // user 호출 과 아이디 비번 설정 생성자
	void setPHONE(char *phone) { strcpy(this->PHONE, phone); } // 전화번호 설정 및 재설정용
	char *getPHONE() { return this->PHONE; } // 전화번호 getter
	void print() { cout << getID() << "\t" << getPASS() << "\t" << getPHONE() << endl; } // 사용자의 모든 정보 출력용 함수
	void member_print() { cout << getID(); } // 사용자 ID 정보 출력용
};

// 아래 포지션들의 부모 클래스 -> 능력치 구현/ 가상함수 베이스 구현
class FORMATION {
public:
	double goal; // 골결정력
	double power; // 슛파워
	double shotpass; // 짧은패스
	double longpass; // 롱패스
	double cut; // 가로채기
	double cross; // 크로스
	double defence; // 대인수비
	double run; // 속력
	double save; // 선방능력
	double fast; // 반응속도
	double poten; // 개인기능력 (전체곱셈용)
	double LR; // 좌측 우측 선호도 (왼쪽 마이너스 우측 이외)
	char name[20]; // 선수 이름
public:
	FORMATION() { this->goal = 0; this->power = 0; this->shotpass = 0; this->longpass = 0; this->cut = 0; this->cross = 0; this->defence = 0; this->run = 0; this->save = 0; this->fast = 0; this->poten = 0; this->LR = 0; name[0] = '\0'; }
	// 선수 스텟 디폴트
	virtual int value() { return (int)poten*((goal + power + shotpass + longpass + cut + cross + defence + run + save + fast)/10); } // 디폴트 가상함수
	char *getName() { return this->name; } // 선수 이름 불러오기
};
// FORMATION 을 상속받는 클래스들 (아래) / 가상함수 구현 ( 각스텟을 이용해 해당하는 포지션 별 계산해줌)
class LW : public FORMATION { // FORMATION 을 상속 받는다
public: // 권한
	LW() : FORMATION() {}; // 디폴트 생성자
	LW(double *stat, char *na) { // PLAYER 형식 인자들 받아옴, 객체 변수에 저장함 / stat = 스탯저장되있는 PLAYER의 stats 데이터 / na = PLAYER의 name 데이터
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	} // 선수의 스탯을 받아와 계산해줌
	virtual int value() { // 해당 클래스 포지션에 대한 토탈 스탯값 계산하는 부분
		if(LR < 0) // 왼쪽 선호
			return (int)poten*((10 * goal + 13 * power + 13 * shotpass + 10 * longpass + 5 * cut + 17 * cross + 2 * defence + 25 * run + 0 * save + 5 * fast) / 90);
		else // 오른쪽 선호
			return (int)poten*((10 * goal + 13 * power + 13 * shotpass + 10 * longpass + 5 * cut + 17 * cross + 2 * defence + 25 * run + 0 * save + 5 * fast) / 100);
	}
};
class RW : public FORMATION {
public:
	RW() : FORMATION() {};
	RW(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() { 
		if (LR < 0) 
			return (int)poten*((10 * goal + 13 * power + 13 * shotpass + 10 * longpass + 5 * cut + 17 * cross + 2 * defence + 25 * run + 0 * save + 5 * fast) / 100);
		else
			return (int)poten*((10 * goal + 13 * power + 13 * shotpass + 10 * longpass + 5 * cut + 17 * cross + 2 * defence + 25 * run + 0 * save + 5 * fast) / 90);
	}
};
class LB : public FORMATION {
public:
	LB() : FORMATION() {};
	LB(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() { 
		if (LR < 0) 
			return (int)poten*((5 * goal + 7 * power + 10 * shotpass + 7 * longpass + 16 * cut + 20 * cross + 11 * defence + 20 * run + 0 * save + 5 * fast) / 90);
		else
			return (int)poten*((5 * goal + 7 * power + 10 * shotpass + 7 * longpass + 16 * cut + 20 * cross + 11 * defence + 20 * run + 0 * save + 5 * fast) / 100);
	}
};
class RB : public FORMATION {
public:
	RB() : FORMATION() {};
	RB(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() { 
		if(LR < 0)
			return (int)poten*((5 * goal + 7 * power + 10 * shotpass + 7 * longpass + 16 * cut + 20 * cross + 11 * defence + 20 * run + 0 * save + 5 * fast) / 100);
		else
			return (int)poten*((5 * goal + 7 * power + 10 * shotpass + 7 * longpass + 16 * cut + 20 * cross + 11 * defence + 20 * run + 0 * save + 5 * fast) / 90);
	}
};
class LM : public FORMATION {
public:
	LM() : FORMATION() {};
	LM(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() {
		if (LR < 0)
			return (int)poten*((5 * goal + 15 * power + 15 * shotpass + 15 * longpass + 15 * cut + 10 * cross + 10 * defence + 10 * run + 0 * save + 5 * fast) / 90);
		else
			return (int)poten*((5 * goal + 15 * power + 15 * shotpass + 15 * longpass + 15 * cut + 10 * cross + 10 * defence + 10 * run + 0 * save + 5 * fast) / 100);
	}
};
class RM : public FORMATION {
public:
	RM() : FORMATION() {};
	RM(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() { 
		if (LR < 0)
			return (int)poten*((5 * goal + 15 * power + 15 * shotpass + 15 * longpass + 15 * cut + 10 * cross + 10 * defence + 10 * run + 0 * save + 5 * fast) / 100);
		else
			return (int)poten*((5 * goal + 15 * power + 15 * shotpass + 15 * longpass + 15 * cut + 10 * cross + 10 * defence + 10 * run + 0 * save + 5 * fast) / 90);
	}
};
class CM : public FORMATION {
public:
	CM() : FORMATION() {};
	CM(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() {
		return (int)poten*((5 * goal + 10 * power + 22 * shotpass + 23 * longpass + 10 * cut + 5 * cross + 10 * defence + 10 * run + 0 * save + 5 * fast) / 100);
	}
};
class CDM : public FORMATION {
public:
	CDM() : FORMATION() {};
	CDM(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);

	}
	virtual int value() {
		return (int)poten*((5 * goal + 10 * power + 20 * shotpass + 23 * longpass + 12 * cut + 3 * cross + 15 * defence + 7 * run + 0 * save + 5 * fast) / 100);
	}
};
class CF : public FORMATION {
public:
	CF() : FORMATION() {};
	CF(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() {
		return (int)poten*((30 * goal + 15 * power + 5 * shotpass + 3 * longpass + 2 * cut + 5 * cross + 5 * defence + 25 * run + 0 * save + 10 * fast) / 100);
	}
};
class LCB : public FORMATION {
public:
	LCB() : FORMATION() {};
	LCB(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() {
		if (LR < 0)
			return (int)poten*((5 * goal + 3 * power + 10 * shotpass + 10 * longpass + 22 * cut + 0 * cross + 35 * defence + 5 * run + 0 * save + 10 * fast) / 90);
		else
			return (int)poten*((5 * goal + 3 * power + 10 * shotpass + 10 * longpass + 22 * cut + 0 * cross + 35 * defence + 5 * run + 0 * save + 10 * fast) / 100);
	}
};
class RCB : public FORMATION {
public:
	RCB() : FORMATION() {};
	RCB(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() {
		if (LR < 0)
			return (int)poten*((5 * goal + 3 * power + 10 * shotpass + 10 * longpass + 22 * cut + 0 * cross + 35 * defence + 5 * run + 0 * save + 10 * fast) / 100);
		else
			return (int)poten*((5 * goal + 3 * power + 10 * shotpass + 10 * longpass + 22 * cut + 0 * cross + 35 * defence + 5 * run + 0 * save + 10 * fast) / 90);
	}
};
class SW : public FORMATION {
public:
	SW() : FORMATION() {};
	SW(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() {
		return (int)poten*((5 * goal + 5 * power + 10 * shotpass + 10 * longpass + 20 * cut + 0 * cross + 30 * defence + 10 * run + 0 * save + 10 * fast) / 100);
	}
};
class GK : public FORMATION {
public:
	GK() : FORMATION() {};
	GK(double *stat, char *na) {
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	}
	virtual int value() {
		return (int)poten*((0 * goal + 5 * power + 5 * shotpass + 10 * longpass + 0 * cut + 0 * cross + 0 * defence + 5 * run + 55 * save + 20 * fast) / 100);
	}
};
// 위 주석에 해당되는 포지션 하위클래스들 (LW에 주석 모두 달아놓았습니다)

// 포메이션 정보와 포메이션 리스트 (LW RW LB RB LM RM CM CDM CF LCB RCB SW GK)
/*
포메이션 INFO
---- 433 ----
  LW CF RW
  LM CM RM
LB LCB RCB RB
     GK

---- 343 ----
LW  CF  RW
    CM
LB  CDM RB
LCB SW RCB
GK

--- 4141 ---
     CF
LW LM RM RW
     CDM
LB LCB RCB RB
     GK
*/

int LOGIN(user_info *); // 로그인 작업 처리하는 서브메인
void PLAY(char *LOCAL); // 로그인 통과 후 실제 플레이 담당 서브메인
void list(PLAYER *, int); // 로그인한 회원의 로컬 선수단 리스트 출력하는 함수
void search(PLAYER *, int); // 해당선수 검색하고 선수들의 포지션별 스텟과 최적 포지션 추천하는 함수
int HAS(int, int *); // 포메이션 구성시 필요한 중복선수 처리 보조함수
int sLW(PLAYER *, int, int *); // s+포지션명 함수들 함수원형 -> 해당 포지션의 최고의 선수 반환 ( PLAYER 배열에서 선수에 해당되는 번지수 반환 )
int sRW(PLAYER *, int, int *);
int sLB(PLAYER *, int, int *);
int sRB(PLAYER *, int, int *);
int sLM(PLAYER *, int, int *);
int sRM(PLAYER *, int, int *);
int sCM(PLAYER *, int, int *);
int sCDM(PLAYER *, int, int *);
int sCF(PLAYER *, int, int *);
int sLCB(PLAYER *, int, int *);
int sRCB(PLAYER *, int, int *);
int sSW(PLAYER *, int, int *);
int sGK(PLAYER *, int, int *);
// s+포지션명 함수들 위 -------------

// 프로그램 시작 ( 로그인으로 연계 )
int main() {
	user_info *INFO; // 회원들의 정보들 받을 포인터 변수 INFO
	INFO = new user_info[100]; // 최대 100명으로 잡고 할당함
	while (1) { if (LOGIN(INFO) == 0) { break; } } // 로그인 디렉토리로 넘어감 ( 추후 로그인 디렉토리에서 플레이로 넘어감 )
	free(INFO); // 메모리 해제
	return 0;
}
// 로그인 처리 하는 서브 메인
int LOGIN(user_info *INFO) {
	int seperate, permitt = 0, pas; // 로그인 메뉴용, 로그인 퍼미션, 아이디 비번 매칭시 필요한 보조변수
	char make_id[20] = { '\0' }; // 임시 아이디 변수 ( 회원가입이나 불러올때 사용 )
	char make_pass[100] = { '\0' }; // 임시 비밀번호 변수 ( 회원가입이나 불러올때 사용 )
	char make_phone[100] = { '\0' }; // 임시 전화번호 변수 ( 회원가입이나 불러올때 사용 )
	static int count = 0, first = 1; // 회원멤버 수 총 인원, 신규회원 구분 변수
	char LOCAL[20]; // 로그인한 회원 아이디
	ofstream fout; // 파일출력용 파일변수
	ifstream fin; // 파일입력용 파일변수

	if (first == 1) { // 처음 LOGIN 호출시에만 회원정보 불러오기
		fin.open("LOGIN.txt", ios::in); // 읽는모드
		if (!fin) {  // 파일 열기 실패 확인
			cout << "\t\t파일을 열 수 없습니다\n";
			return 0;
		}
		while (true) { // 통과시 LOGIN 에 있는 회원 목록을 모두 불러와서 INFO포인터 변수에 모두 저장해 둡니다 -> LOGIN.txt에 회원정보들 저장되어 있습니다
			fin >> make_id >> make_pass >> make_phone; // ID, PASSWORD, PHONE 데이터를 가져옵니다
			INFO[count].setID(make_id); // 아이디 설정
			INFO[count].setPASS(make_pass); // 비밀번호 설정
			INFO[count].setPHONE(make_phone); // 전화번호 설정
			++count; // 총 회원수 증가
			if (fin.eof()) break; // 읽기 종료
		}
		fin.close(); // 파일 닫기
		first = 0; // 최초해제
	}
	else { // 로그인 메뉴 메인
		cout << "\t\t■■■■■■■■  최적전술 매니저   ■■■■■■■■■" << endl;
		cout << "\t\t■                  회원가입 (1)                    ■" << endl;
		cout << "\t\t■                   로그인  (2)                    ■" << endl;
		cout << "\t\t■                  회원목록 (3)                    ■" << endl;
		cout << "\t\t■                  관리자용 (4)                    ■" << endl;
		cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "\t\t메뉴 선택 -> ";
		cin >> seperate; // 메뉴 변수 입력받습니다
		system("cls"); // 화면 지우기

		switch (seperate) {
		case 1: // 회원가입
			cout << "\t\t신규 아이디를 입력해주세요 : ";
			cin >> make_id; // 아이디 받음
			cout << "\t\t신규 비밀번호를 입력해주세요 : ";
			cin >> make_pass; // 비밀번호 받음
			cout << "\t\t전화번호를 입력해주세요 : ";
			cin >> make_phone; // 전화번호 받음
			// 아래서 현재인원+1번지에 정보를 넣게되는데 이후 파일에 입력이 안되어도 통과전까지 count가 늘지않아 곂쳐서 안전처리 해주었음
			INFO[count].setID(make_id); // ID 설정
			INFO[count].setPASS(make_pass); // 비밀번호 설정
			INFO[count].setPHONE(make_phone); // 전화번호 설정

			fout.open("LOGIN.txt", ios::out | ios::app); // 회원들의 정보가 담긴 LOGIN.txt에 새로운 회원정보를 넣기 위해 파일 쓰기로 오픈
			if (!fout) {  // 파일 열기 실패 확인
				cout << "\t\t파일을 열 수 없습니다\n";
				return 0;
			}
			fout << INFO[count].getID() << "\t" << INFO[count].getPASS() << "\t" << INFO[count].getPHONE() << "\t"; // 탭붙여 파일에 회원정보 기입
			fout.close(); // 파일 닫기

			++count; // 모든 정보가 파일에 들어가고 확인이 될시 여기에 도착하게 되는데 그때 회원수를 늘려 중복이나 에러 방지도 가능하게됨
			cout << endl;
			break;
		case 2: // 로그인 및 프로그램 실행
			cout << "\n\t\t\t▣YOUR ID\t\t: ";
			cin >> make_id;
			cout << "\n\t\t\t▣PASSWORD\t\t: ";
			cin >> make_pass;
			// 로그인 입력받음
			for (pas = 0; pas < count; pas++) { // 회원정보를 돌면서 회원ID와 비밀번호가 일치하면 permitt이 1로 허가되면서 후에 통과
				if (!strcmp(INFO[pas].getID(), make_id) && !strcmp(INFO[pas].getPASS(), make_pass)) {
					permitt = 1; // 권한 허용
					break; // 루프탈출
				}
			}
			if (permitt == 1) { // 허가 받음
				strcpy(LOCAL, INFO[pas].getID()); // 회원아이디 이름을 LOCAL로 복사
				PLAY(LOCAL); // 회원 아이디 매개변수로 보내주고 플레이 서브메인으로 이동
			}
			else { // 허가 디나이
				cout << "\t\tYOU CANNOT ENTER!" << endl;
			}
			permitt = 0; // 불허
			break;
		case 3: // 회원멤버 출력
			cout << "\t\t회원 ID 리스트" << endl;
			for (int i = 0; i < count; i++) { // 회원수 만큼 루프돌며 모두 출력
				cout << "\t\t";
				INFO[i].member_print(); // 객체에서 구현해둔 ID만 출력해주는 함수 호출
				cout << " ";
			}
			cout << endl;
			cout << endl;
			break;
		case 4:
			cout << "\t\t전체 데이터 관리자용" << endl;
			for (int i = 0; i < count; i++) { // 회원 수 만큼 루프돌며 모두 출력
				cout << "\t\t";
				INFO[i].print(); // 객체에서 구현해둔 모든정보 출력해주는 함수 호출
			}
			break;
		default:
			return 0;
			break;
		}
		return 1;
	}
}
// 실제 게임이 돌아가는 서브 메인
void PLAY(char *USER) {
	system("cls");
	cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "\t\t■                     WELCOME !                    ■" << endl;
	cout << "\t\t■                  YOUR NAME -> " << USER << "\t            ■" << endl;
	cout << "\t\t■                Enjoy Your Football               ■" << endl;
	cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;

	PLAYER start[21]; // 초기제공데이터 선수 21명
	PLAYER update[100]; // 추가할 선수들과 불러온 선수들
	static int update_real = 0;
	int YN, exit = 1; // 초기제공 데이터 질문용 + 질의용

	int prefer; // 선호하는 포지션 선택
	int for_433[11]; // 433 포메이션 변수이고 각 번지에는 순서대로 LW CF RW LM CM RM LB LCB RCB RB GK 포지션 해당되는 선수의 프로그램 내 고유번호가 들어가게됨
	int for_343[11]; // 343 이하동문 LW CF RW LB LM RM RB LCB SW RCB GK
	int for_4141[11]; // 4141 이하동문 CF LW LM RM RW CDM LB LCB RCB RB GK
	int OK[11] = { 100,100,100,100,100,100,100,100,100,100,100 }; // 중복체크위한 벤 목록 ( 선수 고유번호가 들어감 ) -> 100이유는 100명까지 제한이 두어져서 100번을 가진 선수는 없음
	int *ban = OK; // OK의 포인터 변수 임시로 사용

	int pre_count; // 우선순위 저장
	char *ID = new char[24]; // 아이디에 해당하는 파일입니다 중요파일 퍼스날 파일
	ifstream fin; // 가져오기
	ofstream fout; // 저장하기


	cout << "\t\t게임이 처음이신가요? 기본제공선수를 불러오시겠습니까?\n\t\t\t(예 : 1 (누르면 초기화)) - > ";
	cin >> YN; // 초기회원 확인용
	if (YN == 1) { // 초기회원이라면 기본제공되는 start.txt에 저장되어 있는 21명의 선수들이 불러와짐 (start.txt 파일에는 21명의 선수들의 스텟들과 정보가 들어있음)
		fin.open("start.txt", ios::in); // start.txt 파일 열음
		if (!fin) {  // 파일 열기 실패 확인
			cout << "파일을 열 수 없습니다\n";
		}
		for (int i = 0; i < 21; i++) { // 초기 21명이기 때문에 에러발생치 않기 때문에 고정21명 해둠
			for (int k = 0; k < 12; k++) {
				fin >> start[i].stats[k]; // 스텟 순서대로 입력받는다
			}
			fin >> start[i].name; // 해당선수의 이름을 받는다 -> 여기서 i값은 프로그램 내 고유번호가 된다
			if (fin.eof()) break; // 읽기 종료
		}
		fin.close();

		strcpy(ID, USER); // 여기서 초기 회원이기 때문에 자기선수단을 저장할 로컬 파일이 없다 그래서 ID이름으로 txt파일을 생성해준다
		strcat(ID, ".txt");
		fout.open(ID, ios::out | ios::app); // 만든 자기만의 파일을 만들고 연다
		if (!fout) {  // 파일 열기 실패 확인
			cout << "파일을 열 수 없습니다\n";
		}
		cout << "----불러온 선수들----" << endl; // 불러온 선수들 표출
		for (int k = 0; k < 21; k++) {
			cout << "\t\t★" << start[k].name << endl;
			cout << "\t\t";
			fout << start[k].name << "\t";
			for (int j = 0; j < 12; j++) {
				cout << start[k].stats[j] << " ";
				fout << start[k].stats[j] << "\t";
			}
			cout << endl;
		}
		fout.close(); // 파일 닫기

		for (int k = 0; k < 21; k++) { // 실제로 사용할 update라는 PLAYER 포인터 변수에 모두 복사한다
			strcpy(update[update_real].name, start[k].name);
			for (int j = 0; j < 12; j++)
				update[update_real].stats[j] = start[k].stats[j];
			++update_real; // 해당 고유번호 그대로 유지하며 이거는 선수단 총 인원을 나타냄과 동시에 도움주는 변수가 된다
		}
	}
	else { // 처음이 아니라 이전에 플레이해서 자신의 파일이 존재하는 경우
		strcpy(ID, USER); // 자기 아이디에 해당하는 파일을 열기위해 파일명을 제작해준다
		strcat(ID, ".txt");
		fin.open(ID, ios::in); // 자기 파일을 연다
		cout << "\t\tYOUR DATA FROM : " << ID << endl; // 데이터를 어디서 가져왔는지 확인하기 위한 용도이다
		if (!fin) {  // 파일 열기 실패 확인
			cout << "파일을 열 수 없습니다\n";
		}
		else {
			while (true) { // 파일에서 자기 로컬 선수단들을 모두 불러온다
				fin >> update[update_real].name; // 로컬파일에는 start와 달리 이름이 먼저 들어가있어 이름부터 받는다
				for (int a = 0; a < 12; a++) {
					fin >> update[update_real].stats[a]; // 스탯들을 차례대로 받는다
				}
				++update_real; // 선수단 인원체크를 위해 증가 시켜준다
				if (fin.eof()) break; // 읽기 종료
			}
			--update_real; // 마지막에 추가하여 한명이 뻥튀기 되어 한명 줄여준다
		}
		fin.close(); // 파일 닫기
	}

	while (1) {
		cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "\t\t■               1. 선수목록                        ■" << endl;
		cout << "\t\t■               2. 선수검색 (포지션별)             ■" << endl;
		cout << "\t\t■               3. 선수추가                        ■" << endl;
		cout << "\t\t■               4. 자동 스쿼드                     ■" << endl;
		cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "\t\t-> ";
		cin >> YN; // 플레이에서 원하는 작업을 받는다
		switch (YN) { // 원하는 작업으로 이동
		case 1: // 선수 목록 출력
			system("cls");
			cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			cout << "\t\t■               1. 선수목록                        ■" << endl;
			cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			list(update, update_real); // 목록을 출력해주는 함수를 위해 매개변수로 선수단과 선수단 인원을 보내준다
			cout << "\t\t현재 선수 총 " << update_real << "명 입니다" << endl; // 총 선수단 인원 출력
			break;
		case 2: // 선수 검색후 해당 선수의 포지션별 스텟과 최적 포지션 추천
			system("cls");
			cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			cout << "\t\t■               2. 선수검색 (포지션별)             ■" << endl;
			cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			search(update, update_real); // 선수 검색 함수를 위해 매개변수로 선수단과 선수단 인원을 보내준다
			break;
		case 3: // 선수단에 선수를 추가한다
			system("cls");
			cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			cout << "\t\t■               3. 선수추가                        ■" << endl;
			cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			fout.open(ID, ios::out | ios::app); // 선수단 추가할때 이전의 선수들 그대로 유지하기 위해 커서를 맨뒤에 두고 쓰기권한으로 연다
			if (!fout) {  // 파일 열기 실패 확인
				cout << "파일을 열 수 없습니다\n";
			}
			else { // player에 저장하고 파일입출력으로 저장하고 프로그램 껏다가 다시 켰을때 확인 그리고 스텟을 입력 받는다
				cout << "\t\t선수이름 : "; // 프로그램엔 PLAYER 구조체 변수안에 name과 stats라고 12개의 스텟이 구현되어 있다 먼저 이름을 입력받는다
				cin >> update[update_real].name; // 이는 이름 골결정력 짧은패스 긴패스 가로채기 크로스 대인수비 속력 선방능력 반응속도 개인능력 좌우선호의 총 12개의 스텟이 구현되어있다
				cout << "\t\t골결정력 : ";
				cin >> update[update_real].stats[0];
				cout << "\t\t슛파워   : ";
				cin >> update[update_real].stats[1];
				cout << "\t\t짧은패스 : ";
				cin >> update[update_real].stats[2];
				cout << "\t\t긴패스   : ";
				cin >> update[update_real].stats[3];
				cout << "\t\t가로채기 : ";
				cin >> update[update_real].stats[4];
				cout << "\t\t크로스   : ";
				cin >> update[update_real].stats[5];
				cout << "\t\t대인수비 : ";
				cin >> update[update_real].stats[6];
				cout << "\t\t속력     : ";
				cin >> update[update_real].stats[7];
				cout << "\t\t선방능력 : ";
				cin >> update[update_real].stats[8];
				cout << "\t\t반응속도 : ";
				cin >> update[update_real].stats[9];
				cout << "\t\t개인능력 (0.5 - 1.5)\t\t : ";
				cin >> update[update_real].stats[10];
				cout << "\t\t좌우선호 (좌:-1 우:1 상관X:0\t : ";
				cin >> update[update_real].stats[11];
				// 자기 고유파일에도 선수를 추가해준다
				fout << update[update_real].name << '\t'; // 이름부터
				for (int o = 0; o < 12; o++) // 12가지의 스텟 입력
					fout << update[update_real].stats[o] << '\t';
				++update_real; // 선수단 인원 추가
			}
			fout.close();
			break;
		case 4:

			system("cls");
			cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			cout << "\t\t■               4. 자동 스쿼드                     ■" << endl;
			cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			cout << "\t\t■           선호하는 포지션을 입력해주세요         ■" << endl;
			cout << "\t\t■           (1)       4 - 3 - 3                    ■" << endl;
			cout << "\t\t■           (2)       3 - 4 - 3                    ■" << endl;
			cout << "\t\t■           (3)     4 - 1 - 4 - 1                  ■" << endl;
			cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			cout << "\t\t-> ";
			cin >> prefer; // 선호하는 포지션을 입력 받는다
			switch (prefer) { // 해당되는 포지션으로 이동한다
			case 1: // 433 포메이션
				// 중요한 순서대로 호출하고 반환해줘야하는 함수 만들고 받아서 처리
				// LW RW CM LM RM CF LB RB LCB RCB GK
				/*
				*아래 최적 포메이션 출력 알고리즘 설명*
				여기가 조금 복잡한 부분이어서 한번에 설명하겠습니다
				포메이션에서 우선순위를 경험과 조사를 통해 알아왔다 이에 우선순위는 for_433 변수안에 순서대로
				우선순위에 맞는 포지션을 넣어준다 0번지에는 제일 중요한 포지션이 10번지에는 덜 중요한 포지션이 자리한다
				그리고 순서대로 선수 고유번호가 그 자리에 들어가게 되는데 이는 사용한 선수를 나타내는 지표이기도하다
				그래서 OK라는 벤목록에 선수를 추가해준다
				이후 출력창에 포메이션 모양에 맞게 선수고유번호를 기입하면 그 선수 이름이 나오게 구현을 해두었다
				그렇다면 for_433에는 우선순위에 정리됨과 동시에 선수고유번호가 들어가있다
				그래서 출력부분에 우선순위대로 update[]괄호 안에 for_433[우선순위]를 기입해준다 그러면 출력했을때
				해당되는 선수가 포지션에 자리하며 출려되게 된다 아래 부분 소스들 전부가 그렇가
				*포메이션 별 우선순위 부여*
				433  -> LW RW CM LM RM CF LB RB LCB RCB GK
				343  -> LB RB SW LW RW CM CDM LCB RCB CF GK
				4141 -> CF LW RW LM RM CDM LCB RCB LB RB GK
				*/
				system("cls");
				OK[0] = for_433[0] = sLW(update, update_real, OK);
				OK[1] = for_433[1] = sRW(update, update_real, OK);
				OK[2] = for_433[2] = sCM(update, update_real, OK);
				OK[3] = for_433[3] = sLM(update, update_real, OK);
				OK[4] = for_433[4] = sRM(update, update_real, OK);
				OK[5] = for_433[5] = sCF(update, update_real, OK);
				OK[6] = for_433[6] = sLB(update, update_real, OK);
				OK[7] = for_433[7] = sRB(update, update_real, OK);
				OK[8] = for_433[8] = sLCB(update, update_real, OK);
				OK[9] = for_433[9] = sRCB(update, update_real, OK);
				OK[10] = for_433[10] = sGK(update, update_real, OK);
				cout << endl;
				cout << "\t\t\t         ● 4 - 3 - 3 ●\n" << endl;
				cout << "\t\t\t     " << update[for_433[0]].name << "\t" << update[for_433[5]].name << "\t" << update[for_433[1]].name << "\t" << endl;
				cout << "\t\t\t     " << update[for_433[3]].name << "\t" << update[for_433[2]].name << "\t" << update[for_433[4]].name << "\t" << endl;
				cout << "\t\t\t" << update[for_433[6]].name << "\t" << update[for_433[8]].name << "\t" << update[for_433[9]].name << "\t" << update[for_433[7]].name << "\t" << endl;
				cout << "     \t\t\t\t    " << update[for_433[10]].name << "\t" << endl;
				cout << endl;
				break;
			case 2: // 343 포메이션
				// 중요한 순서대로 호출하고 반환해줘야하는 함수 만들고 받아서 처리 (설명은 위에 참조)
				system("cls");
				OK[0] = for_343[0] = sLB(update, update_real, OK);
				OK[1] = for_343[1] = sRB(update, update_real, OK);
				OK[2] = for_343[2] = sSW(update, update_real, OK);
				OK[3] = for_343[3] = sLW(update, update_real, OK);
				OK[4] = for_343[4] = sRW(update, update_real, OK);
				OK[5] = for_343[5] = sCM(update, update_real, OK);
				OK[6] = for_343[6] = sCDM(update, update_real, OK);
				OK[7] = for_343[7] = sLCB(update, update_real, OK);
				OK[8] = for_343[8] = sRCB(update, update_real, OK);
				OK[9] = for_343[9] = sCF(update, update_real, OK);
				OK[10] = for_343[10] = sGK(update, update_real, OK);
				cout << endl;
				cout << "\t\t\t           ● 3 - 4 - 3 ●\n" << endl;
				cout << "\t\t\t     " << update[for_343[3]].name << "\t" << update[for_343[9]].name << "\t" << update[for_343[4]].name << "\t" << endl;
				cout << "\t\t\t     " << "\t\t" << update[for_343[5]].name << endl;
				cout << "\t\t\t     " << update[for_343[0]].name << "\t" << update[for_343[6]].name << "\t" << update[for_343[1]].name << "\t" << endl;
				cout << "\t\t\t     " << update[for_343[7]].name << "\t" << update[for_343[2]].name << "\t" << update[for_343[8]].name << "\t" << endl;
				cout << "\t\t\t     \t\t" << update[for_343[10]].name << "\t" << endl;
				cout << endl;
				break;
			case 3: // 4141 포메이션
				// 중요한 순서대로 호출하고 반환해줘야하는 함수 만들고 받아서 처리 (설명은 위에 참조)
				system("cls");
				OK[0] = for_4141[0] = sCF(update, update_real, OK);
				OK[1] = for_4141[1] = sLW(update, update_real, OK);
				OK[2] = for_4141[2] = sRW(update, update_real, OK);
				OK[3] = for_4141[3] = sLM(update, update_real, OK);
				OK[4] = for_4141[4] = sRM(update, update_real, OK);
				OK[5] = for_4141[5] = sCDM(update, update_real, OK);
				OK[6] = for_4141[6] = sLCB(update, update_real, OK);
				OK[7] = for_4141[7] = sRCB(update, update_real, OK);
				OK[8] = for_4141[8] = sLB(update, update_real, OK);
				OK[9] = for_4141[9] = sRB(update, update_real, OK);
				OK[10] = for_4141[10] = sGK(update, update_real, OK);
				cout << endl;
				cout << "\t\t\t      ● 4 - 1 - 4 - 1 ●\n" << endl;
				cout << "\t\t\t     \t   " << update[for_4141[0]].name << "\t" << endl;
				cout << "\t\t\t" << update[for_4141[1]].name << "\t" << update[for_4141[3]].name << "\t" << update[for_4141[4]].name << "\t" << update[for_4141[2]].name << "\t" << endl;
				cout << "\t\t\t     \t   " << update[for_4141[5]].name << "\t" << endl;
				cout << "\t\t\t" << update[for_4141[8]].name << "\t" << update[for_4141[6]].name << "\t" << update[for_4141[7]].name << "\t" << update[for_4141[9]].name << "\t" << endl;
				cout << "\t\t\t     \t   " << update[for_4141[10]].name << "\t" << endl;
				cout << endl;
				break;
			default: // 없는 포메이션 입력시
				cout << "없는 포메이션 입니다" << endl;
				break;
			}
			break;

		default: // 없는 번호 눌렀을때 탈출권한 얻음
			exit = 0;
			break;
		}
		if (exit == 0) // 메뉴에 없는 번호를 입력하면 게임플레이 서브메인에서 나온다
			break;
		for (int i = 0; i < 11; i++) { OK[i] = 100; } // 벤 목록 청소
	}
	cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "\t\t■                   게임 플레이 종료               ■" << endl;
	cout << "\t\t■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	// 모든 처리가 되었을때 종료
}
// 로그인한 계정의 로컬 선수단 목록 출력
void list(PLAYER *update, int update_real) { // 선수단과 선수단 인원 받아옴
	for (int k = 0; k < update_real; k++) { // 인원수만큼 반복
		cout << "\t\t▲" << update[k].name << endl; // 선수이름
		cout << "\t\t";
		for (int j = 0; j < 12; j++) {
			cout << update[k].stats[j] << " "; // 선수들 스텟들
		}
		cout << endl;
	}
}
// 로컬 선수단중에서 선수 검색하고 그 선수의 포지션별 스텟과 최적 포지션 추천하는 함수
void search(PLAYER *up, int count) { // 선수단과 선수단 인원 받아옴
	char temp[20], BEST[5] = { '\0' }; // 검색할 선수 이름 임시변수, 최고 스텟에 해당하는 포지션 명
	FORMATION *find; // 오버라이딩 하기위한 부모 클래스 포인터 변수
	find = new FORMATION; // 시작전 부모클래스로 할당
	int YN = 1, stat = 0; // 선수 찾기 성공확인용, 각 포지션 비교 후 최고 스텟 체크용
	cout << "\t\t검색할 선수 이름을 입력해주세요 -> ";
	cin >> temp; // 검색할 선수이름 입력받음
	for (int i = 0; i < count; i++) { // 선수단 인원수 만큼 루프
		if (!strcmp(up[i].name, temp)) { // 선수단에서 선수 이름 매칭
			YN = 1; // 선수 찾음
			// LW RW LB RB LM RM CM CDM CF LCB RCB SW GK 순서대로
			cout << "\t\t▲" << up[i].name << "'s STATS by FORMATION" << endl; // 검색한 선수 정보 시작
			find = new LW(up[i].stats, up[i].name); // 여기에 호출된 자식클래스로 FORMATION 포인터변수 find 에 오버라이딩하여 새롭게 바인딩 아래 모두 같다
			cout << "\t\tLW   - " << find->value() << endl; // 해당 포지션 클래스에 구현되어 있는 가상함수인 해당 포지션 스텟계산 함수를 통해 스텟값 받아 출력
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "LW"); } // 만약에 이 포지션 스텟이 최고의 스텟이면 최적 포지션과 스텟을 저장한다
			find = new RW(up[i].stats, up[i].name);
			cout << "\t\tRW   - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "RW"); }
			find = new LB(up[i].stats, up[i].name);
			cout << "\t\tLB   - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "LB"); }
			find = new RB(up[i].stats, up[i].name);
			cout << "\t\tRB   - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "RB"); }
			find = new LM(up[i].stats, up[i].name);
			cout << "\t\tLM   - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "LM"); }
			find = new RM(up[i].stats, up[i].name);
			cout << "\t\tRM   - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "RM"); }
			find = new CM(up[i].stats, up[i].name);
			cout << "\t\tCM   - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "CM"); }
			find = new CDM(up[i].stats, up[i].name);
			cout << "\t\tCDM  - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "CDM"); }
			find = new CF(up[i].stats, up[i].name);
			cout << "\t\tCF   - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "CF"); }
			find = new LCB(up[i].stats, up[i].name);
			cout << "\t\tLCB  - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "LCB"); }
			find = new RCB(up[i].stats, up[i].name);
			cout << "\t\tRCB  - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "RCB"); }
			find = new SW(up[i].stats, up[i].name);
			cout << "\t\tSW   - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "SW"); }
			find = new GK(up[i].stats, up[i].name);
			cout << "\t\tGK   - " << find->value() << endl;
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "GK"); }
			cout << "\t\t⊙ THIS PLAYER's BEST POSITION -> " << BEST << " : " << stat << "\n" << endl; // 저장해두었던 최고의 포지션과 스텟을 알려준다
			stat = 0; // 최고 스텟 초기화 ( 다른 선수도 사용해야 하기 때문에 )
			delete find; // find 할당 해제
			break;
		}
		else YN = 0; // 검색한 선수가 선수단에 없을 때
	}
	if (YN == 0) { cout << "\t\t찾으시는 선수가 존재하지 않습니다" << endl; } // 선수단에 검색한 선수 없다
}

// s+포지션명 함수들 ->  해당 포지션의 최고의 선수 반환 ( PLAYER 배열에서 선수에 해당괴는 번지수 반환 ) -> 내부 소스 주석은 sLW에 모두 기입
int sLW(PLAYER *up, int count, int *BAN) { // 선수단과 선수단 인원 그리고 벤 목록을 받는다
	FORMATION *find; // 오버라이딩 하기 위해 부모 클래스의 포인터 변수를 만들어준다
	int temp, big = 0; // 최고의 선수 고유번호 임시저장용, 최고 스텟 임시 저장용
	for (int i = 0; i < count; i++) { // 선수단 인원수 따라 루프를 돈다
		if (HAS(i, BAN) == 0) { // 벤 목록에 있나 체크
			find = new LW(up[i].stats, up[i].name); // s+포지션에 써있는 해당 포지션의 자식클래스로 할당받고 오버라이딩(바인딩) 한다
			if (big < find->value()) { big = find->value(); temp = i; } // 가상함수로 스텟을 뽑아내고 최고의 스텟을 가진 선수라면 고유번호를 저장하고 스텟을 저장한다
		}
	}
	delete find; // 할당 해제
	return temp; // 이 포지션 최고의 선수 고유번호 리턴
}
int sRW(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new RW(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sLB(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new LB(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sRB(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new RB(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sLM(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new LM(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sRM(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new RM(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sCM(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new CM(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sCDM(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new CDM(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sCF(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new CF(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sLCB(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new LCB(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sRCB(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new RCB(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sSW(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new SW(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
int sGK(PLAYER *up, int count, int *BAN) {
	FORMATION *find;
	int temp, big = 0;
	for (int i = 0; i < count; i++) {
		if (HAS(i, BAN) == 0) {
			find = new GK(up[i].stats, up[i].name);
			if (big < find->value()) { big = find->value(); temp = i; }
		}
	}
	delete find;
	return temp;
}
// 포지션을 구성할때 이미 사용한 선수를 중복되지 않게 하기 위해 벤목록에서 걸러내어 주는 함수
int HAS(int num, int *ban) { // 선수의 고유번호와 벤 목록을 받아온다
	for (int i = 0; i < 11; i++) { // 벤목록은 어차피 최대 11명이기 때문에 11번 루프돈다
		if (ban[i] == num) // 벤목록에 선수가 있다면 1 반환
			return 1;
	}
	return 0; // 벤 목록에 없다면 0
}