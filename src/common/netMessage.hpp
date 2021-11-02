/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-antonin.fille
** File description:
** netMessage
*/

#ifndef NETMESSAGE_HPP_
#define NETMESSAGE_HPP_

#include "netCommon.hpp"

namespace net
{
    template <typename T>
    struct Header {
        T id {};
        uint32_t size = 0;
    };

    template <typename T>
    struct Message {
        Header<T> header{};
        std::vector<uint8_t> body;

        size_t size() const
        {
            return sizeof(Header<T> + body.size());
        }

        friend std::ostream& operator << (std::ostream& os, const Message<T>& msg)
        {
            os << "ID: " << static_cast<int>(msg.header.id) << std::endl << msg.header.size;
            return os;
        }

        template <typename DataType>
        friend Message<T>& operator << (Message<T>& msg, const DataType& data)
        {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into the vector");
        }
    };
    
        
} // namespace net


#endif /* !NETMESSAGE_HPP_ */
