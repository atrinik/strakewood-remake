from Atrinik import *
import string, os
from inspect import currentframe

activator = WhoIsActivator()
me = WhoAmI()

guild_tag = "Mercenary"
guild_rank = ""

execfile(os.path.dirname(currentframe().f_code.co_filename) + "/quests.py")

quest_arch_name = quest_items["mercenary_guild"]["arch_name"]
quest_item_name = quest_items["mercenary_guild"]["item_name"]

msg = WhatIsMessage().strip().lower()
text = string.split(msg)

guild_force = activator.GetGuildForce()

if text[0] == "join":
	if guild_force.slaying == guild_tag:
		me.SayTo(activator, "\nYou are a Mercenary, aren't you?\nYou can't join twice...")
	else:
		# So request a player_info arch set to GUILD_INFO
		pinfo = activator.GetPlayerInfo("GUILD_INFO")

		# If none or not what we want, go to else... but first search
		while pinfo != None:
			if pinfo.slaying == guild_tag:
				me.SayTo(activator, "\nWelcome old member!\nYou rejoin now with your old guild rank.")
				guild_rank = pinfo.title

				if guild_rank == None:
					guild_rank = ""

				break

			pinfo = activator.GetNextPlayerInfo(pinfo)
			
		if pinfo == None or pinfo.slaying != guild_tag:
			qitem = activator.CheckQuestObject(quest_arch_name, quest_item_name)

			if qitem == None:
				me.SayTo(activator, "\nI don't see my helmet... Where is it?\nRemember: Enter the hole next to me and kill the ants there.\nOne of them stole my old helmet.\nBring it back to me and I will let you join the ^guild^.")
			else:
				me.SayTo(activator, "\nThere is my helmet back... Well, keep it!\nI am impressed. I think you will make your way.\nWelcome to the Mercenaries of Thraal!\nAsk Jahrlen for instructions. He is down the stairs.")

				# Setup an own PLAYER_INFO
				guild_info = activator.CreatePlayerInfo("GUILD_INFO")

				# Title in this guild
				guild_info.title = guild_rank
				# The guild_info tag of this guild
				guild_info.slaying = guild_tag
				# Our active guild, give us our profession title 
				activator.SetGuildForce(guild_rank)
				# Real tag to the guild_info
				guild_force.slaying = guild_tag
		else:
			# Our active guild, give us our profession title 
			activator.SetGuildForce(guild_rank)
			# The real tag to the guild_info
			guild_force.slaying = guild_tag

elif text[0] == "leave":
	if guild_force.slaying != guild_tag:
		me.SayTo(activator, "\nYou are not a member here...")
	else:
		me.SayTo(activator, "\nOk, you are out!\nYou can rejoin any time.")

		# Empty string forces the system to insert a NULL in the object
		guild_force = activator.SetGuildForce("")
		guild_force.slaying = ""

elif text[0] == "guild":
	if guild_force.slaying == guild_tag:
		me.SayTo(activator,"\nYou can ^leave^ at any time.\nYou can also rejoin without problems.")
	else:
		qitem = activator.CheckQuestObject(quest_arch_name, quest_item_name)

		if qitem == None:
			me.SayTo(activator,"\nBefore you can ^join^ the guild I have a small task for you.\nSome giant ants have invaded our water supply.\nSee this hole by my side!\nOne of those silly ants stole my old helmet!\nEnter the hole and kill the ants there.\nNo fear, they are weak.\nBring me the helmet back and I will let you ^join^.\n");		
		else:
			pinfo = activator.GetPlayerInfo("GUILD_INFO")

			while pinfo != None:
				if pinfo.slaying == guild_tag:
					me.SayTo(activator, "\nYou are an old member of ours!\nYou can re^join^ at any time.\nYou will get your old guild rank back too.")
					guild_rank = pinfo.title

					if guild_rank == None:
						guild_rank = ""
					break

				pinfo = activator.GetNextPlayerInfo(pinfo)

			if pinfo == None or pinfo.slaying != guild_tag:
				me.SayTo(activator,"\nAh, you have my helmet! Excellent!\nWell, keep it and may it protect you.\nIf you want you can ^join^ us now.")

elif text[0] == "jahrlen":
		me.SayTo(activator,"\nJahrlen is our guild mage.\nWell, normally we don't have a guild mage.\nBut we are at war here and he was assigned to us.\nIn fact, he is a high level chronomancer and we are honored he helps us.\nHe is in our guild rooms. Talk to him when you meet him!\nHe often has tasks and quests for newbies.")

elif text[0] == "troops":
		me.SayTo(activator,"\nWe, as part of the the Thraal army corps, are invading these abandoned areas after the defeat of Moroch.\nWell, the chronomancers ensured us after they created the portal that we are still in the galactic main sphere.\nBut it seems to me that these lands have many wormholes to other places...\nPerhaps the long time under Morochs influence has weakened the borders between the planes. You should ask ^Jahrlen^ about it.");

elif msg == 'hello' or msg == 'hi' or msg == 'hey':
	if guild_force.slaying == guild_tag:
		me.SayTo(activator, "\nHello %s! Welcome back.\nNice that you have joined our ^troops^.\nAsk me when you need info about the guild." % activator.name)
	else:
		# Cap is one time drop - if we got it this is auto set
		qitem = activator.CheckQuestObject(quest_arch_name, quest_item_name)

		if qitem == None:
			me.SayTo(activator,"\nHello, I am the mercenary guildmaster.\nSay ^guild^ if you want to join or for info about the guild.\nOur task is to support the regular ^troops^.\nIf you want a good start - we will give it you.")
		else:
			pinfo = activator.GetPlayerInfo("GUILD_INFO")

			while pinfo != None:
				if pinfo.slaying == guild_tag:
					me.SayTo(activator, "\nYou are an old member of ours!\nYou can re^join^ at any time.\nYou will get your old guild rank back too.")
					guild_rank = pinfo.title

					if guild_rank == None:
						guild_rank = ""
					break

				pinfo = activator.GetNextPlayerInfo(pinfo)

			if pinfo == None or pinfo.slaying != guild_tag:
				me.SayTo(activator,"\nAh, you have my helmet! Excellent!\nWell, keep it and may it protect you.\nIf you want you can ^join^ us now.")

else:
	activator.Write("%s listens to you without answer." % me.name, COLOR_WHITE)