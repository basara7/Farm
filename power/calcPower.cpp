#include <iostream>   
#include <cstdio>
#include <cstring>
#include <fstream>
#include <stdlib.h>
using namespace std;

#define MAXINTERVAL 200
#define LOWESTPOWER 320
#define HIGHESTPOWER 1020
const int n = 36;
const int calcn = 71;
int value[calcn] = {0};
int weight[calcn] = {0};

const int NODES = (24*60/15);  //96个节点
int powerAlocate[NODES] = {0};
int power10MW[calcn][2] = {0};

int remainPowerCount = NODES;
int totalW = 0;
int remainPower = 0;


//const int INF = 0x3f3f3f3f;
//const int MAXL = 500+5;
/*
int dp[30000];
int bag[MAXL][300000] ={0};
*/

int min(int a, int b) { return a < b ? a : b; }
 

const int POWER[n][2] =  //{{300, 35428},
{{320, 34631},
{340, 34314},
{360, 34086},
{380, 33826},
{400, 33492},
{420, 33215},
{440, 33314},
{460, 33095},
{480, 32303},
{500, 32481},
{520, 32581},
{540, 32041},
{560, 31612},
{580, 31804},
{600, 31453},
{620, 31328},
{640, 31357},
{660, 30775},
{680, 30715},
{700, 30618},
{720, 30535},
{740, 30486},
{760, 30535},
{780, 30066},
{800, 30174},
{820, 30132},
{840, 29913},
{860, 29712},
{880, 29451},
{900, 29452},
{920, 29598},
{940, 29633},
{960, 29679},
{980, 29527},
{1000, 29723},
{1020, 29820}};

void initCoalConsumptionAndPower();
bool getCoalConsumptionFromPower(int power, int &coalConsumption);
int powerIncrease(int power, int increasePower);
int powerStable (int power);
int findPower (int averagePower);
int setInputPower( float timeStart, float timeEnd, int power);
int getAveragePower();
void saveToFile();
void splitToPower10MW();
bool inputAndCheck();

/*
//1.程序的主要目的为根据全天总电量，结合每个负荷点的煤耗，规划处全天最佳煤耗运行图
//2.负荷改变的最短时间是15分钟，每变动一次中间值煤耗2%，
//  例如: 从320变化到340，煤耗为 (346.31 + （ 346.31 + 343.14 ）/2 * 2% )
//3. 稳定后15分钟内煤耗增加1%,
//  例如：达到340后第一个15分钟， 煤耗为 343.14 * （ 1+ 1%）
//4. 每天出力一定，可手动输入某个时间段的出力值，由程序规划剩余出力，以实现煤耗最少
//  例如： 从1点到6点，设定最低出力320，剩余由程序规划


//结论：发电功率保持恒定时最省煤
//设计： 每天的总发电量 - 规定时间的规定发电量（需要注意功率跳变时的煤耗），
//可以得到剩余时间内需要完成的发电量，
//将发电量除以剩余的节点数，得到平均值跟表格里的功率值对比，找到最接近的功率值
//根据程序计算，只有保持某个功率值一直不变是最省煤的
//所以，理论上保持这个功率值即可
*/

