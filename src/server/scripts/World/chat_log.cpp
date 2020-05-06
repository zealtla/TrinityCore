/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "Channel.h"
#include "Group.h"
#include "Guild.h"
#include "Log.h"
#include "Player.h"
#pragma execution_character_set("utf-8")

class ChatLogScript : public PlayerScript
{
    public:
        ChatLogScript() : PlayerScript("ChatLogScript") { }

        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg) override
        {
            switch (type)
            {
                case CHAT_MSG_SAY:
                    TC_LOG_DEBUG("chat.log.say", "[%s]˵: %s",
                        player->GetName().c_str(), msg.c_str());
                    break;

                case CHAT_MSG_EMOTE:                    
                    break;

                case CHAT_MSG_YELL:
                    TC_LOG_DEBUG("chat.log.yell", "[%s]��: %s",
                        player->GetName().c_str(), msg.c_str());
                    break;
            }
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver) override
        {
            if (lang != LANG_ADDON)
                TC_LOG_DEBUG("chat.log.whisper", "[%s]-����-[%s]: %s",
                    player->GetName().c_str(), receiver ? receiver->GetName().c_str() : "<unknown>", msg.c_str());
            else
                TC_LOG_DEBUG("chat.log.addon.whisper", "[%s]-����[%s]: %s",
                    player->GetName().c_str(), receiver ? receiver->GetName().c_str() : "<unknown>", msg.c_str());
        }

        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group) override
        {
            //! NOTE:
            //! LANG_ADDON can only be sent by client in "PARTY", "RAID", "GUILD", "BATTLEGROUND", "WHISPER"
            switch (type)
            {
                case CHAT_MSG_PARTY:
                    if (lang != LANG_ADDON)
                        TC_LOG_DEBUG("chat.log.party", "[%s]����: %s",
                            player->GetName().c_str(), msg.c_str());
                    else
                        TC_LOG_DEBUG("chat.log.addon.party", "[%s]����: %s",
                            player->GetName().c_str(), msg.c_str());
                    break;

                case CHAT_MSG_PARTY_LEADER:
                    TC_LOG_DEBUG("chat.log.party", "[%s]�ӳ�: %s",
                        player->GetName().c_str(), msg.c_str());
                    break;

                case CHAT_MSG_RAID:
                    if (lang != LANG_ADDON)
                        TC_LOG_DEBUG("chat.log.raid", "[%s]�Ŷ�: %s",
                            player->GetName().c_str(), msg.c_str());
                    else
                        TC_LOG_DEBUG("chat.log.addon.raid", "[%s]�Ŷ�: %s",
                            player->GetName().c_str(), msg.c_str());
                    break;

                case CHAT_MSG_RAID_LEADER:
                    TC_LOG_DEBUG("chat.log.raid", "[%s]�Ŷ�����: %s",
                        player->GetName().c_str(), msg.c_str());
                    break;

                case CHAT_MSG_RAID_WARNING:
                    TC_LOG_DEBUG("chat.log.raid", "[%s]�Ŷ����侯��: %s",
                        player->GetName().c_str(), msg.c_str());
                    break;

                case CHAT_MSG_BATTLEGROUND:
                    if (lang != LANG_ADDON)
                        TC_LOG_DEBUG("chat.log.bg", "[%s]ս��: %s",
                            player->GetName().c_str(), msg.c_str());
                    else
                        TC_LOG_DEBUG("chat.log.addon.bg", "[%s]ս��: %s",
                            player->GetName().c_str(), msg.c_str());
                    break;

                case CHAT_MSG_BATTLEGROUND_LEADER:
                    TC_LOG_DEBUG("chat.log.bg", "[%s]ս������: %s",
                        player->GetName().c_str(), msg.c_str());
                    break;
            }
        }

        void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild) override
        {
            switch (type)
            {
                case CHAT_MSG_GUILD:
                    if (lang != LANG_ADDON)
                        TC_LOG_DEBUG("chat.log.guild", "[%s]����(%s): %s",
                            player->GetName().c_str(), guild ? guild->GetName().c_str() : "<unknown>", msg.c_str());
                    else
                        TC_LOG_DEBUG("chat.log.addon.guild", "[%s]���͸�����<%s>: %s",
                            player->GetName().c_str(), guild ? guild->GetName().c_str() : "<unknown>", msg.c_str());
                    break;

                case CHAT_MSG_OFFICER:
                    TC_LOG_DEBUG("chat.log.guild.officer", "[%s]�����Ա(%s): %s",
                        player->GetName().c_str(), guild ? guild->GetName().c_str() : "<unknown>", msg.c_str());
                    break;
            }
        }
};

void AddSC_chat_log()
{
    new ChatLogScript();
}
