#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>
#define _CRT_SECURE_NO_DEPRECATE

#pragma comment(lib, "Winmm.lib")

int choose;					  //���ڱ������ѡ��ť�Ľ��
int len;					  //���ڼ�¼��������볤��
double ans_right;			  //��ȷ����
double ans_wrong;			  //�������
double ansaccuracy;			  //��ȷ�ʼ���
char content[1001];			  //���潫Ҫ����Ĵ���
char temp[10];				  //������ʱ�洢����ת������
clock_t time_start, time_end; //��ʱ����

//�������
IMAGE init_img;		   //��ʼ���汳��ͼ
IMAGE bkg_img;		   //ѡ��ģʽ����ͼ
IMAGE bkg_help;		   //��������
IMAGE img_plant;	   //����ͼƬ
IMAGE img_plant2;	   //����ͼƬ
IMAGE bkg_end1;		   //����������������
IMAGE bkg_end2;		   //����������߽�������
IMAGE bkg_end3;		   //��սģʽ��������
IMAGE bkg_record;	   //�鿴��߼�¼����
IMAGE img_accu_temp;   //������ʱ��ȡ��ȷ�ʼ�����ı���
IMAGE img_signal_temp; //������ʱ��ȡ���󵯴����ı���
IMAGE img_output_temp; //������ʱ��ȡ�����ʾ�򴦵ı���
IMAGE img_live_temp;   //������ʱ��ȡ����ֵ��ʾ��ı���
IMAGE temp_key;		   //������ʱ��ȡ���̰����ı���

void game_start(); //���������庯�������������õ�

//��ʼ�������
void draw_initial()
{
	initgraph(1344, 768);
	setbkmode(TRANSPARENT); //����������ʾģʽΪ͸��
	putimage(0, 0, &init_img);
	settextstyle(80, 40, _T("Comic Sans MS"));

	//���ý�������ַ�����ֱ���������������һ����
	int r = 0, g = 0, b = 0;
	while (1)
	{
		settextcolor(RGB(r, g, b));
		outtextxy(1344 / 2 - 450, 768 - 180, _T("���������ʼ��ϰ����"));
		{
			r += 4;
			g += 3;
			b += 2;
		}
		if (_kbhit())
		{
			_getch();
			break;
		}
		Sleep(40);
	}
}

//ѡ��ģʽ����
int gamemode_choose()
{
	putimage(0, 0, &bkg_img);

	settextstyle(80, 40, _T("Comic Sans MS"));
	settextcolor(RGB(230, 230, 250));
	outtextxy(1344 / 2 - 450, 768 - 570, _T("��ѡ����Ϸģʽ"));

	setlinecolor(BLACK);
	setfillcolor(RGB(193, 205, 193));//�����ɫ
	//fillroundrect(1344 / 2 - 155  , 768 - 455, 1344 / 2 + 155, 768 - 345, 20, 20); //gm1(Բ�Ǿ��κ���)
	fillroundrect(1344 / 2 - 155  , 768 - 335, 1344 / 2 + 155, 768 - 225, 20, 20); //gm2
	fillroundrect(1344 / 2 - 155  , 768 - 215, 1344 / 2 + 155, 768 - 105, 20, 20); //gm3

	setfillcolor(RGB(230, 230, 250));
 
	fillroundrect(1344 / 2 - 150, 768 - 330, 1344 / 2 + 150, 768 - 230, 15, 15); //gm2
	fillroundrect(1344 / 2 - 150, 768 - 210, 1344 / 2 + 150, 768 - 110, 15, 15); //gm3
	 
	settextstyle(45, 22, _T("����"));
	settextcolor(RGB(139, 35, 35));
	 
	outtextxy(1344 / 2 - 100 , 768 - 305, _T("��ϰģʽ"));
	outtextxy(1344 / 2 - 100 , 768 - 185, _T("��սģʽ"));
	settextstyle(35, 17, _T("����"));
	 

	MOUSEMSG choose_gamemode; //����������������������ť�¼�
	while (1)
	{
		choose_gamemode = GetMouseMsg(); //��ֵ������

		if (_kbhit())
			_getch(); //��ֹ������

		 if (choose_gamemode.x >= 1344 / 2 - 150 && choose_gamemode.x <= 1344 / 2 + 150 && choose_gamemode.y >= 768 - 330 && choose_gamemode.y <= 768 - 230)
		{
			if (choose_gamemode.uMsg == WM_LBUTTONDOWN)
				return 2;
		}
		//gm3
		else if (choose_gamemode.x >= 1344 / 2 - 150 && choose_gamemode.x <= 1344 / 2 + 150 && choose_gamemode.y >= 768 - 210 && choose_gamemode.y <= 768 - 110)
		{
			if (choose_gamemode.uMsg == WM_LBUTTONDOWN)
				return 3;
		}
	}
}

