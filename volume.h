#ifndef VOLUME_H
#define VOLUME_H

#include <memory>
#include <iostream>

namespace yy {

class Volume
{
public:
    // struct Stats holds statistics of the volumetric data in normalized format,
    // so mean 0.5 in dataType unsigned char is 128.
    struct Stats
    {
        Stats() : sum(0.0), mean(0.0) {}
        friend std::ostream& operator<<(std::ostream& out, const Stats& stats);
        std::pair<double, double> range;
        double sum, mean;
    };

    enum DataType { DT_Unsigned_Char, DT_Char, DT_Float, DT_Double };
    Volume() {}
    Volume(std::unique_ptr<unsigned char[]>& data, DataType type,
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
    virtual DataType pixelType() const { return dataType; }
    virtual unsigned int nBytesPerVoxel() const;
    virtual unsigned int nBytes() const;
    virtual const Stats& getStats() const { return stats; }
    virtual const std::unique_ptr<unsigned char []>& getData() const { return data; }
    virtual void normalized();

protected:

private:
    std::unique_ptr<unsigned char []> data;
    DataType dataType;
    int width, height, depth;
    float scaleX, scaleY, scaleZ;
    Stats stats;

    void computeStats();

    Volume(const Volume&); // Not implemented!!
    Volume& operator=(const Volume&); // Not implemented!!
};

} // namespace yy

#endif // VOLUME_H
