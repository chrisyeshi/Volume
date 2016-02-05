#include "volloadpvm.h"
#include "volloadfactory.h"
#include <map>
#include "ddsbase.h"
#include "volume.h"

namespace yy
{

std::unique_ptr<VolLoadPVM> VolLoadPVM::create(const std::string &filename)
{
    return std::unique_ptr<VolLoadPVM>(new VolLoadPVM(filename));
}

VolLoadPVM::VolLoadPVM(const std::string& filename)
 : filename(filename)
{

}

VolLoadPVM::~VolLoadPVM()
{

}

std::shared_ptr<Volume> VolLoadPVM::open()
{
    unsigned int width, height, depth, components;
    float scalex, scaley, scalez;
    std::unique_ptr<unsigned char[]> data(readPVMvolume(filename.c_str(),
                         &width, &height, &depth,
                         &components,
                         &scalex, &scaley, &scalez));
    if (!data)
        return nullptr;
    static std::map<unsigned int, Volume::ScalarType> components2datatype
            = {{4, Volume::ST_Float},
               {8, Volume::ST_Double},
               {1, Volume::ST_Unsigned_Char}};
    if (0 == components2datatype.count(components))
        return nullptr;
    auto volume = std::make_shared<Volume>(data,
           components2datatype[components], 1,
           width, height, depth,
           scalex, scaley, scalez);
    return volume;
}

} // namespace yy
