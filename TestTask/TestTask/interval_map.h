#pragma once
#include <map>

template <typename K, typename V>
class interval_map {
private:
    std::map<K, V> m_map;
    V m_valBegin;
    K maxKeyEnd = std::numeric_limits<K>::min();

    V const& get(K const& key) const {
        if (key >= maxKeyEnd) {
            return m_valBegin;
        }
        auto it = m_map.upper_bound(key);
        if (it != m_map.begin()) {
            return (--it)->second;
        }
        return m_valBegin;
    }

public:
    interval_map(V const& val) : m_valBegin(val) {
        m_map[std::numeric_limits<K>::min()] = val;
        m_map[std::numeric_limits<K>::max()] = val;
    }

    V const& operator[](K const& key) const {
        return get(key);
    }

    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd)) {
            return; // Do nothing for an empty interval
        }

        if (keyEnd > maxKeyEnd) {
            maxKeyEnd = keyEnd;
        }

        // Check if there is an interval that starts between the beginning and end of this interval and ends after keyEnd
        auto itEnd = m_map.lower_bound(keyEnd);
        auto itBegin = m_map.upper_bound(keyBegin);
        auto curInt = std::prev(itEnd);
        if (curInt->first >= keyBegin) {
            auto curVal = curInt->second;
            m_map.erase(curInt);
            if (curVal != val) {
                m_map[keyEnd] = curVal;
            }
        }
        else {
            // Check if there is an interval that starts before keyBegin and ends after keyEnd; if yes, split it into two parts
            itEnd = m_map.upper_bound(keyEnd);
            itBegin = m_map.upper_bound(keyBegin);
            itBegin = std::prev(itBegin);
            // If trying to insert into an interval with the same value, no changes are required
            if (itBegin != m_map.end()) {
                auto curVal = itBegin->second;
                if (curVal == val)
                    return;
            }
            if (itBegin == --itEnd && itBegin != m_map.end()) {
                m_map[keyEnd] = itBegin->second;
            }
        }

        // Update the values of itEnd and itBegin after each possible element removal
        itEnd = m_map.lower_bound(keyEnd);
        itBegin = m_map.lower_bound(keyBegin);
        // Remove old values within the interval
        m_map.erase(itBegin, itEnd);

        // Insert the new value into the interval
        m_map[keyBegin] = val;
    }

    size_t size() const {
        return m_map.size();
    }
};
