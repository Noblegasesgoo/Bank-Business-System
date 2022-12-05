**题目要求：**
		
		设银行有四个服务窗口，一个等待队列, 每个窗口均可以办理存款、取款、挂失、还贷等业务，每种业务所需的服务时间不同，客户到达银行后，先到打号机上打号，号票上包括到达时间、编号和需要办理的业务，然后在银行内等候, 当任一服务窗口空闲时,处理等候客户中排在最前面的客户的业务。写一个上述银行业务的模拟系统,通过模拟方法求出客户在银行内逗留的平均时间和每个窗口办理的客户数及办理的每种业务数。
		基本要求：每个客户到达银行的时间和需要办理的业务随机产生，输出一天客户在银行的平均逗留时间和每个窗口每天办理的客户数和每种业务数。
		提高要求：设计图形用户界面，模拟中国银行真实的打号机操作界面，当用户选择一种业务后，能够提示排在用户前面的人数。
		测试数据：营业时间为8小时，其它模拟量自行设定。

**仅完成的基本要求：**
		
		运行软件DevC++，编译选项：-std=c++11。
		运用了C/C++的库文件。
		此次分为四个文件:
				CustomClass.h：存储提供类和结构。
				Function.cpp：提供各种统计，模拟方法的实现体。
				Menu.cpp：提供菜单方法的实现体。
				main.cpp：主函数主要就是支起逻辑框架。

**main.cpp:**
```cpp
#include <string>
#include <iostream>
#include <ctime>
#include <windows.h>
#include "CustomClass.h"

using namespace std;

int main(int argc, char** argv)
{
	srand((int)time(NULL));  //用时间作为种子对随机数进行操作
	
	welcome();
	
	try
	{
		bankStartMenu();	
	} catch (const char* msg)
		{
			cout << msg << endl;	
		} 
	
	return 0;
}
```

**CustomClass.h：**

