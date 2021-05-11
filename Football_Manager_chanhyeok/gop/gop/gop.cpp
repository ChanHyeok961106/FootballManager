#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;
// ��Ʈ�� ó���� �⺻ �����, ���� ����½� ����ϴ� ���̺귯���� ���

// PLAYER ��� ���� ������ �����͸� �����ϰ� ���α׷����� ������ ���� ���� (������ ������ ������ ����)
typedef struct player {
	double stats[12]; // ���ȵ� �����ϴ� �� 12���� ������ �����
	char name[20]; // �����̸�
}PLAYER;
// ������� ID�� PASSWORD�� ���� ��ü
class user { // �����
public:
	char ID[10]; // ID
	char PASS[10]; // PASSWORD
public:
	user() { strcpy(this->ID, "test_id"); strcpy(this->PASS, "test_pass"); } // ����Ʈ
	user(char *id, char *pass) { strcpy(this->ID, id); strcpy(this->PASS, pass); } // ���̵�� ��й�ȣ �޾� �����ϴ� ������
	void setID(char *id) { strcpy(this->ID, id); } // ���̵� ���� �� �缳����
	void setPASS(char *pass) { strcpy(this->PASS, pass); } // ��й�ȣ ���� �� �缳����
	char *getID() { return this->ID; } // ID getter
	char *getPASS() { return this->PASS; } // PASSWORD getter
};
// user�� ��ӹ޴� user�� ���� ��ü
class user_info : public user { // user�� ��ӹ޴� user�� ���� ��ü
public:
	user DATA; // user ID PASSWORD ������ ��ü
	char PHONE[20]; // ��ȭ��ȣ
public:
	user_info() :DATA() { strcpy(this->PHONE, "test_phone"); } // ����Ʈ
	user_info(char *id, char *pass, char *phone) :user(id, pass) { strcpy(this->PHONE, phone); } // user ȣ�� �� ���̵� ��� ���� ������
	void setPHONE(char *phone) { strcpy(this->PHONE, phone); } // ��ȭ��ȣ ���� �� �缳����
	char *getPHONE() { return this->PHONE; } // ��ȭ��ȣ getter
	void print() { cout << getID() << "\t" << getPASS() << "\t" << getPHONE() << endl; } // ������� ��� ���� ��¿� �Լ�
	void member_print() { cout << getID(); } // ����� ID ���� ��¿�
};

