#include "..\Headers\Dirry.hpp"
#include "..\Headers\QuickString.hpp"
#include <map>
#include <stdlib.h>

#define Dirry_VisualStudio
using namespace std;


namespace TrickyUnits {

    static map<string, string> DVar;
    //static map<string, string> ADrv;

    void DirryInit(bool force=false) {
        static bool notdoneyet = true;
        if (notdoneyet || force) {
            notdoneyet = false;
#ifdef unix
            DVar["HomeDrive"] = "/";
            DVar["Home"] = getenv("HOME");
#elif defined(_WIN32)
#ifdef Dirry_VisualStudio
            char* fuck;
            char* you;
            // Those variable names are a notion to Microschoft!
            size_t bc = 200;
            auto e1 = _dupenv_s(&fuck, &bc, "HOME");
            auto e2 = _dupenv_s(&you, &bc, "HOME");
            if ((!e1) && (!e2) && fuck && you) {
                string H = fuck; H += you;
                DVar["HomeDrive"] = fuck;
                DVar["Home"] = TReplace(H, '\\', '/');
            } else {
                DVar["HomeDrive"] = "";
                DVar["Home"] = "";
            }
            free(fuck);
            free(you);

#else
            DVar["HomeDrive"] = getenv("HOMEDRIVE");
            DVar["Home"] = TReplace(DVar["HomeDrive"] + getenv("HOMEPATH"), '\\', '/');
#endif
#endif
            DVar["AppSupport"] = DVar["Home"] + "/.Tricky__ApplicationSupport";
        }
    }

    string Dirry(string path) {
        auto ret = path;
        for (auto dostuff : DVar) {
            ret = TReplace(ret, "$" + dostuff.first + "$", dostuff.second);
        }
        return ret;
    }

    void DirryVar(string var, string value) {
        DirryInit();
        if (value == "") {
            if (DVar.count(value)) DVar.erase(value);
        } else {
            DVar[var] = TReplace(value,'\\','/');
        }
    }

    string TrickyUnits::DirryVar(string var) {
        DirryInit();
        if (DVar.count(var)) return DVar[var];
        return "";
    }

}