```cpp
#pragma once
#ifndef HACKER_H_//#ifendif防止多次包含一个文件
#define HACKER_H_ 

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

//-------------------------------------------------- 银行类 ，用来提供窗口 --------------------------------------------------
class Bank
{
	private:
		int bank_open_time;//银行开始营业时间（小时） 
		int bank_closed_time;//银行结束营业时间（小时） 
		int bank_all_time;//银行总营业时间（分钟） = (银行结束营业时间（小时）- 银行开始营业时间（小时）*60) 
	
		int business_start_time;//开始办理业务时间（分钟） 
		int business_end_time;//上一个业务办理的结束时间（分钟） 
	
		int save_money_num;//存款业务办理次数
		int get_money_num;//取款业务办理次数 
		int report_loss_of_num;//挂失业务办理次数 
		int refund_num;//还款业务办理所次数
	
		int client_stay_bank_time;//顾客逗留银行的时间（分钟）
		bool windows_empty;//窗口是否为空（true：空、false：不空） 
	
	public:
		//无参初始化 
		Bank()
		{
			
		}
		
		~Bank()//析构函数 
		{
			
		}
		 
		//有参初始化 
		Bank(int open_time, int closed_time)
		{
			this->bank_open_time = open_time;
			this->bank_closed_time = closed_time;
			this->bank_all_time = this->bank_closed_time * 60 - this->bank_open_time * 60; //设置银行结束营业时间（分钟） 
	
			this->business_start_time = bank_open_time * 60;//开始办理业务时间此时初始化为银行开门时间（分钟） 
			this->business_end_time = bank_open_time * 60;//上一个业务办理的结束时间初始化，由于此时还没处理业务，所以初始化为开门时间（分钟） 
			
			this->save_money_num = 0;//存款业务办理次数
			this->get_money_num = 0;//取款业务办理次数 
			this->report_loss_of_num = 0;//挂失业务办理次数 
			this->refund_num = 0;//还款业务办理所次数
			
			this->windows_empty = false;//初始化窗口为不空也就是未开门的状态 
			
			//用户逗留时间 = 用户离开的时间（窗口服务当前客户结束时间）- 用户到达的时间
			this->client_stay_bank_time = 0; 
		}
	
		//各属性的get方法
		int getBankAllTime()//得到总时间常用 
		{
			return this->bank_all_time;
		}
	
		bool getWindowsEmpty()//得到窗口是否为空常用 
		{
			return this->windows_empty;
		}
	
		int getClientStayBankTime()//得到客户在该窗口的逗留的总时间 
		{
			return this->client_stay_bank_time;
		}
		
		int getSaveMoneyNum()
		{
			return this->save_money_num;
		}
		
		int getGetMoneyNum()
		{
			return this->get_money_num;
		}
		
		int getReportLossOfNum()
		{
			return this->report_loss_of_num;
		}
		
		int getRefundNum()
		{
			return this->refund_num;
		}
		
		int getBankOpenTime()
		{
			return this->bank_open_time;
		}
	
		int getBankClosedTime()
		{
			return this->bank_closed_time;
		}
	
		int getBusinessStartTime()
		{
			return this->business_start_time;
		}
	
		int getbusinessEndTime()
		{
			return this->business_end_time;
		}
	
		//各属性的set方法
		void setBankAllTime(int time)//设置总时间常用 
		{
			this->bank_all_time = time;
		}
	
		void setWindowsEmpty(bool status)//设置窗口是否为空常用
		{
			this->windows_empty = status;
		}
	
		void setClientStayBankTime(int time)//设置客户在该窗口逗留的总时间 
		{
			this->client_stay_bank_time += time;
		}
		
		void setSaveMoneyNum()
		{
			this->save_money_num += 1;
		}
		
		void setGetMoneyNum()
		{
			this->get_money_num += 1;
		}
		
		void setReportLossOfNum()
		{
			this->report_loss_of_num += 1;
		}
		
		void setRefundNum()
		{
			this->refund_num += 1;
		}
		
		void setBankOpenTime(int time)
		{
			this->bank_open_time = time;
		}
	
		void setBankClosedTime(int time)
		{
			this->bank_closed_time = time;
		}
	
		void setBusinessStartTime(int time)
		{
			this->business_start_time = time;
		}
	
		void setbusinessEndTime(int time)
		{
			this->business_end_time = time;
		}
};

//--------------------------------------------------顾客类 ，用来初始化队链的对象 --------------------------------------------------
class Client
{
	private:
		int client_ID;//顾客编号（无序随机） 
		int client_arrive_time_hour;//顾客到达银行的时间（小时） 
		int client_arrive_time_minutes;//顾客到达银行的时间（分钟） 
		int client_arrive_time;//顾客到达银行的总时间（分钟） 
		int business_name;//业务种类
		int business_name_time;//业务办理的需要时间 

	public:
		Client()//构造函数 
		{
			randomClient();
		}
	
		~Client()//析构函数 
		{
			
		} 
		 
		//构造函数调用的随机创建顾客的方法
		void randomClient()
		{
			this->client_ID = rand() % 10000;//初始化得到一到四位数的顾客编号 
	
			this->business_name = rand() % 4;  //任何一个客户的办理业务为业务0~3
			switch (this->business_name)	//得到客户的business_name后设置此时该顾客办理业务的时间
			{
				case 0:
					this->business_name_time = 5;//设置此时该顾客办理业务的时间
					break;
		
				case 1:
					this->business_name_time = 15;//设置此时该顾客办理业务的时间 
					break;
		
				case 2:
					this->business_name_time = 30;//设置此时该顾客办理业务的时间 
					break;
		
				case 3:
					this->business_name_time = 60;//设置此时该顾客办理业务的时间 
					break;
		
				default:
					break;
			}
	
			this->client_arrive_time_hour = rand() % 24;//顾客到达银行的时间（0~24小时） 
			this->client_arrive_time_minutes = 1 + rand() % 59;//顾客到达银行的时间（1~59分钟）
	
			//初始化总时间 = 到达小时数*60 + 到达分钟数 单位：分钟 
			this->client_arrive_time = ((this->client_arrive_time_hour * 60) + this->client_arrive_time_minutes);
		}
	
		//打印客户信息
		void showClientInfor()
		{
			cout << "----------------------------------------------------------------" << endl;
			cout << " 顾客到来，当前到来的顾客信息为：" << endl;
			cout << "客户ID:" << this->client_ID << " " << "客户到达时间：" << this->client_arrive_time_hour << "时" << this->client_arrive_time_minutes << "分" << endl;
	
			string client_business_name;//不是client类的属性，临时定义的
	
			switch (this->business_name)
			{
				case 0:
					client_business_name = "存款";//设置此时该顾客办理业务的时间 
					break;
		
				case 1:
					client_business_name = "取款";//设置此时该顾客办理业务的时间 
					break;
		
				case 2:
					client_business_name = "挂失";//设置此时该顾客办理业务的时间 
					break;
		
				case 3:
					client_business_name = "还贷";//设置此时该顾客办理业务的时间 
					break;
		
				default:
					break;
			}
	
			cout << "该客户办理的业务为：" << client_business_name << endl;
			cout << "----------------------------------------------------------------" << endl;
		}
	
		//各个属性的get方法 
		int getClientArriveTime()//常用，顾客到达银行的总时间（分钟，开始办理业务，不包括业务办理时间）
		{
			return this->client_arrive_time;
		}
	
		int getClientID()
		{
			return this->client_ID;
		}
	
		int getClientArriveTimeHour()
		{
			return this->client_arrive_time_hour;
		}
	
		int getClientArriveTimeMinutes()
		{
			return this->client_arrive_time_minutes;
		}
	
		int getClientBusinessName()
		{
			return this->business_name;
		}
		
		int getClientBusinessNameTime()
		{
			return this->business_name_time;
		}
	
		//各个属性的set方法
		void setClientArriveTime(int _a)//常用，顾客到达银行的总时间（开始办理业务，不包括业务办理时间） 
		{
			this->client_arrive_time = _a;
		}
	
		void setClientID(int _a)
		{
			this->client_ID = _a;
		}
	
		void setClientArriveTimeHour(int _a)
		{
			this->client_arrive_time_hour = _a;
		}
	
		void setClientArriveTimeMinutes(int _a)
		{
			this->client_arrive_time_minutes = _a;
		}
	
		void setClientBusinessName(int _a)
		{
			this->business_name = _a;
		}
		
		void setClientBusinessNameTime(int _a)
		{
			this->business_name_time = _a;
		}
};

//------------------------------------------等待队列-------------------------------------------------- 
struct Person
{
	Client client;//数据域：顾客类的对象 
	Person* next;//指针域 
};

class LinkedQueue
{
	private:
		Person* front;//队头指针
		Person* rear;//队尾指针 
		int length;//队链长度 

	public:
		LinkedQueue()//队链的构造函数 
		{
			Person* p = new Person;//新建一个节点 
			p->next = NULL;//令此节点的下一个节点为空
	
			front = p;//队首等于该节点 
			rear = p; //队尾等于该节点 
			
			this->length = 0; 
		}
	
		~LinkedQueue()//队链的析构函数 
		{
			Person* p = front;//初始化一个工作指针为此时的队首指针
	
			while (p != NULL)//工作指针不为空的话进行循环 
			{
				p = p->next;//工作指针后移 
				delete front;//删除工作指针后移前的节点 
				front = p;//将队首指针初始化为工作指针后移后的位置 
			}
	
			front = NULL;//队首置空 
			rear = NULL;//队尾置空 
		}
	
		/*
			入队操作方法
			参数一：client类的对象数组
			参数二：client类的对象数组的长度
			参数三：Bank类的对象，用来告知银行开门关门时间 
		*/
		void joinQueue(Client *client, int client_length, int open_time, int closed_time)
		{
			int i = 0;//控制循环 
	
			//循环入队
			//注意：银行窗口的营业开始时间和结束时间是小时，在这里判断转为分钟
					
			for (i = 0; i < client_length; i++)
			{
				//顾客能否入队是和银行窗口的营业开始时间和结束时间有关
				if ((client[i].getClientArriveTime() >= (open_time * 60)) && (client[i].getClientArriveTime() < (closed_time * 60))) 
				{
					Person* p = new Person;//新建一个工作指针
	
					p->client = client[i];//初始化数据域 
					p->next = NULL; //初始化指针域
		
					//尾插 
					rear->next = p;
					rear = p;
					
					length++;
				}
			}
		}
	
		/*
			出队队操作方法
		*/
		Client deleteQueue()
		{
			Person* p = NULL;//新建一个工作指针
			Client client;
	
			if (rear == front)//如果队首队尾指针相同的话 
			{
				throw "队空";
			} 
				
			p = front->next;//工作指针指要删除的位置 
			client = p->client;//存储出对对象 
			front->next = p->next;//队首指针的下一个节点等于出队节点的下一个节点
	
			if (p->next == NULL)//出队前队的队链长度为1的话 
			{
				rear = front;
			}

			delete p;//出队
			
			return client;
		}
	
		/*
			队链判空
			true为空，false为不空
		*/
		bool empty()
		{
			bool result = false;
	
			if (front == rear)
			{
				result = true;
			}
	
			return result;
		}
		
		/*
			得到队链长度 
		*/
		int getQueueLength()
		{
			return this->length;
		}
};

//---------------------------------------------所有函数方法--------------------------------------------
//是否准备开始下一轮模拟 
void startAnotherSimulate();
 
//打印所有窗口的每个业务的办理次数 
/*
	参数一：Bank类的名为窗口的对象数组
	参数二：该对象数组的长度 
*/
void showAllWindow(Bank *window, int window_length);

//冒泡排序，用来对客户数组按升序排序
/*
	参数一：Client类的对象数组
	参数二：对象数组的长度 
*/
void bubbleSortForClientArray(Client *client, int client_length);

//统计一天客户在银行的平均逗留时间
/*
	参数一：Bank类的对象数组
	参数二：对象数组的长度 
*/
void statisticData(Bank *window, int window_length);

//找到此时服务时间超过了银行营业时间的窗口，并将它关闭 
/*
	参数一：Bank类的名为window的对象数组
	参数二：对象数组的长度 
	参数三：银行关门时间 
*/

//欢迎方法
void welcome();

//银行菜单方法 
void bankStartMenu();
	
//银行菜单
void bankMenu(); 

//--------------------下列方法是为了辅助startWorking方法而设计的----------------------
//找到此时服务时间超过了银行营业时间的窗口，并将它关闭 
/*
	参数一：Bank类的名为window的对象数组
	参数二：对象数组的长度 
	参数三：银行关门时间 
*/ 
void setWindowStatusByBankEndTime(Bank *window, int window_length, int bank_end_time);

//找到业务办理结束时间最小的窗口 
/*
	参数一：Bank类的名为window的对象数组
	参数二：对象数组的长度 
*/
int getMinTimeByWindow(Bank *window, int window_length);

//窗口开始工作 
/*
	参数一，客户队链
	参数二，窗口数组
	参数三，窗口长度 
*/
//void startWorking(LinkedQueue client_queue, Bank *window, int window_length);//运用变量模拟线程
void startWorking(int open_time, int closed_time);//运用变量模拟线程

#endif//防止文件被重复包含  

```

