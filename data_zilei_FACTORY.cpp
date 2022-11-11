#include "data_zilei_FACTORY.h"
#include "data_zilei.h"

data_zilei* data_zilei_FACTORY::get_data_zilei(std::string data, std::string zi)
{
    return new data_zilei(data, zi);
}
