//动态规划 背包问题 
//#include "stdafx.h"
#include <iostream>   
#include<cstdio>
#include<cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXL = 500+5;
const int totalW =12500*4;
const int n = 36;
int value[36] = {0};
int weight[36] = {0};

const int NODES = (24*60/15);  //96个节点
int powerAlocate[NODES] = {0};

/*
int dp[30000];
int bag[MAXL][300000] ={0};
*/

int min(int a, int b) { return a < b ? a : b; }
 

const int POWER[36][2] =  //{{300, 35428},
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
int setInputPower( int timeStart, int timeEnd, int power);
int getAveragePower();

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
	//验证只有功率恒定才是最省煤的方案
    for ( int num = 1; num <= 7; num ++)		
	{
		cout << " ===== start from n = " << num << "=======================" <<endl;
		int count = 0;
	
	 for (int i = 0; i < (n-5*num); i ++ )	
	 {
		 int power = 320 + 20*i ;
		 int increaseConsumption = 0;
		 
		 //int num = (35 - 15)/5;
		 
		 for ( int j = 0 ; j < num ; j ++)
		 {
			 increaseConsumption +=  powerIncrease( power + 100 * j);
		 }
		 
		 increaseConsumption += powerStable( power + 100 * (num -1 ));
		
        cout << " power = "<< power <<" increase power, "<< 15*num <<" mins CoalConsumption = " <<  increaseConsumption << endl;
	
	    int currentConsumption = 0;
		int getPower = findPower(((power*2 +100*num)/2));
	
	    getCoalConsumptionFromPower( getPower, currentConsumption);
	
	    cout << " power = " << getPower <<" stay, "<< 15*num << " mins CoalConsumption = " << currentConsumption*(num+1) << endl;
		
		if ( increaseConsumption - currentConsumption*(num+1) < 0 )
		{
			count ++;
			cout << "****************************************************" << endl;
			
			cout << "****************************************************" << endl;
		}
	 }
		cout << " ===== end at n = " << num << " count = " << count << "=======================" << endl;
		cout << endl;
	}
	*/
 
	/*
	int getPower = findPower(721);
	int currentConsumption = 0;
	getCoalConsumptionFromPower(getPower, currentConsumption);
	cout << " power = " << getPower <<" stay, 30 min CoalConsumption = " << currentConsumption*2 << endl;
	*/
	
	getAveragePower();
    return 0;
}

//Function initCoalConsumptionAndPower
void initCoalConsumptionAndPower()
{
	for( int i = 0; i < n; i++)
	{
		weight[i] = POWER[i][0];
        value[i] = POWER[i][1];
	}

}

//Function getCoalConsumptionFromPower
bool getCoalConsumptionFromPower(int power, int &coalConsumption)
{
	for( int i = 0; i < 37; i++)
	{
		if ( power == POWER[i][0])
		{
			coalConsumption = POWER[i][1];
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
	if ( abs(increasePower) > 200 )
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
	for (int i = 0 ; i < 35 ; i++)
	{
		int power = 320 + 20*i;
		if (( power - averagePower >= 0)
			&& abs(power - averagePower) < 20)
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
int setInputPower( int timeStart, int timeEnd, int power)
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
	
	int startPosition = timeStart*4;
	int endPosition = timeEnd*4 - 1;
	
	count = timeEnd*4 - timeStart*4;
	
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

//Function 
int getAveragePower()
{
	int averagePower = 0;
	int setPowerCount = 0; 
	int remainPowerCount = NODES;
	int remainPower = totalW;
	
	
	
	
	
	setPowerCount = setInputPower(18, 20, 320);
	remainPowerCount -= setPowerCount;
	remainPower -= setPowerCount*320; //320 should modified. 
	
	setPowerCount = setInputPower(22, 23, 400);
	remainPowerCount -= setPowerCount;
	remainPower -= setPowerCount*400; //400 should modified. 
	cout << " remainPowerCount = " << remainPowerCount << endl;
	cout << " remainPower = " << remainPower << endl;
	
	averagePower = (int)remainPower/remainPowerCount;
	cout << " averagePower = " << averagePower << endl;
	
	averagePower = findPower(averagePower);
	cout << " averagePower = " << averagePower << endl;
	
	
	//test 2 case
	//1. 320 -> average -> 400 
	int totalCoal  = 0;
	for (int i = 0; i < NODES; i++)
	{
		if( powerAlocate[i] == 0 && 
			((i > 0 && abs(powerAlocate[i-1] - averagePower) > 200)))
		{
			 if ( powerAlocate[i-1] - averagePower > 0 )
			 {
			     powerAlocate[i] = powerAlocate[i-1] - 200;
			 }
			 else
			 {
				powerAlocate[i] = powerAlocate[i-1] + 200;
			 }
		}
			else if (powerAlocate[i] == 0)
			{
				powerAlocate[i] = averagePower;
			}

	}
	
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
	
	for (int j = 0; j < NODES; j++)
	{
		cout << "index = " << j << " powerAlocate = " << powerAlocate[j] << endl;
	}
	cout << " totalCoal = " << totalCoal << endl;
	 
	
	//2. 320-> 420 
	
	
	return averagePower;
}
