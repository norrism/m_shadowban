#m_shadowban - InspIRCd Module

Description
-

m_shadowban is a third party InspIRCd module that adds an extban option 'w' to mute users without their knowledge. This module is derived from m_muteban which offers similar functionality, but notifies the user that their messages are blocked. m_shadowban leads the user to believe that their messages are being seen and ignored.

Installation
-

1. Download the file m_shadowban.cpp and place it in the '/src/modules/' directory of your InspIRCd installation.

2. Add the following code to your 'modules.conf' file

        #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
        # Shadowban: Implements extended ban 'w', which stops anyone matching
        # a mask like +b w:nick!user@host from speaking on channel, without
        # notifying the user that their messages are blocked.
        <module name="m_shadowban.so">

3. Run the following command from the root InspIRCd directory:

        make && make install

4. Start the InspIRCd server.

Usage
-

    /mode <channel> +b w:<nick>!<user>@<host>