**Menu.cpp：**
```cpp
#include <iostream>
#include <string>
#include <windows.h>
#include "CustomClass.h" 

using namespace std;

//欢迎方法
void welcome()
{
	system("color f9");//调整控制台背景色
	
	cout << "                    ***---------------------------------------------------------------------***" << endl;
	cout << "                                                                                               " << endl;
	cout << "                                                Welcome to                                     " << endl;
	
	Sleep(1500);//沉睡1.5秒
	
	cout << "                                                            Freedom-Bank                       " << endl;
	cout << "                                                                                               " << endl;
	cout << "                    ***---------------------------------------------------------------------***" << endl;
	
	Sleep(1500);//沉睡1.5秒
								
	cout << "                    ===========================================================================" << endl;
	cout << "                    *                                                                         *" << endl;
	cout << "                    *                       @If you fixed the time,                           *" << endl;
	cout << "                    *                       @t cannot be changed!                             *" << endl;
	cout << "                    *                                                                         *" << endl;
	cout << "                    *                       ~if you wanna changed the time,                   *" << endl;
	cout << "                    *                       you can exit the program and restarted.           *" << endl;
	cout << "                    *                                                                         *" << endl;
	cout << "                    ===========================================================================" << endl;
	
	Sleep(1000);//1秒后进入程序 
		
} 
 
//银行菜单
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

//银行菜单方法 
void bankStartMenu()
{
	int select = 0;
	
	int open_time;//银行开门时间 
	int closed_time;//银行关闭时间 
	
	cout << "                                        Please enter the bank open time (h)：";
	cin >> open_time;//设置银行开始营业时间 （小时）
	cout << endl;
	cout << "                                        Please enter the bank close time (h): " ;
	cin >> closed_time;//设置银行结束营业时间（小时）
	
	while (select != 2)
	{

		
		bankMenu();//显示银行菜单 
		cout << "                                        Please enter the select：      ";
		cin >> select;//输入选择
		
		switch (select)
		{
			case 1:
				system("cls");//清屏然后开始银行模拟 
				startWorking(open_time, closed_time);//开始模拟银行工作
				
				break;
			
			case 2:
				system("cls");//清屏然后结束 
				cout << "                                              Welcome to come next time!                                   " << endl;
				
				break;
			
			default:
				cout << "                                  Invalid input,Please try to enter the 1~3,thank you!" << endl;
				
				break;
		}
	}
	
	return ; 
} 
```
**Function.cpp**：