//ѡ��������
int draw_content_choose()
{
	putimage(0, 0, &bkg_img);

	settextstyle(80, 40, _T("Comic Sans MS"));
	settextcolor(RGB(230, 230, 250));
	outtextxy(1344 / 2 - 350, 768 - 570, _T("ѡ����Ҫ��ϰ�ĳ���"));

	setlinecolor(BLACK);

	setfillcolor(RGB(193, 205, 193));
	fillroundrect(1344 / 2 - 155, 768 - 405, 1344 / 2 + 155, 768 - 295, 20, 20); //code1
	fillroundrect(1344 / 2 - 155, 768 - 225, 1344 / 2 + 155, 768 - 115, 20, 20); //code2
	fillroundrect(1344 - 165, 768 - 85, 1344 - 35, 768 - 15, 15, 15);			 //����

	setfillcolor(RGB(230, 230, 250));
	fillroundrect(1344 / 2 - 150, 768 - 400, 1344 / 2 + 150, 768 - 300, 15, 15); //code1
	fillroundrect(1344 / 2 - 150, 768 - 220, 1344 / 2 + 150, 768 - 120, 15, 15); //code2
	fillroundrect(1344 - 160, 768 - 80, 1344 - 40, 768 - 20, 10, 10);			 //����

	settextstyle(45, 22, _T("Comic Sans MS"));
	settextcolor(RGB(139, 35, 35));
	outtextxy(1344 / 2 - 130, 768 - 375, _T("   ��������"));
	outtextxy(1344 / 2 - 130, 768 - 195, _T("�������ϴ���"));
	settextstyle(35, 17, _T("����"));
	outtextxy(1344 - 138, 768 - 65, _T("����"));
	MOUSEMSG choose_gamemode; //����������
	while (1)
	{
		choose_gamemode = GetMouseMsg(); //��ȡ������

		if (_kbhit())
			_getch(); //��ֹ������

		//code1
		if (choose_gamemode.x >= 1344 / 2 - 150 && choose_gamemode.x <= 1344 / 2 + 150 && choose_gamemode.y >= 768 - 400 && choose_gamemode.y <= 768 - 300)
		{
			if (choose_gamemode.uMsg == WM_LBUTTONDOWN)
				return 1;
		}
		//code2
		else if (choose_gamemode.x >= 1344 / 2 - 150 && choose_gamemode.x <= 1344 / 2 + 150 && choose_gamemode.y >= 768 - 220 && choose_gamemode.y <= 768 - 120)
		{
			if (choose_gamemode.uMsg == WM_LBUTTONDOWN)
				return 2;
		}
		//����
		else if (choose_gamemode.x >= 1344 - 160 && choose_gamemode.x <= 1344 - 40 && choose_gamemode.y >= 768 - 80 && choose_gamemode.y <= 768 - 20)
		{
			if (choose_gamemode.uMsg == WM_LBUTTONDOWN)
				return 3;
		}
	}
	_getch();
}

