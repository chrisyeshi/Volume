#ifndef VOLUMECUDA_H
#define VOLUMECUDA_H

#include "volumegl.h"

struct cudaGraphicsResource;

namespace yy {

class IVolumeCUDA : public virtual IVolumeFilter
{
public:
	virtual cudaGraphicsResource* getCUDAResource() const = 0;
};

// TODO: implement VolumeCUDA

} // namespace yy

#endif // VOLUMECUDA_H
