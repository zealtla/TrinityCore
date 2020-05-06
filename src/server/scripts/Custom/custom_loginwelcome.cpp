#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include <World\World.h>
#include "ScriptedGossip.h"
#pragma execution_character_set("utf-8")

#define AllianceIcon "|cff3399FF[|r|TInterface/ICONS/Achievement_PVP_A_A:13|t|cff3399FF����]|r"
#define HordeIcon "|cffCC0000[|r|TInterface/ICONS/Achievement_PVP_H_H:13|t|cffCC0000����]|r"
#define WelcomeIcon "|TInterface/ICONS/Achievement_BG_winbyten:13|t"
#define CongraIcon "|TInterface/ICONS/Achievement_BG_trueAVshutout:13|t"

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
            }
            else
            {
                std::ostringstream ss;
                ss << WelcomeIcon << "|cffFF69B4" << "���һ�ӭ|r" << HordeIcon << player->GetPlayerNameLink() << "|cffFF69B4" << "�������ħ��|r";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
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
};

void AddSC_Custom_Login()
{
    new CustomLoginScript();
}
