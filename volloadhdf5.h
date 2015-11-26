/*
#ifndef VOLLOADHDF5_H
#define VOLLOADHDF5_H

#include "volloader.h"
#include <memory>

namespace yy
{

class VolLoadHDF5 : public VolLoader
{
public:
    static std::unique_ptr<VolLoadHDF5> create(const std::string& filename);
    VolLoadHDF5(const std::string& filename);
    virtual ~VolLoadHDF5() {}

    virtual std::shared_ptr<Volume> open();

private:
    std::string filename;
};

} // namespace yy

#endif // VOLLOADHDF5_H
*/
