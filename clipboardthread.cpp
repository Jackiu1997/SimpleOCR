#include "clipboardthread.h"
#include <QImage>

ClipboardThread::ClipboardThread(QClipboard *clipboard)
{
    this->clipboard = clipboard;
}

void ClipboardThread::run()
{
    while (true) {
        sleep(2); // 执行剪贴板监控的频率
        if (!clipboard->text().isEmpty() && clipboard->text() != lastText)
        {
            lastText = clipboard->text();
            emit callClipboard();
        }
        else if (!clipboard->image().isNull() && clipboard->image() != lastImage)
        {
            lastImage = clipboard->image();
            emit callClipboard();
        }
    }
}
