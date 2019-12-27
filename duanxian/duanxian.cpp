#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "LBCS.h"

using namespace std;

//生成的dll及相关依赖dll请拷贝到通达信安装目录的T0002/dlls/下面,再在公式管理器进行绑定

void set_lbcs_data(int len, float* outs, float* code, float* highs, float* ztqks)
//设置数据
{
	LBCS::set_data(len, outs, code, highs, ztqks);
}

void lbcs(int len, float* outs, float* code, float* n, float* gap)
{
	auto lbcs = LBCS::get(code);
	lbcs->calculate_lbcs(len, outs, n, gap);
}

void df(int len, float* outs, float* code, float* closes, float*)
{
	auto lbcs = LBCS::get(code);
	lbcs->calculate_df(len, outs, closes);
}

//加载的函数
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{ 1,(pPluginFUNC)&set_lbcs_data },
	{ 2,(pPluginFUNC)&lbcs },
	{ 3,(pPluginFUNC)&df },
	{0,NULL},
};

//导出给TCalc的注册函数
BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun)
{
	if(*pFun==NULL)
	{
		(*pFun)=g_CalcFuncSets;
		return TRUE;
	}
	return FALSE;
}
