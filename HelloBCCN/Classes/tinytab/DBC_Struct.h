#pragma once

#include "BaseType.h"

#define DBC_GENERAL 1
struct _DBC_GENERAL
{
	// 编号	
	int id;
	// 姓名
	char* name;
	// 职业
	int zhiYe;
	// 职业名称
	char* zhiYeMingCheng;
	// 攻击属性
	int gongJiShuXing;
	// 姓别
	int xingBie;
	// 武力
	int	wuLi;
	// 智力
	int	zhiLi;
	// 体力
	int	tiLi;
	// 速度
	int	minJie;
	// 星级
	float xingJi;
	// 暴击率
	float BaoJiLv;
	// 格挡率
	float geDangLv;
	// 闪避率
	float shanBiLv;
	// 命中率
	float mingZhongLv;
	// 识破率
	float shiPoLv;
	// 暴击伤害
	int baoJiShangHai;
	// 天赋
	char* tianFu;
	// 技能
	char* JiNeng;
	// 技能特效 
	char* jiNengTeXiao;
	// 头像
	char* tuPian;
	// 动画
	char* dongHua;
};

#define DBC_SOLIDER 2
struct _DBC_SOLIDER
{
	// 编号
	int id;
	// 姓名
	char* name;
	// 动画
	char* dongHua;
	// 攻击
	int gongJi;
	// 生命
	int shengMing;
	// 级别
	int jieBie;
};

#define DBC_FORMATION 3
struct _DBC_FORMATION
{
	// 编号
	int id;
	// 姓名
	char* name;
	// 图片
	char* tuPian;
};

#define DBC_EQUIPMENT 4
struct _DBC_EQUIPMENT
{
	// 编号
	int id;
	// 名字
	char* name;
	// 种类名称
	char* zhongLeiMingCheng;
	// 种类
	int zhongLei;
	// 开启级数
	int kaiQiJiShu;
	// 强化等级
	int qiangHuaDengJi;
	// 职业需求
	char* zhiYeXuQiu;
	// 性别
	int xingBie;
	// 初始点数 
	int chuShiDianShu;
	// 图片
	char* tuPian;
	// 描述
	char* miaoShu;
	// 卖出价格
	int maiChuJiaGe;
};

#define DBC_SKILL 5
struct _DBC_SKILL
{
	// 编号
	int id;
	// 名字
	char* name;
};

#define DBC_GEM 6
struct _DBC_GEM
{
	// 编号
	int id;
	// 名称
	char* name;
	// 种类
	int zhongLei;
	// 图片
	char* tuPian;
	// 描述
	char* miaoShu;
	// 卖出价格
	int maiChuJiaGe;
};

#define DBC_SOUL_BEAD 7
struct _DBC_SOUL_BEAD 
{
	// 编号	
	int id;
	// 名称	
	char* name;
	// 种类
	int zhongLei;
	// 属性值	
	float shuXingZhi;
	// 等级
	int dengJi;
	// 开启等级	
	int kaiQiJiShu;
	// 动画
	char* dongHua;
};

#define DBC_RIDE 8
struct _DBC_RIDE
{
	// 编号	
	int id;
	// 名字
	const char* name;
	// 图片
	const char* tuPian;
	// 星级	
	int xingJi;
	// 初始攻击
	int chuShiGongJi;
	// 初始防御
	int chuShiFangYu;
	// 初始生命
	int chuShiShengMing;
};

#define DBC_TELENT 9

struct _DBC_TELENT
{
	// 编号	
	int id;
	// 名称	
	char* name;
	// 加成属性	
	char* jiaChengShuXing;
	// 第一个点
	int diYiGeDian;
	// 第二个点
	int diErGeDian;
	// 第三个点
	int diSanGeDian;
	// 第四个点
	int diSiGeDian;
	// 第五个点
	int diWuGeDian;
	// 第六个点
	int diLiuGeDian;
	// 第七个点
	int diQiGeDian;
	// 第八个点
	int diBaGeDian;
	// 第九个点
	int diJiuGeDian;
	// 第十个点
	int diShiGeDian;
	// 第十一个点
	int diShiYiGeDian;
	// 第十二个点
	int diShiErGeDian;
	// 第十三个点
	int diShiSanGeDian;
	// 第十四个点
	int diShiSiGeDian;
	// 第十五个点
	int diShiWuGeDian;
	// 第十六个点
	int diShiLiuGeDian;
	// 第十七个点
	int diShiQiGeDian;
	// 第十八个点
	int diShiBaGeDian;
	// 第十九个点
	int diShiJiuGeDian;
	// 第二十个点
	int	diErShiGeDian;
};

#define DBC_GEM_STRENGTHEN 10
struct _DBC_GEM_STRENGTHEN
{
	// 编号
	int id;
	// 名称
	char* name;
	// 加成属性
	char* jiaChengShuXing;
	// 一级属性值
	int yiJiShuXingZhi;
	// 二级属性值
	int erJiShuXingZhi;
	// 三级属性值
	int sanJiShuXingZhi;
	// 四级属性值
	int siJiShuXingZhi;
	// 五级属性值
	int wuJiShuXingZhi;
	// 六级属性值
	int liuJiShuXingZhi;
	// 七级属性值
	int qiJiShuXingZhi;
	// 八级属性值
	int baJiShuXingZhi;
	// 九级属性值
	int jiuJiShuXingZhi;
	// 十级属性值
	int shiJiShuXingZhi;
};

#define DBC_ADVANCED 11
struct _DBC_ADVANCED
{
	// 编号
	int id;
	// 名称
	char* name;
	// 等级
	int dengJi;
	// 加成点数
	int jiaChengDianShu;
	// 消耗品
	char* xiaoHaoPin;
};

#define DBC_RIDE_STRENGTHEN_MANAGER 12
struct _DBC_RIDE_STRENGTHEN
{
	// 编号
	int id;
	// 名称
	char* name;
	// 一级数值
	char* yiJiShuZhi;
	// 二级数值
	char* erJiShuZhi;
	// 三级数值
	char* sanJiShuZhi;
	// 四级数值
	char* siJiShuZhi;
	// 五级数值
	char* wuJiShuZhi;
	// 六级数值
	char* liuJiShuZhi;
	// 七级数值
	char* qiJiShuZhi;
	// 八级数值
	char* baJiShuZhi;
	// 九级数值
	char* jiuJiShuZhi;
	// 十级数值
	char* shiJiShuZhi;
};

#define DBC_OFFICIAL 13
struct _DBC_OFFICIAL
{
	// 编号
	int id;
	// 名称
	char* name;
	// 贡献需求
	int gongXianXuQiu;
};

#define DBC_ROUND 14
struct _DBC_ROUND
{
	// 编号
	int id;
	// 名称
	char* name;
	// 封面
	int fengMianGeneral;
	// 军队
	char* army;
	// 地图
	char* diTu;
};

#define DBC_SOLIDER_POSITION 15
struct _DBC_SOLIDER_POSITION
{
	// 编号
	int id;
	// 无BOOS占位
	char* wuBossZhanWei;
	// 有BOSS占位
	char* youBossZhanWei;
};