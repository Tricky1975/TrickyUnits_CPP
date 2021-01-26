// Lic:
// Source/RPGSave.cpp
// RPGSave
// version: 20.10.06
// Copyright (C) 2020 Jeroen P. Broks
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
// EndLic
#include <RPGSave.hpp>
#include <QuickString.hpp>

#define RCase(a) } else if (TR==a) {
#define LCase(a) } else if (linktype==a) {
#define WriteByte(B,a) B->Write((unsigned char)a);

#define Chat(a) cout << "\x1b[32mRPG-DEBUG> \x1b[0m"<<a<<endl

namespace TrickyUnits{
	using namespace jcr6;

	void RPGLoad(jcr6::JT_Dir* jcr, std::string prefix) {
		// Clear mem
		ResetRPG();
		for (auto& scanentry : jcr->Entries()) {
			Chat("Check entry: " + scanentry.first);
			if (prefixed(scanentry.first, Upper(prefix) + "CHARACTER/")) {
				Chat("Character Entry to load!");
				auto TN = StripDir(ExtractDir(scanentry.second.Entry()));
				auto TR = StripDir(scanentry.first);
				Chat("Char: " + TN + "; DT: " + TR);
				if (!Character::Map.count(TN)) Character::CreateChar(TN);
				if (false) {
					// Char: Name
					RCase("NAME")
						JT_EntryReader BT;
					jcr->B(scanentry.first, BT);
					Character::Map[TN].Name = BT.ReadString();
					// Char: Stats
					RCase("STATS")
						JT_EntryReader BT;
					jcr->B(scanentry.first, BT);
					CharStat* sv = NULL;
					while (!BT.eof()) {
						auto tag = BT.ReadByte();
						std::string sname;
						//Print tag
						switch (tag) {
						case 1:
							sname = BT.ReadString();
							sv = Character::Map[TN].GetStat(sname);
							//Print TN
							//sv = new RPGStat();
							//RPG_TMap.MapInsert(ch.Stats, TN, sv);
							break;
						case 2:
							sv->Pure = (BT.ReadByte() != 0);
							break;
						case 3:
							sv->ScriptFile(BT.ReadString());
							sv->ScriptFunction(BT.ReadString());
							break;
						case 4:
							sv->Value(BT.ReadInt());
							break;
						case 5:
							sv->Modifier = BT.ReadInt();
							break;
						case 6:
							sv->Script(BT.ReadString());
							break;
						default:
							//EndGraphics
							doRPGPanic("FATAL ERROR:\n\nUnknown tag in character (" + TN + ") stat file (" + to_string(tag) + ") within this savegame file ");
						}
					}
					// Char: Points
					RCase("POINTS")
						JT_EntryReader BT;
					jcr->B(scanentry.first, BT);
					CharPoints* sp = NULL;
					vector<string> UnForceLijst;
					while (!BT.eof()) {
						auto tag = BT.ReadByte();
						switch (tag) {
						case 1: {
							/* original (now useless C# code)
							sp = new RPGPoints();
							TN = BT.ReadString();
							RPG_TMap.MapInsert(ch.Points, TN, sp);
							*/
							auto PN = BT.ReadString();
							sp = Character::Map[TN].GetPoints(PN);
							UnForceLijst.push_back(PN);
							Chat("Points pointer set to: " + PN);
						}
							  break;
						case 2: {
							auto fuck = BT.ReadString(); // For some reason C++ wants to crash on this (without apparent reason).
							if (!sp) doRPGPanic("Tried to maxcopy a NULL pointer for points (" + TN + ")");
							sp->MaxCopy(fuck);
							break;
						}
						case 3:
							sp->ForceHave(BT.ReadInt());
							break;
						case 4:
							sp->Maxi(BT.ReadInt());
							break;
						case 5:
							sp->Mini(BT.ReadInt());
							break;
						default:
							//EndGraphics
							doRPGPanic("FATAL ERROR:\n\nUnknown tag in character (" + TN + ") points file (" + to_string(tag) + ") within this savegame file ");
						}
					}
					//sp->UnForce();
					/*
					Chat("Unforcing " << UnForceLijst.size() << " points records!"); // DEBUG ONLY!
					for (auto ufsp : UnForceLijst) {
						auto u{ Character::Map[TN].GetPoints(ufsp) };
						Chat("- " << ufsp << "   Have: " << u->Have() << "; Mini: " << u->Mini() << "; Maxi: " << u->Maxi());
						u->UnForce();
					}
					*/
					// Char: Data
					RCase("STRDATA")
						//cout << "Scan data: " << scanentry.first << "\n";
						auto data = jcr->StringMap(scanentry.first);
					auto ch = &Character::Map[TN];
					ch->NULLAllData(); // Once again make sure all data is destroyed, to prevent conflicts
					for (auto it : data) {
						//cout << "Read Data: " << it.first << " => " << it.second << "\n";
						ch->GetData(it.first)->Value = it.second;
					}
					// Char: List
					RCase("LISTS")
						JT_EntryReader BT;
					jcr->B(scanentry.first, BT);
					CharList* ls = NULL;
					while (!BT.eof()) {
						auto tag = BT.ReadByte();
						switch (tag) {
						case 1:
							//TN = BT.ReadString();
							//RPG_TMap.MapInsert(ch.Lists, TN, new List<string>());
							ls = Character::Map[TN].GetList(BT.ReadString());
							break;
						case 2:
							ls->Add(BT.ReadString());
							break;
						default:
							doRPGPanic("FATAL ERROR:\n\nUnknown tag in character (" + TN + ") list file (" + to_string(tag) + ") within this savegame file ");
						}
					}
				}
			}
		}
		// Party
		{
			JT_EntryReader BT;
			jcr->B(prefix + "Party", BT);
			int PMAX = BT.ReadInt();
			int p = 0;
			Party::Max(PMAX);
			while (!BT.eof()) {
				Party::Member(++p, BT.ReadString(), true);
			}
		}
		// Links		
		if (jcr->EntryExists(prefix + "Links")) {
			//DebugLog("Links found! Loading them!");
			//BT = new QuickStream(LoadFrom.AsMemoryStream(D + "Links"));
			JT_EntryReader BT;
			jcr->B(prefix + "Links", BT);
			//do { //Repeat
			while (!BT.eof()) {
				auto tag = BT.ReadByte();
				switch (tag) {
				case 001: {
					auto linktype = Upper(BT.ReadString());
					auto linkch1 = BT.ReadString();
					auto linkch2 = BT.ReadString();
					auto linkstat = BT.ReadString();
					auto ch = &Character::Map[linkch1];
					if (false) { //switch (linktype.ToUpper()) {
						LCase("STAT") ch->LinkStat(linkstat, linkch2);
						LCase("PNTS") ch->LinkPoints(linkstat, linkch2);
						LCase("DATA") ch->LinkData(linkstat, linkch2);
						LCase("LIST") ch->LinkList(linkstat, linkch2);
					} else {
						cout << "ERROR! I don't know what a " << linktype << " is so I cannot link! Request ignored!\n";
					}
				}
						break;
				case 255:
					goto GetOutOfThisLinkLoop; // Nothing I hate more than "goto" commands, but due to the way switches are set up in C-dialects, I got no choice!
				default:
					doRPGPanic("ERROR! Unknown link command tag (" + to_string(tag) + ")");
				}
			}// while (!BT.EOF); //Until Eof(bt)
		GetOutOfThisLinkLoop:
			;
		}
		for (auto c : Character::Map) {
			for (auto p : c.second.Points()) {
				c.second.GetPoints(p)->UnForce();
			}
		}
	}

