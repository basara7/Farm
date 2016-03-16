//��̬�滮 �������� 
//#include "stdafx.h"
#include <iostream>   
#include<cstdio>
#include<cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXL = 500+5;
const int totalW = 60;
const int n = 2;
const int value[2] = {1, 30};
const int weight[2]= {1, 50};
int dp[10005];
int min(int a, int b) { return a < b ? a : b; }
 
const int NODES = (24*60/15);  //96���ڵ�
const double POWER[37][2] ={{300, 354.28},
{320, 346.31},
{340, 343.14},
{360, 340.86},
{380, 338.26},
{400, 334.92},
{420, 332.15},
{440, 333.14},
{460, 330.95},
{480, 323.03},
{500, 324.81},
{520, 325.81},
{540, 320.41},
{560, 316.12},
{580, 318.04},
{600, 314.53},
{620, 313.28},
{640, 313.57},
{660, 307.75},
{680, 307.15},
{700, 306.18},
{720, 305.35},
{740, 304.86},
{760, 305.35},
{780, 300.66},
{800, 301.74},
{820, 301.32},
{840, 299.13},
{860, 297.12},
{880, 294.51},
{900, 294.52},
{920, 295.98},
{940, 296.33},
{960, 296.79},
{980, 295.27},
{1000, 297.23},
{1020, 298.2}};

bool getCoalConsumptionFromPower(int power, double &coalConsumption);

//1.�������ҪĿ��Ϊ����ȫ���ܵ��������ÿ�����ɵ��ú�ģ��滮��ȫ�����ú������ͼ
//2.���ɸı�����ʱ����15���ӣ�ÿ�䶯һ���м�ֵú��2%��
//  ����: ��320�仯��340��ú��Ϊ (346.31 + �� 346.31 + 343.14 ��/2 * 2% )
//3. �ȶ���15������ú������1%,
//  ���磺�ﵽ340���һ��15���ӣ� ú��Ϊ 343.14 * �� 1+ 1%��
//4. ÿ�����һ�������ֶ�����ĳ��ʱ��εĳ���ֵ���ɳ���滮ʣ���������ʵ��ú������
//  ���磺 ��1�㵽6�㣬�趨��ͳ���320��ʣ���ɳ���滮

int main(){
        dp[0] = 0;
		int bag[MAXL][MAXL] ={0};
        for(int i = 1; i <= totalW; i++) dp[i] = INF;
        //---
        for(int i = 0; i < n; i++){
            for(int j = weight[i]; j <= totalW; j++){
                    dp[j] = min(dp[j-weight[i]]+value[i], dp[j]);
					bag[i+1][j] = 1;
            }
        }
		
        if(dp[totalW] == INF) 
		{
			printf("This is impossible.\n");
		}
        else
		{			
			printf("The minimum amount of money in the piggy-bank is %d.\n", dp[totalW]);
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
		

    return 0;
}

//Function getCoalConsumptionFromPower
bool getCoalConsumptionFromPower(int power, double &coalConsumption)
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


