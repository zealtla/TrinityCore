#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Item.h"
#include "Chat.h"
#include "WorldSession.h"
#pragma execution_character_set("utf-8")

#pragma region Define
#define GUIDE_0 "|TInterface/ICONS/INV_Sword_27:30|t��������"
#define GUIDE_1 "|TInterface/ICONS/INV_Chest_Chain_11:30|t����װ��"
#define GUIDE_2 "|TInterface/ICONS/INV_Misc_Toy_05:30|t��������"
//vipgem
#define VIPGEM_0 "|TInterface/ICONS/Spell_Arcane_PortalTheramore:30|t����"
#define VIPGEM_1 "|TInterface/ICONS/Achievement_Zone_HillsbradFoothills:30|t���������ͼ"
#define VIPGEM_2 "|TInterface/ICONS/Achievement_Zone_Outland_01:30|t�����ͼ"
#define VIPGEM_3 "|TInterface/ICONS/Ability_Druid_NaturalPerfection:30|t���˸���"
#define VIPGEM_4 "|TInterface/ICONS/Ability_Mage_FieryPayback:30|t�ŶӸ���"
#define VIPGEM_5 "|TInterface/ICONS/Racial_Dwarf_FindTreasure:30|t��������"
#define CITY_0 "|TInterface/ICONS/Spell_arcane_teleportmoonglade:30|t�ڰ�֮�ţ�������ǣ�"
#define CITY_1 "|TInterface/ICONS/Spell_arcane_teleportshattrath:30|tɳ��˹"
//����
#define CITY_2 "|TInterface/ICONS/Spell_Arcane_TeleportStormWind:30|t�����"
#define CITY_3 "|TInterface/ICONS/Achievement_Zone_Ironforge:30|t��¯��"
#define CITY_4 "|TInterface/ICONS/Achievement_Zone_Darnassus:30|t������˹"
#define CITY_5 "|TInterface/ICONS/Achievement_Zone_AzuremystIsle_01:30|t������"
//����
#define CITY_6 "|TInterface/ICONS/Achievement_Zone_Durotar:30|t�¸�����"
#define CITY_7 "|TInterface/ICONS/Spell_arcane_teleportthunderbluff:30|t������"
#define CITY_8 "|TInterface/ICONS/Spell_arcane_teleportundercity:30|t�İ���"
#define CITY_9 "|TInterface/ICONS/Achievement_Zone_IsleOfQuelDanas:30|t���³�"
//��½
#define MAINLAND_0 "|TInterface/ICONS/Achievement_Zone_EasternKingdoms_01:30|t��������"
#define MAINLAND_1 "|TInterface/ICONS/Achievement_Zone_Kalimdor_01:30|t����ķ��"
//�����ͼ 6
#define OUTLAND_0 "|TInterface/ICONS/Achievement_Zone_Zangarmarsh:30|t�޼�����"
#define OUTLAND_1 "|TInterface/ICONS/Achievement_Zone_Terrokar:30|t̩�޿�ɭ��"
#define OUTLAND_2 "|TInterface/ICONS/Achievement_Zone_BladesEdgeMtns_01:30|t����ɽ"
#define OUTLAND_3 "|TInterface/ICONS/Achievement_Zone_Nagrand_01:30|t�ɸ���"
#define OUTLAND_4 "|TInterface/ICONS/Achievement_Zone_Netherstorm_01:30|t��շ籩"
#define OUTLAND_5 "|TInterface/ICONS/Achievement_Zone_Shadowmoon:30|tӰ�¹�"
#define OUTLAND_6 "|TInterface/ICONS/Achievement_Zone_HellfirePeninsula_01:30|t������뵺"
#pragma endregion