//���̻�����߹���ʾ
void draw_key_small(int x, int y)
{
	//���̵�С�������� ������������С���ڿ�
	setfillcolor(RGB(176, 226, 255));
	fillroundrect(x - 2, y - 2, x + 54, y + 54, 5, 5);
	fillroundrect(x, y, x + 50, y + 50, 5, 5);
}
void draw_key_mid(int x, int y)
{
	fillroundrect(x - 2, y - 2, x + 74, y + 54, 5, 5);
	fillroundrect(x, y, x + 70, y + 50, 5, 5);
}
//RGB(191, 239, 255)
//RGB(255, 192, 203)
//RGB(255, 192, 203)->255, 192, 203
void draw_keyboard()
{
	setfillcolor(RGB(191, 239, 255));//239
	setlinecolor(BLACK);

	//�߿�
	fillroundrect((1344 - 890) / 2 - 10, 768 - 330, (1344 - 890) / 2 + 900, 768 - 20, 15, 15);

	for (int i = (1344 - 890) / 2; i <= (1344 - 890) / 2 + 720; i += 60)
		draw_key_small(i, 768 - 320); //��һ��С����

	//Backspace
	setfillcolor(RGB(255, 192, 203));
	fillroundrect((1344 - 890) / 2 + 778, 768 - 322, (1344 - 890) / 2 + 894, 768 - 266, 5, 5);
	fillroundrect((1344 - 890) / 2 + 780, 768 - 320, (1344 - 890) / 2 + 890, 768 - 270, 5, 5);

	//�ڶ���С����
	for (int i = (1344 - 890) / 2 + 90; i <= (1344 - 890) / 2 + 750; i += 60)
		draw_key_small(i, 768 - 260);

	//Tab
	setfillcolor(RGB(255, 192, 203));
	fillroundrect((1344 - 890) / 2 - 2, 768 - 262, (1344 - 890) / 2 + 84, 768 - 206, 5, 5);
	fillroundrect((1344 - 890) / 2, 768 - 260, (1344 - 890) / 2 + 80, 768 - 210, 5, 5);

	//|||||
	setfillcolor(RGB(176, 226, 255));
	fillroundrect((1344 - 890) / 2 + 808, 768 - 262, (1344 - 890) / 2 + 894, 768 - 206, 5, 5);
	fillroundrect((1344 - 890) / 2 + 810, 768 - 260, (1344 - 890) / 2 + 890, 768 - 210, 5, 5);

	//������С����
	for (int i = (1344 - 890) / 2 + 105; i <= (1344 - 890) / 2 + 705; i += 60)
		draw_key_small(i, 768 - 200);

	//CapsLock
	setfillcolor(RGB(255, 192, 203));
	fillroundrect((1344 - 890) / 2 - 2, 768 - 202, (1344 - 890) / 2 + 99, 768 - 146, 5, 5);
	fillroundrect((1344 - 890) / 2, 768 - 200, (1344 - 890) / 2 + 95, 768 - 150, 5, 5);

	//Enter
	setfillcolor(RGB(255, 192, 203));
	fillroundrect((1344 - 890) / 2 + 763, 768 - 202, (1344 - 890) / 2 + 894, 768 - 146, 5, 5);
	fillroundrect((1344 - 890) / 2 + 765, 768 - 200, (1344 - 890) / 2 + 890, 768 - 150, 5, 5);

	//������С����
	for (int i = (1344 - 890) / 2 + 130; i <= (1344 - 890) / 2 + 690; i += 60)
		draw_key_small(i, 768 - 140);

	//Shift1
	setfillcolor(RGB(255, 192, 203));
	fillroundrect((1344 - 890) / 2 - 2, 768 - 142, (1344 - 890) / 2 + 124, 768 - 86, 5, 5);
	fillroundrect((1344 - 890) / 2, 768 - 140, (1344 - 890) / 2 + 120, 768 - 90, 5, 5);

	//Shift2
	setfillcolor(RGB(255, 192, 203));
	fillroundrect((1344 - 890) / 2 + 728, 768 - 142, (1344 - 890) / 2 + 894, 768 - 86, 5, 5);
	fillroundrect((1344 - 890) / 2 + 730, 768 - 140, (1344 - 890) / 2 + 890, 768 - 90, 5, 5);

	//�������а�������
	for (int i = (1344 - 890) / 2; i <= (1344 - 890) / 2 + 160; i += 80)
		draw_key_mid(i, 768 - 80);

	//�������а�������
	for (int i = (1344 - 890) / 2 + 580; i <= (1344 - 890) / 2 + 820; i += 80)
		draw_key_mid(i, 768 - 80);

	//Space
	setfillcolor(RGB(176, 226, 255));
	fillroundrect((1344 - 890) / 2 + 238, 768 - 82, (1344 - 890) / 2 + 574, 768 - 26, 5, 5);
	fillroundrect((1344 - 890) / 2 + 240, 768 - 80, (1344 - 890) / 2 + 570, 768 - 30, 5, 5);
}
void key_light(char c)
{
	int m=0, n=0;
	if (c >= 'A' && c <= 'Z')
		c = c + 32; //��дתСд�ж�

	/*ÿ����������*/
	switch (c)
	{
	case 27:
		break; //Esc������
	case '~':
	case '`':
		m = (1344 - 890) / 2;
		n = 768 - 320;
		break;
	case '1':
	case '!':
		m = (1344 - 890) / 2 + 60;
		n = 768 - 320;
		break;
	case '2':
	case '@':
		m = (1344 - 890) / 2 + 120;
		n = 768 - 320;
		break;
	case '3':
	case '#':
		m = (1344 - 890) / 2 + 180;
		n = 768 - 320;
		break;
	case '4':
	case '$':
		m = (1344 - 890) / 2 + 240;
		n = 768 - 320;
		break;
	case '5':
	case '%':
		m = (1344 - 890) / 2 + 300;
		n = 768 - 320;
		break;
	case '6':
	case '^':
		m = (1344 - 890) / 2 + 360;
		n = 768 - 320;
		break;
	case '7':
	case '&':
		m = (1344 - 890) / 2 + 420;
		n = 768 - 320;
		break;
	case '8':
	case '*':
		m = (1344 - 890) / 2 + 480;
		n = 768 - 320;
		break;
	case '9':
	case '(':
		m = (1344 - 890) / 2 + 540;
		n = 768 - 320;
		break;
	case '0':
	case ')':
		m = (1344 - 890) / 2 + 600;
		n = 768 - 320;
		break;
	case '-':
	case '_':
		m = (1344 - 890) / 2 + 660;
		n = 768 - 320;
		break;
	case '=':
	case '+':
		m = (1344 - 890) / 2 + 720;
		n = 768 - 320;
		break;
	case 'q':
		m = (1344 - 890) / 2 + 90;
		n = 768 - 260;
		break;
	case 'w':
		m = (1344 - 890) / 2 + 150;
		n = 768 - 260;
		break;
	case 'e':
		m = (1344 - 890) / 2 + 210;
		n = 768 - 260;
		break;
	case 'r':
		m = (1344 - 890) / 2 + 270;
		n = 768 - 260;
		break;
	case 't':
		m = (1344 - 890) / 2 + 330;
		n = 768 - 260;
		break;
	case 'y':
		m = (1344 - 890) / 2 + 390;
		n = 768 - 260;
		break;
	case 'u':
		m = (1344 - 890) / 2 + 450;
		n = 768 - 260;
		break;
	case 'i':
		m = (1344 - 890) / 2 + 510;
		n = 768 - 260;
		break;
	case 'o':
		m = (1344 - 890) / 2 + 570;
		n = 768 - 260;
		break;
	case 'p':
		m = (1344 - 890) / 2 + 630;
		n = 768 - 260;
		break;
	case '{':
	case '[':
		m = (1344 - 890) / 2 + 690;
		n = 768 - 260;
		break;
	case '}':
	case ']':
		m = (1344 - 890) / 2 + 750;
		n = 768 - 260;
		break;
	case '|':
	case '\\':
		m = (1344 - 890) / 2 + 810;
		n = 768 - 260;
		break;
	case 'a':
		m = (1344 - 890) / 2 + 105;
		n = 768 - 200;
		break;
	case 's':
		m = (1344 - 890) / 2 + 165;
		n = 768 - 200;
		break;
	case 'd':
		m = (1344 - 890) / 2 + 225;
		n = 768 - 200;
		break;
	case 'f':
		m = (1344 - 890) / 2 + 285;
		n = 768 - 200;
		break;
	case 'g':
		m = (1344 - 890) / 2 + 345;
		n = 768 - 200;
		break;
	case 'h':
		m = (1344 - 890) / 2 + 405;
		n = 768 - 200;
		break;
	case 'j':
		m = (1344 - 890) / 2 + 465;
		n = 768 - 200;
		break;
	case 'k':
		m = (1344 - 890) / 2 + 525;
		n = 768 - 200;
		break;
	case 'l':
		m = (1344 - 890) / 2 + 585;
		n = 768 - 200;
		break;
	case ':':
	case ';':
		m = (1344 - 890) / 2 + 645;
		n = 768 - 200;
		break;
	case '\'':
	case '\"':
		m = (1344 - 890) / 2 + 705;
		n = 768 - 200;
		break;
	case '\r':
		m = (1344 - 890) / 2 + 765;
		n = 768 - 200;
		break;
	case 'z':
		m = (1344 - 890) / 2 + 130;
		n = 768 - 140;
		break;
	case 'x':
		m = (1344 - 890) / 2 + 190;
		n = 768 - 140;
		break;
	case 'c':
		m = (1344 - 890) / 2 + 250;
		n = 768 - 140;
		break;
	case 'v':
		m = (1344 - 890) / 2 + 310;
		n = 768 - 140;
		break;
	case 'b':
		m = (1344 - 890) / 2 + 370;
		n = 768 - 140;
		break;
	case 'n':
		m = (1344 - 890) / 2 + 430;
		n = 768 - 140;
		break;
	case 'm':
		m = (1344 - 890) / 2 + 490;
		n = 768 - 140;
		break;
	case ',':
	case '<':
		m = (1344 - 890) / 2 + 550;
		n = 768 - 140;
		break;
	case '.':
	case '>':
		m = (1344 - 890) / 2 + 610;
		n = 768 - 140;
		break;
	case '/':
	case '?':
		m = (1344 - 890) / 2 + 670;
		n = 768 - 140;
		break;
	case ' ':
		m = (1344 - 890) / 2 + 240;
		n = 768 - 80;
		break;
	}

	/*ģ�ⷢ��*/
	setfillcolor(WHITE);

	/*'|','\'�����⿼��*/
	if (m == (1344 - 890) / 2 + 810 && n == 768 - 260)
	{
		getimage(&temp_key, m, n, m + 80, n + 50);
		fillroundrect(m, n, m + 80, n + 50, 5, 5);
	}
	/*�س������⿼��*/
	else if (m == (1344 - 890) / 2 + 765 && n == 768 - 200)
	{
		getimage(&temp_key, m, n, m + 125, n + 50);
		fillroundrect(m, n, m + 125, n + 50, 5, 5);
	}
	/*�ո�����⿼��*/
	else if (m == (1344 - 890) / 2 + 240 && n == 768 - 80)
	{
		getimage(&temp_key, m, n, m + 330, n + 50);
		fillroundrect(m, n, m + 330, n + 50, 5, 5);
	}
	/*�����ͨ��*/
	else
	{
		getimage(&temp_key, m, n, m + 50, n + 50);
		fillroundrect(m, n, m + 50, n + 50, 5, 5);
	}

	/*��λ*/
	Sleep(50);
	putimage(m, n, &temp_key);
	setfillcolor(RGB(240, 255, 255));
	setlinecolor(RGB(240, 255, 255));
}
void keyboard_fill()
{
	char keyboard_1[] = { '~,', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+' };
	char keyboard_2[] = { '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=' };
	char keyboard_3[] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '|' };
	char keyboard_4[] = { 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"' };
	char keyboard_5[] = { 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?' };
	char keyboard_6[] = { '[', ']', '\\' };
	char keyboard_7[] = { ';', '\'' };
	char keyboard_8[] = { ',', '.', '/' };
	const int boardinit_x = (1344 - 890) / 2;
	const int boardinit_y = 768 - 320;
	settextcolor(BLACK);
	settextstyle(18, 9, _T("Comic Sans MS"));
	for (int i = 0; i < 13; i++)
		outtextxy(boardinit_x + i * 60 + 15, boardinit_y + 5, keyboard_1[i]);
	for (int i = 0; i < 13; i++)
		outtextxy(boardinit_x + i * 60 + 30, boardinit_y + 20, keyboard_2[i]);
	outtextxy(boardinit_x + 790, boardinit_y + 15, "Backspace");
	for (int i = 0; i < 13; i++)
		outtextxy(boardinit_x + i * 60 + 100, boardinit_y + 65, keyboard_3[i]);
	for (int i = 0; i < 3; i++)
		outtextxy(boardinit_x + i * 60 + 720, boardinit_y + 80, keyboard_6[i]);
	outtextxy(boardinit_x + 25, boardinit_y + 75, "Tab");
	for (int i = 0; i < 11; i++)
		outtextxy(boardinit_x + i * 60 + 115, boardinit_y + 125, keyboard_4[i]);
	for (int i = 0; i < 2; i++)
		outtextxy(boardinit_x + i * 60 + 670, boardinit_y + 140, keyboard_7[i]);
	outtextxy(boardinit_x + 8, boardinit_y + 135, "CapsLock");
	outtextxy(boardinit_x + 805, boardinit_y + 135, "Enter");
	for (int i = 0; i < 10; i++)
		outtextxy(boardinit_x + i * 60 + 140, boardinit_y + 185, keyboard_5[i]);
	for (int i = 0; i < 3; i++)
		outtextxy(boardinit_x + i * 60 + 570, boardinit_y + 200, keyboard_8[i]);
	outtextxy(boardinit_x + 43, boardinit_y + 195,"Shift");
	outtextxy(boardinit_x + 790, boardinit_y + 195, "Shift");
	outtextxy(boardinit_x + 22, boardinit_y + 255, "Ctrl");
	outtextxy(boardinit_x + 100, boardinit_y + 255, "Win");
	outtextxy(boardinit_x + 185, boardinit_y + 255, "Alt");
	outtextxy(boardinit_x + 605, boardinit_y + 255, "Alt");
	outtextxy(boardinit_x + 680, boardinit_y + 255, "Win");
	outtextxy(boardinit_x + 765, boardinit_y + 255, "Fn");
	outtextxy(boardinit_x + 842, boardinit_y + 255, "Ctrl");
}

//�������
void draw_screen_main()
{
	setlinecolor(BLACK);
	setfillcolor(RGB(193, 205, 193));
	fillroundrect((1344 - 890) / 2 - 5, 15, (1344 - 890) / 2 + 895, 768 - 355, 15, 15);
	setfillcolor(RGB(240, 255, 255));
	fillroundrect((1344 - 890) / 2, 20, (1344 - 890) / 2 + 890, 768 - 360, 10, 10);
}
void draw_screen_input_1()
{
	setlinecolor(BLACK);
	setfillcolor(RGB(193, 205, 193));
	fillroundrect(15, 15, (1344 - 890) / 2 - 15, 768 - 355, 15, 15);
	setfillcolor(RGB(240, 255, 255));
	fillroundrect(20, 20, (1344 - 890) / 2 - 20, 768 - 360, 10, 10);
	settextcolor(BLACK);
	settextstyle(16, 8, _T("����"));
	outtextxy(30, 50,"��Ҫ����ĳ�������:");
	 
	outtextxy(30, 90, "#include <stdio.h>");
	outtextxy(30, 120, "int main()");
	outtextxy(30, 150, "{");
	outtextxy(30, 180, "int a,b;");
	outtextxy(30, 210, "scanf(\"%d %d\",&a,&b);");
	outtextxy(30, 240, "a=a^b;");
	outtextxy(30, 270, "b=a^b;");
	outtextxy(30, 300, "b=a^b;");
	outtextxy(30, 330, "printf(\"a=%d b=%d\",a,b);");
	outtextxy(30, 360, "return 0;");
	outtextxy(30, 390, "}");
}
void draw_screen_input_2()
{
	setlinecolor(BLACK);
	setfillcolor(RGB(193, 205, 193));
	fillroundrect(15, 15, (1344 - 890) / 2 - 15, 768 - 355, 15, 15);
	setfillcolor(RGB(240, 255, 255));
	fillroundrect(20, 20, (1344 - 890) / 2 - 20, 768 - 360, 10, 10);
	settextcolor(BLACK);
	settextstyle(16, 8, _T("����"));
	outtextxy(30, 50, "��Ҫ����ĳ���Ϊ:");
	outtextxy(30, 90, "#include <stdio.h>");
	outtextxy(30, 120, "int main()");
	outtextxy(30, 150,"{");
	outtextxy(30, 180, "int a,b;");
	outtextxy(30, 210, "scanf(\"%d %d\",&a,&b);");
	outtextxy(30, 240, "printf(\"%d\",a>b?a:b);");
	outtextxy(30, 270, "return 0;");
	outtextxy(30, 300, "}");
}
void draw_screen_output()
{
	setfillcolor(RGB(193, 205, 193));
	fillroundrect((1344 - 890) / 2 + 905, 15, 1344 - 15, 768 - 555, 15, 15);
	setfillcolor(RGB(240, 255, 255));
	fillroundrect((1344 - 890) / 2 + 910, 20, 1344 - 20, 768 - 560, 10, 10);
	settextcolor(BLACK);
	settextstyle(20, 10, _T("����"));
	 
}
void draw_screen_accuracy()
{
	setfillcolor(RGB(193, 205, 193));
	fillroundrect(15, 768 - 345, (1344 - 890) / 2 - 15, 768 - 145, 15, 15);
	setfillcolor(RGB(240, 255, 255));
	fillroundrect(20, 768 - 340, (1344 - 890) / 2 - 20, 768 - 150, 10, 10);
	settextcolor(BLACK);
	settextstyle(20, 10, _T("����"));
	outtextxy(40, 768 - 320,"��ȷ��:");
}
void fill_screen_accuracy()
{
	char accu[2];
	settextstyle(50, 25, _T("Comic Sans MS"));
	settextcolor(RED);
	putimage(45, 768 - 270, &img_accu_temp);
	double accuracy;
	if (ans_wrong == 0)
	{
		outtextxy(45, 768 - 270, "100%");
	}
	else if (ans_right == 0)
	{
		outtextxy(45, 768 - 270, "0%");
	}
	else
	{
		accuracy = ans_right / (ans_right + ans_wrong);
		accu[0] = ((int)(accuracy * 10)) + '0';
		accu[1] = ((int)(accuracy * 100) % 10) + '0';
		outtextxy(45, 768 - 270, accu[0]);
		outtextxy(85, 768 - 270, accu[1]);
		outtextxy(125, 768 - 270, '%');
	}
}
void draw_screen_life()
{

}
void draw_screen_point()
{
	setlinecolor(BLACK);
	setfillcolor(RGB(193, 205, 193));
	fillroundrect(15, 15, (1344 - 890) / 2 - 15, 768 - 555, 15, 15);
	 
	setfillcolor(RGB(240, 255, 255));
	fillroundrect(20, 20, (1344 - 890) / 2 - 20, 768 - 560, 10, 10);
	 

	 settextcolor(BLACK);
	settextstyle(20, 10, _T("����"));
	outtextxy(30, 50, "��ǰ�÷�Ϊ:"); 
	 
}
void draw_best_score()//�޸ģ��ɲ���ӡ�������������̫���ˣ��㱻����
{
	settextstyle(60, 30, _T("Comic Sans MS"));
	settextcolor(RED);
	 
}
void draw_best_acc1()
{
	setfillcolor(RGB(193, 205, 193));
	fillroundrect((1344 - 890) / 2 + 905, 768 - 345, 1344 - 15, 768 - 145, 15, 15);
	setfillcolor(RGB(240, 255, 255));
	fillroundrect((1344 - 890) / 2 + 910, 768 - 340, 1344 - 20, 768 - 150, 10, 10);
	settextcolor(BLACK);

	settextstyle(50, 25, _T("Comic Sans MS"));
	settextcolor(RED);
	 
}
void draw_best_acc2()
{
	setfillcolor(RGB(193, 205, 193));
	fillroundrect((1344 - 890) / 2 + 905, 768 - 345, 1344 - 15, 768 - 145, 15, 15);
	setfillcolor(RGB(240, 255, 255));
	fillroundrect((1344 - 890) / 2 + 910, 768 - 340, 1344 - 20, 768 - 150, 10, 10);
	settextcolor(BLACK);
	settextstyle(20, 10, _T("����"));

	settextstyle(50, 25, _T("Comic Sans MS"));
	settextcolor(RED);
	 
}

//����
//����ab�Ľ�������
void end1()
{
	Sleep(100);
	 
	while (_getch() != 27)
		;

	game_start();
}
//��ab�ϴ�ֵ�Ľ�������
void end2()
{
	Sleep(100);
	//putimage(0, 0, &bkg_end2);

	//�����ǰ�ɼ�
	settextcolor(WHITE);
	settextstyle(80, 40, _T("Comic Sans MS"));

	while (_getch() != 27)
		;
	game_start();
}
//�޾�ģʽ�Ľ�������
void end3()
{
	Sleep(100);
	putimage(0, 0, &bkg_end3);

	//�����ǰ�ɼ�
	settextcolor(WHITE);
	settextstyle(80, 40, _T("Comic Sans MS"));
		sprintf(temp, "%.f", ans_right);
		 

	if (ans_wrong + ans_right == 0)
		; 
	else
	{
		ansaccuracy = (ans_right) / (ans_right + ans_wrong) * 100;
		if (ansaccuracy < 10)
		{
			sprintf(temp, "%.f", ansaccuracy);
		 
			outtextxy(1230, 500, "");
		}
		else if (ansaccuracy < 100)
		{
			sprintf(temp, "%.f", ansaccuracy);
		 
			outtextxy(1230, 500, "");
		}
		else
			; 
	}

	 

	while (_getch() != 27)
		;

	game_start();
}
//������Ϸģʽ
void gm2()
{
	//��������ģ��
	setfillcolor(WHITE);
	fillroundrect(1344 / 2 - 150, 768 - 330, 1344 / 2 + 150, 768 - 230, 15, 15);
	Sleep(100);

	choose = draw_content_choose();

	switch (choose)
	{
		//code1
	case 1:
	{
		setfillcolor(WHITE);
		fillroundrect(1344 / 2 - 150, 768 - 400, 1344 / 2 + 150, 768 - 300, 15, 15);
		Sleep(100);

		cleardevice();
		putimage(0, 0, &bkg_img);
		draw_screen_input_1();
		//draw_best_acc1();
		strcpy_s(content, "#include<stdio.h>intmain(){int a,b;scanf(\"%d %d\",&a,&b);a=a^b;b=a^b;b=a^b;printf(\"a=%d b=%d\",a,b);return0;};");

		break;
	}
	//code2
	case 2:
	{
		setfillcolor(WHITE);
		fillroundrect(1344 / 2 - 150, 768 - 220, 1344 / 2 + 150, 768 - 120, 15, 15);
		Sleep(100);

		cleardevice();
		putimage(0, 0, &bkg_img);
		draw_screen_input_2();
		//draw_best_acc2();
		strcpy_s(content, "#include<stdio.h>intmain(){inta,b;scanf(\"%d%d\",&a,&b);printf(\"%d\",a+b);return0;}");

		break;
	}
	//����������
	case 3:
	{
		setfillcolor(WHITE);
		fillroundrect(1344 - 160, 768 - 80, 1344 - 40, 768 - 20, 10, 10);
		Sleep(100);
		game_start();
		break;
	}
	}

	/*���Ƽ���*/
	draw_keyboard();
	/*��䰴��*/
	keyboard_fill();
	/*������Ļ*/
	draw_screen_main();
	draw_screen_accuracy();
	/*������Ļ*/
	draw_screen_main();
	draw_screen_accuracy();
	//draw_screen_point();

	getimage(&img_accu_temp, 45, 768 - 270, 150, 50);							//��ȡ��ȷ����ʾ��
	getimage(&img_live_temp, (1344 - 890) / 2 + 910, 20, 1344 - 20, 768 - 560); //��ȡ����ֵ��ʾ��

	time_start = clock(); //��ʱ���

	/*��Ҫ���ݳ�ʼ��*/
	int x, y, speed = 1;
	//char input;
	ans_right = 0, ans_wrong = 0, ansaccuracy = 1; //��ȷ�ʹ�λ
	srand(time(NULL));
	//char content[] = { "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890!#%&*()-+={}[]\\|:;\'\"<>,./?" };
	len = strlen(content);
	int i=0, j; //	i��¼������ַ�	j��¼����

	//����һ���뱳����ȫͬɫ�ľ��Σ���ʵ����ĸ����Ч��
	setfillcolor(RGB(240, 255, 255));
	setlinecolor(RGB(240, 255, 255));

	/*���ơ����ӡ�*/
	for (i = (1344 - 890) / 2 + 20; i <= (1344 - 890) / 2 + 820; i += 80)
	{
		putimage(i, 768 - 480, &img_plant);
		putimage(i, 768 - 420, &img_plant2);
	}
	setfillcolor(RGB(240, 255, 255));
	setlinecolor(RGB(240, 255, 255));
	int plant_life[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, deadline; //��¼��������ֵ����������

	i = -1;
	/*�޾�ѭ��*/
	while (1)
	{
		putimage((1344 - 890) / 2 + 910, 20, &img_live_temp);
		settextcolor(RGB(255, 185, 15));
		settextstyle(100, 50, _T("Comic Sans MS"));

		/*�����ȡ����*/
		settextcolor(BLACK);
		settextstyle(30, 15, _T("Comic Sans MS"));
		j = (rand() % 11); //���һ��0~10֮��������
		x = (1344 - 890) / 2 + 30 + j * 80;
		srand(rand());
		//i = rand() % len;
		i++;
		srand(rand());

		/*�жϻ�ʣ����*/
		switch (plant_life[j])
		{
		case 0:
			deadline = 768 - 400;
			break;
		case 1:
			deadline = 768 - 460;
			break;
		case 2:
			deadline = 768 - 520;
			break;
		}


		settextcolor(BLACK);
		settextstyle(30, 15, _T("Comic Sans MS"));
		char input = 0;
		/*��ѭ��*/
		for (y = 25; y <= deadline; y += speed)
		{

			outtextxy(x, y, content[i]);
			fill_screen_accuracy();
			settextcolor(BLACK);
			settextstyle(30, 15, _T("Comic Sans MS"));
			if (_kbhit())
			{
				input = _getch(); // ��ȡ�û�����

				key_light(input); //����

				if ((input == content[i]))
				{
					// ������ȷ�������䡱��ĸ��������
					fillrectangle(x - 5, y, x + 50, y + 35);
					ans_right++;
					break; // ����ѭ����������һ����ĸ
				}
				else if (input == 27)
				{
					break; // ����� ESC���˳���Ϸ��ѭ��
				}
				else if ((input != content[i]))
				{
					ans_wrong++;
				} //����������
			}
			Sleep(20);
			fillrectangle(x - 5, y, x + 50, y + 35);
		} 
		//���Բ����÷�
		fillrectangle(70, 90, 110, 130);

		/*һ����������ȥ��һ��*///������ȦȻ�����
		if (y >= deadline)
		{
			plant_life[j]--;
			ans_wrong++;
		}

		/*�������Ӷ������˳�*///����Ӧ�ÿ�����������
		if (plant_life[j] == 1)
		{
			Sleep(100);
			fillrectangle((1344 - 890) / 2 + 20 + j * 80, 768 - 480, (1344 - 890) / 2 + 60 + j * 80, 768 - 440);
		}
		if (plant_life[j] == 0)
		{
			Sleep(100);
			fillrectangle((1344 - 890) / 2 + 20 + j * 80, 768 - 420, (1344 - 890) / 2 + 60 + j * 80, 768 - 380);
		}
		if (plant_life[j] == -1)
		{
			Sleep(200);
			break;
		}

		/*��Esc�˳�*/
		if (input == 27)
		{
			fillrectangle(x, y, x + 50, y + 35);
			break;
		}

	} 

	/*������ʱ�������˳�����*/
	time_end = clock();
	switch (choose)
	{
	case 1:
		end1();
		break;
	case 2:
		end2();
		break;
	} //��ת����������
}

void gm3()
{
	//��������ģ��
	setfillcolor(WHITE);
	fillroundrect(1344 / 2 - 150, 768 - 210, 1344 / 2 + 150, 768 - 110, 15, 15);
	Sleep(100);

	putimage(0, 0, &bkg_img);

	/*���Ƽ���*/
	draw_keyboard();
	/*��䰴��*/
	keyboard_fill();

	/*������Ļ*/
	draw_screen_main();
	draw_screen_accuracy();
	draw_screen_point();

	getimage(&img_accu_temp, 45, 768 - 270, 150, 50);							//��ȡ��ȷ����ʾ��

	time_start = clock(); //��ʱ���

	/*��Ҫ���ݳ�ʼ��*/
	int x, y, speed = 1;
	//char input;
	ans_right = 0, ans_wrong = 0, ansaccuracy = 1; //��ȷ�ʹ�λ
	srand(time(NULL));
	char content[] = { "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890!#%&*()-+={}[]\\|:;\'\"<>,./?" };
	len = strlen(content);
	int i, j; //	i��¼������ַ�	j��¼����

	//����һ���뱳����ȫͬɫ�ľ��Σ���ʵ����ĸ����Ч��
	setfillcolor(RGB(240, 255, 255));
	setlinecolor(RGB(240, 255, 255));

	/*���ơ����ӡ�*/
	for (i = (1344 - 890) / 2 + 20; i <= (1344 - 890) / 2 + 820; i += 80)
	{
		putimage(i, 768 - 480, &img_plant);
		putimage(i, 768 - 420, &img_plant2);
	}
	setfillcolor(RGB(240, 255, 255));
	setlinecolor(RGB(240, 255, 255));
	int plant_life[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, deadline; //��¼��������ֵ����������

	/*��սģʽ*/
	while (1)
	{
		putimage((1344 - 890) / 2 + 910, 20, &img_live_temp);
		settextcolor(RGB(255, 185, 15));
		settextstyle(100, 50, _T("Comic Sans MS"));

		/*�����ȡ����*/
		settextcolor(BLACK);
		settextstyle(30, 15, _T("Comic Sans MS"));
		j = (rand() % 11); //���һ��0~10֮��������
		x = (1344 - 890) / 2 + 30 + j * 80;
		srand(rand());
		i = rand() % len;
		srand(rand());

		/*�жϻ�ʣ����*/
		switch (plant_life[j])
		{
		case 0:
			deadline = 768 - 400;
			break;
		case 1:
			deadline = 768 - 460;
			break;
		case 2:
			deadline = 768 - 520;
			break;
		}

		/*���ݵ÷��޸��ٶ�*/
		if (ans_right >= 0 && ans_right <= 3)
			speed = 1;
		else if (ans_right > 3 && ans_right <= 10)
			speed = 2;
		else if (ans_right > 10 && ans_right <= 20)
			speed = 3;
		else if (ans_right > 20 && ans_right <= 50)
			speed = 4;
		else if (ans_right > 50 && ans_right <= 100)
			speed = 5;
		else
			speed = 6;

		sprintf(temp, "%.f", ans_right);
		if (ans_right < 10)
			outtextxy(80, 100, temp);
		else if (ans_right < 100)
			outtextxy(60, 100, temp);
		else if (ans_right < 1000)
			outtextxy(35, 100, temp);
		else
		{
			settextstyle(70, 35, _T("Comic Sans MS"));
			outtextxy(35, 100, "999+");
		}
		//////////////////////////////////////////////////////////////////////////////

		settextcolor(BLACK);
		settextstyle(30, 15, _T("Comic Sans MS"));
		char input=0;
		/*��ѭ��*/
		for (y = 25; y <= deadline; y += speed)
		{
			
			outtextxy(x, y, content[i]);
			fill_screen_accuracy();
			settextcolor(BLACK);
			settextstyle(30, 15, _T("Comic Sans MS"));
			if (_kbhit())
			{
				input = _getch(); // ��ȡ�û�����

				key_light(input); //����

				if ((input == content[i]))
				{
					// ������ȷ�������䡱��ĸ��������
					fillrectangle(x - 5, y, x + 50, y + 35);
					ans_right++;
					break; // ����ѭ����������һ����ĸ
				}
				else if (input == 27)
				{
					break; // ����� ESC���˳���Ϸ��ѭ��
				}
				else if ((input != content[i]))
				{
					ans_wrong++;
				} //����������
			}
			Sleep(20);
			fillrectangle(x - 5, y, x + 50, y + 35);
		} //forС
		//���Բ����÷�
		fillrectangle(70, 90, 110, 130);

		/*һ����������ȥ��һ��*///������ȦȻ�����
		if (y >= deadline)
		{
			plant_life[j]--;
			ans_wrong++;
		
			 
		}
 
		/*������ʧ�˳�*///����Ӧ�ÿ�����������
		if (plant_life[j] == 1)
		{
			Sleep(100);
			fillrectangle((1344 - 890) / 2 + 20 + j * 80, 768 - 480, (1344 - 890) / 2 + 60 + j * 80, 768 - 440);
		}
		if (plant_life[j] == 0)
		{
			Sleep(100);
			fillrectangle((1344 - 890) / 2 + 20 + j * 80, 768 - 420, (1344 - 890) / 2 + 60 + j * 80, 768 - 380);
		}
		if (plant_life[j] == -1)
		{
			Sleep(200);
			break;
		}

		/*��Esc�˳�*/
		if (input == 27)
		{
			fillrectangle(x, y, x + 50, y + 35);
			break;
		}

	} 

	/*������ʱ�������˳�����*/
	time_end = clock();
	end3();
}
//��������
void help()
{
	 
}

//��߼�¼��ʾ����
void draw_record()
{
	//ģ�ⰴ������
	setfillcolor(WHITE);
	fillroundrect(40, 768 - 160, 300, 768 - 100, 10, 10);
	Sleep(100);

	cleardevice();
	putimage(0, 0, &bkg_record);

	settextcolor(WHITE);
	settextstyle(80, 40, _T("Comic Sans MS"));
	while (_getch() != 27)
		;

	game_start();
}

//��Ϸ��ѭ��
void game_start()
{

	FlushMouseMsgBuffer(); //������������

	choose = gamemode_choose();
	switch (choose)
	{
	//case 1:
	//	gm1();
	//	break;
	case 2:
		gm2();
		break;
	case 3:
		gm3();
		break;
	case 4:
		help();
		break;
	case 5:
	{
		//ģ�ⰴ������
		setfillcolor(WHITE);
		fillroundrect(1344 - 160, 768 - 80, 1344 - 40, 768 - 20, 10, 10);
		Sleep(100);

		//������˳���ťֱ�ӹرմ����˳���Ϸ
		closegraph();
		system("taskkill -f -im Coding_Until_Die.exe");
		break;
	}
	case 6:
	{
		//ģ�ⰴ������
		setfillcolor(WHITE);
		fillroundrect(40, 768 - 80, 300, 768 - 20, 10, 10);
		Sleep(100);
 
		break;
	}
	case 7:
		draw_record();
		break;
	}

	game_start();
}

int main()
{
	loadimage(&init_img, _T("bin\\source\\initial_img.jpg"), 1344, 768);   //��ȡ��ʼ���汳��ͼ
	loadimage(&bkg_img, _T("bin\\source\\background_img.jpg"), 1344, 768); //��ȡģʽѡ�񱳾�ͼ
	loadimage(&bkg_help, _T("bin\\source\\help.dat"), 1344, 768);		   //��ȡ�������汳��ͼ
	loadimage(&bkg_record, _T("bin\\source\\best_record.dat"), 1344, 768); //��ȡ��¼���汳��ͼ
	loadimage(&img_plant, _T("bin\\source\\tuanzhi.jfif"), 40, 40);		   //��ȡ����ͼƬ
	loadimage(&img_plant2, _T("bin\\source\\tuanzhi2.jfif"), 40, 40);
	loadimage(&bkg_end1, _T("bin\\source\\fengzhi.png"), 1344, 768);		   //��ȡend1
	loadimage(&bkg_end2, _T("bin\\source\\fengzhi.png"), 1344, 768);		   //��ȡend2
	loadimage(&bkg_end3, _T("bin\\source\\fengzhi.png"), 1344, 768);		   //��ȡend3
																		   //���뱳�����ֲ�����
	mciSendString(_T("open bin\\source\\bgm.mp3 alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("play mymusic repeat"), NULL, 0, NULL);
	//��Ϸ����
	draw_initial();
	game_start();

	return 0;
}