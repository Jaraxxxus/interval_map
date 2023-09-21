#pragma once
#include <map>

template <typename K, typename V>
class interval_map
{
private:
    std::map<K, V> m_map;
    V m_valBegin;
    K maxKeyEnd = std::numeric_limits<K>::min();

public:
    interval_map(V const& val) : m_valBegin(val) {
        m_map[std::numeric_limits<K>::min()] = val;
        m_map[std::numeric_limits<K>::max()] = val;
    }

    V const& operator[](K const& key) const {
        if (key >= maxKeyEnd) {
            return m_valBegin;
        }
        auto it = m_map.upper_bound(key);
        if (it != m_map.begin()) {
            return (--it)->second;
        }
        return m_valBegin;
    }

    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd)) {
            return; // ������ �� ������ ��� ������� ���������
        }

        if (keyEnd > maxKeyEnd) {
            maxKeyEnd = keyEnd;
        }


        // ���������, ���� �� ��������, ������� ���������� ����� ������� � ������ ����� ��������� � ������������� ����� keyEnd
        auto itBegin = m_map.lower_bound(keyBegin);
        auto itEnd = m_map.lower_bound(keyEnd);
        auto curInt = std::prev(itEnd);
        if (curInt->first >= keyBegin) {
            auto val = curInt->second;
            m_map.erase(curInt);
            m_map[keyEnd] = val;
        }

        // ���������, ���� �� ��������, ������� ���������� �� keyBegin � ������������� ����� keyEnd, ���� ��, ����� ��� �� 2 �����
        itEnd = m_map.upper_bound(keyEnd);
        itBegin = m_map.upper_bound(keyBegin);
        itBegin = std::prev(itBegin);
        if (itBegin == --itEnd && itBegin != m_map.end()) {
            m_map[keyEnd] = itBegin->second;
        }

        //��������� �������� itEnd, itBegin ����� ������� ���������� �������� ���������
        itEnd = m_map.lower_bound(keyEnd);
        itBegin = m_map.lower_bound(keyBegin);
        //������� ������ �������� � ���������
        m_map.erase(itBegin, itEnd);



        // ��������� ����� �������� � ��������
        m_map[keyBegin] = val;
    }
};

