#include "FileName.hpp"

//
//Monster::Monster(int hp, int atk, int def, int exp,char* name) : hp(hp), atk(atk), def(def), exp(exp), name(name) {
//
//	// ����������һЩ��ʼ�����룬�����Ҫ�Ļ�
//}
//
////��������
//char gs[] = "Green Slime";
//Monster GreenSlime(30, 5, 1, 10, gs);
////Monster Sele();
//int main(){
//	printf("%s", GreenSlime.name);
//}
//
//int Battle(int map[][COL], Player& p,Monster& m,int r1,int c1, int r, int c,\
//	int hp,char *name)//��������
//{
//	PK(p, m);
//	if (p.hp)//����Ѫ�������ִ��
//	{
//		printf("You've beaten the %s!\nYou lost %d HP in the battle\nYou get %d gold coin and get %d Exp\n", \
//			*name,hp - p.hp, m.money, m.exp);
//		p.money += m.money;
//		p.Exp += m.exp;
//		//�ĵ�ͼ
//		//Sleep(3000);//
//		map[r1][c1] = 7;
//		map[r][c] = 8;
//		getchar();
//		return 0;
//	}
//	//�������û���
//	set_new_position(p.position, r1, c1);
//	return 2; //����
//	
//}


//
//int countDigits(int number) {
//	if (number == 0) return 1; // 0��һ���������������1λ
//
//	int count = 0;
//	while (number > 0) {
//		number /= 10;
//		++count;
//	}
//	return count;
//}
//// ������
//int main()
//{
//    std::string a = "521";
//    int num = std::stoi(a); // ���ַ���ת��Ϊ����
//    num += 1;               // ������ֵ����
//    a = std::to_string(num); //�����ת�����ַ���
//    std::cout << countDigits(27) << std::endl; // ������
//    return 0;
//}

#include <iostream>
#include <string>

int main() {
    int number = 42;
    const char* cstr = "The answer is: ";
    std::string str = cstr; // ���ַ�ָ��ת��Ϊstd::string
    std::string result = str + std::to_string(number) + ".";
    std::cout << result << std::endl; // �����The answer is: 42.

    return 0;
}