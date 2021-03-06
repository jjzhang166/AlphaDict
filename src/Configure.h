#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_

#include "tinyxml2/tinyxml2.h"

#include <string>
#include <vector>
#include <map>

#include "SpinLock.h"

using namespace std;
using namespace tinyxml2;

struct DictNode {
    string name;
    string open;
    string srclan;
    string detlan;
    bool   en;
    string path;
    string summary;
};

enum CwsShortcutKey {
    Ctrl_Key = 0,
    Shift_Key,
    Alt_Key,
    None_Key,
};

struct Setting {
    int  uilanID;
    int  fontsize;
    string font;
    bool bsystemTray;
};

struct CaptureWordSetting {
    bool benable;
    bool bselection;
    bool bclipboard;
    bool bmouse;
    int  shortcutKey;
    bool autoCloseEn;
    int  autoCloseInv;
};

enum UILanID {
    UILAN_NONE = -1, // Auto detect.
    UILAN_EN,
    UILAN_CN,
};

class Configure
{
public:
    static Configure& getRefrence();
    Configure();
    ~Configure();

    int  initialization();
    void scanDictDir(vector<string>& dictFiles);

    void moveDictItem(int index, bool down=true);
    void enableDict(int index, bool en=true);
    void writeDictItem(int item);
    void writeSrcLan(const string& lan);
    void writeDetLan(const string& lan);
    void writeUILanID(int id);
    void writeFontSize(int size);
    void writeFont(string font);
    void writeSystemTray(bool en);
    void writeCwsSelection(bool en);
    void writeCwsClipboard(bool en);
    void writeCwsMouse(bool en);
    void writeCwsEnable(bool en);
    void writeCwsShortcutKey(int shortcutKey);
    void writeCwsAutoCloseEn(bool en);
    void writeCwsAutoCloseInv(int Inv);
    void writeXml();
    void reset();

    vector<string> m_languages;
    string m_dataDir;
    string m_homeDir;
    string m_configFile;
    string m_srcLan;
    string m_detLan;    
    CaptureWordSetting  m_cws;
    Setting  m_setting;

    vector<struct DictNode> m_dictNodes;

    string getVBPath() { return m_homeDir+"/vbook";}  // suffix is defined at db class.

private:
    int  load(const string& xmlpath);
    void loadLanguage();
    void scanDictDir(const string& path, vector<string>& dictFiles);
    int  findDict(const string& path, const vector<string>& dictFiles);

    tinyxml2::XMLDocument m_doc;
    bool m_dirty;
    SpinCriticalSection m_cs;
};

#endif
