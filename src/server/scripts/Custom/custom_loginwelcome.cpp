#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "World.h"
#include "ScriptedGossip.h"
#include "Mail.h"
#include "DatabaseEnv.h"
#include "Item.h"
#pragma execution_character_set("utf-8")

#define AllianceIcon "|cff3399FF[|r|TInterface/ICONS/Inv_misc_tournaments_banner_human:13|t|cff3399FF����]|r"
#define HordeIcon "|cffCC0000[|r|TInterface/ICONS/Inv_misc_tournaments_symbol_orc:13|t|cffCC0000����]|r"
#define WelcomeIcon "|TInterface/ICONS/Achievement_BG_winbyten:13|t"
#define CongraIcon "|TInterface/ICONS/Achievement_BG_trueAVshutout:13|t"
#define ServerTips "|cFF32CD32���ħ��70��|r\n|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n���飺��ʼ�ȼ�60�������|cFFFFD7002|r��������|cFFFFD7003|r����\n\n\n������1��\n\n\n��������չٷ����ã����QQȺ��|cFFFF69B4 123456|r"

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
            //�״ε�¼
            if (player->GetTeamId() == TEAM_ALLIANCE)
            {
                std::ostringstream ss;                
                ss << WelcomeIcon << "|cffFF69B4" << "���һ�ӭ|r" << AllianceIcon << player->GetPlayerNameLink() << "|cffFF69B4" << "�������ħ��|r";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
                ShowTips(player);
            }
            else
            {
                std::ostringstream ss;
                ss << WelcomeIcon << "|cffFF69B4" << "���һ�ӭ|r" << HordeIcon << player->GetPlayerNameLink() << "|cffFF69B4" << "�������ħ��|r";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
                ShowTips(player);
            }           
        }
        else
        {
            std::ostringstream ss;
            if (player->GetTeamId() == TEAM_ALLIANCE)            
                ss << AllianceIcon << player->GetPlayerNameLink() << "�����ˡ�";            
            else
                ss << HordeIcon << player->GetPlayerNameLink() << "�����ˡ�";

            sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
        }
    }

    //����70��������˫�츳x1 36���x1
    void OnLevelChanged(Player* player, uint8 /*oldLevel*/) override
    {
        if (player->GetLevel() == 70)
        {
            //ȫ���㲥
            std::string str = "|cFFFFFF00";
            str += "��ϲ���|r";
            str += player->GetPlayerNameLink();
            str += "|cFFFFFF00";
            str += "����70����|r";

            WorldPacket data(SMSG_NOTIFICATION, (str.size() + 1));
            data << str;
            sWorld->SendGlobalMessage(&data);
            //�����ʼ�
            std::string subject = "��ϲ����70����";
            std::string text = player->GetName() + ":\n        ��ϲ������70����\n[���ħ��]������������Ʒ���ı����⣺\n---|cffa335ee[˫�츳]|r x1---\n---|cffa335ee[���𱳰�]|r x1---\n \n \n \n [���ħ�޹�����] ף����Ϸ��죡";

            typedef std::pair<uint32, uint32> ItemPair;
            typedef std::list< ItemPair > ItemPairs;
            ItemPairs items;
            //23162 36�񱳰�
            items.push_back(ItemPair(23162, 1));
            //100003 ˫�츳
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
