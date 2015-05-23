#include "volloadrawdialog.h"
#include "ui_volloadrawdialog.h"
#include <sstream>
#include <unordered_map>
#include <cassert>
#include <QLocale>
#include <QDebug>

namespace yy {

VolLoadRAWDialog::VolLoadRAWDialog(QWidget *parent)
 : QDialog(parent)
 , ui(new Ui::VolLoadRAWDialog)
{
    ui->setupUi(this);
    // connect
    connect(ui->type, SIGNAL(currentTextChanged(QString)), this, SLOT(updateEstimate()));
    connect(ui->x, SIGNAL(valueChanged(int)), this, SLOT(updateEstimate()));
    connect(ui->x, SIGNAL(valueChanged(int)), ui->y, SLOT(setValue(int)));
    connect(ui->x, SIGNAL(valueChanged(int)), ui->z, SLOT(setValue(int)));

    connect(ui->y, SIGNAL(editingFinished()), this, SLOT(disconWHD()));
    connect(ui->z, SIGNAL(editingFinished()), this, SLOT(disconWHD()));

    connect(ui->y, SIGNAL(valueChanged(int)), this, SLOT(updateEstimate()));
//    connect(ui->y, SIGNAL(valueChanged(int)), this, SLOT(onHValueChanged(int)));
    connect(ui->z, SIGNAL(valueChanged(int)), this, SLOT(updateEstimate()));
//    connect(ui->z, SIGNAL(valueChanged(int)), this, SLOT(onDValueChanged(int)));
}

VolLoadRAWDialog::~VolLoadRAWDialog()
{
    delete ui;
}

void VolLoadRAWDialog::setFileSize(size_t bytes)
{
    ui->filesize->setText(QLocale().toString(qlonglong(bytes)));
}

int VolLoadRAWDialog::w() const
{
    return ui->x->value();
}

int VolLoadRAWDialog::h() const
{
    return ui->y->value();
}

int VolLoadRAWDialog::d() const
{
    return ui->z->value();
}

Volume::DataType VolLoadRAWDialog::type() const
{
    static std::unordered_map<std::string, Volume::DataType> type
            = { { "unsigned byte (char)", Volume::DT_Unsigned_Char },
                { "byte (char)", Volume::DT_Char },
                { "float", Volume::DT_Float },
                { "double", Volume::DT_Double } };
    std::string typeText = ui->type->currentItem()->text().toStdString();
    assert(type.count(typeText) > 0);
    return type[typeText];
}

void VolLoadRAWDialog::disconWHD()
{
    disconnect(ui->x, SIGNAL(valueChanged(int)), ui->y, SLOT(setValue(int)));
    disconnect(ui->x, SIGNAL(valueChanged(int)), ui->z, SLOT(setValue(int)));
}

//void VolLoadRAWDialog::onWValueChanged(int w)
//{

//}

//void VolLoadRAWDialog::onHValueChanged(int h)
//{
////    disconnect(ui->x, SIGNAL(valueChanged(int)), ui->y, SLOT(setValue(int)));
////    disconnect(ui->x, SIGNAL(valueChanged(int)), ui->z, SLOT(setValue(int)));
//}

//void VolLoadRAWDialog::onDValueChanged(int d)
//{
////    disconnect(ui->x, SIGNAL(valueChanged(int)), ui->y, SLOT(setValue(int)));
////    disconnect(ui->x, SIGNAL(valueChanged(int)), ui->z, SLOT(setValue(int)));
//}

size_t VolLoadRAWDialog::bytes() const
{
    QString typeText = ui->type->currentItem()->text();
    size_t x = ui->x->value();
    size_t y = ui->y->value();
    size_t z = ui->z->value();
    static std::unordered_map<std::string, size_t> type2size
            = { { "unsigned byte (char)", sizeof(unsigned char) },
                { "byte (char)", sizeof(char) },
                { "float", sizeof(float) },
                { "double", sizeof(double) } };
    size_t size = type2size[typeText.toStdString()];
    size_t volbytes = x * y * z * size;
    return volbytes;
}

void VolLoadRAWDialog::updateEstimate()
{
    ui->estimate->setText(QLocale().toString(qlonglong(bytes())));
}

} // namespace yy
