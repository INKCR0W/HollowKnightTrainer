/*
*  ��������������
*�����ߩ��������ߩ�
*��              �� ��
*������������������
*�����ש������ס���
*��              ��
*���������ߡ�������
*��              ��
*������������������
*�����������������ޱ���		THE MYTHICAL BEAST BLESS
*��������������������BUG��	THE CODE WITHOUT BUGS!
*����������������������
*������              �ǩ�
*������              ����
*���������������ש�����
*���������ϩϡ����ϩ�
*���������ߩ������ߩ� ��
*/


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
	ObjectOffset PlayerData(L"mono-2.0-bdwgc.dll", { 0x497DE8, 0x90, 0xE20, 0x11C }, {
		{ L"health", 0x74 },				// ����ֵ:Int32
		{ L"maxHealth", 0x78 },				// ����ֵ����:Int32
		{ L"maxHealthBase", 0x7C },			// ����ֵ���޻�ֵ:Int32
		{ L"healthBlue", 0x80 },			// ��ɫ����ֵ:Int32
		{ L"heartPieces", 0x8C },			// �����Ƭ:Int32
		{ L"geo", 0xA8 },					// ��ŷ:Int32		��Ǯ��
		{ L"maxMP", 0xAC },					// �����ֵ:Int32
		{ L"MPCharge", 0xB0 },				// ��:Int32			��Ϊʲô��������ֵ��ǰ�棩
		{ L"vesselFragments", 0xC0 },		// ������Ƭ����:Int32
		{ L"canDash", 0x13C },				// ���:Boolean
		{ L"canBackDash", 0x13D },			// ���³��:Boolean
		{ L"canWallJump", 0x13E },			// ��ǽ:Boolean
		{ L"canSuperDash", 0x13F },			// �������:Boolean
		{ L"canShadowDash", 0x140 },		// ��Ӱ���:Boolean
		{ L"hasSpell", 0x141 },				// ��������:Boolean	��bushi
		{ L"hasNailArt", 0x150 },			// ����ն:Boolean
		{ L"hasCyclone", 0x151 },			// ��������:Boolean
		{ L"hasDashSlash", 0x152 },			// ���ն:Boolean
		{ L"hasUpwardSlash", 0x153 },		// ǿ������:Boolean
		{ L"hasDreamNail", 0x155 },			// ��֮��:Boolean
		{ L"hasDreamGate", 0x156 },			// ��֮��:Boolean
		{ L"dreamNailUpgraded", 0x157 },	// ���ѵ���֮��:Boolean
		{ L"hasDash", 0x168 },				// �������:Boolean
		{ L"hasWalljump", 0x169 },			// ���צ:Boolean
		{ L"hasSuperDash", 0x16A },			// ˮ��֮��:Boolean
		{ L"hasShadowDash", 0x16B },		// ��Ӱ����:Boolean
		{ L"hasAcidArmour", 0x16C },		// ��˼�������:Boolean
		{ L"hasDoubleJump", 0x16D },		// ����֮��:Boolean
		{ L"hasLantern", 0x16E },			// ��Ӭ����:Boolean
		});

	ObjectOffset HeroControllerStates(L"UnityPlayer.dll", { 0x1A181C0, 0x20, 0x88, 0x28, 0x50, 0x8 }, {
		{ L"invulnerable", 0x2A },			// �޵�:Boolean
		});

	memory::Memory memory(L"hollow_knight.exe");

	int menu_point = 0;

	menu::Menu menu({
		"�޵� | invulnerable",
		"��������ֵ | infinite hp",
		"���޻� | infinite soul",
		"���޽�Ǯ | infinite geo"
		});

	if (!menu.init()) {
		cerr << "��ʼ��ʧ��" << endl;
		exit(0);
	}


	while (1) {
		menu.listen();

		if (menu.feature(0)) {
			byte state = 0;
			if (memory.read_object(HeroControllerStates, L"invulnerable", &state)) {
				memory.write_object(HeroControllerStates, L"invulnerable", state | _TRUE);
			}
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
	}

	system("pause");
	return 0;
}