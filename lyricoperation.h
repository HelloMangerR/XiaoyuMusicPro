#ifndef LYRICOPERATION_H
#define LYRICOPERATION_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QMouseEvent>

namespace Ui {
class LyricOperation;
}

class LyricOperation : public QWidget
{
    Q_OBJECT

public:
    explicit LyricOperation(QWidget *parent = 0);
    ~LyricOperation();

    void showLyricW(void);
    void setLyric(void);
    void setLyricPath(QString LyricPath);

    void setCurrentRow(qint64 time);

public slots:
    void slotControlCurrentSongChanged(QString songName);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private slots:
    void on_pb_hide_clicked();

    void on_pb_max_clicked();

private:
    Ui::LyricOperation *ui;

    QString m_lyricPath;
    QStringList m_lyric;
    QMap<qint64, int> m_lrc;

    QPoint m_mouseClick;

    void initLyricOperation(void);
};

#endif // LYRICOPERATION_H
