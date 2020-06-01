#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Item.h"
#include "Chat.h"
#include "WorldSession.h"
#include "PassiveAI.h"
#include "DatabaseEnv.h"
#pragma execution_character_set("utf-8")

#define ADV_0 "暂无宣传活动"

#pragma region Vip
/* 商城NPC entry:100006
*  菜单:
*  1.专业秒升 <积分>
*  2.声望秒升 <金币>
*  3.坐骑
*  4.幻化物品
*  5.药剂
*/
class npc_vip : public CreatureScript
{
public:
    npc_vip() : CreatureScript("npc_vip") { }

    struct npc_vipAI : public ScriptedAI
    {
        npc_vipAI(Creature* creature) : ScriptedAI(creature), _talkCheckTimer(600000) { }

        bool GossipHello(Player* player) override
        {
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface\\ICONS\\Inv_scroll_11:30|t专业秒升", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface\\ICONS\\Inv_scroll_12:30|t声望秒升", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface\\ICONS\\Ability_mount_ridinghorse:30|t稀有坐骑", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface\\ICONS\\Achievement_BG_grab_cap_flagunderXseconds:30|t幻化物品", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface\\ICONS\\Achievement_BG_masterofallBGs:30|t变身卡", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface\\ICONS\\INV_Enchant_DreamShard_01:30|t杂物", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|cFF0000FF|TInterface\\ICONS\\Spell_holy_proclaimchampion:30|t〓领取积分〓|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            AddGossipItemFor(player, 7, "|TInterface/COMMON/VOICECHAT-MUTED:15|t关闭", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);
            
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
            case GOSSIP_ACTION_INFO_DEF + 0: //关闭
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 1: //专业
                player->GetSession()->SendListInventory(me->GetGUID(), 100008);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2: //声望
                player->GetSession()->SendListInventory(me->GetGUID(), 100009);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3: //坐骑
                player->GetSession()->SendListInventory(me->GetGUID(), 100010);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4: //幻化
                player->GetSession()->SendListInventory(me->GetGUID(), 100011);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5: //变身
                player->GetSession()->SendListInventory(me->GetGUID(), 100012);
                break;
            case GOSSIP_ACTION_INFO_DEF + 6: //杂物
                player->GetSession()->SendListInventory(me->GetGUID(), 100013);
                break;
            case GOSSIP_ACTION_INFO_DEF + 7: //领取积分
            {
                uint32 jf = 0;
                QueryResult GetAccountId = CharacterDatabase.PQuery("SELECT `account` FROM `characters` WHERE `name` = '%s'", player->GetName());
                if (GetAccountId)
                {
                    Field* field2 = GetAccountId->Fetch();
                    uint32 AccountID = field2[0].GetInt32();
                    QueryResult result = LoginDatabase.PQuery("SELECT `jf` FROM auth.`account` WHERE `id` = '%u'", AccountID);
                    Field* fields = result->Fetch();
                    if (result)
                    {
                        jf = fields[0].GetUInt32();
                        if (jf > 0)
                        {
                            player->AddItem(99999, jf);

                            LoginDatabase.PExecute("update auth.account set jf=0 where id= '%u' ", AccountID);
                            player->GetSession()->SendNotification("|cff4CFF00积分领取成功，获得积分:[%d]!! ", jf);
                        }
                        else
                            player->GetSession()->SendNotification("|cff4CFF00你没有积分领取，当前积分:[%d]!! ", jf);
                    }
                }

                CloseGossipMenuFor(player);
            }break;
            }
            
            return true;
        }

        void UpdateAI(uint32 diff) override
        {
            if (diff < _talkCheckTimer)
            {
                _talkCheckTimer -= diff;
                return;
            }

            _talkCheckTimer = 600000;
            Talk(0);
        }

        uint32 _talkCheckTimer;
    };
   
    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vipAI(creature);
    }
};
#pragma endregion

#pragma region 材料商
class npc_materialvendor : public CreatureScript
{
public:
    npc_materialvendor() : CreatureScript("npc_materialvendor") { }

    struct npc_materialvendorAI : public ScriptedAI
    {
        npc_materialvendorAI(Creature* creature) : ScriptedAI(creature) { }

