#include <QtWidgets/QApplication>
#include "repository/repository.h"
#include "controller/controller.h"
#include "Morgue_qtDesignerGUI.h"
#include <QMessageBox.h>
#include <fstream>
#include <qdebug.h>
#include <regex>

/// THE SETTINGS CAN BE CHANGED IN configFile.cfg
bool readConfigurationSettings(string& repoFile, string& assistantFile, string& assistantFileExtension, bool& addEntries)
{
    using namespace std::regex_constants;
    ifstream fin("configFile.cfg");
    bool ok1=false, ok2=false, ok3=false;
    string line, token;
    while (getline(fin, line))
        if (!regex_match(line, regex("^\\s*#.*|^\\s*$")))
        {
            if (regex_match(line, regex("^\\s*admin_repository\\s*=.*")))
            {
                stringstream tokenStream(line);
                getline(tokenStream, token, '=');
                getline(tokenStream, token, '=');
                smatch m;
                regex_search(token, m, regex("\\S+\\s*\\.txt"));
                repoFile = m[0];
                ifstream fin(repoFile);
                if (!fin.good())
                    repoFile = "";
                ok1 = true;
            }
            else if (regex_match(line, regex("^\\s*assistant_file\\s*=.*")))
            {
                stringstream tokenStream(line);
                getline(tokenStream, token, '=');
                getline(tokenStream, token, '=');
                smatch m;
                regex_search(token, m, regex("\\S+\\s*\\.(txt|csv|html)"));
                assistantFile = m[0];
                ifstream fin(assistantFile);
                if (!fin.good())
                    assistantFile = "";
                regex_search(assistantFile, m, regex("txt|csv|html"));
                assistantFileExtension = m[0];
                ok2 = true;
            }
            else if (regex_match(line, regex("^\\s*add_entries\\s*=.*")))
            {
                stringstream tokenStream(line);
                getline(tokenStream, token, '=');
                getline(tokenStream, token, '=');
                if (regex_match(token, regex("[ ]*true[ ]*|[ ]*yes[ ]*", ECMAScript | icase)))
                    addEntries = true;
                else addEntries = false;
                ok3 = true;
            }
            else qDebug() << "Incorrect setting! -> "<<QString::fromStdString(line);
        }
    return ok1 && ok2 && ok3;
}

//\\//\\//\\//\\//\\//\\///\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\////\\//\\//\\//\\//\\//\\///\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\/\\//\\//\\//\\//\\//\\//\\//\\//


int main(int argc, char *argv[])
{
    /// MY LOVELY MORGUE APP :)
    QApplication a(argc, argv);
    
    string repoFile, assistantFile, assistantFileExtension;
    bool addEntries;
    if (!readConfigurationSettings(repoFile, assistantFile, assistantFileExtension, addEntries))
    {
        qDebug() << "Configuration file error!";
        return -1;
    }
    
    Repository* repoA;
    if (repoFile.size())
        repoA = new FileRepository{ repoFile };
    else
        repoA = new Repository{};
    
    Service service{ repoA };
    service.createMylistRepo(assistantFile, assistantFileExtension);
    if(addEntries) service.addEntries();

    Morgue_qtDesignerGUI GUI{service};
    GUI.show();

    return a.exec();
    //_CrtDumpMemoryLeaks();
}
