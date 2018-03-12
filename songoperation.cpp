#include "songoperation.h"

#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>

SongOperation::SongOperation(QObject *parent) : QObject(parent)
{
    m_songFilePath.clear();
    m_songNameList.clear();
    m_songSourceList.clear();

    setSongFilePath("C:/KwDownload/song");
}

void SongOperation::setSongFilePath(QString songPath)
{
    m_songFilePath = songPath;
//    m_songFilePath = "C:/KwDownload/song";
    QDir dir(m_songFilePath);
    QFileInfoList infos =
            dir.entryInfoList(QStringList() << "*.mp3", QDir::Files,
                              QDir::Name);
    foreach (QFileInfo info, infos) {
        m_songNameList.append(info.baseName());
        m_songSourceList.append(info.absoluteFilePath());
    }
}

const QStringList &SongOperation::getSongNameList(void) const
{
    return m_songNameList;
}

const QStringList &SongOperation::getSongSourceList(void) const
{
    return m_songSourceList;
}

const QString SongOperation::getSongFilePath(void) const
{
    return m_songFilePath;
}
