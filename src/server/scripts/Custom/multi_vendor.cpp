#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Item.h"
#include "Chat.h"
#include "WorldSession.h"
#pragma execution_character_set("utf-8")

#define GUIDE_0 "|TInterface/ICONS/INV_Sword_27:30:30:-18:0|t|cFF228B22新手武器|r"
#define GUIDE_1 "|TInterface/ICONS/INV_Chest_Chain_11:30:30:-18:0|t|cFF228B22新手装备|r"
#define GUIDE_2 "|TInterface/ICONS/INV_Misc_Toy_05:30:30:-18:0|t|cFF228B22新手杂物|r"

#pragma region 新手商人
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
            SendGossipMenuFor(player, player->GetGossipTextId(me), me->GetGUID());
            return true;
        }

        bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1: //武器
                player->GetSession()->SendListInventory(me->GetGUID(), 90000);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2: //装备
                player->GetSession()->SendListInventory(me->GetGUID(), 90001);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3: //杂物
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

void AddSC_npc_newplayerguide()
{
    new npc_newplayerguide();    
}
