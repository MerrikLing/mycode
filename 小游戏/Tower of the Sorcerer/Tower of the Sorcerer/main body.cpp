#include"head.hpp"
//先实现控制台版本，再实现图形化版本
// 
// 创建不同属性的角色？ 增加宝箱，随机生成效果？ 增加解谜？
// 增加对敌手册
//角色、怪物用class来实现。在initi中初始化玩家，直接创建也行
//存档？ 副手武器  武器效果  炸弹? 镐子(挖墙壁)
//手册  剑盾 宝石
//职业 魔药 多门 隐藏地图 多地图

//或许可以借鉴哈利波特
// 借鉴  刀剑神域 ！
// 传送水晶？ 剑技  
//增加音效，背景音乐 可以考虑不同楼层不同的背景音乐
//存在的问题：
// 数值有问题！ 可以考虑每层怪物设计不同的数值
//商人
//如果双方都无法打穿对方的防御就会死循环

//游戏说明： ——寒假做成可视化
//必须按ESC退出！！ 不要直接点关闭！！否则音频资源不会释放，音频可能损坏！！

int main()
{
		Player P;            //初始化
		initgraph(850, 650); // 初始化一个窗口
		LoadImages();        // 加载图片素材
		StartImage();        // 游戏开始画面
		InventInfor();       //制作者信息
		//背景音乐
		PlaySound(TEXT("ZeldaBackground.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP); //这个函数只适用于处理单个音频！
		InitImage();         // 打印游戏过程中始终不变的图片
		int ret;
		int f = P.position[0];
		while(P.position[0]<FLOOR)
		{
			f = P.position[0];
			PrintMap(Map[P.position[0]],P);
			ret = play(Map[P.position[0]], P);
			if (ret == -12)
			{
				break;
			}
			else if (ret == 2) //死亡
			{
				musicDie();
				PrintLose();
				break;
			}
			else if (ret == 3)   //胜利——找到公主
			{
				musicWin();
				PrintWin();
				break;
			}
			//ret 4 5 6 7 分别表示上下左右，用于楼层转换后的初始位置
			if (f != P.position[0])
			{ 
				ChangeFloor(Map,P,ret);
			}
		}
		closeMusic();
		closegraph();        // 关闭图形窗口
	
	return 0;
}