int main(){
	/*
	//完全背包取最小值算法
        dp[0] = 0;
        for(int i = 1; i <= totalW; i++) dp[i] = INF;
        //---
		initCoalConsumptionAndPower();
        for(int i = 0; i < n; i++){
            for(int j = weight[i]; j <= totalW; j++){
                    dp[j] = min(dp[j-weight[i]]+value[i], dp[j]);
					bag[i+1][j] = 1;
            }
        }
		
        if(dp[totalW] == INF) 
		{
			cout <<"This is impossible" << endl;
		}
        else
		{			
			cout<< "The minimum amount of money in the piggy-bank is" <<dp[totalW] <<endl;
			int i = n, j = totalW;  
			while(i > 0 && j > 0)  
            {  
               if(bag[i][j] == 1)  
               {
                  cout << weight[i-1] << " ";  
                  j -= weight[i-1];  
               }  
               else  
                  i--;  
            }  
		    cout << endl; 
		}
	*/	

	/*
	15*10 mins 
	20   341428
    40   334390
    100  330154
    200  328857

    15*11 mins
    20   374334
    40   366971
    100  362735
    200  361438
	*/
	
	//验证只有功率恒定才是最省煤的方案
	/*
		cout << " ===== start from  320 interval 20 =======================" <<endl;
		
		 int power = 320 ;
		 int increaseConsumption = 0;
		 
		 //int num = (35 - 15)/5;
		 
		 for ( int j = 0 ; j < 1 ; j ++)
		 {
			 increaseConsumption +=  powerIncrease( power+ 200*j, 200);
		 }
		 
		 increaseConsumption += powerStable( power + 200 );
		 
	     int currentConsumption = 0;
	     getCoalConsumptionFromPower(power + 200 , currentConsumption);
		 
		increaseConsumption += currentConsumption*9;
		
        cout << " power = "<< power <<" increase power, "<< 15*10 <<" mins CoalConsumption = " <<  increaseConsumption << endl;
	
	
	    //getCoalConsumptionFromPower( getPower, currentConsumption);
	
	    //cout << " power = " << getPower <<" stay, "<< 15*num << " mins CoalConsumption = " << currentConsumption*(num+1) << endl;
	*/	

	
 
	/*
	int getPower = findPower(721);
	int currentConsumption = 0;
	getCoalConsumptionFromPower(getPower, currentConsumption);
	cout << " power = " << getPower <<" stay, 30 min CoalConsumption = " << currentConsumption*2 << endl;
	*/
	
	splitToPower10MW();
	if ( inputAndCheck())
	{
		if (getAveragePower())
		{
		    cout << "计算完毕，请检查软件目录下的power.txt文件" << endl;
		}
		else
		{
			cout << "计算失败，请重新检查输入是否正确" << endl;
		}
	}
	system("pause");
    return 0;
}

//Function initCoalConsumptionAndPower
void initCoalConsumptionAndPower()
{
	for( int i = 0; i < calcn; i++)
	{
		weight[i] = power10MW[i][0];
        value[i] = power10MW[i][1];
	}

}

//Function getCoalConsumptionFromPower
bool getCoalConsumptionFromPower(int power, int &coalConsumption)
{
	for( int i = 0; i < calcn; i++)
	{
		if ( power == power10MW[i][0])
		{
			coalConsumption = power10MW[i][1];
			return true;
		}
	}
	return false;
}

//Function powerIncrease
int powerIncrease(int power, int increasePower)
{
	int coalConsumption = 0;
	int nextCoalConsumption = 0;
	int currentConsumption = 0;
	//15分钟的功率变化量最大为200
	if ( abs(increasePower) > MAXINTERVAL )
	{
		cout << "out of range!!!!" << endl;
		return 0;
	}
	int nextPower = power + increasePower;
	
	if ( getCoalConsumptionFromPower( power, coalConsumption) 
		&&  getCoalConsumptionFromPower( nextPower, nextCoalConsumption) )
		{
			currentConsumption = (int)(coalConsumption + ((coalConsumption + nextCoalConsumption)/2)* 0.02);
			return currentConsumption;
		}
		else
		{
			return 0;
		}
}

//Function powerStable
int powerStable(int power)
{
	int coalConsumption = 0;
	int currentConsumption = 0;
	if ( getCoalConsumptionFromPower( power, coalConsumption) )
	{
	    currentConsumption = (int) (coalConsumption * (1 + 0.01));
		return currentConsumption;
	}
	else
	{
		return 0;
	}
}

//Function findPower
int findPower (int averagePower)
{
	for (int i = 0 ; i < 70 ; i++)
	{
		int power = LOWESTPOWER + 10*i;
		if (( power - averagePower >= 0)
			&& abs(power - averagePower) < 10)
			{
				cout << "averagePower is " << averagePower << " then power should be " << power << endl;
				return power;
			}
			else 
			{
				continue; 
			}
	}
	return 0;
}

//Function: setInputPower
int setInputPower( float timeStart, float timeEnd, int power)
{
	int count = 0;
	if (( timeStart < 0 || timeStart > 24)
		|| (timeEnd < 0 || timeEnd > 24 ))
		{
			cout << "out of range!!!!" << endl;
			return 0;
		}
	if (timeStart > timeEnd)
	{
		cout << "timeStart is later than timeEnd!!!!" << endl;
			return 0;
	}
	
	int startPosition = (int)(timeStart*4);
	int endPosition = (int)(timeEnd*4) - 1;
	
	count = (int)(timeEnd*4) - (int)(timeStart*4);
	
	for (int i = startPosition; i <= endPosition; i++)
	{
		powerAlocate[i] = power;
	}
	
	//print powerAlocate
	/*
	for (int j = 0; j < NODES; j++)
	{
		cout << "index = " << j << " powerAlocate = " << powerAlocate[j] << endl;
	}
	*/
	
	return count;
}

