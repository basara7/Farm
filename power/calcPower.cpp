//��̬�滮 �������� 
//#include "stdafx.h"
#include <iostream>   
#include<cstdio>
#include<cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXL = 500+5;
const int totalW =50860;
const int n = 35;
int value[35] = {0};
int weight[35] = {0};
int dp[30000];
int bag[MAXL][300000] ={0};
int min(int a, int b) { return a < b ? a : b; }
 
const int NODES = (24*60/15);  //96���ڵ�
const int POWER[35][2] =  //{{300, 35428},
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
{1000, 29723}};
//{1020, 29820}};

void initCoalConsumptionAndPower();

//1.�������ҪĿ��Ϊ����ȫ���ܵ��������ÿ�����ɵ��ú�ģ��滮��ȫ�����ú������ͼ
//2.���ɸı�����ʱ����15���ӣ�ÿ�䶯һ���м�ֵú��2%��
//  ����: ��320�仯��340��ú��Ϊ (346.31 + �� 346.31 + 343.14 ��/2 * 2% )
//3. �ȶ���15������ú������1%,
//  ���磺�ﵽ340���һ��15���ӣ� ú��Ϊ 343.14 * �� 1+ 1%��
//4. ÿ�����һ�������ֶ�����ĳ��ʱ��εĳ���ֵ���ɳ���滮ʣ���������ʵ��ú������
//  ���磺 ��1�㵽6�㣬�趨��ͳ���320��ʣ���ɳ���滮

int main(){
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


