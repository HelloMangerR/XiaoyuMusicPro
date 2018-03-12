#ifndef SONGOPERATION_H
#define SONGOPERATION_H

#include <QObject>
#include <QStringList>

class SongOperation : public QObject
{
    Q_OBJECT
public:
    explicit SongOperation(QObject *parent = 0);

    void setSongFilePath(QString songPath);

    const QStringList &getSongNameList(void) const;
    const QStringList &getSongSourceList(void) const;
    const QString getSongFilePath(void) const;

private:
    QString m_songFilePath;
    QStringList m_songNameList;
    QStringList m_songSourceList;

};

#endif // SONGOPERATION_H
