#include "volume.h"
#include <cassert>
#include <map>
#include <unordered_map>
#include <functional>
#include <limits>

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

template <typename T, bool isFloat>
static void tNormalize(unsigned char* data, int w, int h, int d)
{
    T* ptr = reinterpret_cast<T*>(data);
    // get statistics
    T maxVal = std::numeric_limits<T>::lowest();
    T minVal = std::numeric_limits<T>::max();
    for (int z = 0; z < d; ++z)
    for (int y = 0; y < h; ++y)
    for (int x = 0; x < w; ++x)
    {
        int index = w * h * z + w * y + x;
        T value = ptr[index];
        maxVal = std::max(value, maxVal);
        minVal = std::min(value, minVal);
    }
    // normalize
    for (int z = 0; z < d; ++z)
    for (int y = 0; y < h; ++y)
    for (int x = 0; x < w; ++x)
    {
        int index = w * h * z + w * y + x;
        T value = ptr[index];
        T newVal;
        if (isFloat)
            newVal = (value - minVal) / (maxVal - minVal);
        else {
            T lowest = std::numeric_limits<T>::lowest();
            T highest = std::numeric_limits<T>::max();
            newVal = double(value - minVal) / double(maxVal - minVal) * double(highest - lowest) + lowest;
        }
        ptr[index] = newVal;
    }
}

void Volume::normalized()
{
    static std::map<Volume::DataType, std::function<void(unsigned char*, int, int, int)> > dt2func
            = { { Volume::DT_Unsigned_Char, tNormalize<unsigned char, false> },
                { Volume::DT_Char, tNormalize<char, false> },
                { Volume::DT_Float, tNormalize<float, true> },
                { Volume::DT_Double, tNormalize<double, true> } };
    assert(dt2func.count(dataType) > 0);
    dt2func[dataType](data.get(), width, height, depth);
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