// �Ʒ� �����ǵ��� �θ� Ŭ���� -> �ɷ�ġ ����/ �����Լ� ���̽� ����
class FORMATION {
public:
	double goal; // �������
	double power; // ���Ŀ�
	double shotpass; // ª���н�
	double longpass; // ���н�
	double cut; // ����ä��
	double cross; // ũ�ν�
	double defence; // ���μ���
	double run; // �ӷ�
	double save; // ����ɷ�
	double fast; // �����ӵ�
	double poten; // ���α�ɷ� (��ü������)
	double LR; // ���� ���� ��ȣ�� (���� ���̳ʽ� ���� �̿�)
	char name[20]; // ���� �̸�
public:
	FORMATION() { this->goal = 0; this->power = 0; this->shotpass = 0; this->longpass = 0; this->cut = 0; this->cross = 0; this->defence = 0; this->run = 0; this->save = 0; this->fast = 0; this->poten = 0; this->LR = 0; name[0] = '\0'; }
	// ���� ���� ����Ʈ
	virtual int value() { return (int)poten*((goal + power + shotpass + longpass + cut + cross + defence + run + save + fast)/10); } // ����Ʈ �����Լ�
	char *getName() { return this->name; } // ���� �̸� �ҷ�����
};
// FORMATION �� ��ӹ޴� Ŭ������ (�Ʒ�) / �����Լ� ���� ( �������� �̿��� �ش��ϴ� ������ �� �������)
class LW : public FORMATION { // FORMATION �� ��� �޴´�
public: // ����
	LW() : FORMATION() {}; // ����Ʈ ������
	LW(double *stat, char *na) { // PLAYER ���� ���ڵ� �޾ƿ�, ��ü ������ ������ / stat = ����������ִ� PLAYER�� stats ������ / na = PLAYER�� name ������
		this->goal = stat[0]; this->power = stat[1]; this->shotpass = stat[2]; this->longpass = stat[3]; this->cut = stat[4];  this->cross = stat[5]; this->defence = stat[6]; this->run = stat[7]; this->save = stat[8]; this->fast = stat[9]; this->poten = stat[10]; this->LR = stat[11];
		strcpy(this->name, na);
	} // ������ ������ �޾ƿ� �������
	virtual int value() { // �ش� Ŭ���� �����ǿ� ���� ��Ż ���Ȱ� ����ϴ� �κ�
		if(LR < 0) // ���� ��ȣ
			return (int)poten*((10 * goal + 13 * power + 13 * shotpass + 10 * longpass + 5 * cut + 17 * cross + 2 * defence + 25 * run + 0 * save + 5 * fast) / 90);
		else // ������ ��ȣ
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
// �� �ּ��� �ش�Ǵ� ������ ����Ŭ������ (LW�� �ּ� ��� �޾Ƴ��ҽ��ϴ�)

// �����̼� ������ �����̼� ����Ʈ (LW RW LB RB LM RM CM CDM CF LCB RCB SW GK)
/*
�����̼� INFO
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

int LOGIN(user_info *); // �α��� �۾� ó���ϴ� �������
void PLAY(char *LOCAL); // �α��� ��� �� ���� �÷��� ��� �������
void list(PLAYER *, int); // �α����� ȸ���� ���� ������ ����Ʈ ����ϴ� �Լ�
void search(PLAYER *, int); // �ش缱�� �˻��ϰ� �������� �����Ǻ� ���ݰ� ���� ������ ��õ�ϴ� �Լ�
int HAS(int, int *); // �����̼� ������ �ʿ��� �ߺ����� ó�� �����Լ�
int sLW(PLAYER *, int, int *); // s+�����Ǹ� �Լ��� �Լ����� -> �ش� �������� �ְ��� ���� ��ȯ ( PLAYER �迭���� ������ �ش�Ǵ� ������ ��ȯ )
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
// s+�����Ǹ� �Լ��� �� -------------

// ���α׷� ���� ( �α������� ���� )
int main() {
	user_info *INFO; // ȸ������ ������ ���� ������ ���� INFO
	INFO = new user_info[100]; // �ִ� 100������ ��� �Ҵ���
	while (1) { if (LOGIN(INFO) == 0) { break; } } // �α��� ���丮�� �Ѿ ( ���� �α��� ���丮���� �÷��̷� �Ѿ )
	free(INFO); // �޸� ����
	return 0;
}
// �α��� ó�� �ϴ� ���� ����
int LOGIN(user_info *INFO) {
	int seperate, permitt = 0, pas; // �α��� �޴���, �α��� �۹̼�, ���̵� ��� ��Ī�� �ʿ��� ��������
	char make_id[20] = { '\0' }; // �ӽ� ���̵� ���� ( ȸ�������̳� �ҷ��ö� ��� )
	char make_pass[100] = { '\0' }; // �ӽ� ��й�ȣ ���� ( ȸ�������̳� �ҷ��ö� ��� )
	char make_phone[100] = { '\0' }; // �ӽ� ��ȭ��ȣ ���� ( ȸ�������̳� �ҷ��ö� ��� )
	static int count = 0, first = 1; // ȸ����� �� �� �ο�, �ű�ȸ�� ���� ����
	char LOCAL[20]; // �α����� ȸ�� ���̵�
	ofstream fout; // ������¿� ���Ϻ���
	ifstream fin; // �����Է¿� ���Ϻ���

	if (first == 1) { // ó�� LOGIN ȣ��ÿ��� ȸ������ �ҷ�����
		fin.open("LOGIN.txt", ios::in); // �д¸��
		if (!fin) {  // ���� ���� ���� Ȯ��
			cout << "\t\t������ �� �� �����ϴ�\n";
			return 0;
		}
		while (true) { // ����� LOGIN �� �ִ� ȸ�� ����� ��� �ҷ��ͼ� INFO������ ������ ��� ������ �Ӵϴ� -> LOGIN.txt�� ȸ�������� ����Ǿ� �ֽ��ϴ�
			fin >> make_id >> make_pass >> make_phone; // ID, PASSWORD, PHONE �����͸� �����ɴϴ�
			INFO[count].setID(make_id); // ���̵� ����
			INFO[count].setPASS(make_pass); // ��й�ȣ ����
			INFO[count].setPHONE(make_phone); // ��ȭ��ȣ ����
			++count; // �� ȸ���� ����
			if (fin.eof()) break; // �б� ����
		}
		fin.close(); // ���� �ݱ�
		first = 0; // ��������
	}
	else { // �α��� �޴� ����
		cout << "\t\t���������  �������� �Ŵ���   ����������" << endl;
		cout << "\t\t��                  ȸ������ (1)                    ��" << endl;
		cout << "\t\t��                   �α���  (2)                    ��" << endl;
		cout << "\t\t��                  ȸ����� (3)                    ��" << endl;
		cout << "\t\t��                  �����ڿ� (4)                    ��" << endl;
		cout << "\t\t����������������������������" << endl;
		cout << "\t\t�޴� ���� -> ";
		cin >> seperate; // �޴� ���� �Է¹޽��ϴ�
		system("cls"); // ȭ�� �����

		switch (seperate) {
		case 1: // ȸ������
			cout << "\t\t�ű� ���̵� �Է����ּ��� : ";
			cin >> make_id; // ���̵� ����
			cout << "\t\t�ű� ��й�ȣ�� �Է����ּ��� : ";
			cin >> make_pass; // ��й�ȣ ����
			cout << "\t\t��ȭ��ȣ�� �Է����ּ��� : ";
			cin >> make_phone; // ��ȭ��ȣ ����
			// �Ʒ��� �����ο�+1������ ������ �ְԵǴµ� ���� ���Ͽ� �Է��� �ȵǾ ��������� count�� �����ʾ� ���ļ� ����ó�� ���־���
			INFO[count].setID(make_id); // ID ����
			INFO[count].setPASS(make_pass); // ��й�ȣ ����
			INFO[count].setPHONE(make_phone); // ��ȭ��ȣ ����

			fout.open("LOGIN.txt", ios::out | ios::app); // ȸ������ ������ ��� LOGIN.txt�� ���ο� ȸ�������� �ֱ� ���� ���� ����� ����
			if (!fout) {  // ���� ���� ���� Ȯ��
				cout << "\t\t������ �� �� �����ϴ�\n";
				return 0;
			}
			fout << INFO[count].getID() << "\t" << INFO[count].getPASS() << "\t" << INFO[count].getPHONE() << "\t"; // �Ǻٿ� ���Ͽ� ȸ������ ����
			fout.close(); // ���� �ݱ�

			++count; // ��� ������ ���Ͽ� ���� Ȯ���� �ɽ� ���⿡ �����ϰ� �Ǵµ� �׶� ȸ������ �÷� �ߺ��̳� ���� ������ �����ϰԵ�
			cout << endl;
			break;
		case 2: // �α��� �� ���α׷� ����
			cout << "\n\t\t\t��YOUR ID\t\t: ";
			cin >> make_id;
			cout << "\n\t\t\t��PASSWORD\t\t: ";
			cin >> make_pass;
			// �α��� �Է¹���
			for (pas = 0; pas < count; pas++) { // ȸ�������� ���鼭 ȸ��ID�� ��й�ȣ�� ��ġ�ϸ� permitt�� 1�� �㰡�Ǹ鼭 �Ŀ� ���
				if (!strcmp(INFO[pas].getID(), make_id) && !strcmp(INFO[pas].getPASS(), make_pass)) {
					permitt = 1; // ���� ���
					break; // ����Ż��
				}
			}
			if (permitt == 1) { // �㰡 ����
				strcpy(LOCAL, INFO[pas].getID()); // ȸ�����̵� �̸��� LOCAL�� ����
				PLAY(LOCAL); // ȸ�� ���̵� �Ű������� �����ְ� �÷��� ����������� �̵�
			}
			else { // �㰡 ����
				cout << "\t\tYOU CANNOT ENTER!" << endl;
			}
			permitt = 0; // ����
			break;
		case 3: // ȸ����� ���
			cout << "\t\tȸ�� ID ����Ʈ" << endl;
			for (int i = 0; i < count; i++) { // ȸ���� ��ŭ �������� ��� ���
				cout << "\t\t";
				INFO[i].member_print(); // ��ü���� �����ص� ID�� ������ִ� �Լ� ȣ��
				cout << " ";
			}
			cout << endl;
			cout << endl;
			break;
		case 4:
			cout << "\t\t��ü ������ �����ڿ�" << endl;
			for (int i = 0; i < count; i++) { // ȸ�� �� ��ŭ �������� ��� ���
				cout << "\t\t";
				INFO[i].print(); // ��ü���� �����ص� ������� ������ִ� �Լ� ȣ��
			}
			break;
		default:
			return 0;
			break;
		}
		return 1;
	}
}
// ���� ������ ���ư��� ���� ����
void PLAY(char *USER) {
	system("cls");
	cout << "\t\t����������������������������" << endl;
	cout << "\t\t��                     WELCOME !                    ��" << endl;
	cout << "\t\t��                  YOUR NAME -> " << USER << "\t            ��" << endl;
	cout << "\t\t��                Enjoy Your Football               ��" << endl;
	cout << "\t\t����������������������������" << endl;

	PLAYER start[21]; // �ʱ����������� ���� 21��
	PLAYER update[100]; // �߰��� ������� �ҷ��� ������
	static int update_real = 0;
	int YN, exit = 1; // �ʱ����� ������ ������ + ���ǿ�

	int prefer; // ��ȣ�ϴ� ������ ����
	int for_433[11]; // 433 �����̼� �����̰� �� �������� ������� LW CF RW LM CM RM LB LCB RCB RB GK ������ �ش�Ǵ� ������ ���α׷� �� ������ȣ�� ���Ե�
	int for_343[11]; // 343 ���ϵ��� LW CF RW LB LM RM RB LCB SW RCB GK
	int for_4141[11]; // 4141 ���ϵ��� CF LW LM RM RW CDM LB LCB RCB RB GK
	int OK[11] = { 100,100,100,100,100,100,100,100,100,100,100 }; // �ߺ�üũ���� �� ��� ( ���� ������ȣ�� �� ) -> 100������ 100����� ������ �ξ����� 100���� ���� ������ ����
	int *ban = OK; // OK�� ������ ���� �ӽ÷� ���

	int pre_count; // �켱���� ����
	char *ID = new char[24]; // ���̵� �ش��ϴ� �����Դϴ� �߿����� �۽��� ����
	ifstream fin; // ��������
	ofstream fout; // �����ϱ�


	cout << "\t\t������ ó���̽Ű���? �⺻���������� �ҷ����ðڽ��ϱ�?\n\t\t\t(�� : 1 (������ �ʱ�ȭ)) - > ";
	cin >> YN; // �ʱ�ȸ�� Ȯ�ο�
	if (YN == 1) { // �ʱ�ȸ���̶�� �⺻�����Ǵ� start.txt�� ����Ǿ� �ִ� 21���� �������� �ҷ����� (start.txt ���Ͽ��� 21���� �������� ���ݵ�� ������ �������)
		fin.open("start.txt", ios::in); // start.txt ���� ����
		if (!fin) {  // ���� ���� ���� Ȯ��
			cout << "������ �� �� �����ϴ�\n";
		}
		for (int i = 0; i < 21; i++) { // �ʱ� 21���̱� ������ �����߻�ġ �ʱ� ������ ����21�� �ص�
			for (int k = 0; k < 12; k++) {
				fin >> start[i].stats[k]; // ���� ������� �Է¹޴´�
			}
			fin >> start[i].name; // �ش缱���� �̸��� �޴´� -> ���⼭ i���� ���α׷� �� ������ȣ�� �ȴ�
			if (fin.eof()) break; // �б� ����
		}
		fin.close();

		strcpy(ID, USER); // ���⼭ �ʱ� ȸ���̱� ������ �ڱ⼱������ ������ ���� ������ ���� �׷��� ID�̸����� txt������ �������ش�
		strcat(ID, ".txt");
		fout.open(ID, ios::out | ios::app); // ���� �ڱ⸸�� ������ ����� ����
		if (!fout) {  // ���� ���� ���� Ȯ��
			cout << "������ �� �� �����ϴ�\n";
		}
		cout << "----�ҷ��� ������----" << endl; // �ҷ��� ������ ǥ��
		for (int k = 0; k < 21; k++) {
			cout << "\t\t��" << start[k].name << endl;
			cout << "\t\t";
			fout << start[k].name << "\t";
			for (int j = 0; j < 12; j++) {
				cout << start[k].stats[j] << " ";
				fout << start[k].stats[j] << "\t";
			}
			cout << endl;
		}
		fout.close(); // ���� �ݱ�

		for (int k = 0; k < 21; k++) { // ������ ����� update��� PLAYER ������ ������ ��� �����Ѵ�
			strcpy(update[update_real].name, start[k].name);
			for (int j = 0; j < 12; j++)
				update[update_real].stats[j] = start[k].stats[j];
			++update_real; // �ش� ������ȣ �״�� �����ϸ� �̰Ŵ� ������ �� �ο��� ��Ÿ���� ���ÿ� �����ִ� ������ �ȴ�
		}
	}
	else { // ó���� �ƴ϶� ������ �÷����ؼ� �ڽ��� ������ �����ϴ� ���
		strcpy(ID, USER); // �ڱ� ���̵� �ش��ϴ� ������ �������� ���ϸ��� �������ش�
		strcat(ID, ".txt");
		fin.open(ID, ios::in); // �ڱ� ������ ����
		cout << "\t\tYOUR DATA FROM : " << ID << endl; // �����͸� ��� �����Դ��� Ȯ���ϱ� ���� �뵵�̴�
		if (!fin) {  // ���� ���� ���� Ȯ��
			cout << "������ �� �� �����ϴ�\n";
		}
		else {
			while (true) { // ���Ͽ��� �ڱ� ���� �����ܵ��� ��� �ҷ��´�
				fin >> update[update_real].name; // �������Ͽ��� start�� �޸� �̸��� ���� ���־� �̸����� �޴´�
				for (int a = 0; a < 12; a++) {
					fin >> update[update_real].stats[a]; // ���ȵ��� ���ʴ�� �޴´�
				}
				++update_real; // ������ �ο�üũ�� ���� ���� �����ش�
				if (fin.eof()) break; // �б� ����
			}
			--update_real; // �������� �߰��Ͽ� �Ѹ��� ��Ƣ�� �Ǿ� �Ѹ� �ٿ��ش�
		}
		fin.close(); // ���� �ݱ�
	}

	while (1) {
		cout << "\t\t����������������������������" << endl;
		cout << "\t\t��               1. �������                        ��" << endl;
		cout << "\t\t��               2. �����˻� (�����Ǻ�)             ��" << endl;
		cout << "\t\t��               3. �����߰�                        ��" << endl;
		cout << "\t\t��               4. �ڵ� ������                     ��" << endl;
		cout << "\t\t����������������������������" << endl;
		cout << "\t\t-> ";
		cin >> YN; // �÷��̿��� ���ϴ� �۾��� �޴´�
		switch (YN) { // ���ϴ� �۾����� �̵�
		case 1: // ���� ��� ���
			system("cls");
			cout << "\t\t����������������������������" << endl;
			cout << "\t\t��               1. �������                        ��" << endl;
			cout << "\t\t����������������������������" << endl;
			list(update, update_real); // ����� ������ִ� �Լ��� ���� �Ű������� �����ܰ� ������ �ο��� �����ش�
			cout << "\t\t���� ���� �� " << update_real << "�� �Դϴ�" << endl; // �� ������ �ο� ���
			break;
		case 2: // ���� �˻��� �ش� ������ �����Ǻ� ���ݰ� ���� ������ ��õ
			system("cls");
			cout << "\t\t����������������������������" << endl;
			cout << "\t\t��               2. �����˻� (�����Ǻ�)             ��" << endl;
			cout << "\t\t����������������������������" << endl;
			search(update, update_real); // ���� �˻� �Լ��� ���� �Ű������� �����ܰ� ������ �ο��� �����ش�
			break;
		case 3: // �����ܿ� ������ �߰��Ѵ�
			system("cls");
			cout << "\t\t����������������������������" << endl;
			cout << "\t\t��               3. �����߰�                        ��" << endl;
			cout << "\t\t����������������������������" << endl;
			fout.open(ID, ios::out | ios::app); // ������ �߰��Ҷ� ������ ������ �״�� �����ϱ� ���� Ŀ���� �ǵڿ� �ΰ� ����������� ����
			if (!fout) {  // ���� ���� ���� Ȯ��
				cout << "������ �� �� �����ϴ�\n";
			}
			else { // player�� �����ϰ� ������������� �����ϰ� ���α׷� ���ٰ� �ٽ� ������ Ȯ�� �׸��� ������ �Է� �޴´�
				cout << "\t\t�����̸� : "; // ���α׷��� PLAYER ����ü �����ȿ� name�� stats��� 12���� ������ �����Ǿ� �ִ� ���� �̸��� �Է¹޴´�
				cin >> update[update_real].name; // �̴� �̸� ������� ª���н� ���н� ����ä�� ũ�ν� ���μ��� �ӷ� ����ɷ� �����ӵ� ���δɷ� �¿켱ȣ�� �� 12���� ������ �����Ǿ��ִ�
				cout << "\t\t������� : ";
				cin >> update[update_real].stats[0];
				cout << "\t\t���Ŀ�   : ";
				cin >> update[update_real].stats[1];
				cout << "\t\tª���н� : ";
				cin >> update[update_real].stats[2];
				cout << "\t\t���н�   : ";
				cin >> update[update_real].stats[3];
				cout << "\t\t����ä�� : ";
				cin >> update[update_real].stats[4];
				cout << "\t\tũ�ν�   : ";
				cin >> update[update_real].stats[5];
				cout << "\t\t���μ��� : ";
				cin >> update[update_real].stats[6];
				cout << "\t\t�ӷ�     : ";
				cin >> update[update_real].stats[7];
				cout << "\t\t����ɷ� : ";
				cin >> update[update_real].stats[8];
				cout << "\t\t�����ӵ� : ";
				cin >> update[update_real].stats[9];
				cout << "\t\t���δɷ� (0.5 - 1.5)\t\t : ";
				cin >> update[update_real].stats[10];
				cout << "\t\t�¿켱ȣ (��:-1 ��:1 ���X:0\t : ";
				cin >> update[update_real].stats[11];
				// �ڱ� �������Ͽ��� ������ �߰����ش�
				fout << update[update_real].name << '\t'; // �̸�����
				for (int o = 0; o < 12; o++) // 12������ ���� �Է�
					fout << update[update_real].stats[o] << '\t';
				++update_real; // ������ �ο� �߰�
			}
			fout.close();
			break;
		case 4:

			system("cls");
			cout << "\t\t����������������������������" << endl;
			cout << "\t\t��               4. �ڵ� ������                     ��" << endl;
			cout << "\t\t����������������������������" << endl;
			cout << "\t\t��           ��ȣ�ϴ� �������� �Է����ּ���         ��" << endl;
			cout << "\t\t��           (1)       4 - 3 - 3                    ��" << endl;
			cout << "\t\t��           (2)       3 - 4 - 3                    ��" << endl;
			cout << "\t\t��           (3)     4 - 1 - 4 - 1                  ��" << endl;
			cout << "\t\t����������������������������" << endl;
			cout << "\t\t-> ";
			cin >> prefer; // ��ȣ�ϴ� �������� �Է� �޴´�
			switch (prefer) { // �ش�Ǵ� ���������� �̵��Ѵ�
			case 1: // 433 �����̼�
				// �߿��� ������� ȣ���ϰ� ��ȯ������ϴ� �Լ� ����� �޾Ƽ� ó��
				// LW RW CM LM RM CF LB RB LCB RCB GK
				/*
				*�Ʒ� ���� �����̼� ��� �˰��� ����*
				���Ⱑ ���� ������ �κ��̾ �ѹ��� �����ϰڽ��ϴ�
				�����̼ǿ��� �켱������ ����� ���縦 ���� �˾ƿԴ� �̿� �켱������ for_433 �����ȿ� �������
				�켱������ �´� �������� �־��ش� 0�������� ���� �߿��� �������� 10�������� �� �߿��� �������� �ڸ��Ѵ�
				�׸��� ������� ���� ������ȣ�� �� �ڸ��� ���� �Ǵµ� �̴� ����� ������ ��Ÿ���� ��ǥ�̱⵵�ϴ�
				�׷��� OK��� ����Ͽ� ������ �߰����ش�
				���� ���â�� �����̼� ��翡 �°� ����������ȣ�� �����ϸ� �� ���� �̸��� ������ ������ �صξ���
				�׷��ٸ� for_433���� �켱������ �����ʰ� ���ÿ� ����������ȣ�� ���ִ�
				�׷��� ��ºκп� �켱������� update[]��ȣ �ȿ� for_433[�켱����]�� �������ش� �׷��� ���������
				�ش�Ǵ� ������ �����ǿ� �ڸ��ϸ� ����ǰ� �ȴ� �Ʒ� �κ� �ҽ��� ���ΰ� �׷���
				*�����̼� �� �켱���� �ο�*
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
				cout << "\t\t\t         �� 4 - 3 - 3 ��\n" << endl;
				cout << "\t\t\t     " << update[for_433[0]].name << "\t" << update[for_433[5]].name << "\t" << update[for_433[1]].name << "\t" << endl;
				cout << "\t\t\t     " << update[for_433[3]].name << "\t" << update[for_433[2]].name << "\t" << update[for_433[4]].name << "\t" << endl;
				cout << "\t\t\t" << update[for_433[6]].name << "\t" << update[for_433[8]].name << "\t" << update[for_433[9]].name << "\t" << update[for_433[7]].name << "\t" << endl;
				cout << "     \t\t\t\t    " << update[for_433[10]].name << "\t" << endl;
				cout << endl;
				break;
			case 2: // 343 �����̼�
				// �߿��� ������� ȣ���ϰ� ��ȯ������ϴ� �Լ� ����� �޾Ƽ� ó�� (������ ���� ����)
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
				cout << "\t\t\t           �� 3 - 4 - 3 ��\n" << endl;
				cout << "\t\t\t     " << update[for_343[3]].name << "\t" << update[for_343[9]].name << "\t" << update[for_343[4]].name << "\t" << endl;
				cout << "\t\t\t     " << "\t\t" << update[for_343[5]].name << endl;
				cout << "\t\t\t     " << update[for_343[0]].name << "\t" << update[for_343[6]].name << "\t" << update[for_343[1]].name << "\t" << endl;
				cout << "\t\t\t     " << update[for_343[7]].name << "\t" << update[for_343[2]].name << "\t" << update[for_343[8]].name << "\t" << endl;
				cout << "\t\t\t     \t\t" << update[for_343[10]].name << "\t" << endl;
				cout << endl;
				break;
			case 3: // 4141 �����̼�
				// �߿��� ������� ȣ���ϰ� ��ȯ������ϴ� �Լ� ����� �޾Ƽ� ó�� (������ ���� ����)
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
				cout << "\t\t\t      �� 4 - 1 - 4 - 1 ��\n" << endl;
				cout << "\t\t\t     \t   " << update[for_4141[0]].name << "\t" << endl;
				cout << "\t\t\t" << update[for_4141[1]].name << "\t" << update[for_4141[3]].name << "\t" << update[for_4141[4]].name << "\t" << update[for_4141[2]].name << "\t" << endl;
				cout << "\t\t\t     \t   " << update[for_4141[5]].name << "\t" << endl;
				cout << "\t\t\t" << update[for_4141[8]].name << "\t" << update[for_4141[6]].name << "\t" << update[for_4141[7]].name << "\t" << update[for_4141[9]].name << "\t" << endl;
				cout << "\t\t\t     \t   " << update[for_4141[10]].name << "\t" << endl;
				cout << endl;
				break;
			default: // ���� �����̼� �Է½�
				cout << "���� �����̼� �Դϴ�" << endl;
				break;
			}
			break;

		default: // ���� ��ȣ �������� Ż����� ����
			exit = 0;
			break;
		}
		if (exit == 0) // �޴��� ���� ��ȣ�� �Է��ϸ� �����÷��� ������ο��� ���´�
			break;
		for (int i = 0; i < 11; i++) { OK[i] = 100; } // �� ��� û��
	}
	cout << "\t\t����������������������������" << endl;
	cout << "\t\t��                   ���� �÷��� ����               ��" << endl;
	cout << "\t\t����������������������������" << endl;
	// ��� ó���� �Ǿ����� ����
}
// �α����� ������ ���� ������ ��� ���
void list(PLAYER *update, int update_real) { // �����ܰ� ������ �ο� �޾ƿ�
	for (int k = 0; k < update_real; k++) { // �ο�����ŭ �ݺ�
		cout << "\t\t��" << update[k].name << endl; // �����̸�
		cout << "\t\t";
		for (int j = 0; j < 12; j++) {
			cout << update[k].stats[j] << " "; // ������ ���ݵ�
		}
		cout << endl;
	}
}
// ���� �������߿��� ���� �˻��ϰ� �� ������ �����Ǻ� ���ݰ� ���� ������ ��õ�ϴ� �Լ�
void search(PLAYER *up, int count) { // �����ܰ� ������ �ο� �޾ƿ�
	char temp[20], BEST[5] = { '\0' }; // �˻��� ���� �̸� �ӽú���, �ְ� ���ݿ� �ش��ϴ� ������ ��
	FORMATION *find; // �������̵� �ϱ����� �θ� Ŭ���� ������ ����
	find = new FORMATION; // ������ �θ�Ŭ������ �Ҵ�
	int YN = 1, stat = 0; // ���� ã�� ����Ȯ�ο�, �� ������ �� �� �ְ� ���� üũ��
	cout << "\t\t�˻��� ���� �̸��� �Է����ּ��� -> ";
	cin >> temp; // �˻��� �����̸� �Է¹���
	for (int i = 0; i < count; i++) { // ������ �ο��� ��ŭ ����
		if (!strcmp(up[i].name, temp)) { // �����ܿ��� ���� �̸� ��Ī
			YN = 1; // ���� ã��
			// LW RW LB RB LM RM CM CDM CF LCB RCB SW GK �������
			cout << "\t\t��" << up[i].name << "'s STATS by FORMATION" << endl; // �˻��� ���� ���� ����
			find = new LW(up[i].stats, up[i].name); // ���⿡ ȣ��� �ڽ�Ŭ������ FORMATION �����ͺ��� find �� �������̵��Ͽ� ���Ӱ� ���ε� �Ʒ� ��� ����
			cout << "\t\tLW   - " << find->value() << endl; // �ش� ������ Ŭ������ �����Ǿ� �ִ� �����Լ��� �ش� ������ ���ݰ�� �Լ��� ���� ���ݰ� �޾� ���
			if (find->value() > stat) { stat = find->value(), strcpy(BEST, "LW"); } // ���࿡ �� ������ ������ �ְ��� �����̸� ���� �����ǰ� ������ �����Ѵ�
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
			cout << "\t\t�� THIS PLAYER's BEST POSITION -> " << BEST << " : " << stat << "\n" << endl; // �����صξ��� �ְ��� �����ǰ� ������ �˷��ش�
			stat = 0; // �ְ� ���� �ʱ�ȭ ( �ٸ� ������ ����ؾ� �ϱ� ������ )
			delete find; // find �Ҵ� ����
			break;
		}
		else YN = 0; // �˻��� ������ �����ܿ� ���� ��
	}
	if (YN == 0) { cout << "\t\tã���ô� ������ �������� �ʽ��ϴ�" << endl; } // �����ܿ� �˻��� ���� ����
}

// s+�����Ǹ� �Լ��� ->  �ش� �������� �ְ��� ���� ��ȯ ( PLAYER �迭���� ������ �ش籫�� ������ ��ȯ ) -> ���� �ҽ� �ּ��� sLW�� ��� ����
int sLW(PLAYER *up, int count, int *BAN) { // �����ܰ� ������ �ο� �׸��� �� ����� �޴´�
	FORMATION *find; // �������̵� �ϱ� ���� �θ� Ŭ������ ������ ������ ������ش�
	int temp, big = 0; // �ְ��� ���� ������ȣ �ӽ������, �ְ� ���� �ӽ� �����
	for (int i = 0; i < count; i++) { // ������ �ο��� ���� ������ ����
		if (HAS(i, BAN) == 0) { // �� ��Ͽ� �ֳ� üũ
			find = new LW(up[i].stats, up[i].name); // s+�����ǿ� ���ִ� �ش� �������� �ڽ�Ŭ������ �Ҵ�ް� �������̵�(���ε�) �Ѵ�
			if (big < find->value()) { big = find->value(); temp = i; } // �����Լ��� ������ �̾Ƴ��� �ְ��� ������ ���� ������� ������ȣ�� �����ϰ� ������ �����Ѵ�
		}
	}
	delete find; // �Ҵ� ����
	return temp; // �� ������ �ְ��� ���� ������ȣ ����
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
// �������� �����Ҷ� �̹� ����� ������ �ߺ����� �ʰ� �ϱ� ���� ����Ͽ��� �ɷ����� �ִ� �Լ�
int HAS(int num, int *ban) { // ������ ������ȣ�� �� ����� �޾ƿ´�
	for (int i = 0; i < 11; i++) { // ������� ������ �ִ� 11���̱� ������ 11�� ��������
		if (ban[i] == num) // ����Ͽ� ������ �ִٸ� 1 ��ȯ
			return 1;
	}
	return 0; // �� ��Ͽ� ���ٸ� 0
}