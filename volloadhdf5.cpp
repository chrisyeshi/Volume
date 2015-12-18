#include "volloadhdf5.h"
#include <QSharedPointer>
#include <QDialog>
#include <vector>
#include <H5Cpp.h>
#include "ui_volloadhdf5dialog.h"

namespace yy
{

static std::vector<std::string> names;

std::unique_ptr<VolLoadHDF5> VolLoadHDF5::create(const std::string &filename)
{
    return std::unique_ptr<VolLoadHDF5>(new VolLoadHDF5(filename));
}

VolLoadHDF5::VolLoadHDF5(const std::string &filename)
 : filename(filename)
{

}

std::shared_ptr<Volume> VolLoadHDF5::open()
{
    std::shared_ptr<H5::H5File> file = std::make_shared<H5::H5File>(filename.c_str(), H5F_ACC_RDONLY);
    // a really stupid way to get dataset names of an HDF5 file
    names.clear();
    herr_t idx = H5Literate(file->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL,
        [](hid_t loc_id, const char* name, const H5L_info_t* linfo, void* opdata)->herr_t{
            names.push_back(name);
            return 0;
        }, NULL);
    // a dialog for user to select dataset by name
    QDialog dialog;
    Ui::VolLoadHDF5Dialog ui;
    ui.setupUi(&dialog);
    // add dataset names to the list widget
    for (auto name : names)
        ui.datasets->addItem(QString::fromStdString(name));
    // modal dialog
    dialog.exec();
    if (dialog.result() == QDialog::Rejected)
        return nullptr;
    // get result from the dialog
    std::string name = ui.datasets->currentItem()->text().toStdString();
    // open selected dataset
    H5::DataSet dset = file->openDataSet(("/" + name).c_str());
    hsize_t dims[3] = {0, 0, 0};
    dset.getSpace().getSimpleExtentDims(dims);
    std::unique_ptr<unsigned char[]> data(new unsigned char[dims[0] * dims[1] * dims[2] * H5::PredType(H5::PredType::NATIVE_FLOAT).getSize()]);
    dset.read(data.get(), H5::PredType(H5::PredType::NATIVE_FLOAT));
    auto volume = std::make_shared<Volume>(data, Volume::DT_Float, dims[0], dims[1], dims[2], 1, 1, 1);
    return volume;
}

} // namespace yy
