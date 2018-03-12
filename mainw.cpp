#include "mainw.h"
#include "ui_mainw.h"

#include <QDebug>

#define SINGLEPLAY 0
#define SINGLELOOP 1
#define SEQUENTIALPLAY 2
#define LISTLOOPPLAY 3
#define RANDOMPLAY 4

MainW::MainW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainW)
{
    ui->setupUi(this);
    initMainW();
}

MainW::~MainW()
{
    delete ui;
}

void MainW::initMainW(void)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->show();
    m_playMode = RANDOMPLAY;
    ui->vs_volume->setValue(50);

}

void MainW::setMainWSongNameList(const QStringList songNameList)
{
    ui->lw_song->addItems(songNameList);
}

void MainW::setMainWSongInfo(int index, const QString songName)
{
    QStringList nameInfo = songName.split("-");
    QString singer = nameInfo.at(0);
    QString song = nameInfo.at(1);

    ui->lb_singer->setText(singer);
    ui->lb_songName->setText(song);

    ui->lw_song->setCurrentRow(index);
}

void MainW::setMainWtotalTime(qint64 totalTime)
{
    ui->hs_songProcess->setMaximum(totalTime);
}

void MainW::setMainWCurrentTimeShow(QString currentTime)
{
    ui->lb_songTimeShow->setText(currentTime);
}

void MainW::setMainWCurrentPositionShow(qint64 time)
{
    if (!ui->hs_songProcess->isSliderDown())
    {
        ui->hs_songProcess->setValue(time);
    }
}

void MainW::mousePressEvent(QMouseEvent *ev)
{
    if (ev->buttons() == Qt::LeftButton)
    {
        m_widgetMove = ev->globalPos() - this->frameGeometry().topLeft();
        ev->accept();
    }
}

void MainW::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() == Qt::LeftButton)
    {
        move(ev->globalPos() - m_widgetMove);
        ev->accept();
    }
}

void MainW::on_pb_showSmall_clicked()
{
    this->showMinimized();
}

void MainW::on_pb_close_clicked()
{
    this->close();
}

void MainW::on_pb_prev_clicked()
{
    emit signalControlPrev();
}

void MainW::on_pb_next_clicked()
{
    emit signalControlNext();
}

void MainW::on_pb_playMode_clicked()
{
    m_playMode++;
    m_playMode %= 5;

    switch (m_playMode) {
    case 0:
        ui->pb_playMode->setText("单曲播放");
        break;
    case 1:
        ui->pb_playMode->setText("单曲循环");
        break;
    case 2:
        ui->pb_playMode->setText("顺序播放");
        break;
    case 3:
        ui->pb_playMode->setText("列表循环");
        break;
    case 4:
        ui->pb_playMode->setText("随机播放");
        break;
    default:
        break;
    }

    emit signalControlPlayModeChange(m_playMode);
}

void MainW::on_pb_play_clicked()
{
    emit signalControlPlay();
}

void MainW::on_pb_volume_clicked()
{
    emit signalControlSetMute();
}

void MainW::on_vs_volume_sliderMoved(int position)
{
    emit signalControlVolumeChange(position);
}

void MainW::on_lw_song_doubleClicked(const QModelIndex &index)
{
    ui->lw_song->setCurrentRow(index.row());
    emit signalControlCurrentSongChange(index.row());
}

void MainW::on_hs_songProcess_sliderMoved(int position)
{
    emit signalControlProcessChange(position);
}
