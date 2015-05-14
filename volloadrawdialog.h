#ifndef VOLLOADRAWDIALOG_H
#define VOLLOADRAWDIALOG_H

#include <QDialog>
#include "volume.h"

namespace Ui {
class VolLoadRAWDialog;
}

namespace yy {

class VolLoadRAWDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VolLoadRAWDialog(QWidget *parent = 0);
    ~VolLoadRAWDialog();

    void setFileSize(int bytes);
    int bytes() const;
    int w() const;
    int h() const;
    int d() const;
    Volume::DataType type() const;

private slots:
//    void onWValueChanged(int w);
//    void onHValueChanged(int h);
//    void onDValueChanged(int d);
    void disconWHD();
    void updateEstimate();

private:
    Ui::VolLoadRAWDialog *ui;
};

} // namespace yy

#endif // VOLLOADRAWDIALOG_H
