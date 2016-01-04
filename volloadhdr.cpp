#include "volloadhdr.h"
#include "volloadraw.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QFileInfo>
#include <QDir>

namespace yy
{

std::unique_ptr<VolLoadHDR> VolLoadHDR::create(const std::string &filename)
{
    return std::unique_ptr<VolLoadHDR>(new VolLoadHDR(filename));
}

VolLoadHDR::VolLoadHDR(const std::string& filename)
  : filename(filename)
  , dimensions(0)
{

}

std::shared_ptr<Volume> VolLoadHDR::open()
{
    dimensions = readDimensions();
    std::string datapath = getDataFilePath();
    VolLoadRAW rawLoader(getDataFilePath());
    return rawLoader.open(IVolume::DT_Unsigned_Char, dimensions[0], dimensions[1], dimensions[2]);
}

std::vector<int> VolLoadHDR::readDimensions() const
{
    std::vector<int> ret(3);
    std::ifstream fin(filename);
    fin >> ret[0] >> ret[1] >> ret[2];
    return ret;
}

std::string VolLoadHDR::getDataFilePath() const
{
    QFileInfo info(QString::fromStdString(filename));
    std::string base = info.baseName().toStdString();
    std::string dir = info.dir().absolutePath().toStdString();
    return dir + "/" + base + ".img";
}

} // namespace yy
