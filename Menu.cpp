#include <iostream>
#include <string>
#include <windows.h>
#include "CustomClass.h" 

using namespace std;

//��ӭ����
void welcome()
{
	system("color f9");//��������̨����ɫ
	
	cout << "                    ***---------------------------------------------------------------------***" << endl;
	cout << "                                                                                               " << endl;
	cout << "                                                Welcome to                                     " << endl;
	
	Sleep(1500);//��˯1.5��
	
	cout << "                                                            Freedom-Bank                       " << endl;
	cout << "                                                                                               " << endl;
	cout << "                    ***---------------------------------------------------------------------***" << endl;
	
	Sleep(1500);//��˯1.5��
								
	cout << "                    ===========================================================================" << endl;
	cout << "                    *                                                                         *" << endl;
	cout << "                    *                       @If you fixed the time,                           *" << endl;
	cout << "                    *                       @t cannot be changed!                             *" << endl;
	cout << "                    *                                                                         *" << endl;
	cout << "                    *                       ~if you wanna changed the time,                   *" << endl;
	cout << "                    *                       you can exit the program and restarted.           *" << endl;
	cout << "                    *                                                                         *" << endl;
	cout << "                    ===========================================================================" << endl;
	
	Sleep(1000);//1��������� 
		
} 
 
//���в˵�
void bankMenu()
{
	system("cls");
	system("color f9");
	cout << "                    ===========================================================================" << endl;
	cout << "                    |                                                                         |" << endl;
	cout << "                    |                          ------Freedom-Bank------                       |" << endl;
	cout << "                    |                                                                         |" << endl;
	cout << "                    |                                                                         |" << endl;
	cout << "                    |                         Enter 1 to begin to simulate                    |" << endl;
	cout << "                    |                         Enter 2 to quit system                          |" << endl;
	cout << "                    ===========================================================================" << endl;
}

//���в˵����� 
void bankStartMenu()
{
	int select = 0;
	
	int open_time;//���п���ʱ�� 
	int closed_time;//���йر�ʱ�� 
	
//	int client_array_length = 100;//�˿�������󳤶� 
//	int window_length = 4;//�������� 
	
	cout << "                                        Please enter the bank open time (h)��";
	cin >> open_time;//�������п�ʼӪҵʱ�� ��Сʱ��
	cout << endl;
	cout << "                                        Please enter the bank close time (h): " ;
	cin >> closed_time;//�������н���Ӫҵʱ�䣨Сʱ��
	
	while (select != 2)
	{
//		Client client[client_array_length];//�����˿����� 
//		bubbleSortForClientArray(client, client_array_length);//�Կͻ�����ð�����������׼�� 
//		
//		LinkedQueue client_queue;
//		client_queue.joinQueue(client, client_array_length, open_time, closed_time);//���� 
//		
//		//�������ཨ��4������ 
//		Bank windows[window_length] = {Bank(open_time, closed_time), Bank(open_time, closed_time), Bank(open_time, closed_time), Bank(open_time, closed_time)};
		
		bankMenu();//��ʾ���в˵� 
		cout << "                                        Please enter the select��      ";
		cin >> select;//����ѡ��
		
		switch (select)
		{
			case 1:
				system("cls");//����Ȼ��ʼ����ģ�� 
//				startWorking(client_queue, windows, window_length);//��ʼģ�����й���
				startWorking(open_time, closed_time);//��ʼģ�����й���
				
				break;
			
			case 2:
				system("cls");//����Ȼ����� 
				cout << "                                              Welcome to come next time!                                   " << endl;
				
				break;
			
			default:
				cout << "                                  Invalid input,Please try to enter the 1~3,thank you!" << endl;
				
				break;
		}
	}
	
	return ; 
} 
