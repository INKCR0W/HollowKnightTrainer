/*
*  ┏┓　　　┏┓
*┏┛┻━━━┛┻┓
*┃              ┃ 　
*┃　　　━　　　┃
*┃　┳┛　┗┳　┃
*┃              ┃
*┃　　　┻　　　┃
*┃              ┃
*┗━┓　　　┏━┛
*　　┃　　　┃神兽保佑		THE MYTHICAL BEAST BLESS
*　　┃　　　┃代码无BUG！	THE CODE WITHOUT BUGS!
*　　┃　　　┗━━━┓
*　　┃              ┣┓
*　　┃              ┏┛
*　　┗┓┓┏━┳┓┏┛
*　　　┃┫┫　┃┫┫
*　　　┗┻┛　┗┻┛ 　
*/

// #define DEBUG

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Offset.h"
#include "Memory.h"
#include "Menu.h"

using namespace std;
using offset::ObjectOffset;

static const byte _TRUE = 1;
static const byte _FALSE = 0;


int main() {		// DEBUGGING

	const memory::ADDRPOINT real_invulnerable = reinterpret_cast<memory::ADDRPOINT>(0x7FF687FD0000);		// 真正的无敌，无法被敌人攻击的同时还无法受到地形伤害（完全免疫地刺等） real invulnerable

	ObjectOffset PlayerData(L"mono-2.0-bdwgc.dll", { 0x497DE8, 0x90, 0xE20, 0x11C }, {
		{ L"health", 0x74 },				// 生命值:Int32
		{ L"maxHealth", 0x78 },				// 生命值上限:Int32
		{ L"maxHealthBase", 0x7C },			// 生命值上限基值:Int32
		{ L"healthBlue", 0x80 },			// 蓝色生命值:Int32
		{ L"heartPieces", 0x8C },			// 面具碎片:Int32
		{ L"geo", 0xA8 },					// 吉欧:Int32		（钱）
		{ L"maxMP", 0xAC },					// 魂最大值:Int32
		{ L"MPCharge", 0xB0 },				// 魂:Int32			（为什么魂就是最大值在前面）
		{ L"vesselFragments", 0xC0 },		// 容器碎片数量:Int32
		{ L"canDash", 0x13C },				// 冲刺:Boolean
		{ L"canBackDash", 0x13D },			// 向下冲刺:Boolean
		{ L"canWallJump", 0x13E },			// 爬墙:Boolean
		{ L"canSuperDash", 0x13F },			// 超级冲刺:Boolean
		{ L"canShadowDash", 0x140 },		// 暗影冲刺:Boolean
		{ L"hasSpell", 0x141 },				// 龟派气功:Boolean	（bushi
		{ L"hasNailArt", 0x150 },			// 蓄力斩:Boolean
		{ L"hasCyclone", 0x151 },			// 旋风劈砍:Boolean
		{ L"hasDashSlash", 0x152 },			// 冲刺斩:Boolean
		{ L"hasUpwardSlash", 0x153 },		// 强力劈砍:Boolean
		{ L"hasDreamNail", 0x155 },			// 梦之钉:Boolean
		{ L"hasDreamGate", 0x156 },			// 梦之门:Boolean
		{ L"dreamNailUpgraded", 0x157 },	// 觉醒的梦之钉:Boolean
		{ L"hasDash", 0x168 },				// 冲刺披风:Boolean
		{ L"hasWalljump", 0x169 },			// 螳螂爪:Boolean
		{ L"hasSuperDash", 0x16A },			// 水晶之心:Boolean
		{ L"hasShadowDash", 0x16B },		// 暗影披风:Boolean
		{ L"hasAcidArmour", 0x16C },		// 伊思玛的眼泪:Boolean
		{ L"hasDoubleJump", 0x16D },		// 帝王之翼:Boolean
		{ L"hasLantern", 0x16E },			// 光蝇灯笼:Boolean
		});

	ObjectOffset HeroControllerStates(L"UnityPlayer.dll", { 0x1A181C0, 0x20, 0x88, 0x28, 0x50, 0x8 }, {
		{ L"invulnerable", 0x2A },			// 无敌:Boolean		（这个只作用于敌人的攻击，无法免疫地形杀，如果需要真·无敌，可以使用real_invulnerable）
		});

	memory::Memory memory(L"hollow_knight.exe");

	int menu_point = 0;

	menu::Menu menu({
		"无敌 | invulnerable",
		"无限生命值 | infinite hp",
		"无限魂 | infinite soul",
		"无限金钱 | infinite geo",
		});

	if (!menu.init()) {
		cerr << "初始化失败" << endl;
		exit(0);
	}

	bool invulnerabled = false;

	while (1) {
		menu.listen();

		if (menu.feature(0)) {
			memory.write_addr(real_invulnerable, _TRUE);
			invulnerabled = true;
		}
		else if (invulnerabled) {
			invulnerabled = false;
			memory.write_addr(real_invulnerable, _FALSE);
		}

		if (menu.feature(1)) {
			int max = 0;
			if (memory.read_object(PlayerData, L"maxHealth", &max)) {
				memory.write_object(PlayerData, L"health", max);
			}

		}

		if (menu.feature(2)) {
			int max = 0;
			if (memory.read_object(PlayerData, L"maxMP", &max)) {
				memory.write_object(PlayerData, L"MPCharge", max);
			}
		}

		if (menu.feature(3)) {
			memory.write_object(PlayerData, L"geo", 99999);
		}

		Sleep(50);
	}

	system("pause");
	return 0;
}