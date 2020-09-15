#pragma once
#include <string>
#include <jcr6_core.hpp>
#include <RPGStat.hpp>

namespace TrickyUnits{

	void RPGLoad(jcr6::JT_Dir *jcr, std::string prefix="");
	void RPGLoad(std::string mainfile, std::string prefix="");
	void RPGSave(jcr6::JT_Create *jcr, std::string prefix="", std::string Storage="Store");
	void RPGSave(std::string mainfile, std::string prefix,std::string Storage="Store");

}
