#include "functions.h"
#include <QProcess>
#include <QSysInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QStandardPaths>
#include <QProcess>
#ifdef Q_OS_WIN
#include <Windows.h>
#endif

void OpenYandex() {
    OpenCustomUrl("https://ya.ru/");
}

void OpenPracticum() {
    OpenCustomUrl("https://practicum.yandex.ru/");
}

void OpenHomeDirectory() {
    OpenCustomDirectory(QDir::homePath());
}

void OpenCmd() {
    QString s = QSysInfo::productType();
    if (QSysInfo::productType() == "macos") {
        QProcess::execute("osascript", {"-e", "tell application \"Terminal\" to do script \"\""});
        QProcess::execute("osascript", {"-e", "tell application \"Terminal\" to activate"});
    }
    else if (QSysInfo::productType() == "windows") {
        QString cd = "C:/users";
        QProcess::startDetached("cmd.exe", {"/C", "cd", QDir::toNativeSeparators(cd), "&&", "start", "cmd"});
    } else {
        QProcess::startDetached("x-terminal-emulator");
        QProcess::startDetached("gnome-terminal");
        QProcess::startDetached("konsole");
        QProcess::startDetached("xfce4-terminal");
    }
}

void OpenCustomUrl(const QString &url) {
    QDesktopServices::openUrl(QUrl(url));
}

void OpenCustomDirectory(const QString &path) {
    if (QSysInfo::productType() == "windows") {
        QProcess::startDetached("explorer.exe", QStringList() << "/select," << QDir::toNativeSeparators(path));
        return;
    }
    QDesktopServices::openUrl(QUrl("file://" + path));
}
