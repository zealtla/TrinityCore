#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include <World\World.h>
#include "Channel.h"
#include "GameTime.h"
#include "WorldSession.h"
#pragma execution_character_set("utf-8")

std::string wcc_channel_name = "���ħ��";
uint32 wcc_channel_id = 1; //ָ��Ƶ��
uint64 wcc_delay = 5; //��������CD
uint8 wcc_level = 1; //����ȼ�����

struct WorldChannelChatElements
{
    uint64 time;
    std::string last_msg;
};

std::unordered_map<uint32, WorldChannelChatElements>WorldChannelChat;

std::string wcc_TeamIcon[2] =
{
    "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Human:13|t",
    "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Orc:13|t"
};

std::string wcc_ClassIcon[11] =
{
    "|TInterface\\icons\\INV_Sword_27:13|t",
    "|TInterface\\icons\\INV_Hammer_01:13|t",
    "|TInterface\\icons\\INV_Weapon_Bow_07:13|t",
    "|TInterface\\icons\\INV_ThrowingKnife_04:13|t",
    "|TInterface\\icons\\INV_Staff_30:13|t",
    "|TInterface\\icons\\Spell_Deathknight_ClassIcon:13|t",
    "|TInterface\\icons\\inv_jewelry_talisman_04:13|t",
    "|TInterface\\icons\\INV_Staff_30:13|t",
    "|TInterface\\icons\\INV_Staff_30:13|t",
    "",
    "|TInterface\\icons\\Ability_Druid_Maul:13|t",
};

//Ĭ��Ƶ��������ɫ
std::string wcc_default = "|cffD2B48C";
//ͼ��
//std::string wcc_icon = "|TInterface/ICONS/Achievement_reputation_01:13|t";
std::string wcc_server = "|cff32CD32"; //�����

class WORLD_CHANNEL_CHAT : public PlayerScript
{
public:
	WORLD_CHANNEL_CHAT() : PlayerScript("WORLD_CHANNEL_CHAT") { }

    void OnLogin(Player* player, bool /* firstLogin */) override
    {
        ChatHandler(player->GetSession()).PSendSysMessage("|cFF00FFFF�ۺ�Ƶ��Ĭ��Ϊ��������Ƶ��������ˢ�������໰��|r");
    }

	void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel) override
	{
        if (lang != LANG_ADDON)
        {
            if (player->IsGameMaster())
                return;

            //��������ȼ�����
            if (player->GetLevel() < wcc_level)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("���ĵȼ�����%d����������ʹ������Ƶ����",wcc_level);
                return;
            }
                            
            uint32 raw_id = channel->GetChannelId();
            uint32 id;

            // channel id's seem to differ than what you see in game so we will convert them here.
            if (raw_id == 1) { id = 1; }

            if (id == wcc_channel_id)
            {
                if ((msg != "") && (msg != "Away") && (player->GetSession()->CanSpeak() == true))
                {
                    uint64 current_time = GameTime::GetGameTime();
                    uint32 guid = player->GetGUID();

                    if (!WorldChannelChat[guid].time)
                    {
                        WorldChannelChat[guid].time = (current_time - wcc_delay);
                        WorldChannelChat[guid].last_msg = "";
                    }

                    if ((current_time - WorldChannelChat[guid].time) < wcc_delay)
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("�����Ե�һ������ٴη��ԡ�");
                    }
                    else
                    {
                        if (WorldChannelChat[guid].last_msg == msg)
                        {
                            ChatHandler(player->GetSession()).PSendSysMessage("�����ظ����ԡ�");
                        }
                        else
                        {                            
                            uint8 team_id = player->GetTeamId();
                            std::string WCCMSG = "";

                            WCCMSG += "[" + wcc_server + wcc_channel_name + "|r]";
                            WCCMSG += "[" + wcc_TeamIcon[player->GetTeamId()] + "]";

                            WCCMSG += "[" + wcc_ClassIcon[player->GetClass() - 1] + "]";
                            WCCMSG += player->GetPlayerNameLink();
                            WCCMSG += ":" + wcc_default + msg;

                            WorldChannelChat[guid].time = current_time;
                            WorldChannelChat[guid].last_msg = msg;
                           
                            sWorld->SendServerMessage(SERVER_MSG_STRING, WCCMSG.c_str());
                        }
                    }
                }
                msg = -1;
            }
        }
	}
	
};

void AddSC_WorldChannelChat()
{	
	new WORLD_CHANNEL_CHAT();
}
