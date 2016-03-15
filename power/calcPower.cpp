//3d10-1 动态规划 背包问题 
//#include "stdafx.h"
#include <iostream>   
using namespace std;   

const int N = 4; 
const int NODES = (24*60/15);  //96个节点
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
void Knapsack(int v[],int w[],int c,int n,int m[][10]); 
void Traceback(int m[][10],int w[],int c,int n,int x[]); 

bool getCoalConsumptionFromPower(int power, double &coalConsumption);

//1.程序的主要目的为根据全天总电量，结合每个负荷点的煤耗，规划处全天最佳煤耗运行图
//2.负荷改变的最短时间是15分钟，每变动一次中间值煤耗2%，
//  例如: 从320变化到340，煤耗为 (346.31 + （ 346.31 + 343.14 ）/2 * 2% )
//3. 稳定后15分钟内煤耗增加1%,
//  例如：达到340后第一个15分钟， 煤耗为 343.14 * （ 1+ 1%）
//4. 每天出力一定，可手动输入某个时间段的出力值，由程序规划剩余出力，以实现煤耗最少
//  例如： 从1点到6点，设定最低出力320，剩余由程序规划
int main() 
{ 
    int c=8;
    int v[]={0,2,1,4,3},w[]={0,1,4,2,3};//下标从1开始 
    int x[N+1]; 
    int m[10][10]; 

    cout<<"待装物品重量分别为："<<endl; 
    for(int i=1; i<=N; i++) 
    { 
        cout<<w[i]<<" "; 
    } 
    cout<<endl; 

    cout<<"待装物品价值分别为："<<endl; 
    for(int i=1; i<=N; i++) 
    { 
        cout<<v[i]<<" "; 
    } 
    cout<<endl; 

    Knapsack(v,w,c,N,m); 

    cout<<"背包能装的最大价值为："<<m[1][c]<<endl; 

    Traceback(m,w,c,N,x); 
    cout<<"背包装下的物品编号为："<<endl; 
    for(int i=1; i<=N; i++) 
    { 
        if(x[i]==1) 
        { 
            cout<<i<<" "; 
        } 
    } 
    cout<<endl; 
	
	//test
	double coalConsumption = 0.0;
	getCoalConsumptionFromPower(780, coalConsumption);
	cout<<"coalConsumption = " <<coalConsumption<<endl; 

    return 0; 
} 

void Knapsack(int v[],int w[],int c,int n,int m[][10]) 
{ 
    int jMax = min(w[n]-1,c);//背包剩余容量上限 范围[0~w[n]-1] 
    for(int j=0; j<=jMax;j++) 
    { 
        m[n][j]=0; 
    } 

    for(int j=w[n]; j<=c; j++)//限制范围[w[n]~c] 
    { 
        m[n][j] = v[n]; 
    } 

    for(int i=n-1; i>1; i--) 
    { 
        jMax = min(w[i]-1,c); 
        for(int j=0; j<=jMax; j++)//背包不同剩余容量j<=jMax<c 
        { 
            m[i][j] = m[i+1][j];//没产生任何效益 
        } 

        for(int j=w[i]; j<=c; j++) //背包不同剩余容量j-wi >c 
        { 
            m[i][j] = max(m[i+1][j],m[i+1][j-w[i]]+v[i]);//效益值增长vi   
        } 
    } 
    m[1][c] = m[2][c]; 
    if(c>=w[1]) 
    { 
        m[1][c] = max(m[1][c],m[2][c-w[1]]+v[1]); 
    } 
} 

//x[]数组存储对应物品0-1向量,0不装入背包，1表示装入背包 
void Traceback(int m[][10],int w[],int c,int n,int x[]) 
{ 
    for(int i=1; i<n; i++) 
    { 
        if(m[i][c] == m[i+1][c]) 
        { 
            x[i]=0; 
        } 
        else 
        { 
            x[i]=1; 
            c-=w[i]; 
        } 
    } 
    x[n]=(m[n][c])?1:0; 
}

//Function
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