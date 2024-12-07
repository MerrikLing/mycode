#include"head.hpp"
//先实现控制台版本，再实现图形化版本
// 
// 创建不同属性的角色？ 增加宝箱，随机生成效果？ 增加解谜？
// 增加对敌手册
//角色、怪物用class来实现。在initi中初始化玩家，直接创建也行
//存档？ 副手武器  武器效果  炸弹? 镐子(挖墙壁)
//升级函数 显示属性 手册  剑盾 宝石
//职业 魔药 多门 隐藏地图 多地图

//增加人物左右移动的图形？ 下：原图，上：背影
//存在的问题：
//
//
int main()
{start:
		/*printf("Brave warrior, welcome to the Tower of Sorcerer.\nPlease use your wisdom and courage to defeat the demon king and rescue the imprisoned princess! \n\n(Press any key to start the game)");
		_getch();*/
		//初始化
		Player P;
		//zheshiweistingshusogohfoe
		initgraph(850, 650); // 初始化一个窗口
		LoadImages();        // 加载图片素材
		InitImage();         // 打印游戏过程中始终不变的图片
		//printf("%d", P.position[0]);
		int ret;
		int f = P.position[0];
		while(P.position[0]<FLOOR)
		{
			f = P.position[0];
			//display_map(Map[ P.position[0] ]);
			PrintMap(Map[P.position[0]],P);
			ret = move(Map[P.position[0]], P);
			//ret = 3;      //用于调试
			if (ret == 2) //死亡
			{
				//printf("Brave warrior,it's a reget that you have lost your life.\n");
				_getch();
				break;
			}
			if (ret == 3)   //胜利——击败魔王
			{
				//printf("Congratulations!\nWith your great effort, you've managed to beat the demo king\nand save the princess from the Tower of the Sorcerer!\n");
				_getch();
				return 0;
			}
			//如果上下楼，修改位置,出来的位置固定为门下一格
			if (f != P.position[0])
			{
				P.position[1] -= 1;
				Map[P.position[0]][P.position[1]][P.position[2]] = 8;
			}
		}
		closegraph();        // 关闭图形窗口
	
	return 0;
}