```cpp
#include <iostream>
#include <string>
#include <windows.h>
#include "CustomClass.h" 

using namespace std;

//------------------------------------------最主要的功能函数-------------------------------------------------- 
//是否准备开始下一轮模拟 
void startAnotherSimulate()
{
	int select = 0;
	
	cout << "Ready to leave and get another data？If you ready to leave please inputed the “1 ”：";

	while (select != 1)
	{
		cin >> select;
		
		if (select != 1)
		{
			cout << "input error,please input again（you need to inputed the  “1 ”！！！）" << endl;
		}
	} 
}

//打印所有窗口的每个业务的办理次数 
/*
	参数一：Bank类的名为窗口的对象数组
	参数二：该对象数组的长度 
*/
void showAllWindow(Bank *window, int window_length) 
{
	int i = 0;
	int count = 0;
	 
	for (i = 0; i < window_length; i++)
	{
		cout << "窗口：" << ++count << "的存款办理次数：" << window[i].getSaveMoneyNum() << " " << "取款办理次数：" << window[i].getGetMoneyNum() << " " << "挂失办理次数：" << window[i].getReportLossOfNum() << " " << "贷款办理次数：" << window[i].getRefundNum() << " " << endl;
		cout << "该窗口总计接纳人数：" << (window[i].getSaveMoneyNum() + window[i].getGetMoneyNum() + window[i].getReportLossOfNum() + window[i].getRefundNum()) << endl;
		cout << endl;
	}
}

//冒泡排序，用来对客户数组按升序排序
/*
	参数一：Client类的对象数组
	参数二：对象数组的长度 
*/
void bubbleSortForClientArray(Client *client, int client_length)
{
	int j;
	int exchange;//交换位置记录 
	int bound;//遍历区间 
	Client temp_client;//临时存储
	
	exchange = client_length - 1;//交换位置初始化，第一趟冒泡排序区间0~client_length-1 
	
	while (exchange != 0)
	{
		bound = exchange;
		exchange = 0;
		
		for (j = 0; j < bound; j++)//接下来每趟冒牌排序区间是0~bound
		{
			if (client[j].getClientArriveTime() > client[j+1].getClientArriveTime())
			{
				temp_client = client[j];
				client[j] = client[j+1];
				client[j+1] = temp_client;	
			}				
			
			exchange = j;
		}	
	} 
} 

//统计一天客户在银行的平均逗留时间
/*
	参数一：Bank类的对象数组
	参数二：对象数组的长度 
*/
void statisticData(Bank *window, int window_length)
{
	int i = 0;//用来控制循环 
	
	int client_all_stay_time = 0;//客户总的逗留时间 
	int all_client_num = 0;//今日总到客量 
	double client_average_time;//客户今日平均逗留时间 
	
	for (i = 0; i < window_length; i++)
	{
		//顾客逗留总时间为：所有窗口的客户逗留时间累加 
		client_all_stay_time += window[i].getClientStayBankTime();
		
		//今日总到客量为：所有窗口的所有业务办理量的累加
		all_client_num += (window[i].getGetMoneyNum() + window[i].getSaveMoneyNum() + window[i].getReportLossOfNum() + window[i].getRefundNum());
	}
	
	//输出窗口的信息:
	showAllWindow(window,window_length);//统计
	
	client_average_time = ((double)client_all_stay_time / (double)all_client_num);//客户一天平均逗留时间 = 客户今日总逗留时间 / 今日到客总量 
	cout << "今日客户平均逗留时间：" << client_average_time << endl; 
}

//-------------------------------------------------------------------------下列方法是辅助startWorking方法的子方法-----------------------------------------------------------------
//找到此时服务时间超过了银行营业时间的窗口，并将它关闭 
/*
	参数一：Bank类的名为window的对象数组
	参数二：对象数组的长度 
	参数三：银行关门时间 
*/
void setWindowStatusByBankEndTime(Bank *window, int window_length, int bank_end_time)
{
	int i = 0;
	for	(i = 0; i< window_length; i++)
	{
		if (window[i].getBusinessStartTime() >= bank_end_time)
		{
			window[i].setWindowsEmpty(false);	
		} 
	}
} 
					
//找到业务办理结束时间最小的窗口 
/*
	参数一：Bank类的名为window的对象数组
	参数二：对象数组的长度 
*/
int getMinTimeByWindow(Bank *window, int window_length)
{
	int i;
	int index;
	
	int min = window[0].getbusinessEndTime();
	
	for (i = 0; i < window_length; i++)
	{
	    if (min >= window[i].getbusinessEndTime())
	    {
	        min = window[i].getbusinessEndTime();
	        index = i;//记录结束时间最小的窗口下标 
	    }
	}
	
	return index;//放回窗口数组中办理时间最短的那个窗口的下标 
} 

//-------------------------------------------------------------------------下列方法是模拟银行的核心方法！！！--------------------------------------------------------------------

//窗口开始工作 
/*
	参数一，客户队链
	参数二，窗口数组
	参数三，窗口长度 
*/
void startWorking(int open_time, int closed_time)//运用变量模拟线程 
{
	//-----------------------------队链以及窗口建立-------------------------  
	const int client_array_length = 100;//顾客数组最大长度 
	const int window_length = 4;//窗口数量 
	Client client[client_array_length];//创建顾客数组 
	bubbleSortForClientArray(client, client_array_length);//对客户数组冒泡排序做入队准备 
	LinkedQueue client_queue;
	client_queue.joinQueue(client, client_array_length, open_time, closed_time);//建队 
	//用银行类建立4个窗口 
	Bank windows[window_length] = {Bank(open_time, closed_time), Bank(open_time, closed_time), Bank(open_time, closed_time), Bank(open_time, closed_time)};
	//-----------------------------队链以及窗口建立------------------------- 
	
	int i;//用来控制遍历空窗口的循环 
	int j;//用来控制遍历业务办理时间最小窗口的循环 
	
	int index_for_min = 0;//记录结束时间最小的窗口下标
	int bank_end_time = 0;//记录银行结束营业时间 
	
	int now_temp_all_time_min = 0;//记录当前办理时间最短的那个窗口的结束办理时间 
	
	bank_end_time = windows[0].getBankClosedTime() * 60;//将银行结束营业时间存储并转化为分钟表达。
		
	if(client_queue.empty() == true)
	{
		//如果等待队列一开始就为空的话那就退出 
	} else
	    {
	        while (client_queue.empty() != true && now_temp_all_time_min <= bank_end_time)//只要队列还有元素或者此时办理时间最小的窗口的总时间没超银行营业结束时间 
	        {
	        	//如果窗口都不为空 
	           	if(!windows[0].getWindowsEmpty() && !windows[1].getWindowsEmpty() 
	           		&& !windows[2].getWindowsEmpty() && !windows[3].getWindowsEmpty())
	            {
	         		index_for_min = getMinTimeByWindow(windows, window_length);//调用找最小下标的找到业务办理结束时间最小的窗口
	         		
	                windows[index_for_min].setWindowsEmpty(true);//时间最小的窗口设置为没人状态 
	                windows[index_for_min].setBusinessStartTime(windows[index_for_min].getbusinessEndTime());//将最快办理完毕的窗口的下一个业务开始办理时间设置为它上一个业务办理的结束时间 
	                now_temp_all_time_min = windows[index_for_min].getbusinessEndTime();//将此时办理时间最短的窗口的时间设置为总时间
					
					setWindowStatusByBankEndTime(windows, window_length, bank_end_time);//找到此时服务时间超过了银行营业时间的窗口，并将它关闭，意味着它不再接受客人 
					
	            } else//否则执行业务办理 
	            	{
	            		//执行出队操作
	            		Client client = client_queue.deleteQueue();//用一个临时对象来存储当前出队对象 
	            		
						//遍历找到当前空的窗口 
	               		for (i = 0; i < window_length; i++)
	               		{
							
	                  		if (windows[i].getWindowsEmpty() == true)//找到当前空的窗口并输出打印 
	                  		{
	                  			cout << "当前到来顾客在第 " << i+1 << " 窗口办理业务" << endl;
	                  			client.showClientInfor();//打印当前办理业务的客户的票的信息
								cout << endl;
	            				cout << endl;  
	                  			
	                  			//如果此时到达该窗口的用户的时间远大于窗口上一个业务办理完毕的时间（也就是该窗口业务下一个业务开始时间） 
	                  			//那么就将该业务下一个业务开始时间 = 下一个顾客到来的时间 
 	                  			if (client.getClientArriveTime() > windows[i].getBusinessStartTime())
	                  			{
	                  				windows[i].setBusinessStartTime(client.getClientArriveTime());	
								}
								  
	                    		windows[i].setWindowsEmpty(false);//将该窗口设置为有人状态 

	                    		switch (client.getClientBusinessName())//运用当前出队对象的得到办理的业务方法来得到当前出队用户在该窗口办理的业务种类以及逗留时间和当前窗口该业务办理结束时间。 
	                     		{
	                     		    case 0:
	                     		    		//设置当前窗口办理结束时间为，窗口上一个人办理完毕的时间 + 当前到来顾客需要办理的时间 
	                     		    		windows[i].setbusinessEndTime(windows[i].getBusinessStartTime() + client.getClientBusinessNameTime());
	                     		    		//用户逗留时间 = 用户离开的时间（窗口服务当前客户结束时间）- 用户到达的时间
	                     		    		windows[i].setClientStayBankTime((windows[i].getbusinessEndTime() - client.getClientArriveTime()));//当前窗口顾客逗留时间累加

	                     		    		windows[i].setSaveMoneyNum();//当前窗口的存款办理次数+1

	                               			break;
	
	                          		case 1:
	                          			  	//设置当前窗口办理结束时间为，窗口上一个人办理完毕的时间 + 当前到来顾客需要办理的时间 
	                     		    		windows[i].setbusinessEndTime(windows[i].getBusinessStartTime() + client.getClientBusinessNameTime());
	                     		    		//用户逗留时间 = 用户离开的时间（窗口服务当前客户结束时间）- 用户到达的时间
	                     		    		windows[i].setClientStayBankTime((windows[i].getbusinessEndTime() - client.getClientArriveTime()));//当前窗口顾客逗留时间累加
	                     		    		
											windows[i].setGetMoneyNum();//当前窗口的取款办理次数+1 

	                     		    		break;
	                     		    		
	                          		case 2:
	                          			 	//设置当前窗口办理结束时间为，窗口上一个人办理完毕的时间 + 当前到来顾客需要办理的时间 
	                     		    		windows[i].setbusinessEndTime(windows[i].getBusinessStartTime() + client.getClientBusinessNameTime());
	                     		    		//用户逗留时间 = 用户离开的时间（窗口服务当前客户结束时间）- 用户到达的时间
	                     		    		windows[i].setClientStayBankTime((windows[i].getbusinessEndTime() - client.getClientArriveTime()));//当前窗口顾客逗留时间累加
	                     		    		
	                     		    		windows[i].setReportLossOfNum();//当前窗口的挂失办理次数+1 
	                     		    		break;
	                     		    		
	                           		case 3:
											//设置当前窗口办理结束时间为，窗口上一个人办理完毕的时间 + 当前到来顾客需要办理的时间 
	                     		    		windows[i].setbusinessEndTime(windows[i].getBusinessStartTime() + client.getClientBusinessNameTime());
	                     		    		//用户逗留时间 = 用户离开的时间（窗口服务当前客户结束时间）- 用户到达的时间
	                     		    		windows[i].setClientStayBankTime((windows[i].getbusinessEndTime() - client.getClientArriveTime()));//当前窗口顾客逗留时间累加
	                     		    		
	                     		    		windows[i].setRefundNum();//当前窗口的贷款办理次数+1 
	                     		    		break;
	                     		    		
	                       			default:
	                       					cout << "error！" << endl;
	                       					break; 
	                       		}
							}
	                        
	                   	}
	                }
	                
	            Sleep(500);//每执行一次循环就睡眠0.5秒模拟顾客缓缓到来 
	            
	    	}
	    	
	    		cout << "Today's data generation is complete :" << endl;
				statisticData(windows, window_length);
				startAnotherSimulate();
		}
}
```
