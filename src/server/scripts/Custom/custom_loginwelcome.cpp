#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "World.h"
#include "ScriptedGossip.h"
#include "Mail.h"
#include "DatabaseEnv.h"
#include "Item.h"
#pragma execution_character_set("utf-8")

#define AllianceIcon "|cff3399FF[|r|TInterface/ICONS/Inv_misc_tournaments_banner_human:13|t|cff3399FF联盟]|r"
#define HordeIcon "|cffCC0000[|r|TInterface/ICONS/Inv_misc_tournaments_symbol_orc:13|t|cffCC0000部落]|r"
#define WelcomeIcon "|TInterface/ICONS/Achievement_BG_winbyten:13|t"
#define CongraIcon "|TInterface/ICONS/Achievement_BG_trueAVshutout:13|t"
#define ServerTips "|cFF32CD32蚩尤魔兽70级|r\n|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n经验：起始等级60级，打怪|cFFFFD7002|r倍，任务|cFFFFD7003|r倍；\n\n\n声望：1倍\n\n\n其余均仿照官服设置，玩家QQ群：|cFFFF69B4 123456|r"

void ShowTips(Player* player)
{
    ClearGossipMenuFor(player);
    AddGossipItemFor(player, 30, "notify", 0, 999, ServerTips, 0, false);   
    SendGossipMenuFor(player, 999, player->GetGUID());
}

class CustomLoginScript : public PlayerScript
{

public:
    CustomLoginScript() : PlayerScript("CustomLoginScript") { }
   
    void OnLogin(Player* player, bool firstLogin) override
    {
        if (firstLogin)
        {
            //首次登录
            if (player->GetTeamId() == TEAM_ALLIANCE)
            {
                std::ostringstream ss;                
                ss << WelcomeIcon << "|cffFF69B4" << "热烈欢迎|r" << AllianceIcon << player->GetPlayerNameLink() << "|cffFF69B4" << "加入蚩尤魔兽|r";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
                ShowTips(player);
            }
            else
            {
                std::ostringstream ss;
                ss << WelcomeIcon << "|cffFF69B4" << "热烈欢迎|r" << HordeIcon << player->GetPlayerNameLink() << "|cffFF69B4" << "加入蚩尤魔兽|r";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
                ShowTips(player);
            }           
        }
        else
        {
            std::ostringstream ss;
            if (player->GetTeamId() == TEAM_ALLIANCE)            
                ss << AllianceIcon << player->GetPlayerNameLink() << "上线了。";            
            else
                ss << HordeIcon << player->GetPlayerNameLink() << "上线了。";

            sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
        }
    }

    //升到70级奖励：双天赋x1 36格包x1
    void OnLevelChanged(Player* player, uint8 /*oldLevel*/) override
    {
        if (player->GetLevel() == 70)
        {
            //全服广播
            std::string str = "|cFFFFFF00";
            str += "恭喜玩家|r";
            str += player->GetPlayerNameLink();
            str += "|cFFFFFF00";
            str += "升到70级！|r";

            WorldPacket data(SMSG_NOTIFICATION, (str.size() + 1));
            data << str;
            sWorld->SendGlobalMessage(&data);
            //发送邮件
            std::string subject = "恭喜升至70级！";
            std::string text = player->GetName() + ":\n        恭喜你升到70级！\n[蚩尤魔兽]奖励你以下物品，聊表心意：\n---|cffa335ee[双天赋]|r x1---\n---|cffa335ee[至尊背包]|r x1---\n \n \n \n [蚩尤魔兽管理组] 祝你游戏愉快！";

            typedef std::pair<uint32, uint32> ItemPair;
            typedef std::list< ItemPair > ItemPairs;
            ItemPairs items;
            //23162 36格背包
            items.push_back(ItemPair(23162, 1));
            //100003 双天赋
            items.push_back(ItemPair(100003, 1));

            // from console show nonexisting sender
            MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);

            // fill mail
            MailDraft draft(subject, text);

            CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

            for (ItemPairs::const_iterator itr = items.begin(); itr != items.end(); ++itr)
            {
                if (Item* item = Item::CreateItem(itr->first, itr->second, 0))
                {
                    item->SaveToDB(trans);              // Save to prevent being lost at next mail load. If send fails, the item will be deleted.
                    draft.AddItem(item);
                }
            }

            draft.SendMailTo(trans, MailReceiver(player, player->GetGUID().GetCounter()), sender);
            CharacterDatabase.CommitTransaction(trans);
        }
    }
};

void AddSC_Custom_Login()
{
    new CustomLoginScript();
}
