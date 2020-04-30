#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include <World\World.h>
#include "Channel.h"
#include "GameTime.h"
#include "WorldSession.h"
#pragma execution_character_set("utf-8")

std::string wcc_channel_name = "蚩尤魔兽";
uint32 wcc_channel_id = 1; //指定频道
uint64 wcc_delay = 5; //世界聊天CD
uint8 wcc_level = 1; //聊天等级限制

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

//默认频道文字颜色
std::string wcc_default = "|cffD2B48C";
//图标
//std::string wcc_icon = "|TInterface/ICONS/Achievement_reputation_01:13|t";
std::string wcc_server = "|cff32CD32"; //酸橙绿

class WORLD_CHANNEL_CHAT : public PlayerScript
{
public:
	WORLD_CHANNEL_CHAT() : PlayerScript("WORLD_CHANNEL_CHAT") { }

    void OnLogin(Player* player, bool /* firstLogin */) override
    {
        ChatHandler(player->GetSession()).PSendSysMessage("|cFF00FFFF综合频道默认为世界聊天频道，请勿刷屏和骂脏话！|r");
    }

	void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel) override
	{
        if (lang != LANG_ADDON)
        {
            if (player->IsGameMaster())
                return;

            //世界聊天等级限制
            if (player->GetLevel() < wcc_level)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("您的等级不够%d级，还不能使用世界频道。",wcc_level);
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
                        ChatHandler(player->GetSession()).PSendSysMessage("请您稍等一会才能再次发言。");
                    }
                    else
                    {
                        if (WorldChannelChat[guid].last_msg == msg)
                        {
                            ChatHandler(player->GetSession()).PSendSysMessage("请勿重复发言。");
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
