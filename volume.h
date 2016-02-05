#ifndef VOLUME_H
#define VOLUME_H

#include <memory>
#include <iostream>

namespace yy {

class IVolume
{
public:
    // struct Stats holds statistics of the volumetric data in normalized format,
    // so mean 0.5 in scalarType unsigned char is 128.
    struct Stats
    {
        Stats() : sum(0.0), mean(0.0) {}
        friend std::ostream& operator<<(std::ostream& out, const Stats& stats);
        std::pair<double, double> range;
        double sum, mean;
    };
    enum ScalarType { ST_Unsigned_Char, ST_Char, ST_Float, ST_Double };

    virtual ~IVolume() {}
    virtual int w() const = 0;
    virtual int h() const = 0;
    virtual int d() const = 0;
    virtual float sx() const = 0;
    virtual float sy() const = 0;
    virtual float sz() const = 0;
    virtual ScalarType scalarType() const = 0;
    virtual unsigned int nScalarsPerVoxel() const = 0;
    virtual unsigned int nBytesPerScalar() const = 0;
    virtual unsigned int nBytesPerVoxel() const { return nBytesPerScalar() * nScalarsPerVoxel(); }
    virtual int nVoxels() const { return w() * h() * d(); }
    virtual int nScalars() const { return nVoxels() * nScalarsPerVoxel(); }
    virtual unsigned int nBytes() const { return nScalars() * nBytesPerScalar(); }
    virtual const Stats& getStats() const = 0;
    virtual const std::unique_ptr<unsigned char []>& getData() const = 0;
    virtual void normalized() = 0;
};

class Volume : public IVolume
{
public:
    Volume(std::unique_ptr<unsigned char[]>& data,
           ScalarType type, unsigned int nScalarsPerVoxel,
           int width, int height, int depth,
           float scaleX = 1.f, float scaleY = 1.f, float scaleZ = 1.f);
    Volume(Volume&& volume);
    Volume& operator=(Volume&& volume);
    virtual ~Volume();

    friend std::ostream& operator<<(std::ostream& os, const Volume& volume);
    virtual int w() const { return width; }
    virtual int h() const { return height; }
    virtual int d() const { return depth; }
    virtual float sx() const { return scaleX; }
    virtual float sy() const { return scaleY; }
    virtual float sz() const { return scaleZ; }
    virtual ScalarType scalarType() const { return dataType; }
    virtual unsigned int nBytesPerScalar() const;
    virtual unsigned int nScalarsPerVoxel() const { return nvScalars; }
    virtual const Stats& getStats() const { return stats; }
    virtual const std::unique_ptr<unsigned char []>& getData() const { return data; }
    virtual void normalized();

protected:

private:
    std::unique_ptr<unsigned char []> data;
    ScalarType dataType;
    unsigned int nvScalars;
    int width, height, depth;
    float scaleX, scaleY, scaleZ;
    Stats stats;

    void computeStats();

    Volume(const Volume&); // Not implemented!!
    Volume& operator=(const Volume&); // Not implemented!!
};

} // namespace yy

#endif // VOLUME_H
