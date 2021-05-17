#include <vector>
#include <iomanip>
#include <cmath>

namespace core
{

template<class PayoutTableRow>
class PayoutTable
{
private:
    std::vector<PayoutTableRow> m_data;
public:
    PayoutTable() {}

    inline void insert(PayoutTableRow row) {
        m_data.push_back(row);
    }

    std::vector<PayoutTableRow> data() {
        return m_data;
    }

    friend std::ostream& operator<<(std::ostream& os, PayoutTable<PayoutTableRow> table) {
        // Print headers
        int max_width = 0;
        for(std::string row: PayoutTableRow::getColumns()) {
            if(max_width < row.size())
                max_width = row.size();
        }

        for(std::string row: PayoutTableRow::getColumns()) {
            os << std::setw(max_width+2) << row << " ";
        }
        os << std::endl;

        for(PayoutTableRow row: table.data()) {
            os << row.getValues(max_width+2) << std::endl;
        }
        return os;
    }
};

} // namespace core
