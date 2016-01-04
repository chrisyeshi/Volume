#include "volloadfactory.h"
#include <map>
#include <string>
#include "volloadpvm.h"
#ifdef ENABLE_HDF5
    #include "volloadhdf5.h"
#endif // ENABLE_HDF5
#include "volloadraw.h"
#include "volloadhdr.h"

namespace yy
{

std::map<std::string, VolLoadFactory::CreateFunc> VolLoadFactory::creators
 = { { "pvm",  VolLoadPVM::create },
#ifdef ENABLE_HDF5
     {  "h5", VolLoadHDF5::create },
#endif // ENABLE_HDF5
     { "raw",  VolLoadRAW::create },
     { "dat",  VolLoadRAW::create },
     { "data", VolLoadRAW::create },
     { "hdr",  VolLoadHDR::create } };

std::set<std::string> VolLoadFactory::extensions()
{
    std::set<std::string> ret;
    for (auto entry : creators)
        ret.insert(entry.first);
    return ret;
}

std::unique_ptr<VolLoader> VolLoadFactory::create(const std::string& filename)
{
    QFileInfo info(QString::fromStdString(filename));
    std::string ext = info.completeSuffix().toStdString();
    if (creators.count(ext) == 0)
        return nullptr;
    return creators[ext](filename);
}

} // namespace yy
