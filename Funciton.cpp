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
	int count = 0;//用来记录顾客所在窗口 
	
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
	           		&& !windows[2].getWindowsEmpty() &&! windows[3].getWindowsEmpty())
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
							count = i;//得到当前顾客所在窗口 
							
	                  		if (windows[i].getWindowsEmpty() == true)//找到当前空的窗口并输出打印 
	                  		{
	                  			cout << "当前到来顾客在第 " << count+1 << " 窗口办理业务" << endl;
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
	                     		    		//户逗留时间 = 用户离开的时间（窗口服务当前客户结束时间）- 用户到达的时间
	                     		    		windows[i].setClientStayBankTime((windows[i].getbusinessEndTime() - client.getClientArriveTime()));//当前窗口顾客逗留时间累加

	                     		    		windows[i].setSaveMoneyNum();//当前窗口的存款办理次数+1

	                               			break;
	
	                          		case 1:
	                          			  	//设置当前窗口办理结束时间为，窗口上一个人办理完毕的时间 + 当前到来顾客需要办理的时间 
	                     		    		windows[i].setbusinessEndTime(windows[i].getBusinessStartTime() + client.getClientBusinessNameTime());
	                     		    		//户逗留时间 = 用户离开的时间（窗口服务当前客户结束时间）- 用户到达的时间
	                     		    		windows[i].setClientStayBankTime((windows[i].getbusinessEndTime() - client.getClientArriveTime()));//当前窗口顾客逗留时间累加
	                     		    		
											windows[i].setGetMoneyNum();//当前窗口的取款办理次数+1 

	                     		    		break;
	                     		    		
	                          		case 2:
	                          			 	//设置当前窗口办理结束时间为，窗口上一个人办理完毕的时间 + 当前到来顾客需要办理的时间 
	                     		    		windows[i].setbusinessEndTime(windows[i].getBusinessStartTime() + client.getClientBusinessNameTime());
	                     		    		//户逗留时间 = 用户离开的时间（窗口服务当前客户结束时间）- 用户到达的时间
	                     		    		windows[i].setClientStayBankTime((windows[i].getbusinessEndTime() - client.getClientArriveTime()));//当前窗口顾客逗留时间累加
	                     		    		
	                     		    		windows[i].setReportLossOfNum();//当前窗口的挂失办理次数+1 
	                     		    		break;
	                     		    		
	                           		case 3:
											//设置当前窗口办理结束时间为，窗口上一个人办理完毕的时间 + 当前到来顾客需要办理的时间 
	                     		    		windows[i].setbusinessEndTime(windows[i].getBusinessStartTime() + client.getClientBusinessNameTime());
	                     		    		//户逗留时间 = 用户离开的时间（窗口服务当前客户结束时间）- 用户到达的时间
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