	void RPGLoad(std::string mainfile, std::string prefix) {
		JT_Dir jcr;
		jcr = Dir(mainfile);
		RPGLoad(&jcr, prefix);
	}

	static void SaveRPGLink(jcr6::JT_CreateBuf* BTE, std::string ltype, std::string ch1, std::string ch2, std::string stat) {
		BTE->Write((char)1); //' marks new entry version 1
		BTE->Write(ltype);
		BTE->Write(ch1);
		BTE->Write(ch2);
		BTE->Write(stat);
	}



	void RPGSave(jcr6::JT_Create* jcr, std::string prefix, std::string Storage) {
		auto BT{ jcr->StartEntry(prefix + "Party",Storage) };
		BT->Write(Party::Max());
		for (int i = 1; i <= Party::Max(); ++i) BT->Write(Party::Member(i));
		delete BT; // Show close stuff.
		for (auto& scanchar : Character::Map) {
			// Name
			auto ch = scanchar.first;
			auto dt = &scanchar.second;
			BT = jcr->StartEntry(prefix + "Character/" + ch + "/Name", Storage);
			BT->Write(dt->Name);
			delete BT;
			// Stats
			BT = jcr->StartEntry(prefix + "CHARACTER/" + ch + "/Stats", Storage);
			for (auto& key : dt->Stats()) {
				auto st{ dt->GetStat(key) };
				BT->Write((char)1);
				BT->Write(key);
				BT->Write((char)2);
				BT->Write((char)st->Pure);
				BT->Write((char)3);
				BT->Write(st->ScriptFile());
				BT->Write(st->ScriptFunction());
				BT->Write((char)4);
				BT->Write(st->Value());
				BT->Write((char)5);
				BT->Write(st->Modifier);
				BT->Write((char)6);
				BT->Write(st->Script());
			}
			delete BT;
			BT = jcr->StartEntry(prefix + "CHARACTER/" + ch + "/Points", Storage);
			for (auto& key : dt->Points()) {
				auto pt = dt->GetPoints(key);
				WriteByte(BT, 1);
				BT->Write(key);
				WriteByte(BT, 2);
				BT->Write(pt->MaxCopy());
				WriteByte(BT, 3);
				BT->Write(pt->Have());
				WriteByte(BT, 4);
				BT->Write(pt->Maxi());
				WriteByte(BT, 5);
				BT->Write(pt->Mini());
			}
			delete BT;
			//BT = jcr->StartEntry(prefix + "CHARACTER/"+ch+ "/Data", Storage);
			{
				map<string, string>m;
				auto dseq = dt->Datas();
				for (auto& key : dseq) {
					auto gd = dt->GetData(key);

					m[key] = gd->Value;
				}
				jcr->AddStringMap(prefix + "CHARACTER/" + ch + "/StrData", m, Storage);
			}
			BT = jcr->StartEntry(prefix + "CHARACTER/" + ch + "/Lists");
			for (auto& key : dt->Lists()) {
				WriteByte(BT, 1);
				BT->Write(key);
				for (auto& item : dt->GetList(key)->List) {
					WriteByte(BT, 2);
					BT->Write(item);
				}
			}
			delete BT;
		}
		auto BTE = jcr->StartEntry(prefix + "Links"); //BT.NewEntry(D + "Links", JCRSTORAGE);
		//var ch1=""
		//var ch2 = "";
		//var stat = "";
		Character* och1=NULL;
		Character* och2=NULL;
		// C#: foreach(string ch1 in RPG_TMap.MapKeys(RPGChars)) foreach(string ch2 in RPG_TMap.MapKeys(RPGChars)) {
		/* C++: */ for(auto itch1:Character::Map) for(auto itch2:Character::Map){
			auto ch1 = itch1.first;
			auto ch2 = itch2.first;
			if (ch1 != ch2) {
				// Debug.WriteLine($"Comparing {ch1} and {ch2}");
				try {
					och1 = &itch1.second; //(RPGCharacter)RPG_TMap.MapValueForKey(RPGChars, ch1);
					och2 = &itch2.second; // (RPGCharacter)RPG_TMap.MapValueForKey(RPGChars, ch2);
					//foreach(string stat in RPG_TMap.MapKeys(och1.Stats))
					for (auto stat : och1->Stats())
						if (och1->GetStat(stat) == och2->GetStat(stat)) SaveRPGLink(BTE, "Stat", ch1, ch2, stat);
					//foreach(string stat in RPG_TMap.MapKeys(och1->StrData))
					for (auto stat : och1->Datas())
						if (och1->GetData(stat) == och2->GetData(stat)) SaveRPGLink(BTE, "Data", ch1, ch2, stat);
					//foreach(string stat in RPG_TMap.MapKeys(och1->Points))
					for (auto stat : och1->Points())
						if (och1->GetPoints(stat) == och2->GetPoints(stat)) SaveRPGLink(BTE, "PNTS", ch1, ch2, stat);
					//foreach(string stat in RPG_TMap.MapKeys(och1->Lists))
					for (auto stat : och1->Lists())
						if (och1->GetList(stat) == och2->GetList(stat)) SaveRPGLink(BTE, "LIST", ch1, ch2, stat);
					//Debug.WriteLine("= All okay!");
				//} catch (System.Exception Ex) {
				} catch (const std::exception& e){
					//Debug.WriteLine($"= Error occurred: {Ex.Message}!");
					std::cout << "\x7 = Error occurred " << e.what() << endl;
				}// finally {
				//	Debug.WriteLine("= End of record");
				//}
			}
		}
		//Debug.WriteLine("Closing link file");
		BTE->Write((unsigned char)255);
		BTE->Close();
		//Debug.WriteLine($"Offset {BT.Entries["XTRA / PARTY / LINKS"].Offset} / {BT.Entries["XTRA / PARTY / LINKS"].Size}"); // High debug, must be commented on normal use!
		delete BTE;
	}

	void RPGSave(std::string mainfile, std::string prefix, std::string Storage) {
		JT_Create jcr(mainfile,Storage);
		RPGSave(&jcr, prefix, Storage);
		jcr.Close();
	}
}