        bool GossipHello(Player* player) override
        {
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_potion_119:30|t专业材料", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_misc_dust_01:30|t施法材料", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_misc_food_64:30|t食物", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_potion_162:30|t毒药", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_misc_ammo_bullet_06:30|t弓箭/弹药", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            AddGossipItemFor(player, 0, "|TInterface/COMMON/VOICECHAT-MUTED:15|t关闭", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);

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
            case GOSSIP_ACTION_INFO_DEF + 1: //专业
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_misc_pelt_wolf_01:30|t剥皮/制皮供应商", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_tailoring:30|t裁缝供应商", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);                
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_herbalism:30|t草药学供应商", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_blacksmithing:30|t锻造供应商", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_engraving:30|t附魔供应商", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_engineering:30|t工程学供应商", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Trade_alchemy:30|t炼金术供应商", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_inscription_tradeskill01:30|t铭文供应商", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Jewelcrafting_Gem_14:30|t珠宝供应商", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                AddGossipItemFor(player, 0, "<-主菜单", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);

                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2: //施法
                player->GetSession()->SendListInventory(me->GetGUID(), 90003);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3: //食物
                player->GetSession()->SendListInventory(me->GetGUID(), 19232);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4: //毒药
                player->GetSession()->SendListInventory(me->GetGUID(), 4585);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5: //弹药
                player->GetSession()->SendListInventory(me->GetGUID(), 19243);
                break;
            case GOSSIP_ACTION_INFO_DEF + 0: //关闭
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 20: //主菜单
                ClearGossipMenuFor(player);
                AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_potion_119:30|t专业材料", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_misc_dust_01:30|t施法材料", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_misc_food_64:30|t食物", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_potion_162:30|t毒药", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
				AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_misc_ammo_bullet_06:30|t弓箭/弹药", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                AddGossipItemFor(player, 0, "|TInterface/COMMON/VOICECHAT-MUTED:15|t关闭", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);

                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6: //制皮/剥皮供应商
                player->GetSession()->SendListInventory(me->GetGUID(), 28718);
                break;
            case GOSSIP_ACTION_INFO_DEF + 7: //裁缝供应商
                player->GetSession()->SendListInventory(me->GetGUID(), 4168);
                break;
            case GOSSIP_ACTION_INFO_DEF + 8: //草药
                player->GetSession()->SendListInventory(me->GetGUID(), 28868);
                break;
            case GOSSIP_ACTION_INFO_DEF + 9: //锻造
                player->GetSession()->SendListInventory(me->GetGUID(), 33599);
                break;
            case GOSSIP_ACTION_INFO_DEF + 10: //附魔
                player->GetSession()->SendListInventory(me->GetGUID(), 33597);
                break;
            case GOSSIP_ACTION_INFO_DEF + 11: //工程
                player->GetSession()->SendListInventory(me->GetGUID(), 33594);
                break;
            case GOSSIP_ACTION_INFO_DEF + 12: //炼金
                player->GetSession()->SendListInventory(me->GetGUID(), 33600);
                break;
            case GOSSIP_ACTION_INFO_DEF + 13: //铭文
                player->GetSession()->SendListInventory(me->GetGUID(), 33598);
                break;
            case GOSSIP_ACTION_INFO_DEF + 14: //珠宝
                player->GetSession()->SendListInventory(me->GetGUID(), 16624);
                break;                        
            }

            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_materialvendorAI(creature);
    }
};
#pragma endregion

#pragma region 宣传活动
class npc_advertise : public CreatureScript
{
public:
    npc_advertise() : CreatureScript("npc_advertise") { }

    struct npc_advertiseAI : public ScriptedAI
    {
        npc_advertiseAI(Creature* creature) : ScriptedAI(creature), _talkCheckTimer(1200000) { }

        bool GossipHello(Player* player) override
        {
            AddGossipItemFor(player, 0, ADV_0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            AddGossipItemFor(player, 7, "关闭", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);
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
            case GOSSIP_ACTION_INFO_DEF + 0: //关闭
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 1: //ad
                CloseGossipMenuFor(player);
                break;
            }

            return true;
        }

        void UpdateAI(uint32 diff) override
        {
            if (diff < _talkCheckTimer)
            {
                _talkCheckTimer -= diff;
                return;
            }
            else
            {
                _talkCheckTimer = 1200000;
                //随机说话
                uint8 r = urand(0, 2);
                Talk(r);
                //放烟花
                if (r == 0)
                    me->CastSpell(me, 26304, false);
                else if (r == 1)
                    me->CastSpell(me, 26325, false);
                else
                    me->CastSpell(me, 26327, false);
            }            
        }

        uint32 _talkCheckTimer;
        //uint32 _castChekTimer;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_advertiseAI(creature);
    }
};
#pragma endregion

void AddSC_npc_vip()
{       
    new npc_vip();
    new npc_materialvendor();
    new npc_advertise();
}
