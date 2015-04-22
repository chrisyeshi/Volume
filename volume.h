#ifndef VOLUME_H
#define VOLUME_H

#include <memory>
#include <iostream>

namespace yy
{

class Volume
{
public:
    enum DataType { DT_Unsigned_Char, DT_Char, DT_Float, DT_Double };
    Volume(std::unique_ptr<unsigned char[]>& data, DataType type,
           int width, int height, int depth,
           float scaleX = 1.f, float scaleY = 1.f, float scaleZ = 1.f);
    Volume(Volume&& volume);
    Volume& operator=(Volume&& volume);
    ~Volume();

    friend std::ostream& operator<<(std::ostream& os, const Volume& volume);
    int w() const { return width; }
    int h() const { return height; }
    int d() const { return depth; }
    float sx() const { return scaleX; }
    float sy() const { return scaleY; }
    float sz() const { return scaleZ; }
    DataType pixelType() const { return dataType; }
    unsigned int nBytesPerVoxel() const;
    unsigned int nBytes() const;
    const std::unique_ptr<unsigned char []>& getData() const { return data; }

protected:

private:
    std::unique_ptr<unsigned char []> data;
    DataType dataType;
    int width, height, depth;
    float scaleX, scaleY, scaleZ;

    Volume(const Volume&); // Not implemented!!
    Volume& operator=(const Volume&); // Not implemented!!
};

} // namespace yy

#endif // VOLUME_H