//���˵�
void VipGemMainMenu(Player* player, Item* item)
{
    ClearGossipMenuFor(player); // Clears old options
    AddGossipItemFor(player, 5, VIPGEM_0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    AddGossipItemFor(player, 5, VIPGEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    AddGossipItemFor(player, 5, VIPGEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    AddGossipItemFor(player, 5, VIPGEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    AddGossipItemFor(player, 5, VIPGEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);    

    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
}

//��������
void EasternKingdomsMenu(Player* player, Item* item)
{
    ClearGossipMenuFor(player); // Clears old options
    AddGossipItemFor(player, 5, "����ϣ�ߵ�", GOSSIP_SENDER_MAIN, 613);
    AddGossipItemFor(player, 5, "����֮��", GOSSIP_SENDER_MAIN, 614);
    AddGossipItemFor(player, 5, "��Ī��", GOSSIP_SENDER_MAIN, 615);
    AddGossipItemFor(player, 5, "ĺɫɭ��", GOSSIP_SENDER_MAIN, 616);
    AddGossipItemFor(player, 5, "������֮��", GOSSIP_SENDER_MAIN, 617);
    AddGossipItemFor(player, 5, "������ɭ��", GOSSIP_SENDER_MAIN, 618);
    AddGossipItemFor(player, 5, "ϣ��˹����������", GOSSIP_SENDER_MAIN, 619);
    AddGossipItemFor(player, 5, "�༹ɽ", GOSSIP_SENDER_MAIN, 620);
    AddGossipItemFor(player, 5, "����ɭ��", GOSSIP_SENDER_MAIN, 621);
    AddGossipItemFor(player, 5, "������", GOSSIP_SENDER_MAIN, 622);
    AddGossipItemFor(player, 5, "��������", GOSSIP_SENDER_MAIN, 623);
    AddGossipItemFor(player, 5, "������", GOSSIP_SENDER_MAIN, 624);
    AddGossipItemFor(player, 5, "����˹���ֵ�", GOSSIP_SENDER_MAIN, 625);
    AddGossipItemFor(player, 5, "������Ұ", GOSSIP_SENDER_MAIN, 626);
    AddGossipItemFor(player, 5, "ʪ��", GOSSIP_SENDER_MAIN, 627);
    AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);

    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
}

//����ķ��
void KalimdorMenu(Player* player, Item* item)
{
    ClearGossipMenuFor(player); // Clears old options
    AddGossipItemFor(player, 5, "�ҹ�", GOSSIP_SENDER_MAIN, 601);
    AddGossipItemFor(player, 5, "�ں���", GOSSIP_SENDER_MAIN, 602);
    AddGossipItemFor(player, 5, "����֮��", GOSSIP_SENDER_MAIN, 603);
    AddGossipItemFor(player, 5, "��¡����", GOSSIP_SENDER_MAIN, 604);
    AddGossipItemFor(player, 5, "��������", GOSSIP_SENDER_MAIN, 605);
    AddGossipItemFor(player, 5, "����˹", GOSSIP_SENDER_MAIN, 606);
    AddGossipItemFor(player, 5, "ϣ����˹", GOSSIP_SENDER_MAIN, 607);
    AddGossipItemFor(player, 5, "ʯצɽ��", GOSSIP_SENDER_MAIN, 608);
    AddGossipItemFor(player, 5, "������˹", GOSSIP_SENDER_MAIN, 609);
    AddGossipItemFor(player, 5, "ƶ�֮��", GOSSIP_SENDER_MAIN, 610);
    AddGossipItemFor(player, 5, "ǧ��ʯ��", GOSSIP_SENDER_MAIN, 611);
    AddGossipItemFor(player, 5, "��Ȫ��", GOSSIP_SENDER_MAIN, 612);
    AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);

    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
}

//����
void MainCityMenu(Player* player, Object* object)
{
    if (player->GetTeamId() == TEAM_ALLIANCE)
    {
        ClearGossipMenuFor(player); // Clears old options
        AddGossipItemFor(player, 5, CITY_0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        AddGossipItemFor(player, 5, CITY_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
        AddGossipItemFor(player, 5, CITY_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
        AddGossipItemFor(player, 5, CITY_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
        AddGossipItemFor(player, 5, CITY_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
        AddGossipItemFor(player, 5, CITY_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
        AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, object->GetGUID());
    }
    else
    {
        ClearGossipMenuFor(player); // Clears old options
        AddGossipItemFor(player, 5, CITY_0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
        AddGossipItemFor(player, 5, CITY_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
        AddGossipItemFor(player, 5, CITY_6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
        AddGossipItemFor(player, 5, CITY_7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
        AddGossipItemFor(player, 5, CITY_8, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
        AddGossipItemFor(player, 5, CITY_9, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
        AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, object->GetGUID());
    }
}

#pragma region ��������
class npc_newplayerguide : public CreatureScript
{
public:
    npc_newplayerguide() : CreatureScript("npc_newplayerguide") { }

    struct npc_newplayerguideAI : public ScriptedAI
    {
        npc_newplayerguideAI(Creature* creature) : ScriptedAI(creature) { }

        bool GossipHello(Player* player) override
        {
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, GUIDE_0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, GUIDE_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, GUIDE_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

            player->TalkedToCreature(me->GetEntry(), me->GetGUID());
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
            return true;
        }

        bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            if (!player)
                return true;

            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1: //����
                player->GetSession()->SendListInventory(me->GetGUID(), 90000);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2: //װ��
                player->GetSession()->SendListInventory(me->GetGUID(), 90001);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3: //����
                player->GetSession()->SendListInventory(me->GetGUID(), 90002);
                break;
            }
            
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_newplayerguideAI(creature);
    }
};
#pragma endregion

#pragma region ����ʯ
class item_vipgem : public ItemScript
{
public:
    item_vipgem() : ItemScript("item_vipgem") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override // Any hook here
    {
        //ս���в�����
        if (player->IsInCombat())
        {
            CloseGossipMenuFor(player);
            player->GetSession()->SendNotification("ս�����޷�ʹ�ã�");
            return false;
        }

        VipGemMainMenu(player, item);
        return false; // Cast the spell on use normally
    }

    void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action) override
    {
        if (!player)
            return;

        ClearGossipMenuFor(player);

        switch (action)
        {            
        case GOSSIP_ACTION_INFO_DEF + 1: //����
            MainCityMenu(player, item);
            break;
        case GOSSIP_ACTION_INFO_DEF + 2: //������˹��ͼ
            ClearGossipMenuFor(player); // Clears old options
            AddGossipItemFor(player, 5, MAINLAND_0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
            AddGossipItemFor(player, 5, MAINLAND_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3: //�����ͼ
            ClearGossipMenuFor(player); // Clears old options
            AddGossipItemFor(player, 5, OUTLAND_0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
            AddGossipItemFor(player, 5, OUTLAND_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 101);
            AddGossipItemFor(player, 5, OUTLAND_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 102);
            AddGossipItemFor(player, 5, OUTLAND_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 103);
            AddGossipItemFor(player, 5, OUTLAND_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 104);
            AddGossipItemFor(player, 5, OUTLAND_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 105);
            AddGossipItemFor(player, 5, OUTLAND_6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4: //5�˸���
            ClearGossipMenuFor(player); // Clears old options
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Zone_Kalimdor_01:30|t����ķ�ั��", GOSSIP_SENDER_MAIN, 5010);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Zone_EasternKingdoms_01:30|t������������", GOSSIP_SENDER_MAIN, 5015);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Zone_Outland_01:30|tȼ�յ�Զ������", GOSSIP_SENDER_MAIN, 5025);
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
        case 5010: //����ķ��5�˱�
            ClearGossipMenuFor(player); // Clears old options
            AddGossipItemFor(player, 5, "�ڰ���Ԩ", GOSSIP_SENDER_MAIN, 6001);            
            AddGossipItemFor(player, 5, "����֮�", GOSSIP_SENDER_MAIN, 6010);
            AddGossipItemFor(player, 5, "������", GOSSIP_SENDER_MAIN, 6015);            
            AddGossipItemFor(player, 5, "ŭ���ѹ�", GOSSIP_SENDER_MAIN, 6025);
            AddGossipItemFor(player, 5, "�굶�ߵ�", GOSSIP_SENDER_MAIN, 6030);
            AddGossipItemFor(player, 5, "�굶����", GOSSIP_SENDER_MAIN, 6035);            
            AddGossipItemFor(player, 5, "������Ѩ", GOSSIP_SENDER_MAIN, 6050);
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
        case 5015: //Eastern Kingdoms 1
            ClearGossipMenuFor(player); // Clears old options
            AddGossipItemFor(player, 5, "��ʯ��Ԩ", GOSSIP_SENDER_MAIN, 7001);
            AddGossipItemFor(player, 5, "��ʯ��", GOSSIP_SENDER_MAIN, 7005);            
            AddGossipItemFor(player, 5, "������", GOSSIP_SENDER_MAIN, 7015);
            AddGossipItemFor(player, 5, "ŵĪ���", GOSSIP_SENDER_MAIN, 7020);
            AddGossipItemFor(player, 5, "Ѫɫ�޵�Ժ", GOSSIP_SENDER_MAIN, 7040);
            AddGossipItemFor(player, 5, "˹̹��ķ", GOSSIP_SENDER_MAIN, 7055);
            AddGossipItemFor(player, 5, "��û������", GOSSIP_SENDER_MAIN, 7060);                       
            AddGossipItemFor(player, 7, "��һҳ", GOSSIP_SENDER_MAIN, 5020);
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
        case 5020: //Eastern Kingdoms 2
            ClearGossipMenuFor(player); // Clears old options            
            AddGossipItemFor(player, 5, "����", GOSSIP_SENDER_MAIN, 7065);
            AddGossipItemFor(player, 5, "�´���", GOSSIP_SENDER_MAIN, 7070);                        
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
        case 5025: //����5�˱�   
            ClearGossipMenuFor(player); // Clears old options
            AddGossipItemFor(player, 5, "��ɫ����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 200);
            AddGossipItemFor(player, 5, "��ϣ��˹����������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 201);
            AddGossipItemFor(player, 5, "��Ӱ�Թ�", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 202);
            AddGossipItemFor(player, 5, "������Ĺ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 203);
            AddGossipItemFor(player, 5, "�½����Ѩ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 204);
            AddGossipItemFor(player, 5, "�������ǽ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 205);
            AddGossipItemFor(player, 5, "��Ѫ��¯", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 206);
            AddGossipItemFor(player, 5, "�������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 207);
            AddGossipItemFor(player, 5, "��ħ����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 208);
            AddGossipItemFor(player, 5, "��Դ��", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 209);
            AddGossipItemFor(player, 5, "��̬��", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 210);
            AddGossipItemFor(player, 5, "ū��Χ��", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 211);
            AddGossipItemFor(player, 5, "�����ؽ�", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 212);
            AddGossipItemFor(player, 5, "�İ�����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 213);
            
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5: //�ŶӸ���            
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Zone_HillsbradFoothills:30|t��������ű�", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 300);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Zone_Outland_01:30|tȼ�յ�Զ���ű�", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 301);
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
            //�����ű�
        case GOSSIP_ACTION_INFO_DEF + 300:
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Ability_mount_drake_red:30|t���ݿ�ϣ�ǵĳ�Ѩ", GOSSIP_SENDER_MAIN, 6020);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_boss_ossiriantheunscarred:30|t����������", GOSSIP_SENDER_MAIN, 6040);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_boss_cthun:30|t����������", GOSSIP_SENDER_MAIN, 6045);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_boss_nefarion:30|t����֮��", GOSSIP_SENDER_MAIN, 7010);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_boss_ragnaros:30|t�ۻ�֮��", GOSSIP_SENDER_MAIN, 7035);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_boss_hakkar:30|t���������", GOSSIP_SENDER_MAIN, 7080);
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
            //tbc�ű�
        case GOSSIP_ACTION_INFO_DEF + 301:
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_boss_princemalchezaar_02:30|t������", GOSSIP_SENDER_MAIN, 7030);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Boss_Zuljin:30|t�氢��", GOSSIP_SENDER_MAIN, 7075);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Boss_Illidan:30|t�ڰ����", GOSSIP_SENDER_MAIN, 8005);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Boss_LadyVashj:30|t����ˮ��", GOSSIP_SENDER_MAIN, 8010);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_boss_gruulthedragonkiller:30|t��³���ĳ�Ѩ", GOSSIP_SENDER_MAIN, 8015);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Boss_Magtheridon:30|t��������", GOSSIP_SENDER_MAIN, 8020);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Boss_Kael'thasSunstrider_01:30|t�籩Ҫ��", GOSSIP_SENDER_MAIN, 8025);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_Boss_Archimonde :30|t���Ӷ���", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 214);
            AddGossipItemFor(player, 5, "|TInterface/ICONS/Achievement_boss_kiljaedan:30|t̫��֮���ߵ�", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 215);
            AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            break;
#pragma region ����
            //����
        case GOSSIP_ACTION_INFO_DEF + 6: //�ڰ�֮��
        case GOSSIP_ACTION_INFO_DEF + 12:
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -247.29f, 910.638f, 84.3798f, 1.49341f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 7: //ɳ��˹
        case GOSSIP_ACTION_INFO_DEF + 13:
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 8: //�����
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 9: //��¯��
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 10: //������˹
            CloseGossipMenuFor(player);
            player->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 11: //������
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -3954.20f, -11656.54f, -138.69f, 0.0f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 14: //�¸�����
            CloseGossipMenuFor(player);
            player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 15: //������
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -1290.0f, 147.033997f, 129.682007f, 4.919000f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 16: //�İ���
            CloseGossipMenuFor(player);
            player->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 17: //���³�
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
            break;
#pragma endregion 
            //���˵�
        case GOSSIP_ACTION_INFO_DEF + 20: //���˵�
            VipGemMainMenu(player, item);
            break;
#pragma region �����ͼ
            //�����ͼ
        case GOSSIP_ACTION_INFO_DEF + 100: //�޼�����
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -54.8621f, 813.44f, 20.9764f, 0.081722f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 101: //̩�޿�ɭ��
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -2000.47f, 4451.54f, 8.37917f, 4.40447f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 102: //����ɽ
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 3037.67f, 5962.86f, 130.774f, 1.27253f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 103: //�ɸ���
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -1145.95f, 8182.35f, 3.60249f, 6.13478f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 104: //��շ籩
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 3830.23f, 3426.5f, 88.6145f, 5.16677f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 105: //Ӱ�¹�
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -3734.1079f, 2234.0273f, 79.1591f, 4.4846f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 106: //������뵺
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -211.237f, 4278.54f, 86.5678f, 4.59776f);
            break;
#pragma endregion
#pragma region ���������ͼ
        case GOSSIP_ACTION_INFO_DEF + 18: //��������
            EasternKingdomsMenu(player, item);
            break;
        case GOSSIP_ACTION_INFO_DEF + 19: //����ķ��
            KalimdorMenu(player, item);
            break;
        case 601: // Kalimdor -> Ashenvale
            CloseGossipMenuFor(player);
            player->TeleportTo(1, 3469.43f, 847.62f, 6.36476f, 0.0f);
            break;
        case 602: // Kalimdor -> Darkshore
            CloseGossipMenuFor(player);
            player->TeleportTo(1, 6207.5f, -152.833f, 80.8185f, 0.0f);
            break;
        case 603: // Kalimdor -> Desolace
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -93.1614f, 1691.15f, 90.0649f, 0.0f);
            break;
        case 604: // Kalimdor -> Durotar
            CloseGossipMenuFor(player);
            player->TeleportTo(1, 341.42f, -4684.7f, 31.9493f, 0.0f);
            break;
        case 605: // Kalimdor -> Duswallow Marsh
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -3463.26f, -4123.13f, 18.1043f, 0.0f);
            break;
        case 606: // Kalimdor -> Ferelas
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -4458.93f, 243.415f, 65.6136f, 0.0f);
            break;
        case 607: // Kalimdor -> Silithus
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -6824.15f, 821.273f, 50.6675f, 0.0f);
            break;
        case 608: // Kalimdor -> Stonetalon Mountains
            CloseGossipMenuFor(player);
            player->TeleportTo(1, 1145.00f, 85.664f, -6.64f, 0.0f);
            break;
        case 609: // Kalimdor -> Tanaris
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -7373.69f, -2950.2f, 11.7598f, 0.0f);
            break;
        case 610: // Kalimdor -> The Barrens
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -456.263f, -2652.7f, 96.615f, 0.0f);
            break;
        case 611: // Kalimdor -> Thousand Needles
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -4941.66f, -1595.42f, -33.07f, 0.0f);
            break;
        case 612: // Kalimdor -> Winterspring
            CloseGossipMenuFor(player);
            player->TeleportTo(1, 6107.62f, -4181.6f, 853.322f, 0.0f);
            break;
        case 613: // Eastern Kingdoms -> Arathi Highlands
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -1544.93f, -2495.01f, 54.11f, 0.0f);
            break;
        case 614: // Eastern Kingdoms -> Badlands
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -6084.95f, -3328.44f, 253.76f, 0.0f);
            break;
        case 615: // Eastern Kingdoms -> Dun Morogh
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -5660.33f, 755.299f, 390.605f, 0.0f);
            break;
        case 616: // Eastern Kingdoms -> Duskwood
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -10879.85f, -327.06f, 37.78f, 0.0f);
            break;
        case 617: // Eastern Kingdoms -> Eastern Plaguelands
            CloseGossipMenuFor(player);
            player->TeleportTo(0, 2280.12f, -5313.16f, 87.74f, 0.0f);
            break;
        case 618: // Eastern Kingdoms -> Elwynn Forest
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -9545.78f, -51.81f, 56.72f, 0.0f);
            break;
        case 619: // Eastern Kingdoms -> Hillsbrad Foothills
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -436.03f, -583.27f, 53.58f, 0.0f);
            break;
        case 620: // Eastern Kingdoms -> Reridge Mountains
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -9633.80f, -1875.09f, 68.39f, 0.0f);
            break;
        case 621: // Eastern Kingdoms -> Silverpine Forest
            CloseGossipMenuFor(player);
            player->TeleportTo(0, 641.48f, 1297.84f, 85.45f, 0.0f);
            break;
        case 622: // Eastern Kingdoms -> Stranglethorn Vale
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -11393.77f, -288.94f, 58.99f, 0.0f);
            break;
        case 623: // Eastern Kingdoms -> Swamp of Sorrows
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -10522.55f, -3028.30f, 21.79f, 0.0f);
            break;
        case 624: // Eastern Kingdoms -> The Hinterlands
            CloseGossipMenuFor(player);
            player->TeleportTo(0, 155.14f, -2014.95f, 122.55f, 0.0f);
            break;
        case 625: // Eastern Kingdoms -> Tirishfal Glades
            CloseGossipMenuFor(player);
            player->TeleportTo(0, 2255.5f, 288.511f, 35.1138f, 0.0f);
            break;
        case 626: // Eastern Kingdoms -> Westfall
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -10919.09f, 998.47f, 35.47f, 0.0f);
            break;
        case 627: // Eastern Kingdoms -> Wetlands
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -4086.36f, -2610.95f, 47.0143f, 0.0f);
            break;
