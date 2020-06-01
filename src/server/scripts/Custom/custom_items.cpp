#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "WorldSession.h"
#include "SpellMgr.h"
#include "Chat.h"
#pragma execution_character_set("utf-8")

class scroll_Items : public ItemScript
{
public:
    scroll_Items() : ItemScript("scroll_Items") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override // Any hook here
    {
        if (player->GetSpecsCount() > 1)
        {
            player->GetSession()->SendNotification("���Ѿ�������˫�츳�ˡ�");
            return false;
        }

        player->CastSpell(player, 63680, true);
        player->CastSpell(player, 63624, true);
        player->UpdateSpecCount(2);       
        return false; // Cast the spell on use normally
    }   
};


void MaxProfessionSkill(Player* player, int32 skillId, uint16 value)
{
    if (value > 375)
        value=375;
    
    player->SetSkill(skillId, player->GetSkillStep(skillId), value, 375);
}

#pragma region רҵ����
class scroll_ProfessionMax : public ItemScript
{
public:
    scroll_ProfessionMax() : ItemScript("scroll_ProfessionMax") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override // Any hook here
    {
        uint32 pitemEntry = item->GetEntry();

        switch (pitemEntry)
        {
        case 90000:
            MaxProfessionSkill(player, 393, 375);
            break;
        case 90001: //�÷�
            MaxProfessionSkill(player, 197, 375);
            break;
        case 90002: //�ɿ�
            MaxProfessionSkill(player, 186, 375);
            break;
        case 90003: //��ҩѧ
            MaxProfessionSkill(player, 182, 375);
            break;
        case 90004: //����
            MaxProfessionSkill(player, 164, 375);
            break;
        case 90005: //��ħ
            MaxProfessionSkill(player, 333, 375);
            break;
        case 90006: //����ѧ
            MaxProfessionSkill(player, 202, 375);
            break;
        case 90007: //������
            MaxProfessionSkill(player, 171, 375);
            break;
        case 90008: //����
            MaxProfessionSkill(player, 773, 375);
            break;
        case 90009: //��Ƥ
            MaxProfessionSkill(player, 165, 375);
            break;
        case 90010: //�鱦
            MaxProfessionSkill(player, 755, 375);
            break;
        }
        
        return false; // Cast the spell on use normally
    }
};
#pragma endregion

void AddSC_custom_Items() // Add to scriptloader normally
{
    new scroll_Items();
    new scroll_ProfessionMax();   
}
