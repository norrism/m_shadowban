 /*
 * m_shadowban -- InspIRCd Module
 *
 *   Copyright (C) 2015 Michael Norris
 * 
 * Based on m_muteban from InspIRCd.
 * 
 * This file contains a third party module for InspIRCd.  You can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, version 2.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "inspircd.h"

/* $ModDesc: Implements extban +b w: - Shadowbans i.e: block messages from a user to a channel, without notifying the user that their messages are blocked */

class ModuleShadowBan : public Module
{
 private:
 public:
	void init()
	{
		Implementation eventlist[] = { I_OnUserPreMessage, I_OnUserPreNotice, I_On005Numeric };
		ServerInstance->Modules->Attach(eventlist, this, sizeof(eventlist)/sizeof(Implementation));
	}

	virtual ~ModuleShadowBan()
	{
	}

	virtual Version GetVersion()
	{
		return Version("Implements extban +b w: - Shadowbans",VF_NONE);
	}

	virtual ModResult OnUserPreMessage(User *user, void *dest, int target_type, std::string &text, char status, CUList &exempt_list)
	{
		if (!IS_LOCAL(user) || target_type != TYPE_CHANNEL)
			return MOD_RES_PASSTHRU;

		Channel* chan = static_cast<Channel*>(dest);
		if (chan->GetExtBanStatus(user, 'w') == MOD_RES_DENY && chan->GetPrefixValue(user) < VOICE_VALUE)
		{
			return MOD_RES_DENY;
		}

		return MOD_RES_PASSTHRU;
	}

	virtual ModResult OnUserPreNotice(User *user, void *dest, int target_type, std::string &text, char status, CUList &exempt_list)
	{
		return OnUserPreMessage(user, dest, target_type, text, status, exempt_list);
	}

	virtual void On005Numeric(std::string &output)
	{
		ServerInstance->AddExtBanChar('w');
	}
};


MODULE_INIT(ModuleShadowBan)

