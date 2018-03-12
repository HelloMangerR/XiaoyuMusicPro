#include "playlogic.h"

#include <QDebug>
#include <QTime>

PlayLogic::PlayLogic(QObject *parent) : QObject(parent)
{
    initMainW();
    initPlayList();
    initPlayer();
    initLyric();
}

void PlayLogic::initMainW(void)
{
    m_mainW = new MainW;

    connect(m_mainW, SIGNAL(signalControlNext()),
            this, SLOT(slotControlNext()));
    connect(m_mainW, SIGNAL(signalControlPrev()),
            this, SLOT(slotControlPrev()));
    connect(m_mainW, SIGNAL(signalControlPlay()),
            this, SLOT(slotControlPlay()));
    connect(m_mainW, SIGNAL(signalControlPlayModeChange(int)),
            this, SLOT(slotControlPlayModeChange(int)));
    connect(m_mainW, SIGNAL(signalControlProcessChange(int)),
            this, SLOT(slotControlProcessChange(int)));
    connect(m_mainW, SIGNAL(signalControlSetMute()),
            this, SLOT(slotControlSetMute()));
    connect(m_mainW, SIGNAL(signalControlVolumeChange(int)),
            this, SLOT(slotControlVolumeChange(int)));
    connect(m_mainW, SIGNAL(signalControlCurrentSongChange(int)),
            this, SLOT(slotControlCurrentSongChange(int)));
}

void PlayLogic::initPlayList(void)
{
    m_playList = new QMediaPlaylist;
    m_songOp = new SongOperation;
    m_index = 0;
    m_playList->setCurrentIndex(m_index);

    foreach (QString songSource, m_songOp->getSongSourceList()) {
        m_playList->addMedia(QUrl(songSource));
    }

    m_playList->setPlaybackMode(QMediaPlaylist::Random);
    m_mainW->setMainWSongNameList(m_songOp->getSongNameList());

    connect(m_playList, SIGNAL(currentIndexChanged(int)),
            this, SLOT(slotCurrentIndexChanged(int)));
}

void PlayLogic::initLyric(void)
{
    m_lyric = new LyricOperation;
    m_lyric->showLyricW();

    connect(this, SIGNAL(signalControlCurrentSongChanged(QString)),
            m_lyric, SLOT(slotControlCurrentSongChanged(QString)));
}

void PlayLogic::initPlayer(void)
{
    m_player = new QMediaPlayer;
    m_player->setPlaylist(m_playList);
    m_player->setVolume(50);

    connect(m_player, SIGNAL(durationChanged(qint64)),
            this, SLOT(slotDurationChanged(qint64)));
    connect(m_player, SIGNAL(positionChanged(qint64)),
            this, SLOT(slotCurrentPositionChanged(qint64)));
}

void PlayLogic::showMainW(void)
{
    m_mainW->show();
}

void PlayLogic::slotControlNext(void)
{
    m_index = m_playList->nextIndex();

    if (m_index == -1)
    {
        m_index = 0;
        m_playList->setCurrentIndex(m_index);
    }else{
        m_playList->setCurrentIndex(m_index);
    }
}

void PlayLogic::slotControlPrev(void)
{
    m_index = m_playList->previousIndex();

    if (m_index == -1)
    {
        m_player->stop();
    }else{
        m_playList->setCurrentIndex(m_index);
    }
}

void PlayLogic::slotControlPlay(void)
{
    switch (m_player->state()) {
    case QMediaPlayer::StoppedState:
        m_player->play();
        break;
    case QMediaPlayer::PlayingState:
        m_player->pause();
        break;
    case QMediaPlayer::PausedState:
        m_player->play();
        break;
    default:
        break;
    }
}

void PlayLogic::slotControlVolumeChange(const int volume)
{
    m_player->setVolume(volume);
}

void PlayLogic::slotControlSetMute(void)
{
    if (m_player->isMuted())
    {
        m_player->setMuted(false);
    }else{
        m_player->setMuted(true);
    }
}

void PlayLogic::slotControlProcessChange(const int position)
{
    m_player->setPosition(position * 1000);
}

void PlayLogic::slotControlPlayModeChange(const int playMode)
{
    switch (playMode) {
    case SINGLEPLAY:
        m_playList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        break;
    case SINGLELOOP:
        m_playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    case SEQUENTIALPLAY:
        m_playList->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
    case LISTLOOPPLAY:
        m_playList->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    case RANDOMPLAY:
        m_playList->setPlaybackMode(QMediaPlaylist::Random);
        break;
    default:
        break;
    }
}

void PlayLogic::slotControlCurrentSongChange(const int index)
{
    m_playList->setCurrentIndex(index);
    m_player->play();
}

void PlayLogic::slotCurrentIndexChanged(int index)
{
//    qDebug() << m_songOp->getSongNameList().at(index);
    m_mainW->setMainWSongInfo(index, m_songOp->getSongNameList().at(index));
    m_playList->setCurrentIndex(index);
    emit signalControlCurrentSongChanged(m_songOp->getSongNameList().at(index));
//    m_lyric->gainLyric(m_songOp->getSongNameList().at(index));    ///此处访问了私有数据成员造成了段错误
    m_player->play();
}

void PlayLogic::slotDurationChanged(qint64 duration)
{
    qint64 totalTime = duration / 1000;    ///获得秒级时间
    QTime totalT(totalTime/3600, (totalTime%3600)/60, (totalTime%3600)%60);
    m_totalTime = totalT.toString("mm:ss");
//    qDebug() << m_totalTime;

    m_mainW->setMainWCurrentTimeShow("00:00/"+m_totalTime);
}

void PlayLogic::slotCurrentPositionChanged(qint64 postion)
{
    qint64 currentTime = postion / 1000;    ///获得秒级时间
    QTime currentT(currentTime/3600, (currentTime%3600)/60, (currentTime%3600)%60);
    QString currentPosition = currentT.toString("mm:ss");

    m_mainW->setMainWCurrentTimeShow(currentPosition+"/"+m_totalTime);
    m_mainW->setMainWCurrentPositionShow(currentTime);
    m_lyric->setCurrentRow(currentTime);

}
