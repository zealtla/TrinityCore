#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "WorldSession.h"
#pragma execution_character_set("utf-8")

class scroll_Items : public ItemScript
{
public:
    scroll_Items() : ItemScript("scroll_Items") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override // Any hook here
    {
        if (player->GetSpecsCount() > 1)
        {
            player->GetSession()->SendNotification("你已经开启过双天赋了。");
            return false;
        }

        player->CastSpell(player, 63680, true);
        player->CastSpell(player, 63624, true);
        player->UpdateSpecCount(2);       
        return false; // Cast the spell on use normally
    }   
};

void AddSC_custom_Items() // Add to scriptloader normally
{
    new scroll_Items();
}
