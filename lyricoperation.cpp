#include "lyricoperation.h"
#include "ui_lyricoperation.h"

#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QTextStream>
#include <QDebug>

LyricOperation::LyricOperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LyricOperation)
{
    ui->setupUi(this);
    initLyricOperation();
}

LyricOperation::~LyricOperation()
{
    delete ui;
}

void LyricOperation::showLyricW(void)
{
    this->show();
}

void LyricOperation::initLyricOperation(void)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_lrc.clear();
    m_lyric.clear();
    ui->lw_lyricShow->clear();
    setLyricPath("C:/KwDownload/My_Lrcx");
}

void LyricOperation::setLyricPath(QString LyricPath)
{
    m_lyricPath = LyricPath;
}

void LyricOperation::setCurrentRow(qint64 time)
{
    if(m_lrc.contains(time))
    {
        ui->lw_lyricShow->setCurrentRow(m_lrc.value(time));
//        qDebug() << m_lrc.value(time);
    }
}

void LyricOperation::slotControlCurrentSongChanged(QString songName)
{
    QString lrcPath = m_lyricPath + "/" + songName + ".lrc";
    QFile lrcFile(lrcPath);

    if (!lrcFile.open(QFile::ReadOnly))
    {
        qDebug() << "lrc file open filed!";
    }else{
        QTextStream in(&lrcFile);
        QString line;
        QStringList lineSplit;
        QString time;
        QString lrc;
        int index = 0;
        m_lrc.clear();
        m_lyric.clear();
        ui->lw_lyricShow->clear();

        while (!in.atEnd())
        {
            line = in.readLine();
            lineSplit = line.split("]");
            time = lineSplit.at(0);
            lrc = lineSplit.at(1);
            time = time.remove(0,1);
            time = time.mid(0,5);
            QStringList timeOperate = time.split(":");
            qint64 key= QString(timeOperate.at(0)).toInt()*60 + QString(timeOperate.at(1)).toInt();
            m_lyric.append(lrc);
            m_lrc.insert(key, index++);
//            qDebug() << time << endl << lrc;
        }
    }

    lrcFile.close();
    setLyric();
}

void LyricOperation::setLyric(void)
{
    ui->lw_lyricShow->addItems(m_lyric);
}

void LyricOperation::mousePressEvent(QMouseEvent *ev)
{
    if (ev->buttons() == Qt::LeftButton)
    {
        m_mouseClick = ev->globalPos() - this->frameGeometry().topLeft();
    }
}

void LyricOperation::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        this->move(ev->globalPos() - m_mouseClick);
    }
}

void LyricOperation::on_pb_hide_clicked()
{
    this->hide();
}

void LyricOperation::on_pb_max_clicked()
{
    if(!this->isMaximized())
    {
        this->showMaximized();
        ui->pb_max->setText("——");
    }else{
        this->showNormal();
        ui->pb_max->setText("口");
    }
}
