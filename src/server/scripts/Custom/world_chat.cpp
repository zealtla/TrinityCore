#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include <World\World.h>
#include "Channel.h"
#include "GameTime.h"
#include "WorldSession.h"
#include "log.h"
#pragma execution_character_set("utf-8")

std::string wcc_channel_name = "蚩尤魔兽";
uint32 wcc_channel_id = 1; //指定频道
uint64 wcc_delay = 10; //世界聊天CD
uint8 wcc_level = 62; //聊天等级限制

struct WorldChannelChatElements
{
    uint64 time;   
};

std::unordered_map<uint32, WorldChannelChatElements>WorldChannelChat;

//默认频道文字颜色
//std::string wcc_default = "|cffFFBDC0";
std::string wcc_server = "|cffFF6347"; //番茄色
std::string wcc_red = "|cffFF4500"; //橙红色

class WORLD_CHANNEL_CHAT : public PlayerScript
{
public:
    WORLD_CHANNEL_CHAT() : PlayerScript("WORLD_CHANNEL_CHAT") { }

    void OnLogin(Player* player, bool /* firstLogin */) override
    {
        ChatHandler(player->GetSession()).PSendSysMessage("[|cffFFBDC0综合频道|r]|cFF00FFFF默认为世界聊天频道，请文明聊天！|r");
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel) override
    {
        if (lang != LANG_ADDON)
        {
            uint32 raw_id = channel->GetChannelId();
            uint32 id;

            // channel id's seem to differ than what you see in game so we will convert them here.
            if (raw_id == 1) { id = 1; }

            if (id == wcc_channel_id)
            {
                //GM不允许使用
                if (player->IsGameMaster() || player->GetSession()->GetSecurity() > AccountTypes(0))
                {
                    msg = -1;
                    return;
                }
                    
                //世界聊天等级限制
                if (player->GetLevel() < wcc_level)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("%s等级不够%d级，还不能使用世界频道。|r", wcc_red, wcc_level);
                    msg = -1;
                    return;
                }

                if ((msg != "") && (msg != "Away") && (player->GetSession()->CanSpeak() == true))
                {
                    uint64 current_time = GameTime::GetGameTime();
                    uint32 guid = player->GetGUID();

                    if (!WorldChannelChat[guid].time)
                    {
                        WorldChannelChat[guid].time = (current_time - wcc_delay);                        
                    }

                    if ((current_time - WorldChannelChat[guid].time) < wcc_delay)
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("%s请稍等%d秒后才能再次发言。|r", wcc_red, wcc_delay);
                    }
                    else
                    {
                        char message[1024];                       
                        snprintf(message, 1024, "[%s%s|r]%s:%s", wcc_server.c_str(), wcc_channel_name.c_str(), player->GetPlayerNameLink().c_str(), msg.c_str());

                        WorldChannelChat[guid].time = current_time;
                        sWorld->SendServerMessage(SERVER_MSG_STRING, message);                       
                        //记录聊天信息
                        TC_LOG_DEBUG("chat.log.system", "[%s]世界: %s",
                            player->GetName().c_str(), msg.c_str());
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
