#ifndef CLIPBOARDTHREAD_H
#define CLIPBOARDTHREAD_H

#include <QClipboard>
#include <QImage>
#include <QThread>

class ClipboardThread : public QThread
{
    Q_OBJECT

public:
    ClipboardThread(QClipboard *clipboard);

signals:
    void callClipboard();

private:
    QClipboard *clipboard;
    QString lastText;
    QImage lastImage;

    virtual void run();
};

#endif // CLIPBOARDTHREAD_H
