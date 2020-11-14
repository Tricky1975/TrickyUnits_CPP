#pragma once
#include <vector>
#include <string>

namespace TrickyUnits {
	enum DirWant{Files,Directories,FilesAndDirectories,Tree};
	std::vector<std::string> FileList(std::string Dir,DirWant Want=DirWant::Files,bool allowhidden=false, std::string addprefix="");
	std::vector<std::string> GetTree(std::string dir, bool allowhidden = false);
}