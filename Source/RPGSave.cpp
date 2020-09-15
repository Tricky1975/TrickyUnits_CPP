#include <RPGSave.hpp>
#include <QuickString.hpp>

#define RCase(a) } else if (TR==a) {
#define LCase(a) } else if (linktype==a) {
#define WriteByte(B,a) B->Write((unsigned char)a);

namespace TrickyUnits{
	using namespace jcr6;

	void RPGLoad(jcr6::JT_Dir* jcr, std::string prefix) {
		// Clear mem
		ResetRPG();
		for (auto& scanentry : jcr->Entries()) {
			if (prefixed(scanentry.first, Upper(prefix) + "CHARACTER/")) {
				auto TN = StripDir(ExtractDir(scanentry.second.Entry()));
				auto TR = StripDir(scanentry.first);
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
						default:
							//EndGraphics
							doRPGPanic("FATAL ERROR:\n\nUnknown tag in character (" + TN + "}) stat file (" + to_string(tag) + ") within this savegame file ");
						}
					}
					// Char: Points
					RCase("POINTS")
						JT_EntryReader BT;
					jcr->B(scanentry.first, BT);
					while (!BT.eof()) {
						auto tag = BT.ReadByte();
						CharPoints* sp = NULL;
						switch (tag) {
						case 1:
							/* original (now useless C# code)
							sp = new RPGPoints();
							TN = BT.ReadString();
							RPG_TMap.MapInsert(ch.Points, TN, sp);
							*/
							sp = Character::Map[TN].GetPoints(BT.ReadString());
							break;
						case 2:
							sp->MaxCopy(BT.ReadString());
							break;
						case 3:
							sp->Have(BT.ReadInt());
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
					// Char: Data
					RCase("DATA")
						auto data = jcr->StringMap(scanentry.first);
						auto ch = &Character::Map[TN];
						ch->NULLAllData(); // Once again make sure all data is destroyed, to prevent conflicts
						for (auto it : data)ch->GetData(it.first)->Value = it.second;
						// Char: List
						RCase("LIST")
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
			while(!BT.eof()){
				Party::Member(++p, BT.ReadString());
			}
		}
		// Links		
			if (jcr->EntryExists(prefix + "Links")) {
				//DebugLog("Links found! Loading them!");
				//BT = new QuickStream(LoadFrom.AsMemoryStream(D + "Links"));
				JT_EntryReader BT;
				jcr->B(prefix + "Links",BT);
				//do { //Repeat
				while (!BT.eof()) {
					auto tag = BT.ReadByte();
					switch (tag) {
					case 001:{
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
						doRPGPanic("ERROR! Unknown link command tag ("+to_string(tag)+")");
					}
				}// while (!BT.EOF); //Until Eof(bt)
			GetOutOfThisLinkLoop:;
		}
	}

	void RPGLoad(std::string mainfile, std::string prefix) {
		JT_Dir jcr;
		jcr = Dir(mainfile);
		RPGLoad(&jcr, prefix);
	}

	void RPGSave(jcr6::JT_Create* jcr, std::string prefix, std::string Storage) {
		auto BT{ jcr->StartEntry(prefix + "Party",Storage) };
		BT->Write(Party::Max());
		for (int i = 1; i <= Party::Max(); ++i) BT->Write(Party::Member(i));
		delete BT; // Show close stuff.
		for (auto &scanchar : Character::Map) {
			// Name
			auto ch = scanchar.first;
			auto dt = &scanchar.second;
			BT = jcr->StartEntry(prefix + ch+"/Name",Storage);
			BT->Write(dt->Name);
			delete BT;
			// Stats
			BT = jcr->StartEntry(prefix + ch + "/Stats",Storage);
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
			BT = jcr->StartEntry(prefix + ch + "/Points", Storage);
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
			//BT = jcr->StartEntry(prefix + ch + "/Data", Storage);
			{
				map<string, string>m;
				for (auto& key : dt->Datas()) m[key] = dt->GetData(key)->Value;
				jcr->AddStringMap(prefix + ch + "/Data", m, Storage);
			}
			BT = jcr->StartEntry(prefix + ch + "/List");
			for (auto& key : dt->Lists()) {
				WriteByte(BT, 1);
				BT->Write(key);
				for (auto& item : dt->GetList(key)->List) {
					WriteByte(BT, 2);
					BT->Write(item);
				}
			}
		}
	}

	void RPGSave(std::string mainfile, std::string prefix, std::string Storage) {
		JT_Create jcr(mainfile,Storage);
		RPGSave(&jcr, prefix, Storage);
		jcr.Close();
	}
}
