#include "volume.h"
#include <cassert>
#include <map>
#include <unordered_map>

namespace yy
{

Volume::Volume(std::unique_ptr<unsigned char[]>& data, DataType type, int width, int height, int depth, float scaleX, float scaleY, float scaleZ)
 : data(nullptr)
 , dataType(type)
 , width(width), height(height), depth(depth)
 , scaleX(scaleX), scaleY(scaleY), scaleZ(scaleZ)
{
    this->data = std::move(data);
}

Volume::Volume(const Volume&)
{
    assert(false);
}

Volume::Volume(Volume &&volume)
 : data(nullptr)
 , width(0), height(0), depth(0)
{
    std::cout << "move constructor" << std::endl;
    this->data = std::move(volume.data);
    std::swap(this->width, volume.width);
    std::swap(this->height, volume.height);
    std::swap(this->depth, volume.depth);
}

Volume& Volume::operator=(Volume &&volume)
{
    std::cout << "move assignment" << std::endl;
    this->data = std::move(volume.data);
    std::swap(this->width, volume.width);
    std::swap(this->height, volume.height);
    std::swap(this->depth, volume.depth);
    return *this;
}

Volume::~Volume()
{
}

unsigned int Volume::nBytesPerVoxel() const
{
    static std::map<DataType, unsigned int> dt2bytes
            = { { DT_Unsigned_Char, sizeof(unsigned char) }
              , { DT_Char, sizeof(char) }
              , { DT_Float, sizeof(float) }
              , { DT_Double, sizeof(double) } };
    assert(dt2bytes.count(pixelType()) > 0);
    return dt2bytes[pixelType()];
}

unsigned int Volume::nBytes() const
{
    return width * height * depth * nBytesPerVoxel();
}

std::ostream& operator<<(std::ostream &os, const Volume &volume)
{
    static std::map<Volume::DataType, std::string> dt2str
            = {{Volume::DT_Double, "Double"},
               {Volume::DT_Float, "Float"},
               {Volume::DT_Unsigned_Char, "Unsigned char"},
               {Volume::DT_Char, "Char"}};
    assert(0 != dt2str.count(volume.dataType));
    os << "Volume (type: " << dt2str[volume.dataType].c_str()
       << ") (size: [" << volume.width << "," << volume.height << "," << volume.depth << "])";
    return os;
}

} // namespace yy
