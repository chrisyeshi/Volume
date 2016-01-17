#ifndef VOLUMEFILTER_H
#define VOLUMEFILTER_H

#include "volume.h"

namespace yy {

class IVolumeFilter : public virtual IVolume
{
public:
    enum Filter { Filter_Linear, Filter_Nearest };

public:
    virtual void setFilter(Filter filter) = 0;
	virtual Filter getFilter() const = 0;
};

class VolumeFilter : public IVolumeFilter
{
public:
	VolumeFilter(const std::shared_ptr<IVolume>& volume) : volume(volume), filter(Filter_Linear) {}

    virtual int w() const { return volume->w(); }
    virtual int h() const { return volume->h(); }
    virtual int d() const { return volume->d(); }
    virtual float sx() const { return volume->sx(); }
    virtual float sy() const { return volume->sy(); }
    virtual float sz() const { return volume->sz(); }
    virtual DataType pixelType() const { return volume->pixelType(); }
    virtual unsigned int nBytesPerVoxel() const { return volume->nBytesPerVoxel(); }
    virtual unsigned int nBytes() const { return volume->nBytes(); }
    virtual const Stats& getStats() const { return volume->getStats(); }
    virtual const std::unique_ptr<unsigned char []>& getData() const { return volume->getData(); }
    virtual void normalized() { volume->normalized(); }
	virtual void setFilter(Filter filter) { this->filter = filter; }
	virtual Filter getFilter() const { return filter; }

private:
	std::shared_ptr<IVolume> volume;
	Filter filter;
};

} // namespace yy

#endif // VOLUMEFILTER_H