//Function getAveragePower
int getAveragePower()
{
	int averagePower = 0;
	
	averagePower = (int)remainPower/remainPowerCount;
	cout << " averagePower = " << averagePower << endl;
	
	if ( averagePower >= LOWESTPOWER && averagePower <= HIGHESTPOWER)
	{
	    averagePower = findPower(averagePower);
	    cout << " find : averagePower = " << averagePower << endl;
	}
	else
	{
		cout <<" can't find the averagePower!! "<<endl;
		return 0;
	}
	
	//test 1 case
	//1. 320 -> average
	int totalCoal  = 0;
	for (int i = 0; i < NODES; i++)
	{
		if( powerAlocate[i] == 0)
		{
			powerAlocate[i] = averagePower;
		}
		else
		{
			continue;
		}
		
	}
	
	for (int i = 0; i < NODES; i++)
	{
		if ( (i < NODES-1) && (abs(powerAlocate[i] - powerAlocate[i+1]) > MAXINTERVAL) )
		{
			if ( powerAlocate[i] == averagePower )
			{
				
				if ( powerAlocate[i] - powerAlocate[i+1] > 0 ) 
				{
					powerAlocate[i] = powerAlocate[i+1] + MAXINTERVAL;
				}
				else
				{
					powerAlocate[i] = powerAlocate[i+1] - MAXINTERVAL;
				}
				
				for ( int j = 0; j < i ; j++)
				{
					if ( abs(powerAlocate[i-j] - powerAlocate[i-j-1]) > MAXINTERVAL)
					{
						if ( powerAlocate[i-j-1] - powerAlocate[i-j] > 0 ) 
				        {
					        powerAlocate[i-j-1] = powerAlocate[i-j] + MAXINTERVAL;
				        }
				        else
				        {
							powerAlocate[i-j-1] = powerAlocate[i-j] - MAXINTERVAL;
				        }
					}
				}
				
			}
			else if ( powerAlocate[i+1] == averagePower )
			{
				if ( powerAlocate[i] - powerAlocate[i+1] > 0 )
				{
					powerAlocate[i+1] = powerAlocate[i] - MAXINTERVAL;
				}
				else
				{
					powerAlocate[i+1] = powerAlocate[i] + MAXINTERVAL;
				}
			}
			else
			{
				cout << "Invaild input power!" << endl;
				return -1;
			}
		}
	}
	
	
	
	remainPower = totalW;
	remainPowerCount = NODES;
	
	for (int i = 0; i < NODES; i++)
	{
		if ( averagePower != powerAlocate[i] )
		{
			remainPower -=  powerAlocate[i];
			remainPowerCount--;
		}
		else
		{
			powerAlocate[i] = 0;
		}
	}
	
	cout << " ===================================== " << endl;
	cout << " The second round : remainPowerCount = " << remainPowerCount << endl;
	cout << " The second round : remainPower = " << remainPower << endl;
	averagePower = (int)remainPower/remainPowerCount;
	cout << " The second round : averagePower = " << averagePower << endl;
	
	averagePower = findPower(averagePower);
	cout << " The second round : find averagePower = " << averagePower << endl;
	
	for (int i = 0; i < NODES; i++)
	{
		if ( 0 == powerAlocate[i])
		{
			 powerAlocate[i] = averagePower;
		}
		else
		{
			continue;
		}
	}
	
	
	//calculate the actual coal
	for (int i = 0; i < NODES; i++)
	{
		bool changeFlag = false;
		if ( i < NODES-1 && powerAlocate[i] !=  powerAlocate[i+1])
		{
			totalCoal += powerIncrease(powerAlocate[i], (powerAlocate[i+1] - powerAlocate[i]));
			changeFlag = true;
		}
		else if ((changeFlag == true && i < NODES-1 && powerAlocate[i] ==  powerAlocate[i+1]) 
			|| (changeFlag == true && i == NODES-1)
			|| i == 0)
		{
			totalCoal += powerStable(powerAlocate[i]);
			changeFlag = false;
		}
		else 
		{
			int CoalConsumption = 0; 
			getCoalConsumptionFromPower( powerAlocate[i], CoalConsumption );
			totalCoal += CoalConsumption;
		}
		
	}
	
	
	
	//write to file
	ofstream outfile("power.txt");
	
	int totalPower = 0;
	for (int j = 0; j < NODES; j++)
	{
		//cout << "index = " << j << " powerAlocate = " << powerAlocate[j] << endl;
		
		outfile <<  powerAlocate[j] << endl;
		
		totalPower += powerAlocate[j];
	}
	
	outfile.close();
	
	cout << " 当天的总耗煤量为  " << totalCoal << endl;
	
	cout << " 原始输入发电量为： " << ((float)(totalW)/40) << " 实际发电量为：" << ((float)(totalPower)/40) << endl;

	return averagePower;
}

