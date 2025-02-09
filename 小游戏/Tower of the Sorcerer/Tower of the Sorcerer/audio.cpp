#include"head.hpp"
void musicGameLoading()  //真奇怪了，播放有卡顿？难道长一点的音频都不行吗
{
	mciSendString("open GameLoading.mp3 alias GameLoading", NULL, 0, NULL);
	mciSendString("play GameLoading wait", NULL, 0, NULL);
	mciSendString("close GameLoading ", NULL, 0, NULL);

}
void musicPickup()
{
	mciSendString("close pickup", NULL, 0, NULL);
	mciSendString("open pickup.mp3 alias pickup", NULL, 0, NULL);
	mciSendString("play pickup ", NULL, 0, NULL);
}

void musicBattle()
{
	mciSendString("open battle.mp3 alias battle", NULL, 0, NULL);
	mciSendString("play battle wait", NULL, 0, NULL);
	mciSendString("close battle", NULL, 0, NULL);
}

void musicEnter()
{
	mciSendString("close enter", NULL, 0, NULL);
	mciSendString("open in.mp3 alias enter", NULL, 0, NULL);
	mciSendString("play enter", NULL, 0, NULL);
}

void musicLvUp()
{
	mciSendString("close LvUp", NULL, 0, NULL);
	mciSendString("open LvUp.mp3 alias LvUp", NULL, 0, NULL);
	mciSendString("play LvUp", NULL, 0, NULL);
}

void musicDie()
{
	mciSendString("close die", NULL, 0, NULL);
	mciSendString("open die.mp3 alias die", NULL, 0, NULL);
	mciSendString("play die", NULL, 0, NULL);
}

void musicWin()
{
	mciSendString("close win", NULL, 0, NULL);
	mciSendString("open win.mp3 alias win", NULL, 0, NULL);
	mciSendString("play win", NULL, 0, NULL);
}

void musicEncyclopedia()
{
	mciSendString("close Encyclopedia", NULL, 0, NULL);
	mciSendString("open Encyclopedia.mp3 alias Encyclopedia", NULL, 0, NULL);
	mciSendString("play Encyclopedia", NULL, 0, NULL);
}

void musicMeet()
{
	mciSendString("close Godness", NULL, 0, NULL);
	mciSendString("open Godness.mp3 alias Godness", NULL, 0, NULL);
	mciSendString("play Godness", NULL, 0, NULL);
}

void musicDrink()
{
	mciSendString("close drink", NULL, 0, NULL);
	mciSendString("open DrinkPotion.mp3 alias drink", NULL, 0, NULL);
	mciSendString("play drink", NULL, 0, NULL);
}

void musicOpenBackpack()
{
	mciSendString("close ob", NULL, 0, NULL);
	mciSendString("open openBackpack.mp3 alias ob", NULL, 0, NULL);
	mciSendString("play ob", NULL, 0, NULL);
}
void closeMusic()
{
	mciSendString("close GameLoading ", NULL, 0, NULL);
	mciSendString("close pickup", NULL, 0, NULL);
	mciSendString("close battle", NULL, 0, NULL);
	mciSendString("close enter", NULL, 0, NULL);
	mciSendString("close LvUp", NULL, 0, NULL);
	mciSendString("close die", NULL, 0, NULL);
	mciSendString("close win", NULL, 0, NULL);
	mciSendString("close Encyclopedia", NULL, 0, NULL);
	mciSendString("close Godness", NULL, 0, NULL);
	mciSendString("close drink", NULL, 0, NULL);
	mciSendString("close ob", NULL, 0, NULL);

	mciSendString("close background", NULL, 0, NULL);
}