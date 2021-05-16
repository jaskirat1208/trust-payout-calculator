#include <vector>

namespace core
{

template<class PayoutTableRow>
class PayoutTable
{
private:
    std::vector<PayoutTableRow> m_data;
public:
    PayoutTable(PayoutTableRow);

    inline void insert(PayoutTableRow row) {
        m_data.push_back(row);
    }
};

} // namespace core
