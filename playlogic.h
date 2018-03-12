#ifndef PLAYLOGIC_H
#define PLAYLOGIC_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "mainw.h"
#include "songoperation.h"
#include "lyricoperation.h"

class PlayLogic : public QObject
{
    Q_OBJECT
public:
    explicit PlayLogic(QObject *parent = 0);
    void showMainW(void);

    enum{
        SINGLEPLAY,
        SINGLELOOP,
        SEQUENTIALPLAY,
        LISTLOOPPLAY,
        RANDOMPLAY
    };

signals:
    void signalControlCurrentSongChanged(QString songName);

public slots:
    void slotControlNext(void);
    void slotControlPrev(void);
    void slotControlPlay(void);

    void slotControlVolumeChange(const int volume);
    void slotControlSetMute(void);

    void slotControlProcessChange(const int position);
    void slotControlPlayModeChange(const int playMode);

    void slotControlCurrentSongChange(const int index);

private slots:
    ///当前歌曲发生改变
    void slotCurrentIndexChanged(int index);

    ///歌曲总时长槽
    void slotDurationChanged(qint64 duration);

    ///进度条自定义显示
    void slotCurrentPositionChanged(qint64 postion);

private:

    ///初始化主界面
    MainW *m_mainW;
    void initMainW(void);

    ///初始化播放器
    QMediaPlayer *m_player;
    void initPlayer(void);
    QString m_totalTime;

    ///初始化播放列表
    QMediaPlaylist *m_playList;
    void initPlayList(void);
    SongOperation *m_songOp;
    int m_index;

    ///初始化歌词
    LyricOperation *m_lyric;
    void initLyric(void);

};

#endif // PLAYLOGIC_H
