#include "FileName.hpp"

//
//Monster::Monster(int hp, int atk, int def, int exp,char* name) : hp(hp), atk(atk), def(def), exp(exp), name(name) {
//
//	// 这里可以添加一些初始化代码，如果需要的话
//}
//
////创建对象
//char gs[] = "Green Slime";
//Monster GreenSlime(30, 5, 1, 10, gs);
////Monster Sele();
//int main(){
//	printf("%s", GreenSlime.name);
//}
//
//int Battle(int map[][COL], Player& p,Monster& m,int r1,int c1, int r, int c,\
//	int hp,char *name)//传入名字
//{
//	PK(p, m);
//	if (p.hp)//还有血量则继续执行
//	{
//		printf("You've beaten the %s!\nYou lost %d HP in the battle\nYou get %d gold coin and get %d Exp\n", \
//			*name,hp - p.hp, m.money, m.exp);
//		p.money += m.money;
//		p.Exp += m.exp;
//		//改地图
//		//Sleep(3000);//
//		map[r1][c1] = 7;
//		map[r][c] = 8;
//		getchar();
//		return 0;
//	}
//	//坐标重置回来
//	set_new_position(p.position, r1, c1);
//	return 2; //死亡
//	
//}


//
//int countDigits(int number) {
//	if (number == 0) return 1; // 0是一个特殊情况，它有1位
//
//	int count = 0;
//	while (number > 0) {
//		number /= 10;
//		++count;
//	}
//	return count;
//}
//// 主函数
//int main()
//{
//    std::string a = "521";
//    int num = std::stoi(a); // 将字符串转换为整数
//    num += 1;               // 进行数值增加
//    a = std::to_string(num); //将结果转换回字符串
//    std::cout << countDigits(27) << std::endl; // 输出结果
//    return 0;
//}

#include <iostream>
#include <string>

int main() {
    int number = 42;
    const char* cstr = "The answer is: ";
    std::string str = cstr; // 将字符指针转换为std::string
    std::string result = str + std::to_string(number) + ".";
    std::cout << result << std::endl; // 输出：The answer is: 42.

    return 0;
}