#pragma endregion
#pragma region ����
        case 6001:// Blackfathom Deeps
            CloseGossipMenuFor(player);
            player->TeleportTo(1, 4248.72f, 744.35f, -24.67f, 1.34f);
            break;
        case 6010:// Dire Maul
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -3960.95f, 1130.64f, 161.05f, 0.0f);
            break;
        case 6015:// Maraudon
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -1431.33f, 2962.34f, 98.23f, 4.74f);
            break;
        case 6020:// Onyxia's Lair
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -4707.44f, -3726.82f, 54.6723f, 3.8f);
            break;
        case 6025:// Ragefire Chasm
            CloseGossipMenuFor(player);
            player->TeleportTo(1, 1814.47f, -4419.46f, -18.78f, 5.28f);
            break;
        case 6030:// Razorfen Downs
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -4657.88f, -2525.59f, 81.4f, 4.16f);
            break;
        case 6035:// Razorfen Kraul
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -4463.6f, -1664.53f, 82.26f, 0.85f);
            break;
        case 6040:// Ruins of Ahn'Qiraj
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -8413.33f, 1501.27f, 29.64f, 2.61f);
            break;
        case 6045:// Temple of Ahn'Qiraj
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -8245.837891f, 1983.736206f, 129.071686f, 0.936195f);
            break;
        case 6050:// Wailing Caverns
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -722.53f, -2226.30f, 16.94f, 2.71f);
            break;
        case 6055:// Zul'Farrak
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -6801.9f, -2890.22f, 8.88f, 6.25f);
            break;

            //////////////////////////////////////////////////EASTERN KINGDOMS///////////////////////////////////////////////////////////////

        case 7001:// Blackrock Depths
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -7180.57f, -920.04f, 165.49f, 5.02f);
            break;
        case 7005:// Blackrock Spire
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -7526.77f, -1225.64f, 285.73f, 5.31f);
            break;
        case 7010:// Blackwing Lair
            CloseGossipMenuFor(player);
            player->TeleportTo(469, -7672.61f, -1107.21f, 396.65f, 3.75f);
            break;
        case 7015:// Deadmines
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -11208.2f, 1675.92f, 24.57f, 1.48f);
            break;
        case 7020:// Gnomeregan
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -5163.32f, 927.18f, 257.158f, 1.44f);
            break;
        case 7030:// Karazhan
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -11119.6f, -2011.42f, 47.09f, 0.65f);
            break;
        case 7035:// Molten Core
            CloseGossipMenuFor(player);
            player->TeleportTo(230, 1114.85f, -457.76f, -102.81f, 3.83f);
            break;
        case 7040:// Scarlet Monastery
            CloseGossipMenuFor(player);
            player->TeleportTo(0, 2843.89f, -693.74f, 139.32f, 5.11f);
            break;
        case 7045:// Scholomance
            CloseGossipMenuFor(player);
            player->TeleportTo(0, 1273.06f, -2574.01f, 92.66f, 2.06f);
            break;
        case 7050:// Shadowfang Keep
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -239.54f, 1550.8f, 76.89f, 1.18f);
            break;
        case 7055:// Stratholme
            CloseGossipMenuFor(player);
            player->TeleportTo(0, 3370.76f, -3343.63f, 142.26f, 5.23f);
            break;
        case 7060:// Sunken Temple
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -10346.92f, -3851.90f, -43.41f, 6.09f);
            break;
        case 7065:// The Stockade
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -8766.89f, 844.6f, 88.43f, 0.69f);
            break;
        case 7070:// Uldaman
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -6070.72f, -2955.33f, 209.78f, 0.05f);
            break;
        case 7075:// Zul'Aman
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 6851.09f, -7979.71f, 183.54f, 4.72f);
            break;
        case 7080:// Zul'Gurub
            CloseGossipMenuFor(player);
            player->TeleportTo(0, -11916.4f, -1216.23f, 92.28f, 4.75f);
            break;

            //////////////////////////////////////////////////OUTLAND///////////////////////////////////////////////////////////////
        case 8005:// Black Temple
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -3649.1f, 317.33f, 35.19f, 2.97f);
            break;
        case 8010:// Coilfang Reservoir
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 721.08f, 6846.77f, -68.75f, 0.34f);
            break;
        case 8015:// Gruul's Lair
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 3539.01f, 5082.36f, 1.69f, 0.0f);
            break;
        case 8020:// Hellfire Citadel
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -359.8366f, 3167.5708f, -98.0376f, 5.2976f);
            break;
        case 8025:// Tempest Keep
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 3087.62f, 1376.27f, 184.8f, 4.63f);
            break;
            //������
        case GOSSIP_ACTION_INFO_DEF + 214: //���Ӷ���
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -8177.89f, -4181.23f, -167.552f, 0.913338f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 215: //̫��֮���ߵ�
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 12574.1f, -6774.81f, 15.0904f, 3.13788f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 200: //��ɫ����
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -8734.3f, -4230.11f, -209.5f, 2.16212f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 201: //��ϣ��˹����������
            CloseGossipMenuFor(player);
            player->TeleportTo(1, -8404.3f, -4070.62f, -208.586f, 0.237038f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 202: // ��Ӱ�Թ�
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -3627.9f, 4941.98f, -101.049f, 3.16039f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 203: //������Ĺ
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -3104.18f, 4945.52f, -101.507f, 6.22344f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 204: //�½����Ѩ
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -3362.04f, 5209.85f, -101.05f, 1.60924f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 205: //�������ǽ
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -360.671f, 3071.9f, -15.0977f, 1.89389f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 206: //��Ѫ��¯
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -291.324f, 3149.1f, 31.5541f, 2.27147f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 207: //�������
            CloseGossipMenuFor(player);
            player->TeleportTo(530, -305.79f, 3061.63f, -2.53847f, 1.88888f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 208: //��ħ����
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 3308.92f, 1340.72f, 505.56f, 4.94686f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 209: //��Դ��
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 2867.12f, 1549.42f, 252.159f, 3.82218f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 210: //��̬��
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 3407.11f, 1488.48f, 182.838f, 5.59559f);
            break;
        case GOSSIP_ACTION_INFO_DEF + 211: //ū��Χ��
        case GOSSIP_ACTION_INFO_DEF + 212: //�����ؽ�
        case GOSSIP_ACTION_INFO_DEF + 213: //�İ�����
            CloseGossipMenuFor(player);
            player->TeleportTo(530, 717.282f, 6979.87f, -73.0281f, 1.50287f);
            break;
        
#pragma endregion
        }
        
    }
};
#pragma endregion