//Function 
void splitToPower10MW()
{
	int Index = 0;
	int count = 0;
	
	for ( int i = 0; i < n; i++ )
	{
		power10MW[Index][0] = POWER[i][0];
		power10MW[Index][1] = POWER[i][1];
		
	    if ( i < (n - 1) )
		{			
		    power10MW[Index+1][0] = (int)(POWER[i][0]+POWER[i+1][0])/2;
		    power10MW[Index+1][1] = (int)(POWER[i][1]+POWER[i+1][1])/2;
		}
		
		Index += 2;
	}
	
	for (int j = 0; j < calcn; j++)
	{
		if ( 0 != power10MW[j][0])
		{
			//cout << "weight = " << power10MW[j][0] << " power = " << power10MW[j][1] << endl;
		    count ++;
		}
	}
	
	//cout << "count = " << count << endl;
	
	
}

bool inputAndCheck()
{
	//输入数据：
	/*
	1.需要输入当天总发电量
	2.需要输入设定值的时间段的个数
	3.依次输入每个时间段的起止时间，例如：1点30分->1.5,1点15分->1.25,1点45分->1.75
	4.输入每个时间段的设定功率
	举例：
	设定两个时间段：1. 1点15分到5点45分  功率为320
					2. 15点30分到18点    功率为760
	输入为： 2
	         1.15 5.45
			 320
	         15.5 18
		     760
	*/
	
	float totalPower = 0;	
	cout << "请输入当天总发电量：";
	cin >> totalPower;
	totalPower = totalPower*10;
	if ( totalPower < (LOWESTPOWER * 24) || totalPower > (HIGHESTPOWER * 24) )
	{
		cout << "输入错误，请检查总发电量数值是否正确" << endl;
		return false;
	}
	totalW = (int) (totalPower*4);
	remainPower = totalW;
	
    int inputCount = 0;
	cout << "请输入需要设定的时间段的个数(最大设置个数为9， 如果没有请输入0)：";
	cin >> inputCount;
	
	if ( inputCount < 0 || inputCount > 10)
	{
		cout << "Wrong input!" << endl;
		return false;
	}
	
	if ( !inputCount )
	{
		return true;
	}
	
	cout << endl;
	cout << "依次输入每个时间段的起止时间和设定功率"<<endl;
	for ( int i = 0; i < inputCount; i ++ )
	{
		float timeStart =0.0;
		float timeEnd = 0.0;
		int power = 0;
		cout << "第" <<(i+1)<<"个时间段:"<<endl;
		cin >> timeStart >> timeEnd >> power;
		
		/*
		cout << "test ----------" << endl;
		cout << timeStart <<endl;
		cout << timeEnd << endl;
		cout << power <<endl;
		*/
		
		//check 
	    if ( timeStart >= timeEnd )
		{
			cout << "输入错误，请检查起止时间!!"<< endl;
			return false;
		}
		if ( power < LOWESTPOWER || power > HIGHESTPOWER )
		{
			cout << "输入错误，请检查功率值的范围（320~1020）!!"<< endl;
			return false;
		}
		
		//set power
		int setPowerCount = setInputPower(timeStart, timeEnd, power);
	    remainPowerCount -= setPowerCount;
	    remainPower -= setPowerCount * power;
	    
		/*
		cout << "test ----------" << endl;
		cout << " remainPowerCount = " << remainPowerCount << endl;
	    cout << " remainPower = " << remainPower << endl;
		*/
	}
	
	cout << "输入完毕，开始计算......" << endl;
	return true;
}
