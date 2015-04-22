#ifndef VOLLOADPVM_H
#define VOLLOADPVM_H

#include "volloader.h"
#include "volloadfactory.h"
#include <memory>

namespace yy
{

class VolLoadPVM : public VolLoader
{
public:
    static std::unique_ptr<VolLoadPVM> create(const std::string& filename);
    VolLoadPVM(const std::string& filename);
    virtual ~VolLoadPVM();

    virtual std::shared_ptr<Volume> open();

private:
    std::string filename;
};

} // namespace yy

#endif // VOLLOADPVM
