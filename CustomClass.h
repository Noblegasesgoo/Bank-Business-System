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