#pragma region �ۺ�ѵ��ʦ
class npc_synthesistrainer : public CreatureScript
{
public:
    npc_synthesistrainer() : CreatureScript("npc_synthesistrainer") { }

    struct npc_synthesistrainerAI : public ScriptedAI
    {
        npc_synthesistrainerAI(Creature* creature) : ScriptedAI(creature) { }

        bool GossipHello(Player* player) override
        {
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_Holy_DevineAegis:30|tְҵ����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_sword_68:30|t��������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Scroll_11:30|t��ҵ����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Scroll_12:30|t�����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Achievement_general:30|t|cFF0000FF����˫�츳|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 36,
                "��ȷ��Ҫ����˫�츳��\n���ã�", 1000*GOLD, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_misc_platnumdisks:30|t|cFF1E90FF�����츳|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5,
                "��ȷ��Ҫ�����츳��\n���ã�", player->ResetTalentsCost(), false);
            AddGossipItemFor(player, 0, "|TInterface/COMMON/VOICECHAT-MUTED:15|t�ر�", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);
            player->TalkedToCreature(me->GetEntry(), me->GetGUID());
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
            return true;
        }

        bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            if (!player)
                return true;

            WorldSession* m_session = player->GetSession();
            uint8 m_class = player->GetClass();
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1: //ְҵ
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_Holy_Power:30|tսʿ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Ability_Paladin_BeaconofLight:30|tʥ��ʿ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Ability_hunter_runningshot:30|t����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Achievement_Boss_EdwinVancleef:30|t����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_Arcane_FocusedPower:30|t��ʦ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_Holy_PrayerofShadowProtection:30|t��ʿ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Ability_Druid_ForceofNature:30|t��³��", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_Holy_GuardianSpirit:30|t��ʦ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_nature_bloodlust:30|t����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3: //��ҵ
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_misc_pelt_wolf_01:30|t��Ƥ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_tailoring:30|t�÷�", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_pick_02:30|t�ڿ�", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_herbalism:30|t��ҩ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_blacksmithing:30|t����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_engraving:30|t��ħ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_engineering:30|t����ѧ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_alchemy:30|t������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_inscription_tradeskill01:30|t����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_leatherworking:30|t��Ƥ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Jewelcrafting_Gem_14:30|t�鱦", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4: //����
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_fishing:30|t����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_sealofsacrifice:30|t����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_misc_food_15:30|t���", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 34);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Ability_mount_ridinghorse:30|t����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35);
                AddGossipItemFor(player, 0, "<-[���˵�]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5: //�����츳
            {
                if (player->GetLevel() < 10)
                {
                    CloseGossipMenuFor(player);
                    return true;
                }
                // remove fake death
                if (player->HasUnitState(UNIT_STATE_DIED))
                    player->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

                if (!(player->ResetTalents()))
                {
                    m_session->SendNotification("�㻹û�з����κ��츳�㡣");
                    CloseGossipMenuFor(player);
                    return true;
                }

                player->SendTalentsInfoData(false);
                me->CastSpell(player, 14867, true);                  //spell: "Untalent Visual Effect"
                CloseGossipMenuFor(player);
            }break;
            case GOSSIP_ACTION_INFO_DEF + 20: //���˵�
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_Holy_DevineAegis:30|tְҵ����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_sword_68:30|t��������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Scroll_11:30|t��ҵ����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Scroll_12:30|t�����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Achievement_general:30|t|cFF0000FF����˫�츳|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 36,
                    "��ȷ��Ҫ����˫�츳��\n���ã�", 1000 * GOLD, false);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_misc_platnumdisks:30|t|cFF1E90FF�����츳|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5,
                    "��ȷ��Ҫ�����츳��\n���ã�", player->ResetTalentsCost(), false);
                AddGossipItemFor(player, 0, "|TInterface/COMMON/VOICECHAT-MUTED:15|t�ر�", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 0: //�ر�
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 6: //սʿ
            {
                if (m_class != CLASS_WARRIOR) { CloseGossipMenuFor(player); return true; }
                else { m_session->SendTrainerList(me, 914); }
            }break;                
            case GOSSIP_ACTION_INFO_DEF + 7: //��ʿ
            {
                if (m_class != CLASS_PALADIN){ CloseGossipMenuFor(player); return true; }
                else { m_session->SendTrainerList(me, 928); }
            }break;
            case GOSSIP_ACTION_INFO_DEF + 8: //����
            {
                if (m_class != CLASS_HUNTER) { CloseGossipMenuFor(player); return true; }
                else { m_session->SendTrainerList(me, 4138); }
            }break;
            case GOSSIP_ACTION_INFO_DEF + 9: //����
            {
                if (m_class != CLASS_ROGUE) { CloseGossipMenuFor(player); return true; }
                else
                    m_session->SendTrainerList(me, 4584);               
            }break;
            case GOSSIP_ACTION_INFO_DEF + 10: //��ʦ
            {
                if (m_class != CLASS_MAGE) { CloseGossipMenuFor(player); return true; }
                else
                    m_session->SendTrainerList(me, 331);
            }break;
            case GOSSIP_ACTION_INFO_DEF + 11: //��ʿ
            {
                if (m_class != CLASS_WARLOCK) { CloseGossipMenuFor(player); return true; }
                else
                    m_session->SendTrainerList(me, 461);
            }break;
            case GOSSIP_ACTION_INFO_DEF + 12: //��³��
            {
                if (m_class != CLASS_DRUID) { CloseGossipMenuFor(player); return true; }
                else
                    m_session->SendTrainerList(me, 4217);
            }break;
            case GOSSIP_ACTION_INFO_DEF + 13: //��ʦ
            {
                if (m_class != CLASS_PRIEST) { CloseGossipMenuFor(player); return true; }
                else
                    m_session->SendTrainerList(me, 4606);
            }break;
            case GOSSIP_ACTION_INFO_DEF + 14: //����
            {
                if (m_class != CLASS_SHAMAN) { CloseGossipMenuFor(player); return true; }
                else
                    m_session->SendTrainerList(me, 3032);
            }break;
            case GOSSIP_ACTION_INFO_DEF + 21: //��Ƥ                
                m_session->SendTrainerList(me, 33618);
                break;
            case GOSSIP_ACTION_INFO_DEF + 22: //�÷�                
                m_session->SendTrainerList(me, 33613);
                break;
            case GOSSIP_ACTION_INFO_DEF + 23: //�ɿ�                
                m_session->SendTrainerList(me, 33617);
                break;
            case GOSSIP_ACTION_INFO_DEF + 24: //��ҩ                
                m_session->SendTrainerList(me, 33616);
                break;
            case GOSSIP_ACTION_INFO_DEF + 25: //����                
                m_session->SendTrainerList(me, 33609);
                break;
            case GOSSIP_ACTION_INFO_DEF + 26: //��ħ                
                m_session->SendTrainerList(me, 33610);
                break;
            case GOSSIP_ACTION_INFO_DEF + 27: //����ѧ                
                m_session->SendTrainerList(me, 33611);
                break;
            case GOSSIP_ACTION_INFO_DEF + 28: //������                
                m_session->SendTrainerList(me, 33608);
                break;
            case GOSSIP_ACTION_INFO_DEF + 29: //����                
                m_session->SendTrainerList(me, 33615);
                break;
            case GOSSIP_ACTION_INFO_DEF + 30: //��Ƥ                
                m_session->SendTrainerList(me, 33612);
                break;
            case GOSSIP_ACTION_INFO_DEF + 31: //�鱦                
                m_session->SendTrainerList(me, 33614);
                break;
            case GOSSIP_ACTION_INFO_DEF + 32: //����                
                m_session->SendTrainerList(me, 33623);
                break;
            case GOSSIP_ACTION_INFO_DEF + 33: //����                
                m_session->SendTrainerList(me, 33621);
                break;
            case GOSSIP_ACTION_INFO_DEF + 34: //���                
                m_session->SendTrainerList(me, 33619);
                break;
            case GOSSIP_ACTION_INFO_DEF + 35: //����                
                m_session->SendTrainerList(me, 35100);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2: //��������                
                m_session->SendTrainerList(me, 11867);
                break;
            case GOSSIP_ACTION_INFO_DEF + 36: //˫�츳
            {
                if (player->GetLevel() < 40)
                {
                    m_session->SendNotification("��ĵȼ�����%d�����޷�����˫�츳��", 40);
                    CloseGossipMenuFor(player);
                    return true;
                }

                if (player->GetSpecsCount() > 1)
                {
                    m_session->SendNotification("���Ѿ�������˫�츳�ˡ�");
                    CloseGossipMenuFor(player);
                    return true;
                }

                //debug
                //m_session->SendNotification("��ǰSpecsCount: %d", player->GetSpecsCount());

                player->ModifyMoney(int32(-1000*GOLD));
                player->CastSpell(player, 63680, true);
                player->CastSpell(player, 63624, true);
                player->UpdateSpecCount(2);
                CloseGossipMenuFor(player);
            }break;
            }

            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_synthesistrainerAI(creature);
    }
};

#pragma endregion

void AddSC_npc_newplayerguide()
{
    new npc_newplayerguide();
    new item_vipgem();    
    new npc_synthesistrainer();
}
