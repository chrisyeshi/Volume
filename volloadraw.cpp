#include "volloadraw.h"
#include "volume.h"
#include "volloadrawdialog.h"
#include <fstream>

namespace yy {

std::unique_ptr<VolLoadRAW> VolLoadRAW::create(const std::string& filename)
{
    return std::unique_ptr<VolLoadRAW>(new VolLoadRAW(filename));
}

VolLoadRAW::VolLoadRAW(const std::string& filename)
 : filename(filename)
{

}

VolLoadRAW::~VolLoadRAW()
{

}

std::shared_ptr<Volume> VolLoadRAW::open()
{
    // check if can open file
    std::ifstream fin(filename.c_str(), std::ifstream::binary | std::ifstream::ate);
    if (!fin) return nullptr;
    // get file size
    int filesize = fin.tellg();
    fin.seekg(std::ios::beg);
    // modal dialog
    yy::VolLoadRAWDialog dialog;
    dialog.setFileSize(filesize);
    dialog.exec();
    if (dialog.result() == QDialog::Rejected)
        return nullptr;
    // get results
    std::unique_ptr<unsigned char[]> data(new unsigned char[dialog.bytes()]);
    fin.read(reinterpret_cast<char*>(data.get()), dialog.bytes());
    auto volume = std::make_shared<Volume>(data, dialog.type(), dialog.w(), dialog.h(), dialog.d(), 1, 1, 1);
    return volume;
}

} // namespace yy
