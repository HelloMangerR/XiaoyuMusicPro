#ifndef MAINW_H
#define MAINW_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class MainW;
}

class MainW : public QWidget
{
    Q_OBJECT

signals:
    void signalControlNext(void);
    void signalControlPrev(void);
    void signalControlPlay(void);

    void signalControlVolumeChange(const int volume);
    void signalControlSetMute(void);

    void signalControlProcessChange(const int position);
    void signalControlPlayModeChange(const int playMode);

    void signalControlCurrentSongChange(const int index);

public:
    explicit MainW(QWidget *parent = 0);
    ~MainW();

    void setMainWSongNameList(const QStringList songNameList);
    void setMainWSongInfo(int index, const QString songName);
    void setMainWtotalTime(qint64 totalTime);
    void setMainWCurrentTimeShow(QString currentTime);
    void setMainWCurrentPositionShow(qint64 time);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private slots:

    void on_pb_showSmall_clicked();

    void on_pb_close_clicked();

    void on_pb_prev_clicked();

    void on_pb_next_clicked();

    void on_pb_playMode_clicked();

    void on_pb_play_clicked();

    void on_pb_volume_clicked();

    void on_vs_volume_sliderMoved(int position);

    void on_lw_song_doubleClicked(const QModelIndex &index);

    void on_hs_songProcess_sliderMoved(int position);

private:
    Ui::MainW *ui;

    void initMainW(void);

    QPoint m_widgetMove;

    int m_playMode;

};

#endif // MAINW_H
